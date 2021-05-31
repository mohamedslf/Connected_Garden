number = 0
file = open("C:\Users\mugiwarra\Desktop\starf.docx", 'r')
string = file.read()
for i in string:
    number += 1
print(number)
file.close()