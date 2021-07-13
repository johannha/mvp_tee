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
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_split.h"
#include "asylo/client.h"
#include "asylo/enclave.pb.h"
#include "asylo/platform/primitives/sgx/loader.pb.h"
#include "asylo/util/logging.h"
#include "hello_world/hello.pb.h"

ABSL_FLAG(std::string, enclave_path, "", "Path to enclave to load");
ABSL_FLAG(std::string, words, "",
          "A comma-separated list of words to pass to the enclave");

int main(int argc, char *argv[])
{
  // Part 0: Setup
  absl::ParseCommandLine(argc, argv);

  if (absl::GetFlag(FLAGS_words).empty())
  {
    LOG(QFATAL) << "Must supply a non-empty list of words with --words";
  }

  std::vector<std::string> words =
      absl::StrSplit(absl::GetFlag(FLAGS_words), ',');

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

  for (const auto &word : words)
  {
    asylo::EnclaveInput input;
    input.MutableExtension(hello_world::enclave_input_hello)
        ->set_to_count(word);

    asylo::EnclaveOutput output;
    status = client->EnterAndRun(input, &output);
    if (!status.ok())
    {
      LOG(QFATAL) << "EnterAndRun failed: " << status;
    }

    if (!output.HasExtension(hello_world::enclave_output_hello))
    {
      LOG(QFATAL) << "Enclave did not assign an ID for " << word;
    }

    std::cout << "Message from enclave: "
              << output.GetExtension(hello_world::enclave_output_hello)
                     .counted_message()
              << std::endl;
  }

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
