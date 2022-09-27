def translate(
        text: str, 
        key: str,
        ikey,
        alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,?! ",
        encrypt=True
):

    result = ''

    for i in range(len(text)):
        letter_n = alphabet.index(text[i])
        key_n = alphabet.index(key[i % len(key)])

        if encrypt:
            value = (letter_n + key_n + ikey) % len(alphabet)
        else:
            value = (letter_n - key_n - ikey) % len(alphabet)

        result += alphabet[value]

    return result


def encrypt(text, key, key_key):
    return translate(text=text, key=key, ikey=key_key, encrypt=True)


def decrypt(text, key, key_key):
    return translate(text=text, key=key, ikey=key_key, encrypt=False)

def main():
    msg = input("Message: ")
    key_key = int(input("Key: "))
    print("---------------------------------------------\n")
    key="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,?! "
    enc = encrypt(msg, key, key_key)
    print('CipherText:', enc)
    print('PlainText:', decrypt(enc, key, key_key))

if __name__ == '__main__':
    main()