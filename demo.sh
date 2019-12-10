make
echo here we go:
./main.out
expect "miniPy>"
send "a = [1,2,3,4,]"
send "a"
send "b = a * 2"
send "b"
print(a[0])
a[0]="hello"
a[0]
a
a[2]=[5,6,7]
a
a[2].append(8)
a
a[2][1]
c=b+[7,8,9]
c
a==range(6)
a
a[::-1]
a[-1::-1]=range(5)
a
b=[[0]*len(a)]*len(a)
b[0][2:4]=[2.3,"hello"+"world"]
b
