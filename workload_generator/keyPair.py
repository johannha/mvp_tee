# short script for creating key pairs and testing

from ecdsa import SigningKey, NIST256p

sk = SigningKey.generate(curve=NIST256p)
vk = sk.verifying_key

testString = sk.to_string().hex()

print("Signing key: " + sk.to_string().hex())
print(vk)

if (SigningKey.from_string(bytes.fromhex(testString), curve=NIST256p) == sk):
    print("same")

# Test
signature = sk.sign(b"Hello World")
# print(signature.hex())

print(vk.verify(signature, b"Hello World"))
