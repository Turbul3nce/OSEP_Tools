import sys

def rc4_encrypt(key, data):
    # Key-scheduling algorithm (KSA)
    key_length = len(key)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % key_length]) % 256
        S[i], S[j] = S[j], S[i]

    # Pseudo-random generation algorithm (PRGA)
    i = j = 0
    result = bytearray()
    for char in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        result.append(char ^ S[(S[i] + S[j]) % 256])

    return bytes(result)

def encrypt_file(key, input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()

    encrypted_data = rc4_encrypt(key.encode('utf-8'), data)

    with open(output_file, 'wb') as f:
        f.write(encrypted_data)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python script.py <key> <input_file> <output_file>")
        sys.exit(1)

    key = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]

    encrypt_file(key, input_file, output_file)
    print("Encryption complete.")
