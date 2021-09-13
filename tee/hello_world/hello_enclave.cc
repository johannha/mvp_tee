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

#include <openssl/bytestring.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include "openssl/sha.h"
#include "openssl/ecdsa.h"
#include "openssl/bn.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "asylo/trusted_application.h"
#include "asylo/util/logging.h"
#include "asylo/util/status.h"
#include "hello_world/hello.pb.h"
#include "sgx_defs.h"

std::string pemString = "-----BEGIN PUBLIC KEY-----MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEJwI77xkBg8Q+F5ijQ6xw1Toy+VukgjYPG3aIuUz/qbc1G0pnuC2IBpBTHRBjg890LTC8Cso3AMUzKcmaUifIIA==-----END PUBLIC KEY-----";

uint8_t *hex_str_to_uint8(const char *string);
std::string hexStringSwap(std::string little);

// uint8_t *xBuffer = std::malloc(32 * sizeof(uint8_t));
// uint8_t *yBuffer = std::malloc(32 * sizeof(uint8_t));

// std::memcpy(xBuffer, xValues, 32);

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

    /* -------------- Parsing and deserializing hash and signature -------------- */

    std::string signingKeyDer = "30770201010420665345f0a9f342eaac09c209161d25de60233b77834b4db3ece0406758d00a54a00a06082a8648ce3d030107a1440342000427023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820";
    std::string xString = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7";
    std::string yString = "351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820";
    const uint8_t xValues[] = {114, 32, 179, 254, 145, 16, 56, 76, 227, 113, 137, 58, 52, 202, 7, 93, 163, 35, 159, 181, 74, 40, 99, 240, 177, 103, 136, 155, 196, 255, 154, 123};
    const uint8_t yValues[] = {83, 177, 164, 118, 139, 210, 136, 96, 9, 53, 209, 1, 54, 56, 252, 71, 210, 3, 203, 160, 172, 115, 0, 92, 51, 146, 156, 169, 37, 114, 140, 2};

    const uint8_t *xPointer = xValues;
    const uint8_t *yPointer = yValues;

    std::string hash = input.GetExtension(hello_world::parsed_input).hash();
    std::string signature = input.GetExtension(hello_world::parsed_input).signature();

    LOG(INFO) << "Signature in DER: " << signature;
    //signature = hexStringSwap(signature);
    LOG(INFO) << "Length of signature: " << signature.length();
    // LOG(INFO) << "Output Signature: " << signature;

    char *hash_arr = &hash[0];
    char *signingPointer = &signingKeyDer[0];

    uint8_t *intSignature = hex_str_to_uint8(&signature[0]);
    uint8_t *intHash = hex_str_to_uint8(hash_arr);
    uint8_t *intSigner = hex_str_to_uint8(signingPointer);
    uint8_t *xStringtoInt = hex_str_to_uint8(&xString[0]);
    uint8_t *yStringtoInt = hex_str_to_uint8(&yString[0]);

    LOG(INFO) << "Signature: " << signature << "\n";

    // TODO: implement signature verification

    /* ------------------------ Prepare Data for hashing ------------------------ */
    std::string hashPrep;

    for (int y = 0; y < input.GetExtension(hello_world::parsed_input).data_size(); y++)
    {
      //hashPrep = hashPrep + input.GetExtension(hello_world::parsed_input).data(y).mid() + input.GetExtension(hello_world::parsed_input).data(y).idur() + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).iend()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).pavg()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).ein()) + std::to_string(input.GetExtension(hello_world::parsed_input).data(y).eout());
      hashPrep.append(std::to_string(input.GetExtension(hello_world::parsed_input).data(y).iend()));
    }
    LOG(INFO) << "Hash prep is " << hashPrep;
    char const *hashByte = hashPrep.c_str();
    size_t hashSize = sizeof(hashByte);

    // hash batch content
    SHA256_CTX contextDigit;
    uint8_t finalHash[32];
    int resultPrep = SHA256_Init(&contextDigit);
    SHA256_Update(&contextDigit, hashByte, strlen(hashByte));
    int hashVal = SHA256_Final(finalHash, &contextDigit);

    // compare signature
    int n = memcmp(intHash, &finalHash[0], 32);
    LOG(INFO) << "Hash comparison: " << n;
    LOG(INFO) << "Final hash of enclave: " << finalHash;

    // verifiy signature

    EC_KEY *publicKey = EC_KEY_new();
    EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
    int set_group_status = EC_KEY_set_group(publicKey, ecgroup);

    LOG(INFO) << "Group Status: " << set_group_status;

    BIGNUM *xBig = BN_new();
    BIGNUM *yBig = BN_new();

    BIGNUM *xBigResult = BN_bin2bn(xStringtoInt, 32, xBig);
    BIGNUM *yBigResult = BN_bin2bn(yStringtoInt, 32, yBig);

    int createKey = EC_KEY_set_public_key_affine_coordinates(publicKey, xBig, yBig);

    LOG(INFO) << "Key generation: " << createKey;

    // ECDSA_verify(int type, const uint8_t *digest,
    //                            size_t digest_len, const uint8_t *sig,
    //                            size_t sig_len, const EC_KEY *key);

    ECDSA_SIG *signatureDer = ECDSA_SIG_from_bytes(intSignature, (signature.length() / 2));
    if (signatureDer == NULL)
    {
      LOG(INFO) << "Error while signature des";
    }
    //int validation = ECDSA_verify(0, &finalHash[0], 32, intSignature, 64, publicKey);
    int validation = ECDSA_do_verify(&finalHash[0], 32, signatureDer, publicKey);

    LOG(INFO) << "ECDSA result: " << validation;

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

uint8_t *hex_str_to_uint8(const char *string)
{

  if (string == NULL)
    return NULL;

  size_t slength = strlen(string);
  if ((slength % 2) != 0) // must be even
    return NULL;

  size_t dlength = slength / 2;

  uint8_t *data = (uint8_t *)malloc(dlength);

  memset(data, 0, dlength);

  size_t index = 0;
  while (index < slength)
  {
    char c = string[index];
    int value = 0;
    if (c >= '0' && c <= '9')
      value = (c - '0');
    else if (c >= 'A' && c <= 'F')
      value = (10 + (c - 'A'));
    else if (c >= 'a' && c <= 'f')
      value = (10 + (c - 'a'));
    else
      return NULL;

    data[(index / 2)] += value << (((index + 1) % 2) * 4);

    index++;
  }

  return data;
}
std::string hexStringSwap(std::string little)
{
  std::string input = little;

  LOG(INFO) << "Input Signature: " << input;

  std::reverse(input.begin(), input.end());
  for (auto it = input.begin(); it != input.end(); it += 2)
  {
    std::swap(it[0], it[1]);
  }

  return input;
}
