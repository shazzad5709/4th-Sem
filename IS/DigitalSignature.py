#not working
#fix the list vs string issue from main AES and sha


from sha512 import *
from AES_multiblock import *

# make message digest
fin = open("/home/shazzad/Desktop/4th-Sem/IS/ji.txt", "r")
text = fin.read()
fin.close()

message_digest = sha512(text)
fout = open("/home/shazzad/Desktop/4th-Sem/IS/digest.txt", "w+")
fout.writelines(message_digest)
fout.close()

# encrypt message digest
ffin = open("/home/shazzad/Desktop/4th-Sem/IS/digest.txt", "r")
md = ffin.readline()
digest = "0x" + md # in our sha output 0x was not included
ffin.close()

fkey = open("/home/shazzad/Desktop/4th-Sem/IS/key.txt", "r")
sender_private_key = fkey.read()
digital_signature = encrypt_multiblock(digest, sender_private_key)
fkey.close()

fdgs = open("/home/shazzad/Desktop/4th-Sem/IS/DS.txt", "w+")
fdgs.write(digital_signature)
fdgs.close()

# receiver validate
sender_public_key = sender_private_key   # as we are using symmetric encryption here

calculated_message_digest = decrypt_multiblock(digital_signature, sender_public_key)
print(digest)
print(calculated_message_digest[ :len(digest)])
if calculated_message_digest[ :len(digest)] == digest:  # as we padd in encryption so we will take
    print("Yes validated!")                             # just up to digest length
    

