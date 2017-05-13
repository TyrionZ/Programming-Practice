import sys
import os
import time
import threading
import cv2
import pyprind
import charmap

hua = charmap.Huaji()


# 将灰度矩阵转为字符矩阵
def handle_frame(img, limit_size = -1):
	shape = img.shape
	img = cv2.resize(img, (int(shape[0] / 2), shape[1]), interpolation = cv2.INTER_AREA)
	
	if limit_size != -1 and (img.shape[0] > limit_size[1] or img.shape[1] > limitsize[0]):
		scale = min(limit_size[1] / img.shape[0], limit_size[0] / img.shape[1])
		limit_size = (int(img.shape[0] * scale), int(img.shape[1] * scale))
		
		img = cv2.resize(img, limit_size, interpolation = cv2.INTER_AREA)

	frame = ''
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			frame += hua.gray_to_char(img[i, j])
		frame += '\n'

	return frame

class image_converter:
	def __init__(self, path):
		self.convert(path, os.get_terminal_size())

	# 转换图片
	def convert(self, path, limit_size = -1):
		img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

		self.result = handle_frame(img, limit_size)
	
	# 展示图片
	def play(self):
		if not self.result:
			return 

		sys.stdout.write(self.result)
		sys.stdout.flush()
		sys.stdout.write('\n')

class video_converter:
	def __init__(self, path = ''):
		if path:
			self.convert(path)

	# 转码视频，并将信息保存起来
	def convert(self, path):
		self.result = []
		video = cv2.VideoCapture(path)

		self.time_interval = round(1 / video.get(5), 3)
		frame_total = int(video.get(7))

		for i in pyprind.prog_bar(range(frame_total)):
			raw_frame = cv2.cvtColor(video.read()[1], cv2.COLOR_BGR2GRAY)
			frame = handle_frame(raw_frame, os.get_terminal_size())
			self.result.append(frame)

		video.release()
	
	# 边转码边播放
	def play_while_convert(self, path):
		video = cv2.VideoCapture(path)

		self.time_interval = round(1 / video.get(5), 3)
		frame_total = int(video.get(7))

		out = sys.stdout.write
		flush = sys.stdout.flush

		break_flag = None

		def get_char():
			nonlocal break_flag

			ch = sys.stdin.read(1)
			break_flag = True if ch else False
		
		get_stop = threading.Thread(target = get_char)
		get_stop.daemon = True
		get_stop.start()

		if sys.platform == 'win32' or sys.platform == 'cygwin':
			clear = 'cls'
		else:
			clear = 'clear'

		for i in range(frame_total):
			raw_frame = cv2.cvtColor(video.read()[1], cv2.COLOR_BGR2GRAY)
			frame = handle_frame(raw_frame, os.get_terminal_size())

			os.system(clear)
			if break_flag is True:
				break
			
			out('\n')
			out(frame)
			flush()

			time.sleep(self.time_interval)
			
		out('Interrupt!' if break_flag else 'Finished!\n')
		video.release()

	# 播放已保存信息
	def play(self):
		if not self.result:
			return 
		out = sys.stdout.write
		flush = sys.stdout.flush

		break_flag = None

		def get_char():
			nonlocal break_flag

			ch = sys.stdin.read(1)
			break_flag = True if ch else False
		
		get_stop = threading.Thread(target = get_char)
		get_stop.daemon = True
		get_stop.start()

		if sys.platform == 'win32' or sys.platform == 'cygwin':
			clear = 'cls'
		else:
			clear = 'clear'
		for frame in self.result:
			os.system(clear)
			if break_flag is True:
				os.system(clear)
				break
			
			out('\n')
			out(frame)
			flush()

			time.sleep(self.time_interval)

		out('Interrupt!' if break_flag else 'Finished!\n')
	
# 以下为测试代码
if __name__ == '__main__':
	v = video_converter()
	v.play_while_convert('BadApple.mp4')


		
