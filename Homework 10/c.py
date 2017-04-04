f = [[0,1,3,4],[0,1,2],[1,2,4,5],[0,3,6],[1,3,4,5,7],[2,5,8],[3,4,6,7],[6,7,8],[4,5,7,8]]
a = list(map(int, input().split())) + list(map(int, input().split())) + list(map(int, input().split()))

s, ans = [], ['pty'] * 36

def search(depth):
	global ans, a, s
	if a.count(0) == 9:
		ans = s[:]
		return
	if depth == 9 or len(s) >= len(ans):
		return 
	for i in range(4):
		search(depth + 1)
		for j in f[depth]:
			a[j] = (a[j] + 1) % 4
		s.append(depth + 1)
	for i in range(4):
		s.pop()
	
search(0)
for x in ans:
	print(x, end = ' ')