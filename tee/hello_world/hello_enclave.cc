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

#include <cstdint>
#include <string>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "asylo/trusted_application.h"
#include "asylo/util/logging.h"
#include "asylo/util/status.h"
#include "hello_world/hello.pb.h"
#include "sgx_defs.h"
#include "sgx_tcrypto.h"
#include "sgx_error.h"

std::string publicKey = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820";

// batch signature verification
bool verifySignature(std::string *hash, std::string *signature)
{
  return true;
}

class HelloApplication : public asylo::TrustedApplication
{
public:
  HelloApplication() : visitor_count_(0) {}

  asylo::Status Run(const asylo::EnclaveInput &input,
                    asylo::EnclaveOutput *output) override
  {
    if (!input.HasExtension(hello_world::parsed_input))
    {
      return absl::InvalidArgumentError(
          "Expected a HelloInput extension on input.");
    }
    LOG(INFO) << publicKey.length();
    LOG(INFO) << "First String: " << publicKey.substr(0, 64);
    LOG(INFO) << "Second String: " << publicKey.substr(64, 64);

    sgx_ec256_public_t publicSet;
    xSubstring = substr(0, 64);
    ySubstring = substr(64, 64);

    uint8_t xArray[32];
    uint8_t yArray[32];

    //publicSet.gy = stoi(publicKey.substr(64, 64));

    // receiving Buffer

    std::string hash = input.GetExtension(hello_world::parsed_input).hash();
    std::string signature = input.GetExtension(hello_world::parsed_input).signature();

    // TODO: implement signature verification

    // Prepare data for hashing
    std::string hashPrep = "";

    for (int y = 0; y < input.GetExtension(hello_world::parsed_input).data_size(); y++)
    {
      hashPrep = hashPrep + input.GetExtension(hello_world::parsed_input).data(y).mid() + input.GetExtension(hello_world::parsed_input).data(y).idur() + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).iend()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).pavg()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).ein()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).eout());
    }
    LOG(INFO) << "Hash prep is " << hashPrep;

    // sgx_status_t status = SGX_SUCCESS;
    // sgx_ecc_state_handle_t handle = 0;
    // sgx_ec256_signature_t ec_signature;
    //status = SGXAPI sgx_ecc256_open_context(&handle);
    //SGXAPI sgx_ecdsa_verify();

    // if (SGX_SUCCESS != status){
    //      return status;
    // }

    // eccStatus = sgx_ecc256_open_context(&eccContext);

    if (verifySignature(&hash, &signature) == 1)
    {
      int dataSize = input.GetExtension(hello_world::parsed_input).data_size();
      if (output)
      {
        visitor_count_++;
        // threshold detection
        for (int i = 0; i < dataSize; i++)
        {
          double power = input.GetExtension(hello_world::parsed_input).data(i).pavg();
          if (power > 100)
          {
            // TODO: remote attestation
            //LOG(INFO) << "Power is " << std::to_string(power);
            // sets output message
            output->MutableExtension(hello_world::enclave_output_hello)->add_mid(input.GetExtension(hello_world::parsed_input).data(i).mid());
            output->MutableExtension(hello_world::enclave_output_hello)->add_pavg(power);
            output->MutableExtension(hello_world::enclave_output_hello)->add_iend(input.GetExtension(hello_world::parsed_input).data(i).iend());
          }
        }
      }
    }

    return absl::OkStatus();
  }

private:
  uint64_t visitor_count_;
};

namespace asylo
{

  TrustedApplication *BuildTrustedApplication() { return new HelloApplication; }

} // namespace asylo
