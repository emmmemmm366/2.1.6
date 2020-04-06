#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ���
int position_x, position_y;          //�ɻ�λ��
int bullet_x, bullet_y;              //�ӵ�λ��
int enemy_x, enemy_y;                //�л�λ��
int high, width;                     //��Ϸ����ߴ�
int score;                          //�÷�
//����

void gotoxy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);                         // ��ȡ��׼����豸���
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);                                   //���������ֱ���ָ���ĸ����壬����λ��
}

void HideCursor()                                                          // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };                              // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void startup()                      //���ݵĳ�ʼ��
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

void show()                                                          //��ʾ����
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == position_x) && (j == position_y))
				printf("  *");                                         //����ɻ�
			else if ((i == position_x + 1) && (j == position_y))
				printf("*****");
			else if ((i == position_x + 2) && (j == position_y))
				printf(" * *");
			else if ((i == enemy_x) && (j == enemy_y))
				printf("@");                                           //����л�
			else if ((i == bullet_x) && (j == bullet_y))
				printf("  |");                                         //����ӵ�
			else
				printf(" ");                                           //����ո�
		}
		printf("\n");
	}
	printf("�÷֣�%d\n", score);
}

void updateWithoutInput()                           //���û������޹صĸ���
{
	if (bullet_x > -1)
		bullet_x--;
	if ((bullet_x == enemy_x) && bullet_y + 2 == enemy_y)    //�ӵ����зɻ�
	{
		score++;                                    //������1
		enemy_x = -1;                               //�����µķɻ�
		enemy_y = rand() % width + 2;
		bullet_x = -2;                              //�ӵ���Ч
	}
	if (enemy_x > high)                                //�л��ܳ���Ļ
	{
		enemy_x = -1;                                //�����µķɻ�
		enemy_y = rand() % width + 2;
	}

	//�������Ƶл������ƶ����ٶȣ�ÿ������ѭ�����ƶ�һ��
	//�����޸ģ���Ȼ�û������������Ǻܿ죬��NPC���ƶ��ٶ���ʾ���Խ���
	static int speed = 0;
	if (speed < 20)
		speed++;
	if (speed == 20)
	{
		enemy_x++;
		speed = 0;
	}
}
void updateWithInput()              //���û������йصĸ���
{
	char input;
	if (_kbhit())                     //�ж��Ƿ�������
	{
		input = _getch();            //�����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a')
			position_y--;           //λ������
		if (input == 'd')
			position_y++;           //λ������
		if (input == 'w')
			position_x--;           //λ������
		if (input == 's')
			position_x++;           //λ������
		if (input == ' ')            //�����ӵ�
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
		show();                 //��ʾ����
		updateWithoutInput();   //���û������޹صĸ���
		updateWithInput();      //���û������йصĸ���
	}
	return 0;
}
