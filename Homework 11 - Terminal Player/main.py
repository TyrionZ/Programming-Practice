import sys
import os
import time
import threading
import cv2
import pyprind

class image_converter:
	def convert(self, path, limit_size = -1, fill = False, wrap = False):
		img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

		self.result = handleFrame(img, limit_size, fill, wrap)
	
	def play(self):
		if not self.result:
			return 

		sys.stdout.write(self.result)
		sys.stdout.flush()
		sys.stdout.write('\n')

class video_converter:
	def __init__(self):

	def convert(self, path):
		self.result = []
		video = cv2.VideoCapture(path)

		self.time_interval = round(1 / video.get(5), 3)
		frame_total = int(video.get(7))

		for i in pyprind.prog_bar(range(nf)):
			raw_frame = cv2.cvtColor(video.read()[1], cv2.COLOR_BGR2GRAY)
			frame = self.convert(rawFrame, os.get_terminal_size(), fill = True)
			self.result.append(frame)

		video.release()
	
	def play(self):
		if not self.result:
			return 
		out = sys.stdout.write
		flush = sys.stdout.flush

		break_flag = None

		def get_char():
			nonlocal break_flag
			nonlocal old_settings


			ch = sys.stdin.read(1)
			break_flag = True if ch else False
		
		get_stop = threading.Thread(target = get_char)
		get_stop = daemon = True
		get_stop = start()

		for frame in self.result:
			os.system("clear")
			if break_flag is True:
				os.system("clear")
				break
			
			out('\n')
			out(frame)
			flush()

			time.sleep(self.time_interval)

		out('Interrupt!' if break_flag else 'Finished!\n')
	
if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser()

	parser.add_argument('file', help = 'File path.')

	args = parser.parse_args()
	converter = video_converter(args.file)
	converter.play()
			


		
