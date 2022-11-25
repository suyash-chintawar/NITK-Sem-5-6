# This program performs Task2 of Lab Program 2 (191IT109)
# Test cases are hardcoded one-by-one and output filenames are changed for every test case
import hashlib

ifile = open('191IT109_IT352_signature_URL_database.txt','r')
ofile = open('191IT109_IT352_P2_OutputTestCase5.txt','w')

url = 'www.ibm.org' #CHANGED IN EVERY TEST CASE

hash_obj = hashlib.md5(url.encode())
hash = hash_obj.hexdigest()
ofile.write('URL: '+url+'\n')
ofile.write('Signature: '+hash+'\n')
print('URL:',url)
print('Signature:',hash)

found = False
for sign in ifile:
    if sign.strip()==hash:
        ofile.write('URL exists')
        print('URL exists')
        found = True
        break

if found==False:
    ofile.write('URL does not exist')
    print('URL does not exist')