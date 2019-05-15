/*	IDA*算法解决FLOODit问题
*/
#include <iostream>
#include <string.h>
#include <vector>
#include <random>
#include <time.h>
#include <ctime>
using namespace std;

#define SumColor 6//游戏中方格的颜色总数
#define Size 6//游戏中的长度和宽度。

void DFS(int px, int py, int color);
bool IDAStar(int HMax);
int GetH();
void CreateImg();		//随机创建图形
int RandomColor();	 //随机返回一个颜色
bool expand(int color, bool update=false);

vector <int> BestColors;	//负责记录一条最优路径

/*int img[Size][Size] = { 1,4,3,4,2 ,2 ,3,1, 3,1,
		4, 0, 3 ,2 ,2 ,1 ,4 ,4 ,1 ,3,
			1 ,3 ,2, 0 ,2 ,2 ,3, 3, 0 ,4,
4, 2 ,3 ,2 ,4 ,4 ,4 ,0, 3 ,0,
3 ,1 ,4 ,3 ,0 ,2 ,1, 1, 2, 0,
3, 2 ,4, 3, 1, 0 ,3 ,3, 1 ,0,
0 ,0 ,4 ,1 ,4, 4, 4 ,2 ,4, 3,
1 ,0 ,0, 4, 3, 3, 1 ,2 ,1, 3,
3 ,3 ,2, 4, 2 ,4, 1, 4, 3, 2,
2, 0 ,0 ,3, 3 ,3, 2 ,1 ,2, 3};*/

int img[Size][Size];
int States[Size][Size];	// 1代表与左上角颜色相同 ，2 代表与1相邻 ， 3代表剩余的
// 方向
int DisX[4] = { 0,1,0,-1 };
int DisY[4] = { 1,0,-1,0 };


int main()
{

	time_t begin = time(0);

	srand((unsigned)time(0));
	CreateImg();
	/*显示游戏初始状态*/
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j< Size; j++)
		{
			cout << img[i][j]<<" ";

		}
		cout << endl;
	}
	memset(States, 0,sizeof(States));
	// 对当前游戏状态进行计算
	DFS(0, 0, img[0][0]);
	//得到开始时搜索的最大深度
	int HMax = GetH();
	BestColors.clear();
	while (!IDAStar(HMax))
	{
		cout << "搜索深度为" << HMax <<"不能找到可行解"<<endl;
		HMax++;
		BestColors.clear();
	}
	cout << "最优解步数为:" << HMax<<"步"<<endl;
	int length = BestColors.size();
	memset(States, 0, sizeof(States));
	DFS(0, 0, img[0][0]);
	//模拟棋盘的跟新
	for (int i = length - 1; i >= 0; i--)
	{
		cout << "选择:"<<BestColors[i] << endl;
		cout << "棋盘" << endl;
		expand(BestColors[i], true);
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				cout << img[i][j] << " ";

			}
			cout << endl;
		}
	}
	time_t end = time(0);
	cout << "总用时为" << end - begin << "S" << endl;

	getchar();
	return 0;
}
void DFS(int x,int y,int color)
{
	States[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		int px = x + DisX[i];
		int py = y + DisY[i];
		//判断坐标是否存在
		if ((0 <= px &&px<Size) && (0 <= py && py < Size))
		{
			if (States[px][py]!= 1)
			{
				if (img[px][py]==color)
				{
					DFS(px, py, img[px][py]);
				}
				else
				{
					States[px][py] = 2;
				}
			}
		}
	}
}
// 通过一个递归调用，实现IDA*算法
bool IDAStar(int HMax)
{

	if (HMax < GetH())
	{
		return false;
	}
	if (GetH() == 0)
	{
		return true;
	}
	for (int color = 0; color < SumColor; color++)
	{
		int memory[Size][Size];

		memcpy(memory, States, sizeof(States));

		//如果无新的扩展节点，
		if (!expand(color))
		{
			continue;
		}
		if (IDAStar(HMax - 1))
		{
			BestColors.push_back(color);
			return true;
		}
		//如果有新的扩展节点，但最终达到最大深度却不能找到解决方案,恢复原有状态
		memcpy(States, memory, sizeof(memory));

	}

	return false;

}
/*模拟进行一次操作*/
bool expand(int color,bool update)
{
	bool back = false;
	for (int px = 0; px < Size; px++)
	{
		for (int py = 0; py < Size; py++)
		{	//如果在相邻节点中发现与扩展颜色相同，则改变其状态，并对其进行DFS
			if ((States[px][py] == 2) && (img[px][py] == color))
			{
				DFS(px, py, color);
				back = true;
			}
		}
	}
	if (update)
	{
		for (int px = 0; px < Size; px++)
		{
			for (int py = 0; py < Size; py++)
			{
				if (States[px][py] == 1)
				{
					img[px][py] = color;
				}

			}
		}

	}
	//若对img中的数据进行改变，则若该次扩展非最优路线上的解，则还要返回父节点状态，故在此不对img进行修改；
	return back;
}
/*得到当前cost的值*/
int GetH()
{	//H(n) = States状态不为1的剩余颜色的数量
	int MarkedColor[SumColor];
	memset(MarkedColor, 0, SumColor * sizeof(int));
	int num = 0;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (States[i][j] != 1)
			{
				if (MarkedColor[img[i][j]] == 0)
				{
					MarkedColor[img[i][j]] = 1;
					num++;
				}
				else
				{
					continue;
				}
			}
		}
	}

	return num;
}

void CreateImg()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			img[i][j] = RandomColor();
		}
	}
}

int RandomColor()
{
	int color = rand()%SumColor;
	return color;
}
