import sys
import time
import os


rf = open("list", "r")

for line in rf:
	argv = line.split();
	if argv[0][0] == 'f':
		prefix = argv[0]
		ans = argv[1]
	else:
		maxSteps = argv[0]
		delta = argv[1]
		for i in range(5):
			data = prefix + str(i + 1) + '.mis'
			os.system("copy MVCData\\" + data + " input")

			wf = open(data + '-' + delta, "w")
			sys.stdout = wf

			for i in range(5):
				start = time.time();
				os.system("release.exe " + maxSteps + " " + delta + " " + ans)
				count = time.time() - start

				output = open("output", "r")
				outStr = data + " maxSteps:" + maxSteps + " delta:" + delta + " time:" +str(count) + "sec result:"
				for l in output:
					outStr += l.strip('\n');
				print(outStr)

			wf.close()
rf.close()