p = input('p:')
q = input('q:')
b = input('b:')
x = input('texto plano:')

n = p*q
p_n = (p-1)*(q-1)


a_1 = p_n
mod = a_1
b_1 = b
q = []
t = []
r=a_1%b_1

while r>0 :
	d = a_1//b_1
	print a_1,"=",d,"(",b_1,")+",r
	a_1=b_1
	b_1=r
	r=a_1%b_1
	q.append(d)
 
print "\n",b_1, " es el mcd\n"

t.append(0)
t.append(1)

for i in range(2,len(q)+2):
	res = (t[i-2]-(q[i-2]*t[i-1]))%mod
	print "[",t[i-2],"-(",q[i-2],"*",t[i-1],")]mod",mod,"=",res
	t.append(res)
	
a = t[-1]

print "\n\nn=",n,", phi(n)=",p_n,", a=",a,"\n\n"

encripta = (x**b)%n
print x,"^",b,"mod",n,"=",encripta,"<-- Texto encriptado\n"

desencripta = (encripta**a)%n
print encripta,"^",a,"mod",n,"=",desencripta,"<-- Texto desencriptado\n"


