#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int position_x, position_y;          //飞机位置
int bullet_x, bullet_y;              //子弹位置
int enemy_x, enemy_y;                //敌机位置
int high, width;                     //游戏画面尺寸
int score;                          //得分
//测试

void gotoxy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);                         // 获取标准输出设备句柄
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);                                   //两个参数分别是指定哪个窗体，具体位置
}

void HideCursor()                                                          // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };                              // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void startup()                      //数据的初始化
{
	high = 20;
	width = 30;
	position_x = high / 2;
	position_y = width / 2;
	bullet_x = 0;
	bullet_y = position_y;
	enemy_x = 0;
	enemy_y = position_y;
	score = 0;

	HideCursor();
}

void show()                                                          //显示界面
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == position_x) && (j == position_y))
				printf("  *");                                         //输出飞机
			else if ((i == position_x + 1) && (j == position_y))
				printf("*****");
			else if ((i == position_x + 2) && (j == position_y))
				printf(" * *");
			else if ((i == enemy_x) && (j == enemy_y))
				printf("@");                                           //输出敌机
			else if ((i == bullet_x) && (j == bullet_y))
				printf("  |");                                         //输出子弹
			else
				printf(" ");                                           //输出空格
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
}

void updateWithoutInput()                           //与用户输入无关的更新
{
	if (bullet_x > -1)
		bullet_x--;
	if ((bullet_x == enemy_x) && bullet_y + 2 == enemy_y)    //子弹击中飞机
	{
		score++;                                    //分数加1
		enemy_x = -1;                               //产生新的飞机
		enemy_y = rand() % width + 2;
		bullet_x = -2;                              //子弹无效
	}
	if (enemy_x > high)                                //敌机跑出屏幕
	{
		enemy_x = -1;                                //产生新的飞机
		enemy_y = rand() % width + 2;
	}

	//用来控制敌机向下移动的速度，每隔几次循环才移动一次
	//这样修改，虽然用户按键交互还是很快，但NPC的移动速度显示可以降速
	static int speed = 0;
	if (speed < 20)
		speed++;
	if (speed == 20)
	{
		enemy_x++;
		speed = 0;
	}
}
void updateWithInput()              //与用户输入有关的更新
{
	char input;
	if (_kbhit())                     //判断是否有输入
	{
		input = _getch();            //根据用户的不同输入来移动，不必输入回车
		if (input == 'a')
			position_y--;           //位置左移
		if (input == 'd')
			position_y++;           //位置右移
		if (input == 'w')
			position_x--;           //位置上移
		if (input == 's')
			position_x++;           //位置下移
		if (input == ' ')            //发射子弹
		{
			bullet_x = position_x - 1;
			bullet_y = position_y;
		}
	}
}

int main()
{
	startup();
	while (1)
	{
		show();                 //显示界面
		updateWithoutInput();   //与用户输入无关的更新
		updateWithInput();      //与用户输入有关的更新
	}
	return 0;
}
