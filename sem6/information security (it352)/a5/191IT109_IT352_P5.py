# This program performs initial and final permutations of the DES cipher
# Assumptions:
# 1. The ASCII 00000000 has been appended in last block if not of size 64
# 2. The output of initial permutation is printed in binary format
#    because the output text file cannot be opened if their corresponding ASCII
#    values are printed
# 3. The outputs of inital and final permutations are the concatenated outputs of individual blocks
# 4. Finally the text obtained after final permutation is also printed in the last line of output.


BLOCK_SIZE = 64

def text2bin(plain_text):
    binary = ''
    for c in plain_text:
        binary += '{:08b}'.format(ord(c))
    return binary

def bin2text(binary_text):
    plain_text = ''
    n = len(binary_text)//8
    for i in range(n):
        plain_text += chr(int(binary_text[i*8:(i+1)*8],2))
    return plain_text

def initial_permutation(block):
    permuted_block = ''
    initial_perm = [58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7]
    for idx in initial_perm:
        permuted_block += block[idx-1]
    return permuted_block

def final_permutation(permuted_block):
    block = ''
    final_perm  =  [40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25 ]
    for idx in final_perm:
        block += permuted_block[idx-1]
    return block

if __name__=='__main__':
    
    file = open('191IT109_IT352_P5_Output_Sample.txt','w')

    plain_text = input('Enter Plain Text: ')

    print('Input Text:',plain_text)
    print('Input Text:',plain_text,file=file)

    binary_text = text2bin(plain_text)
    n = len(binary_text)

    num_blocks = n//BLOCK_SIZE
    last_block = (n%BLOCK_SIZE!=0)
    i = 0
    blocks = []

    for iteration in range(num_blocks):
        blocks.append(binary_text[i:i+BLOCK_SIZE])
        i += BLOCK_SIZE

    cnt=None
    if last_block:
        cnt=0
        block = binary_text[i:]
        while len(block)!=BLOCK_SIZE:
            block += '0'
            cnt+=1
        blocks.append(block)

    print('\nBlocks are:')
    print('\nBlocks are:',file=file)
    for i in range(len(blocks)):
        print('Block',i+1,':',blocks[i])
        print('Block',i+1,':',blocks[i],file=file)
    
    permuted_binary_text = ''
    permuted_blocks = []
    for block in blocks:
        permuted_block = initial_permutation(block)
        permuted_blocks.append(permuted_block)
        permuted_binary_text += permuted_block
    
    ip_text = bin2text(permuted_binary_text)
    print('\nOutput of Initial Permutation  Operation:', permuted_binary_text)
    print('\nOutput of Initial Permutation  Operation:', permuted_binary_text,file=file)

    original_binary_text = ''
    for block in permuted_blocks:
        original_block = final_permutation(block)
        original_binary_text += original_block
    
    original_plain_text = bin2text(original_binary_text)
    print('Output of Final Permutation Operation:', original_binary_text)
    print('Output of Final Permutation Operation:', original_binary_text,file=file)

    if cnt is not None:
        print('\nText Obtained After final Permutation:',original_plain_text[:-cnt//8])
        print('\nText Obtained After final Permutation:',original_plain_text[:-cnt//8],file=file)
    else:
        print('\nText Obtained After final Permutation:',original_plain_text)
        print('\nText Obtained After final Permutation:',original_plain_text,file=file)

    file.close()    