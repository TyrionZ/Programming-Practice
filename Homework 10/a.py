import bisect
sup = 1000000000

n = int(input())
a = [[sup, 1]]
for i in range(n):
	x, d = input().split()
	g = [int(d), int(x)]
	res = bisect.bisect(a, g)
	if res > 0 and g[0] - a[res - 1][0] <= a[res][0] - g[0]:
		res -= 1 
	print(g[1], a[res][1])
	bisect.insort(a, g)