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

r0=ARGV[0].to_i
r1=ARGV[1].to_i
puts mcd(r0,r1)