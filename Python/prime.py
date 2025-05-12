import math

print(2)
for i in range(3,1001):
    flag = 0
    for j in range(2, int(math.sqrt(i)) + 1):
        if(i%j==0):
            flag=1
    if flag==0:
        print(i)
    