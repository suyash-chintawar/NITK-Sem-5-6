#This program performs RSA digital signature scheme
# Assumptions 
# 1) Each char in the message is considered as a different block 
# 2) The list in the message and signature output are the corresponding blocks


file = open('191IT109_IT352_P9_Output_TC6.txt','w')

def modInverse(a, m):
    for x in range(1, m):
        if (((a%m) * (x%m)) % m == 1):
            return x
    return -1

if __name__=='__main__':
    e = int(input('Enter e: '))
    p = int(input('Enter p: '))
    q = int(input('Enter q: '))

    message =input('Enter message: ')

    n = p * q
    fn = (p-1)*(q-1)

    d = modInverse(e,fn)

    print('\n****d-value computation****\n\nd value:', d)
    print('\n****d-value computation****\n\nd value:', d, file=file)

    message_ascii = []
    signature = []

    for char in message:
        message_ascii.append(ord(char))
        signature.append(pow(ord(char),d,n))

    print('\n****Signer Side****\n\nMessage:',message_ascii)
    print('Signature:',signature)

    print('\n****Signer Side****\n\nMessage:',message_ascii,file=file)
    print('Signature:',signature,file=file)

    decrypted_message_values = []
    decrypted_message=''
    for val in signature:
        decrypted_message_values.append(pow(val,e,n))
        decrypted_message+=chr(decrypted_message_values[-1])


    print('\n****Verifier Side****\n\nDecrypted message:',decrypted_message_values)
    print('Decrypted message text:',decrypted_message)

    print('\n****Verifier Side****\n\nDecrypted message:',decrypted_message_values,file=file)
    print('Decrypted message text:',decrypted_message,file=file)

    if message==decrypted_message:
        print('\nMESSAGE VERIFICATION SUCCESS!!')
        print('\nMESSAGE VERIFICATION SUCCESS!!',file=file)
    else:
        print('\nMESSAGE VERIFICATION FAILED!!')
        print('\nMESSAGE VERIFICATION FAILED!!',file=file)
    
    file.close()