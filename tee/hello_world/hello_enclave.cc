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

#include "sgx_tcrypto.h"
#include "sgx_error.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "asylo/trusted_application.h"
#include "asylo/util/logging.h"
#include "asylo/util/status.h"
#include "hello_world/hello.pb.h"
#include "sgx_defs.h"

std::string publicKey = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820";
uint8_t xValues[32] = {114, 32, 179, 254, 145, 16, 56, 76, 227, 113, 137, 58, 52, 202, 7, 93, 163, 35, 159, 181, 74, 40, 99, 240, 177, 103, 136, 155, 196, 255, 154, 123};
uint8_t yValues[32] = {83, 177, 164, 118, 139, 210, 136, 96, 9, 53, 209, 1, 54, 56, 252, 71, 210, 3, 203, 160, 172, 115, 0, 92, 51, 146, 156, 169, 37, 114, 140, 2};

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

    //publicSet.gy = stoi(publicKey.substr(64, 64));

    // receiving Buffer

    std::string hash = input.GetExtension(hello_world::parsed_input).hash();
    std::string signature = input.GetExtension(hello_world::parsed_input).signature();

    LOG(INFO) << "Signature: " << signature.length() << "\n";

    // TODO: implement signature verification
    // declare public key in coordinte form
    sgx_ec256_public_t publicSet;
    memcpy(publicSet.gx, xValues, sizeof(xValues));
    memcpy(publicSet.gy, yValues, sizeof(yValues));

    // convert signature from data batch
    sgx_ec256_signature_t signatureCoordinates;

    // prepare data for hashing
    std::string hashPrep = "";

    for (int y = 0; y < input.GetExtension(hello_world::parsed_input).data_size(); y++)
    {
      hashPrep = hashPrep + input.GetExtension(hello_world::parsed_input).data(y).mid() + input.GetExtension(hello_world::parsed_input).data(y).idur() + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).iend()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).pavg()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).ein()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).eout());
    }
    LOG(INFO) << "Hash prep is " << hashPrep;
    uint32_t hashSize = sizeof(hashPrep);

    // verifiy signature

    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    sgx_ecc_state_handle_t p_ecc_handle = NULL;

    if ((ret = sgx_ecc256_open_context(&p_ecc_handle)) != SGX_SUCCESS)
    {
      LOG(INFO) << ("\nTrustedApp: sgx_ecc256_open_context() failed !\n");
    }

    // ret = sgx_ecdsa_verify(&hashPrep, hashSize, &publicSet,
    //                        const sgx_ec256_signature_t *p_signature,
    //                        uint8_t *p_result,
    //                        sgx_ecc_state_handle_t ecc_handle);

    sgx_ecc256_close_context(p_ecc_handle);

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
