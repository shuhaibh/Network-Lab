n=int(input())
odd_count=0
even_count=0

for i in range(n):
    if(i%2==0):
        even_count+=1
    else:
        odd_count+=1

print("Even Count:" + even_count)
print(odd_count)