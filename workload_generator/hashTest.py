import hashlib

input = "Das Wetter ist heute sonnig und voller Wasser"

encoded = input.encode()
result = hashlib.sha256(encoded)

print("Resultat direkt nach der Funktion: ")
print(result.hexdigest())
