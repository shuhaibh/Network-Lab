str1 = input()
char_count={}

for ch in str1:
    if ch in char_count:
        char_count[ch]+=1
    else:
        char_count[ch]=1

print("Count of all characters:- \n"+ str(char_count))