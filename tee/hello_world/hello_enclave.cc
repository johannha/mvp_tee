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
#include <sstream>
#include <iomanip>

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
#include "sgx_tcrypto.h"

/* ----------------------------- Helper methods ----------------------------- */
uint8_t *hex_str_to_uint8(const char *string);
std::string hexStringSwap(std::string little);
int verifySignature(uint8_t *x, uint8_t *y, std::string signature, uint8_t *signaturePointer, uint8_t *finalHash);
std::string enryptId(std::string input);
std::string signBatch(std::string toSign, uint8_t *privateKey);

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

    /* -------------- Parsing and deserializing hash and signature -------------- */

    std::string privateDer = "665345f0a9f342eaac09c209161d25de60233b77834b4db3ece0406758d00a54";
    std::string xString = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7";
    std::string yString = "351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820";

    std::string hash = input.GetExtension(hello_world::parsed_input).hash();
    std::string signature = input.GetExtension(hello_world::parsed_input).signature();

    char *hash_arr = &hash[0];

    uint8_t *intSignature = hex_str_to_uint8(&signature[0]);
    uint8_t *intHash = hex_str_to_uint8(hash_arr);
    uint8_t *xStringtoInt = hex_str_to_uint8(&xString[0]);
    uint8_t *yStringtoInt = hex_str_to_uint8(&yString[0]);
    uint8_t *privateDerInt = hex_str_to_uint8(&privateDer[0]);

    /* ------------------------ Prepare Data for hashing ------------------------ */
    std::string hashPrep;

    for (int y = 0; y < input.GetExtension(hello_world::parsed_input).data_size(); y++)
    {
      hashPrep.append(std::to_string(input.GetExtension(hello_world::parsed_input).data(y).iend()));
    }
    //LOG(INFO) << "Hash prep is " << hashPrep;
    char const *hashByte = hashPrep.c_str();
    size_t hashSize = sizeof(hashByte);

    // hash batch content
    SHA256_CTX contextDigit;
    uint8_t finalHash[32];
    int resultPrep = SHA256_Init(&contextDigit);
    SHA256_Update(&contextDigit, hashByte, strlen(hashByte));
    int hashVal = SHA256_Final(finalHash, &contextDigit);

    // compare signature (for testing only)
    // int n = memcmp(intHash, &finalHash[0], 32);
    // LOG(INFO) << "Hash comparison: " << n;
    // LOG(INFO) << "Final hash of enclave: " << finalHash;

    // verifiy signature
    if (verifySignature(xStringtoInt, yStringtoInt, signature, intSignature, &finalHash[0]) == 1)
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
            std::string hashedId = enryptId(input.GetExtension(hello_world::parsed_input).data(i).mid());
            // remote attestation faker: depens on power only
            std::string attestResult = signBatch(std::to_string(power), privateDerInt);
            LOG(INFO) << "Resulting signature is: " << attestResult;

            output->MutableExtension(hello_world::enclave_output_hello)->add_signature(attestResult);
            output->MutableExtension(hello_world::enclave_output_hello)->add_mid(hashedId);
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

/* ----------------------- Convert hex string to uint8 ---------------------- */
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
/* ------------------------ Swap endian of hex string ----------------------- */
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

/* ----------------- Check signature of raw IoT data batches ---------------- */
int verifySignature(uint8_t *x, uint8_t *y, std::string signature, uint8_t *signaturePointer, uint8_t *finalHash)
{
  EC_KEY *publicKey = EC_KEY_new();
  EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
  int set_group_status = EC_KEY_set_group(publicKey, ecgroup);

  BIGNUM *xBig = BN_new();
  BIGNUM *yBig = BN_new();

  BIGNUM *xBigResult = BN_bin2bn(x, 32, xBig);
  BIGNUM *yBigResult = BN_bin2bn(y, 32, yBig);

  int createKey = EC_KEY_set_public_key_affine_coordinates(publicKey, xBig, yBig);

  LOG(INFO) << "Key generation: " << createKey;

  ECDSA_SIG *signatureDer = ECDSA_SIG_from_bytes(signaturePointer, (signature.length() / 2));
  if (signatureDer == NULL)
  {
    LOG(INFO) << "Error while signature deserialization";
  }

  int validation = ECDSA_do_verify(finalHash, 32, signatureDer, publicKey);

  EC_KEY_free(publicKey);
  ECDSA_SIG_free(signatureDer);

  LOG(INFO) << "ECDSA result: " << validation;
  return validation;
}

/* -------------------- Hash Id for privacy on blockchain ------------------- */
std::string enryptId(std::string input)
{

  std::string output;

  char const *hashByte = input.c_str();
  SHA256_CTX contextId;
  uint8_t finalHashId[32];
  int resultPrep = SHA256_Init(&contextId);
  SHA256_Update(&contextId, hashByte, strlen(hashByte));
  int hashVal = SHA256_Final(finalHashId, &contextId);

  for (int i : finalHashId)
  {
    output += std::to_string(i);
  }
  return output;
}

/* ----------------------- Sign processed data batches ---------------------- */
std::string signBatch(std::string toSign, uint8_t *privateKey)
{

  // hash concatenated input string
  std::string output;
  char const *hashByte = toSign.c_str();
  SHA256_CTX context;
  uint8_t finalHashId[32];
  int resultPrep = SHA256_Init(&context);
  SHA256_Update(&context, hashByte, strlen(hashByte));
  int hashVal = SHA256_Final(finalHashId, &context);

  EC_KEY *privateEC = EC_KEY_new();
  EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
  int set_group_status = EC_KEY_set_group(privateEC, ecgroup);

  BIGNUM *privateBig = BN_new();
  BIGNUM *privateBigResult = BN_bin2bn(privateKey, 32, privateBig);

  int test = EC_KEY_set_private_key(privateEC, privateBig);

  // Allocate space for signature
  uint8_t *signBytes = (uint8_t *)malloc(64);
  unsigned int *signLength;

  int resultSign = ECDSA_sign(0, &finalHashId[0], 32, signBytes, signLength, privateEC);

  LOG(INFO) << "Length of signature: " << *signLength;

  EC_KEY_free(privateEC);

  std::string s = "";
  std::ostringstream oss;
  oss << std::setfill('0');

  for (int i = 0; i < *signLength; i++)
  {
    //ss << std::setw(2) << std::setfill('0') << (int)signBytes[i];
    //LOG(INFO) << (int)*(signBytes + i);
    oss << std::setw(2) << std::hex << (int)(*signBytes + i);
  }
  output = oss.str();

  //ECDSA_SIG *signature = ECDSA_do_sign(&finalHashId[0], 32, privateEC);

  // if (signature == NULL)
  // {
  //   LOG(INFO) << "Signature generation failed";
  // }
  free(signBytes);

  return output;
}
