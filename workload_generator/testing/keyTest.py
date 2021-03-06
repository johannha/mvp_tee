from ecdsa import VerifyingKey, NIST256p

publicKey = "27023bef190183c43e1798a343ac70d53a32f95ba482360f1b7688b94cffa9b7351b4a67b82d880690531d106383cf742d30bc0aca3700c53329c99a5227c820"
signature = "85892d24ca5c2b8d06c75c7f842cb2f5807af21cacbe0ab7246c4f24181eb58efb7ddddba2d351a8a0fa4275dd9373e1663b8969e140862d7ce81cf3e02e7958"
hash = "db1c85c669b217cc193011b541749b75c032c4fc612f670b58b95a6591992c33"

verifier = VerifyingKey.from_string(bytes.fromhex(publicKey), curve=NIST256p)

z = verifier.to_string()

print("Der Private Key: ")
print(len(verifier.to_der().hex()))

print("To string: ")
print(z)

# calculates x and y coordinates of the public key and converts it to big-endian for use in enclave


# xPart = publicKey[:64]
# xResult = []
# print("X part of the arrax")
# print(xPart)
# xResult.append([int((xPart[i:i+2])[::-1], 16)
#                for i in range(0, len(xPart), 2)])
# print("x Result = ")
# print(xResult)


# yPart = publicKey[-64:]
# yResult = []
# print("Y part of the arrax")
# print(yPart)
# yResult.append([int((yPart[j:j+2])[::-1], 16)
#                for j in range(0, len(yPart), 2)])
# print("y Result = ")
# print(yResult)


# decoded = int.from_bytes(bytes.fromhex(publicKey),
#                          byteorder='big', signed=False)


# with open("pk.pem", "wb") as f:
#     f.write(verifier.to_pem())

# Tests signature
print(verifier.verify(bytes.fromhex(signature), bytes.fromhex(hash)))
