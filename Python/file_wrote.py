file = open("code.txt","w")
file.write("PROGRAMMING IN PYTHON")
file.close()

infile=open("code.txt","r")
intext=infile.read()

print(intext)
file.close()
