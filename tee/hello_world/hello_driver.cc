/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <chrono>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_split.h"
#include "asylo/client.h"
#include "asylo/enclave.pb.h"
#include "asylo/platform/primitives/sgx/loader.pb.h"
#include "asylo/util/logging.h"
#include "hello_world/hello.pb.h"

ABSL_FLAG(std::string, enclave_path, "", "Path to enclave to load");
// ABSL_FLAG(std::string, words, "",
//           "A comma-separated list of words to pass to the enclave");

int main(int argc, char *argv[])
{
  // Part 0: Setup
  absl::ParseCommandLine(argc, argv);

  // Set clock
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  // Part 1: Initialization
  asylo::EnclaveManager::Configure(asylo::EnclaveManagerOptions());
  auto manager_result = asylo::EnclaveManager::Instance();
  if (!manager_result.ok())
  {
    LOG(QFATAL) << "EnclaveManager unavailable: " << manager_result.status();
  }
  asylo::EnclaveManager *manager = manager_result.value();
  std::cout << "Loading " << absl::GetFlag(FLAGS_enclave_path) << std::endl;

  // Create an EnclaveLoadConfig object.
  asylo::EnclaveLoadConfig load_config;
  load_config.set_name("hello_enclave");

  // Create an SgxLoadConfig object.
  asylo::SgxLoadConfig sgx_config;
  asylo::SgxLoadConfig::FileEnclaveConfig file_enclave_config;
  file_enclave_config.set_enclave_path(absl::GetFlag(FLAGS_enclave_path));
  *sgx_config.mutable_file_enclave_config() = file_enclave_config;
  sgx_config.set_debug(true);

  // Set an SGX message extension to load_config.
  *load_config.MutableExtension(asylo::sgx_load_config) = sgx_config;
  asylo::Status status = manager->LoadEnclave(load_config);
  if (!status.ok())
  {
    LOG(QFATAL) << "Load " << absl::GetFlag(FLAGS_enclave_path)
                << " failed: " << status;
  }

  // Part 2: Secure execution

  asylo::EnclaveClient *client = manager->GetClient("hello_enclave");

  // input approach
  asylo::EnclaveInput rawInput;
  asylo::EnclaveInput processedOutput;
  asylo::EnclaveOutput output;
  int inputCounter = 0;
  int outputCounter = 0;

  auto t1 = high_resolution_clock::now();
  // iteration over input batches
  while (1)
  {
    // break if x batches are created
    if (inputCounter >= 13)
    {
      break;
    }
    // check if file exists
    if (access(("/wg/output/" + std::to_string(inputCounter) + ".bin").c_str(), F_OK) != -1)
    {
      std::cout << "File could be accessed" << std::endl;

      // reading binary from file
      std::fstream input("/wg/output/" + std::to_string(inputCounter) + ".bin", std::ios::in | std::ios::binary);
      if (!input)
      {
        std::cout << "File not found." << std::endl;
      }
      else if (!rawInput.MutableExtension(hello_world::parsed_input)->ParseFromIstream(&input))
      {
        std::cerr << "Failed to parse." << std::endl;
        return -1;
      }
      // send message
      status = client->EnterAndRun(rawInput, &output);
      if (!status.ok())
      {
        LOG(QFATAL) << "EnterAndRun failed: " << status;
      }

      // forward preprocessed output
      for (int z = 0; z < output.GetExtension(hello_world::enclave_output_hello).mid_size(); z++)
      {
        // set temp protobuf for serialization
        rawInput.MutableExtension(hello_world::data_out)->set_signature(output.GetExtension(hello_world::enclave_output_hello).signature(z));
        rawInput.MutableExtension(hello_world::data_out)->set_mid(output.GetExtension(hello_world::enclave_output_hello).mid(z));
        rawInput.MutableExtension(hello_world::data_out)->set_pavg(output.GetExtension(hello_world::enclave_output_hello).pavg(z));
        rawInput.MutableExtension(hello_world::data_out)->set_iend(output.GetExtension(hello_world::enclave_output_hello).iend(z));

        std::cout << "Power is: " << output.GetExtension(hello_world::enclave_output_hello).pavg(z) << std::endl;

        // write processed output to disk
        std::fstream outputStream("/tee/output/" + std::to_string(outputCounter) + ".bin", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!rawInput.MutableExtension(hello_world::data_out)->SerializeToOstream(&outputStream))
        {
          std::cerr << "Failed to write processed data to disk." << std::endl;
          return -1;
        }
        outputCounter++;
      }
      inputCounter++;
    }
  }
  auto t2 = high_resolution_clock::now();

  duration<double, std::milli> ms_double = t2 - t1;

  LOG(INFO) << "Execution Time: " << ms_double.count();

  // Part 3: Finalization

  asylo::EnclaveFinal final_input;
  status = manager->DestroyEnclave(client, final_input);
  if (!status.ok())
  {
    LOG(QFATAL) << "Destroy " << absl::GetFlag(FLAGS_enclave_path)
                << " failed: " << status;
  }

  return 0;
}
