def inverso(a, n, q)
	t = []
	t[0] = 0
	t[1] = 1
	for i in 2..q.length
		t[i] = ( t[i-2] - q[i-1]*t[i-1] ) % n
	end
	return b
end


