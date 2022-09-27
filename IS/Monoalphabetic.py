import random

symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,?! "
key = random.randint(1, 67)

def main():
    msg = input("Message: ")
    print("Key:", key)
    enc = encrypt(msg)
    print('CipherText:',enc)
    print('PlainText:', decrypt(enc))


def encrypt(message):
    encrypted = ""
    for char in message:
        if char in symbols:
            char_idx = symbols.find(char) + key

        if char_idx >= len(symbols):
            char_idx -= len(symbols)

        encrypted = encrypted + symbols[char_idx]
    return encrypted


def decrypt(message):
    decrypted = ""
    for char in message:
        if char in symbols:
            char_idx = symbols.find(char) - key

        if char_idx < 0:
            char_idx += len(symbols)

        decrypted = decrypted + symbols[char_idx]
    return decrypted

if __name__ == '__main__':
    main()