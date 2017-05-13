## 环境配置

所给代码在Windows 10 x64 下使用Anaconda Python 3.6.0下编译运行。

需要额外安装的第三方包有pyprind和opencv。

opencv无法使用pip正常安装，需要到[Unofficial Windows Binaries for Python Extension Packages](http://www.lfd.uci.edu/~gohlke/pythonlibs/)找到对应版本的opencv下载后进行本地安装。

```powershell
pip install pyprind
pip install opencv_python-3.2.0-cp36-cp36m-amd64.whl
```

## 代码解析

### 将图片的灰度矩阵转换为限定大小的字符矩阵

1. 由于在Terminal中等宽英文字体的长宽比大约为2:1，所以先将原图的长度缩放为原来的1/2以期获得更好的显示效果。
2. 根据limit_size来确定图片的缩放比例。
3. 调用Loriex写的API将矩阵中灰度转换为字符。

```python
# 将一帧转为字符矩阵
def handle_frame(img, limit_size = -1):
	shape = img.shape
    # 在Terminal中等宽英文字体的长宽比大约为2:1，所以先将原图的长度缩放为原来的1/2以期获得更好的显示效果
	img = cv2.resize(img, (int(shape[0] / 2), shape[1]), interpolation = cv2.INTER_AREA)
	
    # 根据limit_size来确定缩放比例
	if limit_size != -1 and (img.shape[0] > limit_size[1] or img.shape[1] > limitsize[0]):
		scale = min(limit_size[1] / img.shape[0], limit_size[0] / img.shape[1])
		limit_size = (int(img.shape[0] * scale), int(img.shape[1] * scale))
		
		img = cv2.resize(img, limit_size, interpolation = cv2.INTER_AREA)

    # 调用Loriex写的API将矩阵中灰度转换为字符
	frame = ''
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			frame += hua.gray_to_char(img[i, j])
		frame += '\n'

	return frame
```

### 图片转换器

图片转化器的写法非常简单，直接使用opencv读取图片的灰度矩阵再调用上文中的handle_frame函数即可。

```python
class image_converter:
	def __init__(self, path):
		self.convert(path, os.get_terminal_size())

	# 转换图片
	def convert(self, path, limit_size = -1):
         #以灰度模式读取图片
		img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)

		self.result = handle_frame(img, limit_size)
	
	# 展示图片
	def play(self):
		if not self.result:
			return 

		sys.stdout.write(self.result)
		sys.stdout.flush()
		sys.stdout.write('\n')
```



### 视频转换器

视频转换器实际上就是在将视频拆分成一帧一帧的图片进行转换再按照原视频帧率播放。

有两种转换模式：

1.先转码后播放，缺点是需要等待，消耗内存资源较高

2.边转码边播放，缺点是可能由于转码速度影响帧率

为了适用不同情况所以把两种模式都写了进来。

同时需要实现在播放时按回车键可以终止播放的功能，这个可以依靠开一个守护进程来读取回车操作来实现。

实现第一种模式时，可以使用pyprind为转码操作添加进度条：

#### 第一种模式

```python
	# 转码视频，并将信息保存起来
	def convert(self, path):
		self.result = []
		video = cv2.VideoCapture(path)

		# 记录原视频帧率
		self.time_interval = round(1 / video.get(5), 3) 
		frame_total = int(video.get(7))

        # 使用pyprind为转码操作添加精度条
		for i in pyprind.prog_bar(range(frame_total)):
			raw_frame = cv2.cvtColor(video.read()[1], cv2.COLOR_BGR2GRAY)
			frame = handle_frame(raw_frame, os.get_terminal_size())
			self.result.append(frame)

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
		# 守护进程
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
```

#### 第二种模式

```python
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
```

