# This program uses ECB mode of operation for hill cipher
# Assumptions:
# 1) Modular inverse of the key has been taken with mod=128 for ascii values 
# 2) For the key inverse to exist, both the following conditions must be met, 
#   a) determinant = 0 
#   b) gcd(determinant, 128) = 1

import math
import numpy as np

file = open('191IT109_IT352_P6_Output_TC6.txt','w')

def ascii_to_text(list):
    text = ''.join([chr(ascii_val) for ascii_val in list])
    return text

def mod_inverse(a, m=128):
    res = None
    a = int(a)
    if a<0:
        a=(a+m)%m
    
    for x in range(1,m):
        if (((a%m) * (x%m)) % m == 1):
            res = x
            break
    return res

def encrypt_block(plain_text,key):
    data = [[ord(plain_text[0]),ord(plain_text[1])],[ord(plain_text[2]),ord(plain_text[3])]]
    cipher = np.matmul(key,data)
    cipher_list = list(cipher[0])
    cipher_list.extend(list(cipher[1]))

    for i in range(len(cipher_list)):
        cipher_list[i] %= 128

    return cipher_list

def print_block_encryption(i,block,encrypted_block):
    print('\nBlock',i+1,':')
    print('plain text block:',block)
    print('\nBlock',i+1,':',file=file)
    print('plain text block:',block,file=file)
    cipher_text_block = ascii_to_text(encrypted_block)
    print('cipher text block:',cipher_text_block)
    print('cipher text block:',cipher_text_block,file=file)

def encrypt(n, num_blocks, last_block, plain_text):
    cipher_list = []

    for i in range(num_blocks):
        block = plain_text[4*i:4*(i+1)]
        encrypted_block = encrypt_block(block,key)
        
        print_block_encryption(i,block,encrypted_block)
        
        cipher_list.extend(encrypted_block)
    
    count = None
    if last_block is True:
        count = 0
        block = plain_text[num_blocks*4:]
        
        while len(block) <= 3:
            count += 1
            block+=chr(0)

        encrypted_block = encrypt_block(block,key)
        print_block_encryption(num_blocks,block,encrypted_block)
        cipher_list.extend(encrypted_block)
    
    return count, cipher_list

def decrypt_block(cipher_text,key):
    det = np.linalg.det(key)
    key_inv = (np.linalg.inv(key)*det*mod_inverse(round(det)))%128

    data = [[cipher_text[0],cipher_text[1]],[cipher_text[2],cipher_text[3]]]

    plain = np.matmul(key_inv,data)

    plain_list = list(plain[0])
    plain_list.extend(list(plain[1]))

    for i in range(len(plain_list)):
        plain_list[i] = round(plain_list[i])
        plain_list[i] %= 128
    
    return plain_list

def print_block_decryption(i,block,decrypted_block):
    block_text = ascii_to_text(block)
    print('\nBlock',i+1,':')
    print('cipher text block:',block_text)
    print('\nBlock',i+1,':',file=file)
    print('cipher text block:',block_text,file=file)
    decipher_text_block = ascii_to_text(decrypted_block)
    print('plain text block:',decipher_text_block)
    print('plain text block:',decipher_text_block,file=file)

def decrypt(count, cipher_list):
    decrypt_list = []

    for i in range(len(cipher_list)//4):
        block = cipher_list[i*4:(i+1)*4]
        decrypted_block = decrypt_block(block,key)
        print_block_decryption(i,block,decrypted_block)
        decrypt_list.extend(decrypted_block)
    
    if count is not None:
        decrypt_list = decrypt_list[:-count]
    
    return decrypt_list


if __name__=='__main__':
    plain_text = input('Enter plain text (without spaces): ')
    key = []
    print('Enter 2x2 key row wise(4 integers, 4 lines):')
    for i in range(2):
        temp=[]
        for j in range(2):
            x = int(input())
            temp.append(x)
        key.append(temp)

    det = np.linalg.det(key)
    if det==0 or math.gcd(round(det),128) is not 1:
        print('Key inverse doesn\'t exist')
        print('Key inverse doesn\'t exist',file=file)
    else:
        n = len(plain_text)
        num_blocks = n//4
        last_block = False if n%4==0 else True

        print('******ENCRYPTION******')
        print('******ENCRYPTION******',file=file)
        count, cipher_list = encrypt(n,num_blocks,last_block,plain_text)
        
        cipher_text = ascii_to_text(cipher_list)
        print('\ncomplete cipher text:',cipher_text)
        print('\ncomplete cipher text:',cipher_text,file=file)

        print('\n******DECRYPTION******')
        print('\n******DECRYPTION******',file=file)
        decrypt_list = decrypt(count, cipher_list)

        decrypt_text = ascii_to_text(decrypt_list)
        print('\ncomplete deciphered text:',decrypt_text)
        print('\ncomplete deciphered text:',decrypt_text,file=file)
        file.close()
