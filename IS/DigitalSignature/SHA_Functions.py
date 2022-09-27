from re import T


def stringToBinary(string):
    """
    Convert a string to a binary string.
    :param string: String to convert.
    :return: Binary string.
    """
    ##>> this works only for ascii characters [e.g. this won't work for em dash (–) which doesn't have any defined ascii value]
   # return ' '.join('{0:08b}'.format(ord(x), 'b') for x in string)  
    
    ##>> this works for any characters
    return ' '.join('{0:08b}'.format(b) for b in string.encode('utf-8')) 


def intToBinary(x, y):
    """
    Convert an integer to a binary string.
    :param x: Integer to convert.
    :param y: x is a y-bit integer.
    :return: Binary string of y bit.
    """
    if y == 128: return "{0:0128b}".format(x) # for length binary data
    if y == 64: return "{0:064b}".format(x) # for W data


def preprocess(string1, string2):
    """
    Preprocess a string.
    :param string1: binary string to preprocess.
    :param string2: binary string to preprocess.
    :return: final preprocessed binary string for SHA-512.
    """
    l = int((len(string1)+len(string2)) % 1024)
    if l == 0: return string1 + string2
    else: return string1 + '1' + format(0, 'b').zfill(1023-l) + string2


def hexToBinary(hex):
    """Converts a hex to 64 bit binary string """
    x = bin(int(hex))
    a, b = x.split('b')

    b = b.rjust(64, '0') # padding 0 to the left to make 64 bit binary string
    return b 


def additionModulo(string1, string2):
    """Addition of two strings values
     : param string1: the first string
     : param string2: the second string
     : return additionModulo of string1 and string2 to 2^64
        as string value
    """ 
    x = int(string1, 2)
    y = int(string2, 2)

    return intToBinary(int((x+y) % (2**64)), 64) 

def xor(x, y):
    s = ''
    for i in range(len(x)): 
        if x[i] == y[i]: s += '0'
        else: s += '1'
    return s

def ROTR(x, n): return x[len(x)-n: ] + x[ :len(x)-n]
def SHR(x, n): return x[ :len(x)-n].rjust(64, '0') 

def sigma0(s): return xor(xor(ROTR(s, 1), ROTR(s, 8)), SHR(s, 7))
def sigma1(s): return xor(xor(ROTR(s, 19), ROTR(s, 61)), SHR(s, 6)) 

def Ch(e, f, g):
    s = ''
    for i in range(len(e)):
        if e[i] == '1': s += f[i]
        else: s += g[i]
    return s 

def SUM_0To512(s): return xor(xor(ROTR(s,28), ROTR(s,34)), ROTR(s,39))
def SUM_1To512(s): return xor(xor(ROTR(s,14), ROTR(s,18)), ROTR(s,41))

def Maj(a, b, c):
    s = ''
    for i in range(len(a)):
        s += str((int(a[i]) & int(b[i])) ^ (int(a[i]) & int(c[i])) ^ (int(b[i]) & int(c[i])))
    return s


###################### hash buffers #################################
a = "0110101000001001111001100110011111110011101111001100100100001000"
b = "1011101101100111101011101000010110000100110010101010011100111011"
c = "0011110001101110111100110111001011111110100101001111100000101011"
d = "1010010101001111111101010011101001011111000111010011011011110001"
e = "0101000100001110010100100111111110101101111001101000001011010001"
f = "1001101100000101011010001000110000101011001111100110110000011111"
g = "0001111110000011110110011010101111111011010000011011110101101011"
h = "0101101111100000110011010001100100010011011111100010000101111001"

H = a + b + c + d + e + f + g + h


###################### keys ##########################################
k = [0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
     0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
     0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
     0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
     0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
     0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
     0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
     0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
     0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
     0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
     0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
     0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
     0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
     0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
     0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
     0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817]


###################### main Function Body ##################################
def SHA512(plain_text):
    text_binary_data = stringToBinary(plain_text)
    text_binary_data = text_binary_data.replace(' ', '')

    # append length
    length_of_data = len(text_binary_data)
    length_binary_data = intToBinary(length_of_data, 128)

    final_binary_data = preprocess(text_binary_data, length_binary_data)
    N = int(len(final_binary_data)/1024)

    # convert keys as binary string
    key = []
    for i in range(len(k)):
        key.append(hexToBinary(k[i]))
    
    ########## message digest generation begins ###########
    for i in range(N):
        M = ''
        M = final_binary_data[i*1024 : (i+1)*1024]

        ##### words generation for 80 rounds #####
        W = []
        for j in range(16):
            W.append(M[j*64 : (j+1)*64])
        
        for j in range(16, 80):
            s = ''
            s += additionModulo(sigma1(W[j-2]), sigma0(W[j-15]))
            s = additionModulo(s, W[j-7])
            s = additionModulo(s, W[j-16])
            W.append(s)
        
        ##### rounds #####
        global a, b, c, d, e, f, g, h, H  # we intoduce the variables as global variables
                                          # so that program don't take them as local variables

        for j in range(80):
            T1 = additionModulo(h, Ch(e, f, g))
            T1 = additionModulo(T1, SUM_1To512(e))
            T1 = additionModulo(T1, W[j])
            T1 = additionModulo(T1, key[j])

            T2 = additionModulo(SUM_0To512(a), Maj(a, b, c))
            
            h = g
            g = f
            f = e
            e = additionModulo(d, T1)
            d = c
            c = b
            b = a
            a = additionModulo(T1, T2)

        # update H 
        q = ''

        q += additionModulo(H[:64], a)
        q += additionModulo(H[64:64 * 2], b)
        q += additionModulo(H[64 * 2:64 * 3], c)
        q += additionModulo(H[64 * 3:64 * 4], d)
        q += additionModulo(H[64 * 4:64 * 5], e)
        q += additionModulo(H[64 * 5:64 * 6], f)
        q += additionModulo(H[64 * 6:64 * 7], g)
        q += additionModulo(H[64 * 7:64 * 8], h)

        H = q

        # update buffers
        a = H[:64]
        b = H[64:64 * 2]
        c = H[64 * 2:64 * 3]
        d = H[64 * 3:64 * 4]
        e = H[64 * 4:64 * 5]
        f = H[64 * 5:64 * 6]
        g = H[64 * 6:64 * 7]
        h = H[64 * 7:64 * 8]

        ########## end of message digest generation ##########

    #### print result ####
    result = ''
    for i in range(128):
        x, y = hex(int(H[i * 4:(i + 1) * 4], 2)).split('x')
        result += y
    
    return result 
    

def main():
    print("Enter your text: ", end="")
    plain_text = input()
    
    result = SHA512(plain_text)
    print("Hash Code is: "+ result)


if __name__ == '__main__':
    main()