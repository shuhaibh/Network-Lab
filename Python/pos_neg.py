n = int(input("Enter the number of elements"))
number_list = []
pos_list=[]
neg_list=[]

for i in range(n):
    number=int(input())
    number_list.append(number)

for i in range(n):
    if number_list[i]>0:
        pos_list.append(number_list[i])
    else:
        neg_list.append(number_list[i])

print(pos_list)
print(neg_list)

