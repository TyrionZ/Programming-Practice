T = int(input())
step = ((1, 0), (-1, 0), (0, 1), (0, -1))

for test in range(T):
	a, in_queue, q, l = [], [], [], 0
	n, m = map(int, input().split())
	for i in range(n):
		a += [input()]
		in_queue += [[False] * m]
		for j in range(m):
			if a[i][j] == 'r':
				q += [(i, j, False, 0)]
	ans = -1
	while l < len(q):
		u = q[l]
		l += 1
		if ans != -1:
			continue 
		x, y, s, d = u[0], u[1], u[2], u[3]
		if s:
			q += [(x, y, False, d + 1)]
			continue
		for i in range(4):
			tx = x + step[i][0]
			ty = y + step[i][1]
			if tx < 0 or ty < 0 or tx >= n or ty >= m or in_queue[tx][ty] or a[tx][ty] == '#':
				continue 
			if a[tx][ty] == 'a':
				ans = d + 1
				continue
			in_queue[tx][ty] = True
			q += [(tx, ty, a[tx][ty] == 'x', d + 1)]

	print('Impossible' if ans == -1 else ans)
