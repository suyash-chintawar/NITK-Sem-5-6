import numpy as np

file = open('191IT109_IT352_P8_Output_TC6.txt','w')

def cyclic_attack(e,N,C):
    iterations = 0
    prev = C
    next = pow(C,e,N)
    print('\n***Obtained intermediate texts***')
    print('Iteration 0 :',next)
    print('\n***Obtained intermediate texts***',file=file)
    print('Iteration 0 :',next,file=file)
    while next != C:
        if iterations==100:
            return -np.inf , iterations
        prev = next
        next = pow(prev,e,N)
        iterations += 1
        print('Iteration',iterations,':',next)
        print('Iteration',iterations,':',next,file=file)
    return prev, iterations

if __name__=='__main__':
    e = int(input('Enter e value: '))
    N = int(input('Enter N value: '))
    C = int(input('Enter C value: '))
    
    prev, iterations = cyclic_attack(e,N,C)

    if prev==-np.inf:
        print('\nINSUFFICIENT ITERATIONS')
        print('\nINSUFFICIENT ITERATIONS',file=file)
    else:
        print('\nLoop found, decode success!\nPlain text obtained:',prev)
        print('No. of iterations:',iterations)
        print('\nLoop found, decode success!\nPlain text obtained:',prev,file=file)
        print('No. of iterations:',iterations,file=file)
    
    file.close()