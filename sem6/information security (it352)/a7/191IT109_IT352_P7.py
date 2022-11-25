# This program generates the cryptographic secrets from key matrial which in turn gets generated from 
# the  provided pre-master secret 
# Assumptions: 
# 1) The cryptographic secrets generated are hex values (8 bytes each) whereas the keymaterial is 48 bytes in size.
# 2) Client random and server random are printed in byte string, whereas all other values are printed in hex values.

import numpy as np
from hashlib import md5, sha1

file = open('191IT109_IT352_P7_Output_TC6.txt','w')

def generate_cr_sr():
    cr = np.random.bytes(32)
    sr = np.random.bytes(32)
    return cr, sr

def stage1(premaster, cr, sr):

    #input1
    input1 = 'A'.encode() + premaster.encode() + cr + sr

    #input2
    input2 = 'BB'.encode() + premaster.encode() + cr + sr
    
    #input3
    input3 = 'CCC'.encode() + premaster.encode() + cr + sr

    hash1 = sha1(input1).hexdigest()
    hash2 = sha1(input2).hexdigest()
    hash3 = sha1(input3).hexdigest()

    return hash1, hash2, hash3

def stage2(premaster, hash1, hash2, hash3):
    #input1
    input1 = premaster + hash1

    #input2
    input2 = premaster + hash2
    
    #input3
    input3 = premaster + hash3

    hash1 = md5(input1.encode()).hexdigest()
    hash2 = md5(input2.encode()).hexdigest()
    hash3 = md5(input3.encode()).hexdigest()

    return hash1, hash2, hash3

def extract_cryptographic_secrets(key_material):

    partition_len = len(key_material)//6

    cak = key_material[:partition_len]
    sak = key_material[partition_len:2*partition_len]
    cek = key_material[2*partition_len:3*partition_len]
    sek = key_material[3*partition_len:4*partition_len]
    civ = key_material[4*partition_len:5*partition_len]
    siv = key_material[5*partition_len:]

    return cak,sak,cek,sek,civ,siv

if __name__=='__main__':
    premaster = input('Enter pre master secret: ')
    cr, sr = generate_cr_sr()

    print('*****MASTER SECRET GENERATION*****\n')
    print('*****MASTER SECRET GENERATION*****\n',file=file)
    hash1, hash2, hash3 = stage1(premaster, cr, sr)
    hash1, hash2, hash3 = stage2(premaster, hash1, hash2, hash3)

    master_secret = hash1 + hash2 + hash3

    print('Client Random Number:',cr)
    print('Server Random Number:',sr)
    print('Master Secret:',master_secret)
    print('Client Random Number:',cr,file=file)
    print('Server Random Number:',sr,file=file)
    print('Master Secret:',master_secret,file=file)

    print('\n*****KEY MATERIAL AND CRYPTOGRAPHIC SECRETS*****\n')
    print('\n*****KEY MATERIAL AND CRYPTOGRAPHIC SECRETS*****\n',file=file)

    hash1, hash2, hash3 = stage1(master_secret, cr, sr)
    hash1, hash2, hash3 = stage2(master_secret, hash1, hash2, hash3)

    key_material = hash1 + hash2 + hash3

    cak,sak,cek,sek,civ,siv = extract_cryptographic_secrets(key_material)

    print('Key Material:',key_material)
    print('Client Authentication Key:',cak)
    print('Server Authentication Key:',sak)
    print('Client Encryption Key:',cek)
    print('Server Encryption Key:',sek)
    print('Client Initial Vector:',civ)
    print('Server Initial Vector:',siv)
    print('Key Material:',key_material,file=file)
    print('Client Authentication Key:',cak,file=file)
    print('Server Authentication Key:',sak,file=file)
    print('Client Encryption Key:',cek,file=file)
    print('Server Encryption Key:',sek,file=file)
    print('Client Initial Vector:',civ,file=file)
    print('Server Initial Vector:',siv,file=file)

    file.close()

    



