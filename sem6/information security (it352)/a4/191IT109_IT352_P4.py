# This program implements caesar cipher with plain text and key as input
# Assumptions:
# 1) Spaces have been ignored and only english alphabets texts have been considered
# 2) Key must be between [0,25] both inclusive.


file = open('191IT109_IT352_P4_Output_TC6.txt','w') #CHNAGED IN EVERY TESTCASE

def encrypt(plain_text, key):
    plain_text = plain_text.split()
    encrypted_list = []
    for text in plain_text:
        text = text.upper()
        encrypted_partial_text = ''
        for c in text:
            encrypted_partial_text += chr(int((ord(c)-ord('A'))+key)%26 + ord('A'))
        encrypted_list.append(encrypted_partial_text)
    return ' '.join(encrypted_list)

def decrypt(cipher_text,key):
    cipher_text = cipher_text.split()
    decrypted_list = []
    for text in cipher_text:
        text = text.upper()
        decrypted_partial_text = ''
        for c in text:
            decrypted_partial_text += chr((ord(c)-ord('A')-key+26)%26 + ord('A'))
        decrypted_list.append(decrypted_partial_text.lower())
    return ' '.join(decrypted_list)


if __name__ == '__main__':
    plain_text = input('Enter plain text: ')
    key = int(input('Enter key: '))
    flag = True

    if key<0 or key>26:
        print('\nInvalid Key!')
        file.write('Invalid Key!')
        flag = False

    for c in plain_text:
        if (c>='a' and c<='z') or (c>='A' and c<='Z') or c==' ':
            continue
        else:
            print('\nInvalid Input!')
            file.write('Invalid Input!')
            flag = False
            break

    if flag:
        plain_text = ''.join(plain_text.split()).lower()

        cipher_text = encrypt(plain_text,key)
        cipher_text = ''.join(cipher_text.split())
        print('\nENCRYPTION:')
        print('Plain text:',plain_text)
        print('Cipher text:',cipher_text)
        print('Key:',key)
        file.write('ENCRYPTION:\n')
        file.write('Plain text: '+str(plain_text)+'\n')
        file.write('Cipher text: '+str(cipher_text)+'\n')
        file.write('Key: '+str(key)+'\n')

        decrypted_text = decrypt(cipher_text,key)
        print('\nDECRYPTION:')
        print('Cipher text:',cipher_text)
        print('Plain text:',decrypted_text)
        print('Key:',key)
        file.write('\nDECRYPTION:\n')
        file.write('Cipher text: '+str(cipher_text)+'\n')
        file.write('Plain text: '+str(decrypted_text)+'\n')
        file.write('Key: '+str(key)+'\n')


file.close()
        