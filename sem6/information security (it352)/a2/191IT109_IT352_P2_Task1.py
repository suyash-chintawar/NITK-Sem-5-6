# This program performs Task2 of Lab Program 2 (191IT109)
import time
import hashlib
import pandas as pd

file = open('191IT109_IT352_signature_URL_database.txt','w')
data = pd.read_csv('phish_score.csv',header=None)
data.columns=['url','ip']

start = time.time()
for url in data['url']:
    hash = hashlib.md5(url.encode())
    file.write(hash.hexdigest()+'\n')
    print(hash.hexdigest())
end = time.time()

print('\nTime taken:',end-start,'seconds\n')

file.close()