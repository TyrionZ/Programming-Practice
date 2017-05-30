/**
* Tetris 简单交互样例程序
* https://wiki.botzone.org/index.php?title=Tetris
* 更新于2017年4月20日：
* 修正了rotation函数、将交互方式修改为新规则的格式，还有transfer函数里`if (h2 >= MAPHEIGHT)`改为`if (h2 > MAPHEIGHT)`
*/
// 注意：x的范围是1~MAPWIDTH，y的范围是1~MAPHEIGHT
// 数组是先行（y）后列（c）
// 坐标系：原点在左下角
 
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

#define MAPWIDTH 10
#define MAPHEIGHT 20
#define INF 1e9
const int blockShape[7][4][8] = {
	{ { 0,0,1,0,-1,0,-1,-1 },{ 0,0,0,1,0,-1,1,-1 },{ 0,0,-1,0,1,0,1,1 },{ 0,0,0,-1,0,1,-1,1 } },
	{ { 0,0,-1,0,1,0,1,-1 },{ 0,0,0,-1,0,1,1,1 },{ 0,0,1,0,-1,0,-1,1 },{ 0,0,0,1,0,-1,-1,-1 } },
	{ { 0,0,1,0,0,-1,-1,-1 },{ 0,0,0,1,1,0,1,-1 },{ 0,0,-1,0,0,1,1,1 },{ 0,0,0,-1,-1,0,-1,1 } },
	{ { 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,-1,1,0,1,1 },{ 0,0,1,0,0,1,-1,1 },{ 0,0,0,1,-1,0,-1,-1 } },
	{ { 0,0,-1,0,0,1,1,0 },{ 0,0,0,-1,-1,0,0,1 },{ 0,0,1,0,0,-1,-1,0 },{ 0,0,0,1,1,0,0,-1 } },
	{ { 0,0,0,-1,0,1,0,2 },{ 0,0,1,0,-1,0,-2,0 },{ 0,0,0,1,0,-1,0,-2 },{ 0,0,-1,0,1,0,2,0 } },
	{ { 0,0,0,1,-1,0,-1,1 },{ 0,0,-1,0,0,-1,-1,-1 },{ 0,0,0,-1,1,-0,1,-1 },{ 0,0,1,0,0,1,1,1 } }
};// 7种形状(长L| 短L| 反z| 正z| T| 直一| 田格)，4种朝向(上左下右)，8:每相邻的两个分别为x，y


  // 先y后x，记录地图状态，0为空，1为以前放置，2为刚刚放置，负数为越界
  // （2用于在清行后将最后一步撤销再送给对方）
int gridInfo[2][MAPHEIGHT + 2][MAPWIDTH + 2] = { 0 };

class Tetris
{
public:
	const int blockType;   // 标记方块类型的序号 0~6
	int blockX;            // 旋转中心的x轴坐标
	int blockY;            // 旋转中心的y轴坐标
	int orientation;       // 标记方块的朝向 0~3
	const int(*shape)[8]; // 当前类型方块的形状定义

	int color;

	Tetris(int t, int color) : blockType(t), shape(blockShape[t]), color(color)
	{ }

	inline Tetris &set(int x = -1, int y = -1, int o = -1)
	{
		blockX = x == -1 ? blockX : x;
		blockY = y == -1 ? blockY : y;
		orientation = o == -1 ? orientation : o;
		return *this;
	}

	// 判断当前位置是否合法
	inline bool isValid(int x = -1, int y = -1, int o = -1)
	{
		x = x == -1 ? blockX : x;
		y = y == -1 ? blockY : y;
		o = o == -1 ? orientation : o;
		if (o < 0 || o > 3)
			return false;

		int i, tmpX, tmpY;
		for (i = 0; i < 4; i++)
		{
			tmpX = x + shape[o][2 * i];
			tmpY = y + shape[o][2 * i + 1];
			if (tmpX < 1 || tmpX > MAPWIDTH ||
				tmpY < 1 || tmpY > MAPHEIGHT ||
				gridInfo[color][tmpY][tmpX] != 0)
				return false;
		}
		return true;
	}

	// 判断是否落地
	inline bool onGround()
	{
		if (isValid() && !isValid(-1, blockY - 1))
			return true;
		return false;
	}

	// 将方块放置在场地上
	inline bool place()
	{
		if (!onGround())
			return false;

		int i, tmpX, tmpY;
		for (i = 0; i < 4; i++)
		{
			tmpX = blockX + shape[orientation][2 * i];
			tmpY = blockY + shape[orientation][2 * i + 1];
			gridInfo[color][tmpY][tmpX] = 2;
		}
		return true;
	}

	// 检查能否逆时针旋转自己到o
	inline bool rotation(int o)
	{
		if (o < 0 || o > 3)
			return false;

		if (orientation == o)
			return true;

		int fromO = orientation;
		while (true)
		{
			if (!isValid(-1, -1, fromO))
				return false;

			if (fromO == o)
				break;

			fromO = (fromO + 1) % 4;
		}
		return true;
	}
};

namespace Check
{
	vector<pair<pair<int, int>, int> >landablePoint;
	int borderBlock[7][4][4];
	//0: 上 1：下 2：左 3：右
	void init()
	{
		for (int t = 0; t < 7; t++)
			for (int o = 0; o < 4; o++)
			{
				borderBlock[t][o][1] = borderBlock[t][o][2] = 10;
				borderBlock[t][o][0] = borderBlock[t][o][3] = -10;
				for (int i = 0; i < 4; i++)
					borderBlock[t][o][0] = max(borderBlock[t][o][0], blockShape[t][o][(i << 1) | 1]),
					borderBlock[t][o][1] = min(borderBlock[t][o][1], blockShape[t][o][(i << 1) | 1]),
					borderBlock[t][o][2] = min(borderBlock[t][o][2], blockShape[t][o][i << 1]),
					borderBlock[t][o][3] = max(borderBlock[t][o][3], blockShape[t][o][i << 1]);
			}
	}
	bool Setable(int blockType, int orientation, int x, int y, const int **grid)
	{
		for (int i = 0; i < 4; i++)
		{
			int _x = x + blockShape[blockType][orientation][i << 1];
			int _y = y + blockShape[blockType][orientation][(i << 1) | 1];
			if (_x < 1 || _x > MAPWIDTH || _y < 1 || _y > MAPHEIGHT || grid[_y][_x]) return false;
		}
		return true;
	}

}
namespace Check
{
	bool setable[MAPHEIGHT + 2][MAPWIDTH + 2][4], getable[MAPHEIGHT + 2][MAPWIDTH + 2][4], vis[MAPHEIGHT + 2][MAPWIDTH + 2][4];
	void dfs(int x, int y, int o)
	{
		if (x < 1 || x > MAPWIDTH || y < 1 || y > MAPHEIGHT) return;
		if (vis[y][x][o] || !setable[y][x][o]) return;
		vis[y][x][o] = 1; getable[y][x][o] = 1;
		dfs(x, y - 1, o); dfs(x + 1, y, o); dfs(x - 1, y, o);
		int _o = o + 1; if (_o == 4) _o = 0;
		dfs(x, y, _o);
	}
	vector<pair<pair<int, int>, int> >* getLandablePoint(int blockType, const int **grid)
	{
		//cout << blockType << ' ' << orientation << endl;
		memset(setable, 0, sizeof(setable));
		memset(getable, 0, sizeof(getable));
		memset(vis, 0, sizeof(vis));
		landablePoint.clear();
		for (int y = MAPHEIGHT; y >= 1; y--)
			for (int x = 1; x <= MAPWIDTH; x++)
				for (int o = 0; o < 4; o++)
					if (Setable(blockType, o, x, y, grid))
					{
						setable[y][x][o] = 1;
						if (y + borderBlock[blockType][o][0] == MAPHEIGHT)
							getable[y][x][o] = 1;
					}
		for (int y = MAPHEIGHT; y >= 1; y--)
			for (int x = 1; x <= MAPWIDTH; x++)
				for (int o = 0; o < 4; o++)
					if (!vis[y][x][o] && getable[y][x][o])
						dfs(x, y, o);
		// for (int y = MAPHEIGHT; y >= 1; y--)
		// {
		// 	for (int x = 1; x <= MAPWIDTH; x++) cout << setable[y][x][orientation];
		// 		cout << endl;
		// }			
		// cout << "_____" << endl;
		// for (int y = MAPHEIGHT; y >= 1; y--)
		// {
		// 	for (int x = 1; x <= MAPWIDTH; x++) cout << getable[y][x][orientation];
		// 		cout << endl;
		// }
		for (int y = MAPHEIGHT; y >= 1; y--)
			for (int x = 1; x <= MAPWIDTH; x++)
				for (int o = 0; o < 4; o++)
				{
					if (getable[y][x][o] && !getable[y - 1][x][o])
						landablePoint.push_back(make_pair(make_pair(x, y), o));
				}
		return &landablePoint;
	}
}

namespace evaluate {
	const double landingHeight = -4.400158825082766;
	const double rowsEliminated = 3.4181268101392694;
	const double rowsTransitions = -3.2178882868487753;
	const double columnTransitions = -9.348695305445199;
	const double holesNumber = -7.899265427351652;
	const double wellSums = -3.3855972247263626;

	int grid[MAPHEIGHT + 2][MAPWIDTH + 2];
	bool full[MAPHEIGHT + 2];

	double Eliminate(Tetris landBlock) {
		for (int i = 0; i < 4; i++)
			grid[landBlock.blockY + blockShape[landBlock.blockType][landBlock.orientation][(i << 1) | 1]][landBlock.blockX + blockShape[landBlock.blockType][landBlock.orientation][i << 1]] = 1;
		for (int i = 1; i <= MAPHEIGHT; i++) {
			full[i] = true;
			for (int j = 1; j <= MAPWIDTH; j++)
				if (!grid[i][j]) full[i] = false;
		}
		int fullCount = 0;
		for (int i = 1; i <= MAPHEIGHT; i++)
			if (full[i])
				++fullCount;
			else
				for (int j = 1; j <= MAPHEIGHT; j++)
					grid[i - fullCount][j] = grid[i][j];

		for (int i = MAPHEIGHT - fullCount + 1; i <= MAPHEIGHT; ++i)
			for (int j = 1; j <= MAPWIDTH; j++)
				grid[i][j] = 0;
		return fullCount;
	}

	double getRowTransitions(int x) {
		double res = 0;
		for (int i = 0; i <= MAPWIDTH; i++)
			res += ((i && i != MAPWIDTH) ? 1.0 : 0.4) * (grid[x][i] != grid[x][i + 1] ? 1.0 : 0.0);
		return res;
	}

	double getColumnTransitions(int x) {
		double res = 0;
		for (int i = 0; i <= MAPHEIGHT - 1; i++)
			res += (grid[i][x] != grid[i + 1][x]);
		return res;
	}

	int getStatus(int x) {
		int res = 0;
		for (int i = 1; i <= MAPWIDTH; i++)
			res = (res << 1) | grid[x][i];
		return res;
	}

	double getHolesNumber() {
		int res = 0;
		int rowHoles = 0;
		int previousRow = getStatus(MAPHEIGHT);

		for (int i = MAPHEIGHT - 1; i >= 1; i--) {
			rowHoles = ~(getStatus(i)) & (previousRow | rowHoles);

			for (int j = 1; j <= MAPWIDTH; j++)
				res += (rowHoles >> j) & 1;
		}
		return res;
	} //??

	double getWellSums() {
		double res = 0;
		for (int j = 1; j <= MAPWIDTH; ++j)
			for (int i = MAPHEIGHT; i >= 1; --i)
				if (grid[i][j - 1] && grid[i][j + 1] && !grid[i][j]) {
					int count = 1;
					while (grid[i][j - 1] && grid[i][j + 1] && !grid[i][j])
						--i, count++;
					++i;
					res += count * (count - 1) / 2;
				}
		return res;
	} //??

	double evaluate(Tetris landBlock, const int **initGrid) {
		memset(grid, 0, sizeof grid);
		for (int i = 1; i <= MAPHEIGHT; i++)
			for (int j = 1; j <= MAPWIDTH; j++)
				grid[i][j] = initGrid[i][j];
		for (int i = 0; i <= MAPHEIGHT + 1; i++)
			grid[i][0] = grid[i][MAPWIDTH + 1] = 1;
		for (int i = 0; i <= MAPWIDTH + 1; i++)
			grid[0][i] = grid[MAPHEIGHT + 1][i] = 1;


		double res = 0;
		int er = Eliminate(landBlock);
		int mahai = 0;
		for (int i = 0; i < 4; i++)
			mahai = max(mahai, blockShape[landBlock.blockType][landBlock.orientation][i << 1]);

		if (landBlock.blockX == 6 && landBlock.blockY == 8)
			int  o = 1;

		mahai = mahai + (landBlock.blockY - er);
		res += landingHeight * mahai;
		for (int i = 1; i <= MAPHEIGHT; i++)
			for (int j = 1; j <= MAPWIDTH; j++)
				if (grid[i][j]) mahai = max(i, mahai);
		res += landingHeight * (1 / (double(mahai) * mahai / 9 + 0.01));
		res += rowsEliminated * (1.0 + (1 / (double(mahai) * mahai / 9 + 0.01))) * er;
		for (int i = 1; i <= MAPHEIGHT; i++)
			res += rowsTransitions * getRowTransitions(i);
		for (int i = 1; i <= MAPWIDTH; i++)
			res += columnTransitions * getColumnTransitions(i);

		
		res += wellSums * getWellSums();
		res += holesNumber * getHolesNumber();
		return res;
	}


}
// 我所在队伍的颜色（0为红，1为蓝，仅表示队伍，不分先后）
int currBotColor;
int enemyColor;


// 代表分别向对方转移的行
int trans[2][4][MAPWIDTH + 2] = { 0 };

// 转移行数
int transCount[2] = { 0 };

// 运行eliminate后的当前高度
int maxHeight[2] = { 0 };

// 总消去行数的分数之和
int elimTotal[2] = { 0 };

// 一次性消去行数对应分数
const int elimBonus[] = { 0, 1, 3, 5, 7 };

// 给对应玩家的各类块的数目总计
int typeCountForColor[2][7] = { 0 };


// 围一圈护城河
void init()
{
	int i;
	for (i = 0; i < MAPHEIGHT + 2; i++)
	{
		gridInfo[1][i][0] = gridInfo[1][i][MAPWIDTH + 1] = -2;
		gridInfo[0][i][0] = gridInfo[0][i][MAPWIDTH + 1] = -2;
	}
	for (i = 0; i < MAPWIDTH + 2; i++)
	{
		gridInfo[1][0][i] = gridInfo[1][MAPHEIGHT + 1][i] = -2;
		gridInfo[0][0][i] = gridInfo[0][MAPHEIGHT + 1][i] = -2;
	}
}

namespace Util
{

	// 检查能否从场地顶端直接落到当前位置
	inline bool checkDirectDropTo(int color, int blockType, int x, int y, int o)
	{
		const int *def = blockShape[blockType][o];
		for (; y <= MAPHEIGHT; y++)
			for (int i = 0; i < 4; i++)
			{
				int _x = def[i * 2] + x, _y = def[i * 2 + 1] + y;
				if (_y > MAPHEIGHT)
					continue;
				if (_y < 1 || _x < 1 || _x > MAPWIDTH || gridInfo[color][_y][_x])
					return false;
			}
		return true;
	}

	// 消去行
	void eliminate(int color)
	{
		int &count = transCount[color] = 0;
		int i, j, emptyFlag, fullFlag;
		maxHeight[color] = MAPHEIGHT;
		for (i = 1; i <= MAPHEIGHT; i++)
		{
			emptyFlag = 1;
			fullFlag = 1;
			for (j = 1; j <= MAPWIDTH; j++)
			{
				if (gridInfo[color][i][j] == 0)
					fullFlag = 0;
				else
					emptyFlag = 0;
			}
			if (fullFlag)
			{
				for (j = 1; j <= MAPWIDTH; j++)
				{
					// 注意这里只转移以前的块，不包括最后一次落下的块（“撤销最后一步”）
					trans[color][count][j] = gridInfo[color][i][j] == 1 ? 1 : 0;
					gridInfo[color][i][j] = 0;
				}
				count++;
			}
			else if (emptyFlag)
			{
				maxHeight[color] = i - 1;
				break;
			}
			else
				for (j = 1; j <= MAPWIDTH; j++)
				{
					gridInfo[color][i - count][j] =
						gridInfo[color][i][j] > 0 ? 1 : gridInfo[color][i][j];
					if (count)
						gridInfo[color][i][j] = 0;
				}
		}
		maxHeight[color] -= count;
		elimTotal[color] += elimBonus[count];
	}

	// 转移双方消去的行，返回-1表示继续，否则返回输者
	int transfer()
	{
		int color1 = 0, color2 = 1;
		if (transCount[color1] == 0 && transCount[color2] == 0)
			return -1;
		if (transCount[color1] == 0 || transCount[color2] == 0)
		{
			if (transCount[color1] == 0 && transCount[color2] > 0)
				swap(color1, color2);
			int h2;
			maxHeight[color2] = h2 = maxHeight[color2] + transCount[color1];
			if (h2 > MAPHEIGHT)
				return color2;
			int i, j;

			for (i = h2; i > transCount[color1]; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color2][i][j] = gridInfo[color2][i - transCount[color1]][j];

			for (i = transCount[color1]; i > 0; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color2][i][j] = trans[color1][i - 1][j];
			return -1;
		}
		else
		{
			int h1, h2;
			maxHeight[color1] = h1 = maxHeight[color1] + transCount[color2];//从color1处移动count1去color2
			maxHeight[color2] = h2 = maxHeight[color2] + transCount[color1];

			if (h1 > MAPHEIGHT) return color1;
			if (h2 > MAPHEIGHT) return color2;

			int i, j;
			for (i = h2; i > transCount[color1]; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color2][i][j] = gridInfo[color2][i - transCount[color1]][j];

			for (i = transCount[color1]; i > 0; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color2][i][j] = trans[color1][i - 1][j];

			for (i = h1; i > transCount[color2]; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color1][i][j] = gridInfo[color1][i - transCount[color2]][j];

			for (i = transCount[color2]; i > 0; i--)
				for (j = 1; j <= MAPWIDTH; j++)
					gridInfo[color1][i][j] = trans[color2][i - 1][j];

			return -1;
		}
	}

	// 颜色方还能否继续游戏
	inline bool canPut(int color, int blockType)
	{
		Tetris t(blockType, color);
		for (int y = MAPHEIGHT; y >= 1; y--)
			for (int x = 1; x <= MAPWIDTH; x++)
				for (int o = 0; o < 4; o++)
				{
					t.set(x, y, o);
					if (t.isValid() && checkDirectDropTo(color, blockType, x, y, o))
						return true;
				}
		return false;
	}

	// 打印场地用于调试
	inline void printField()
	{
#ifndef _BOTZONE_ONLINE
		static const char *i2s[] = {
			"~~",
			"~~",
			"  ",
			"[]",
			"##"
		};
//		cout << "~~：墙，[]：块，##：新块" << endl;
		for (int y = MAPHEIGHT + 1; y >= 0; --y)
		{
			for (int x = 0; x <= MAPWIDTH + 1; x++)
				cout << i2s[gridInfo[0][y][x] + 2];
			for (int x = 0; x <= MAPWIDTH + 1; x++)
				cout << i2s[gridInfo[1][y][x] + 2];
			cout << endl;
		}
#endif
	}
}

int **mymk(int r1, int r2) {
	int **s = new int *[r1];
	for (int i = 0; i < r1; ++i) {
		s[i] = new int[r2];
		for (int j = 0; j < r2; ++j)
			s[i][j] = 0;
	}
	return s;
}
void mydl(int **s, int r1) {
	for (int i = 0; i < r1; ++i)
		delete[] s[i];
	delete[] s;
}
void xiaohang(int col) {
	int gg[MAPHEIGHT + 2];
	for (int i = MAPHEIGHT; i >= 1; --i) {
		if (i == MAPHEIGHT) 
			gg[i] = i;
		else 
			gg[i] = gg[i + 1] - 1;

		bool xiao = true;
		for (int j = 1; j <= MAPWIDTH; ++j)
			if (gridInfo[col][i][j] != 1)
				xiao = false;
		if (xiao == true)
			--gg[i];
	}
	if (gg[1] > 0) {
		for (int i = MAPHEIGHT; i >= 1; --i)
			for (int j = 1; j <= MAPWIDTH; ++j)
				gridInfo[col][i][j] = gridInfo[col][gg[i]][j];
	}
	else {
		for (int i = 1; i <= MAPHEIGHT; ++i)
			for (int j = 1; j <= MAPWIDTH; ++j)
				gridInfo[col][i][j] = 0;
	}
}
pair<Tetris, double> getBest(const int *colnum, int blockType, int depth) {
	int **gridinfo = mymk(MAPHEIGHT + 2, MAPWIDTH + 2);
	int **ssp = mymk(MAPHEIGHT + 2, MAPWIDTH + 2);
	for (int i = 0; i < MAPHEIGHT + 2; ++i)
		for (int j = 0; j < MAPWIDTH + 2; ++j)
			ssp[i][j] = gridinfo[i][j] = gridInfo[currBotColor][i][j];
	int tcfk[10];
	memcpy(tcfk, colnum, sizeof(int)*8);

	int blockForEnemy, finalX, finalY, finalO;
	//先创建二维指针
	//-------------------------------------------------------------------------------------------------
	double maxval = -INF;
	Check::init(); //Check使用前要初始化一下

		//获取我方棋盘的新方块的可到达位置
	vector<pair<pair<int, int>, int>> sb = (*Check::getLandablePoint(blockType, (const int **)ssp));
		//		cout << (*sb).size() << endl;

	for (int si = 0; si < sb.size(); ++si) {
		pair<pair<int, int>, int> p = sb[si];
		double val = evaluate::evaluate(Tetris(blockType, currBotColor).set(p.first.first, p.first.second, p.second), (const int **)ssp);
		if (depth > 1) {
			#ifndef _BOTZONE_ONLINE
			printf("%d %d %d\n", p.first.first, p.first.second, p.second);		
			#endif
			
			for (int ssi = 0; ssi < MAPHEIGHT + 2; ++ssi)
				for (int ssj = 0; ssj < MAPWIDTH + 2; ++ssj)
					gridInfo[currBotColor][ssi][ssj] = gridinfo[ssi][ssj];
			Tetris shit(blockType, currBotColor);
			shit.set(p.first.first, p.first.second, p.second);
			shit.place();
			for (int ssi = 0; ssi < MAPHEIGHT + 2; ++ssi)
				for (int ssj = 0; ssj < MAPWIDTH + 2; ++ssj)
					if (gridInfo[currBotColor][ssi][ssj] == 2)
						gridInfo[currBotColor][ssi][ssj] = 1;
			xiaohang(currBotColor);

			double mval = INF;
			for (int gi = 0; gi < 7; ++gi) {
				tcfk[gi]++;
				bool canUse = true;
				for (int u = 0; u < 7; ++u)
					for (int v = 0; v < 7; ++v)
						if (tcfk[u] - tcfk[v] > 2)
							canUse = false;
				if (canUse) {
					pair<Tetris, double> hhd = getBest(tcfk, gi, depth-1);
					double rc = hhd.second;
					if (mval > rc) {
						mval = rc;
					}
				}
				tcfk[gi]--;
			}
			//cout << mval << endl;
			val = val * 0.7 + mval * 0.3;
		}

		//			cout << val << endl;
		if (val > maxval) {
			maxval = val;
			finalX = p.first.first;
			finalY = p.first.second;
			finalO = p.second;
		}

		
	}

	for (int i = 0; i < MAPHEIGHT + 2; ++i)
		for (int j = 0; j < MAPWIDTH + 2; ++j)
			gridInfo[currBotColor][i][j] = gridinfo[i][j];

	mydl(gridinfo, MAPHEIGHT+2);
	return pair<Tetris, double>(Tetris(blockType, currBotColor).set(finalX,finalY,finalO), (maxval>-INF/2) ? maxval : maxval/2);
}
int main()
{
#ifndef _BOTZONE_ONLINE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	// 加速输入
	istream::sync_with_stdio(false);
	srand(time(NULL));
	init();

	int turnID, blockType;
	int nextTypeForColor[2];
	cin >> turnID;

	// 先读入第一回合，得到自己的颜色
	// 双方的第一块肯定是一样的
	cin >> blockType >> currBotColor;
	enemyColor = 1 - currBotColor;
	nextTypeForColor[0] = blockType;
	nextTypeForColor[1] = blockType;
	typeCountForColor[0][blockType]++;
	typeCountForColor[1][blockType]++;

	// 然后分析以前每回合的输入输出，并恢复状态
	// 循环中，color 表示当前这一行是 color 的行为
	// 平台保证所有输入都是合法输入
	for (int i = 1; i < turnID; i++)
	{
		int currTypeForColor[2] = { nextTypeForColor[0], nextTypeForColor[1] };
		int x, y, o;
		// 根据这些输入输出逐渐恢复状态到当前回合

		// 先读自己的输出，也就是自己的行为
		// 自己的输出是自己的最后一步
		// 然后模拟最后一步放置块
		cin >> blockType >> x >> y >> o;

		// 我当时把上一块落到了 x y o！
		Tetris myBlock(currTypeForColor[currBotColor], currBotColor);
		myBlock.set(x, y, o).place();

		// 我给对方什么块来着？
		typeCountForColor[enemyColor][blockType]++;
		nextTypeForColor[enemyColor] = blockType;

		// 然后读自己的输入，也就是对方的行为
		// 裁判给自己的输入是对方的最后一步
		cin >> blockType >> x >> y >> o;

		// 对方当时把上一块落到了 x y o！
		Tetris enemyBlock(currTypeForColor[enemyColor], enemyColor);
		enemyBlock.set(x, y, o).place();

		// 对方给我什么块来着？
		typeCountForColor[currBotColor][blockType]++;
		nextTypeForColor[currBotColor] = blockType;

		// 检查消去
		Util::eliminate(0);
		Util::eliminate(1);

		// 进行转移
		Util::transfer();
	}


	int blockForEnemy, finalX, finalY, finalO;

	// 做出决策（你只需修改以下部分）

	// 遇事不决先输出（平台上编译不会输出）
	Util::printField();


	//先创建二维指针
	int **ssp = mymk(MAPHEIGHT + 2, MAPWIDTH + 2);

	Tetris hhd = getBest(typeCountForColor[currBotColor], blockType, 2).first;
	finalX = hhd.blockX;
	finalY = hhd.blockY;
	finalO = hhd.orientation;
	//-------------------------------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------------------------------

	//// 贪心决策
	//// 从下往上以各种姿态找到第一个位置，要求能够直着落下
	//Tetris block(nextTypeForColor[currBotColor], currBotColor);
	//for (int y = 1; y <= MAPHEIGHT; y++)
	//	for (int x = 1; x <= MAPWIDTH; x++)
	//		for (int o = 0; o < 4; o++)
	//		{
	//			if (block.set(x, y, o).isValid() &&
	//				Util::checkDirectDropTo(currBotColor, block.blockType, x, y, o))
	//			{
	//				finalX = x;
	//				finalY = y;
	//				finalO = o;
	//				goto determined;
	//			}
	//		}

determined:
	// 再看看给对方什么好
	//----------------------------------------------------------------------------------------------
	double minval = INFINITY;
	for (int i = 0; i < MAPHEIGHT + 2; ++i)
		for (int j = 0; j < MAPWIDTH + 2; ++j)
			ssp[i][j] = gridInfo[enemyColor][i][j];

	for (int btfe = 0; btfe < 7; ++btfe) {
		//枚举 block Type for enemy
		typeCountForColor[enemyColor][btfe]++;

		//看能不能上这个方块
		bool canUse = true;
		for (int u = 0; u < 7; ++u)
			for (int v = 0; v < 7; ++v)
				if (typeCountForColor[enemyColor][u] - typeCountForColor[enemyColor][v] > 2)
					canUse = false;
		typeCountForColor[enemyColor][btfe]--;
		if (canUse == false)
			continue;


		double maxval = -INFINITY;
		int finalXX, finalYY, finalOO;

			//同我方策略求敌方最优策略

			vector<pair<pair<int, int>, int> > *sb = Check::getLandablePoint(btfe, (const int **)ssp);
			for (auto p : *sb) {
				double val = evaluate::evaluate(Tetris(btfe, enemyColor).set(p.first.first, p.first.second, p.second), (const int **)ssp);
//				cout << val << endl;
				if (val > maxval) {
					maxval = val;
					finalXX = p.first.first;
					finalYY = p.first.second;
					finalOO = p.second;
				}
			}

//		cout << "--std--" << btfe << ":::" << maxval << endl;
		if (maxval < minval) {
			minval = maxval;
			blockForEnemy = btfe;
		}
	}
	//----------------------------------------------------------------------------------------------
	mydl(ssp, MAPHEIGHT + 2);
	//清空二维指针内存


	//int maxCount = 0, minCount = 99;
	//for (int i = 0; i < 7; i++)
	//{
	//	if (typeCountForColor[enemyColor][i] > maxCount)
	//		maxCount = typeCountForColor[enemyColor][i];
	//	if (typeCountForColor[enemyColor][i] < minCount)
	//		minCount = typeCountForColor[enemyColor][i];
	//}
	//if (maxCount - minCount == 2)
	//{
	//	// 危险，找一个不是最大的块给对方吧
	//	for (blockForEnemy = 0; blockForEnemy < 7; blockForEnemy++)
	//		if (typeCountForColor[enemyColor][blockForEnemy] != maxCount)
	//			break;
	//}
	//else
	//{
	//	blockForEnemy = rand() % 7;
	//}

	// 决策结束，输出结果（你只需修改以上部分）

	std::cout << blockForEnemy << " " << finalX << " " << finalY << " " << finalO;

	Tetris myBlock(blockType, currBotColor);
	myBlock.set(finalX, finalY, finalO).place();
	Util::printField();
//	while (1);
	return 0;
}