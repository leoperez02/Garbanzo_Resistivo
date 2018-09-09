import os, sys

os.system("clear")

def inv_mul(num,modulo):
		b = num
		aux = b
		a = modulo
		mod = a
		q = []
		t = []
		r=a%b
		#print a,"mod",b,"=",r

		while r>0 :
			d = a//b
#			print a,"=",d,"(",b,")+",r
			a=b
			b=r
			r=a%b
			q.append(d)

		if b==1:
			#print "Tiene inverso"
			t.append(0)
			t.append(1)

			for i in range(2,len(q)+2):
				res = (t[i-2]-(q[i-2]*t[i-1]))%mod
			#	print "[",t[i-2],"-(",q[i-2],"*",t[i-1],")]mod",mod,"=",res
				t.append(res)

#			print "El inverso de ",aux,"mod ",mod," es: ",t[-1]
			return t[-1]

		else:
			print "No tiene inverso"
			return 0



if len(sys.argv)==6:
	#suma
	x1 = int(sys.argv[1])
	y1 = int(sys.argv[2])
	x2 = int(sys.argv[3])
	y2 = int(sys.argv[4])
	m = int(sys.argv[5])
	#print x2-x1,";",y2-y1
	lambd = ((y2-y1)*inv_mul((x2-x1)%m,m))%m
	x3 = ((lambd**2)-x1-x2)%m
	y3 = ((lambd*(x1-x3))-y1)%m
else:
	x1 = int(sys.argv[1])
	y1 = int(sys.argv[2])
	a = int(sys.argv[3])
	m = int(sys.argv[4])
	#doblar
	lambd = (((3*(x1**2))+a)*inv_mul(2*y1,m))%m
	x3 = ((lambd**2)-2*x1)%m
	y3 = ((lambd*(x1-x3))-y1)%m
	
print "(",x3,",",y3,")"
