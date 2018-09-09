def mcd(r0, r1)
	q = []
	r = []
	r[0] = r0
	r[1] = r1
	i = 0
	loop do
		r[i+2] = r[i] % r[i+1]
		q[i+1] = r[i] / r[i+1]
		print r[i], " = ", "(", q[i+1], ")", r[i+1]," + ", r[i+2], "\n"
		i=i+1
		break if r[i+1] == 0
	end
	return r[i],q
end

def inverso(n, q)
	t = []
	t[0] = 0
	t[1] = 1
	for i in 2..q.length-1
		t[i] = ( t[i-2] - q[i-1]*t[i-1] ) % n
		print t[i], " = ", "(", t[i-2], " - ", q[i-1],"(", t[i-1], ")) mod ",n,"\n"
	end
	return t[i]
end

r0=ARGV[0].to_i
r1=ARGV[1].to_i
if r1<0 then
	if r1*-1 < r0 then
		puts r0+r1
	else
		nuevo = (r1*-1) % r0
		puts nuevo
	end
else
	res, q  = mcd(r0,r1)
if res != 1
	puts "El numero no tiene inverso"
else
	puts inverso(r0,q)	
end
end

