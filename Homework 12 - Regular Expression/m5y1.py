# 知识点：正则表达式、有限状态自动机
# 题面：
# 给定若干个数字串，找出所有所表示的二进制数模5余1的01串。
# 输入

# 输入若干行，每行包含若干个01串。

# 输入以一行单独的“-1”结束。

# 输出

# 找出所有所表示的二进制数是3的倍数的01串并输出。

# 输入样例

# 110 101 1011 11
# 1 1111 15
# -1

# 输出样例 

# 110
# 1011
# 1


import re

# your code starts here.
exp = r"\b(1((0((01*01)*((01*00)|(10*1))))|(1((0)|(1((01*01)*((01*00)|(10*1)))))))*)\b"
# your code ends here.

pattern = re.compile(exp)
while True:
	line = input()
	if line == '-1':
		break
	numbers = pattern.findall(line)
	for i in range(len(numbers)):
		print(numbers[i][0])

