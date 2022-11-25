### This program checks for network intrusions.
### As for broadcast address, no subnet mask was provided, 
### so 255.255.255.255 has been assumed as the broadcast address
import pandas as pd

file = open('191IT109_IT352_P3_Output_TC6.txt','w') #CHANGES IN EVERY TESTCASE

df = pd.read_csv('Testcase-6-for-First-Set-of-Students.csv') #CHANGES IN EVERY TESTCASE
df = df.dropna()

count = 0
total = 0
for index,row in df.iterrows():
    total += 1
    flag = False

    src = row['src'].strip()
    dst = row['dst'].strip()
    
    if (row['src'].strip()==row['dst'].strip()) or (src=='255.255.255.255') or (dst=='255.255.255.255') or (int(row['bytecount'])<40) or row['Protocol'].strip()=='ICMP':
        flag = True

    if flag:
        count += 1
        file.write('Analyzed Packet is Intrusion Packet\n')
        print('Analyzed Packet is Intrusion Packet')
    else:
        file.write('Analyzed Packet is Not-Intrusion Packet\n')
        print('Analyzed Packet is Not-Intrusion Packet')
    
    for col in df.columns:
        print(row[col],end=' ')
        file.write(str(row[col])+' ')
    print('\n',end='')
    file.write('\n')

file.write('\nTotal number of packets checked is = '+str(total)+'\n')
print('\nTotal number of packets checked is =',total)
file.write('Total number of intrusion packets detected is = '+str(count)+'\n')
print('Total number of intrusion packets detected is =',count)

file.close()
        
    


