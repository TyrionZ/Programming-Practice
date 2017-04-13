# 题面：
# 给定若干个01串，找出所有所表示的二进制数是3的倍数的01串。
# 输入

# 输入若干行，每行包含若干个01串。

# 输入以一行单独的“-1”结束。

# 输出

# 找出所有所表示的二进制数是3的倍数的01串并输出。

# 输入样例

# 1100 10000000000001
# 1100000011 1010101010
# 110011 111
# 111111 101011
# 100111
# -1

# 输出样例 

# 1100
# 10000000000001
# 1100000011
# 110011
# 111111
# 100111


import re
import sys

f = open('data.in', 'r')
sys.stdin = f

exp = \
# your code starts here
	r"\b((1(((01)((11)*(00)*)*(10))|((10)((11)*(00)*)*(01))|(11)|(00))*10*)|0)\b"
# your code ends here

pattern = re.compile(exp)
while True:
	line = input()
	if line == '-1':
		break
	numbers = pattern.findall(line)
	for i in range(len(numbers)):
		print(numbers[i][0])

