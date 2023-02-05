#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

void startup();
void show();
void updatewithoutinput();
void status_change();
void updatewithinput();
void gameover();

#define high 670
#define width 900
#define man_high 72
#define man_width 64
#define stone_width 64
#define stone_high 64
#define fly_high 82
#define fly_width 64
#define digl_high 78
#define digl_width 64
#define digr_width 64
#define digr_high 78
#define digd_high 70
#define digd_width 64
#define num_1_stonerow 4
#define num_1_stonecol 14
#define stone_position 414


IMAGE img_bk;//定义背景图片
IMAGE img_1;//定义第一关的图片
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7;//定义石块的图片
IMAGE img_man_0, img_man_00;//定义挖地小子的正面图片 0表示黑白版 00表示彩版
IMAGE img_man_1, img_man_2;//定义挖地小子左右走的图片 1表示黑白版 2表示彩版
IMAGE img_shoes_1, img_shoes_2;//定义火箭鞋图片 1表示黑白版 2表示彩版
IMAGE img_digl_1, img_digl_2;//定义挖地小子向左挖的照片  1表示黑白版 2表示彩版
IMAGE img_digright_1, img_digright_2;//定义挖地小子向右挖的照片  1表示黑白版 2表示彩版
IMAGE img_digdown_1, img_digdown_2;//定义挖地小子向下挖的照片  1表示黑白版 2表示彩版
MOUSEMSG m;//定义一个鼠标变量

class thing {
public:
	int left_x;
	int left_y;
	int right_x;
	int right_y;
	int top_x;
	int top_y;
	int bottom_x;
	int bottom_y;
	int center_x;
	int center_y;
	int v;
}; thing man;

class stone {
public:
	int left_x;
	int left_y;
	int right_x;
	int right_y;
	int top_x;
	int top_y;
	int bottom_x;
	int bottom_y;
	int center_x;
	int center_y;
	int status;
};
stone stone1[num_1_stonerow][num_1_stonecol];

int scene;
int left_i;
int right_i;
int G;
int fly_a;
int man_1;
int man_2;
int man_3;
int man_4;
int dig;
int digl;
int digr;
int is_leftstone;
int is_rightstone;

int main() {
	//printf("welcome to you");
	startup();
	while (1) {
		show();
		updatewithoutinput();
		status_change();
		updatewithinput();
	}
	gameover();
	return 0;
}
void startup() {
	initgraph(width, high);//画布
	loadimage(&img_bk, _T("..//images//background.jpg"));//导入游戏开始界面
	loadimage(&img_1, _T("..//images//level_1.jpg"));//导入第一关的图片
	loadimage(&img_man_0, _T("..//images//person_0.jpg"));//导入人物正面的图片黑白版
	loadimage(&img_man_00, _T("..//images//person_00.jpg"));//导入人物正面的图片彩版
	loadimage(&img_man_1, _T("..//images//person_1.jpg"));//导入人物左右走路的图片的黑白版
	loadimage(&img_man_2, _T("..//images//person_2.jpg"));//导入人物左右走路的图片彩版
	loadimage(&img_stone_0, _T("..//images//stone_0.jpg"));//导入空的图片
	loadimage(&img_stone_1, _T("..//images//stone_1.jpg"));//导入石块原图的图片
	loadimage(&img_stone_2, _T("..//images//stone_2.jpg"));//导入破碎1的图片
	loadimage(&img_stone_3, _T("..//images//stone_3.jpg"));//导入破碎2的图片
	loadimage(&img_stone_4, _T("..//images//stone_4.jpg"));//导入破碎3的图片
	loadimage(&img_stone_5, _T("..//images//stone_5.jpg"));//导入破碎4的图片
	loadimage(&img_stone_6, _T("..//images//stone_6.jpg"));//导入破碎5的图片
	loadimage(&img_stone_7, _T("..//images//stone_7.jpg"));//导入破碎6的图片
	loadimage(&img_shoes_1, _T("..//images//shoes_1.jpg"));//导入上升的图片黑白版
	loadimage(&img_shoes_2, _T("..//images//shoes_2.jpg"));//导入上升的图片彩版
	loadimage(&img_digl_1, _T("..//images//digleftperson_1.jpg"));//导入向左挖的图片的黑白版
	loadimage(&img_digl_2, _T("..//images//digleftperson_2.jpg"));//导入向左挖的图片的彩版
	loadimage(&img_digright_1, _T("..//images//digrightperson_1.jpg"));//导入向右挖的图片的黑白版
	loadimage(&img_digright_2, _T("..//images//digrightperson_2.jpg"));//导入向右挖的图片的彩版
	loadimage(&img_digdown_1, _T("..//images//digdownperson_1.jpg"));//导入向下挖的图片的黑白版
	loadimage(&img_digdown_2, _T("..//images//digdownperson_2.jpg"));//导入向下挖的图片的彩版
	mciSendString(_T("open ..//images//bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//导入背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环背景音乐
	
	scene = 0;
	fly_a = 1;
	man_1 = 1;
	man_2 = 1;
	man_3 = 1;
	man_4 = 1;
	is_leftstone = 0;
	is_rightstone = 0;
	digl = 0;
	digr = 0;
	//初始化石块位置
	for (int i = 0; i < num_1_stonerow; i++) {
		for (int j = 0; j < num_1_stonecol; j++) {
			 stone1[i][j].center_x = stone_width / 2 + j * stone_width;
			 stone1[i][j].center_y = stone_position + stone_high / 2 + i * stone_high;
			 stone1[i][j].top_x = stone_width / 2 + j * stone_width;
			 stone1[i][j].top_y = stone_position + stone_high * i;
			 stone1[i][j].bottom_x = stone_width / 2 + j * stone_width;
			 stone1[i][j].bottom_y = stone_position + stone_high * i;
			 stone1[i][j].left_x = stone_width * j;
			 stone1[i][j].left_y = stone_position + stone_high / 2 * i;
			 stone1[i][j].right_x = stone_width * j + stone_width;
			 stone1[i][j].right_y = stone_position + stone_high / 2 * i;
			 stone1[i][j].status = 1;
		}
	}
	//角色初始化位置
	man.center_x = width / 2;
	man.center_y = stone_position - man_high / 2;
	//角色移动参数
	left_i = 0;
	right_i = 0;
	man.v = 0;
	BeginBatchDraw();
}

void show() {
	int i, j;
	if (scene == 0) {
		putimage(0, 0, &img_bk);
		FlushBatchDraw();
	}
	else if (scene == 1) {
		putimage(0, 0, &img_1);
		for ( i = 0; i < num_1_stonerow; i++)
		{
			for (j = 0; j < num_1_stonecol; j++) {
				if (stone1[i][j].status==1) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_1);
				}
				else if (stone1[i][j].status == 2) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_2);
				}
				else if (stone1[i][j].status == 3) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_3);
				}
				else if (stone1[i][j].status == 4 ) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_4);
				}
				else if (stone1[i][j].status == 5) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_5);
				}
				else if (stone1[i][j].status == 6) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_6);
				}
				else if (stone1[i][j].status == 7) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_7);
				}
				else if (stone1[i][j].status == 0) {
					putimage(stone_width * j, stone_position + stone_high * i, &img_stone_0);
				}
			}
		}
		//FlushBatchDraw();
	}
	//角色五元组
	man.left_x = man.center_x - man_width / 2;
	man.left_y = man.center_y;
	man.right_x = man.center_x + man_width / 2;
	man.right_y = man.center_y;
	man.top_x = man.center_x;
	man.top_y = man.center_y - man_high / 2;
	man.bottom_x = man.center_x;
	man.bottom_y = man.center_y + man_high / 2;
}

void updatewithoutinput() {
	//确定角色的位置
	int i, j;
	G=1;
	for (i = 0; i < num_1_stonerow; i++) {
		for (j = 0; j < num_1_stonecol; j++) {
			//判断角色是否站在石块上
			if (stone1[i][j].center_y - man.center_y <= man_high / 2 + stone_high / 2 &&
				stone1[i][j].center_y - man.center_y >= (man_high / 2 + stone_high / 2) / 2 &&
				man.center_x <= stone1[i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
				man.center_x >= stone1[i][j].center_x - man_width / 2 - stone_width / 2 + 10 &&
				stone1[i][j].status!= 0) {
				G = 0;
				man.v = 0;
				man.center_y = stone1[i][j].center_y - man_high / 2 - stone_high / 2;
				break;
			}
		}
	}
	//判断角色飞行时上方是否有石块
	if (fly_a == -2) {
		for (i = 0; i < num_1_stonerow; i++) {
			for (j = 0; j < num_1_stonecol; j++) {
				if (man.center_y-stone1[i][j].center_y <= stone_high - man_high / 2+stone_high/2  &&
					man.center_y-stone1[i][j].center_y  >= (stone_high - man_high / 2 + stone_high / 2) / 2 &&
					man.center_x <= stone1[i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
					man.center_x >= stone1[i][j].center_x - man_width / 2 - stone_width / 2 + 10 &&
					stone1[i][j].status != 0) {
					fly_a = -1;
					man.v = 0;
					break;
				}
			}
		}
	}
	//判断是否向下挖
	for (i = 0; i < num_1_stonerow; i++) {
		for (j = 0; j < num_1_stonecol; j++) {
			if (stone1[i][j].center_y - man.center_y <= man_high / 2 + stone_high / 2 &&
				stone1[i][j].center_y - man.center_y >= (man_high / 2 + stone_high / 2) / 2 &&
				man.center_x <= stone1[i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
				man.center_x >= stone1[i][j].center_x - man_width / 2 - stone_width / 2 + 10 &&
				stone1[i][j].status != 0) {
				if (dig == 1 && stone1[i][j].status != 0) {
					man.center_x = stone1[i][j].center_x;
					static int speed_2 = 0;
					if (speed_2 < 100) {
						speed_2++;
					}
					else if (speed_2 == 100) {
						stone1[i][j].status++;
						speed_2 = 0;
					}
					if (stone1[i][j].status == 8) {
						stone1[i][j].status = 0;
					}
				}
			}
		}
	}
	//判断是否向左挖
	for (i = 0; i < num_1_stonerow; i++) {
		for (j = 0; j < num_1_stonecol; j++) {
			if (man.center_x - stone1[i][j].center_x <= stone_width / 2 + man_width / 2 &&
				man.center_x - stone1[i][j].center_x >= (stone_width / 2 + man_width / 2) / 2 &&
				stone1[i][j].center_y - man.center_y == man_high / 2 - stone_high / 2 &&
				stone1[i][j].status != 0) {
				is_leftstone = 1;
				if (digl == 1) {
					man.center_x = stone1[i][j].center_x + stone_width / 2 + man_width / 2;
					static int speed_3 = 0;
					if (speed_3 < 100) {
						speed_3++;
					}
					else if (speed_3 == 100) {
						stone1[i][j].status++;
						speed_3 = 0;
					}
					if (stone1[i][j].status == 8) {
						stone1[i][j].status = 0;
					}
				}
			}
		}
	}
	//判断是否向右挖
	for (i = 0; i < num_1_stonerow; i++) {
		for (j = 0; j < num_1_stonecol; j++) {
			if (stone1[i][j].center_x - man.center_x <= stone_width / 2 + man_width / 2 &&
				stone1[i][j].center_x - man.center_x >= (stone_width / 2 + man_width / 2) / 2 &&
				stone1[i][j].center_y - man.center_y == man_high / 2 - stone_high / 2 &&
				stone1[i][j].status != 0) {
				is_rightstone = 1;
				if (digr == 1) {
					man.center_x = stone1[i][j].center_x - stone_width / 2 - man_width / 2;
					static int speed_3 = 0;
					if (speed_3 < 100) {
						speed_3++;
					}
					else if (speed_3 == 100) {
						stone1[i][j].status++;
						speed_3 = 0;
					}
					if (stone1[i][j].status == 8) {
						stone1[i][j].status = 0;
					}
				}
			}
		}
	}
	//角色控制
	static int speed_1 = 0;
	if (speed_1 < 10) {
		speed_1++;
	}
	else if (speed_1 == 10) {
		man.v = man.v + G + fly_a;
		if (man.v >= 25)
			man.v = 25;
		if (man.v <= -15)
			man.v = -15;
		man.center_y = man.center_y + man.v;
		speed_1 = 0;
	}
}

void status_change() {
	int i, j;
	if (scene == 1) {
		if (fly_a == 0 && dig==0 && digl == 3 && digr == 3) {
			if (man_1 == 1) {
				clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);
				putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);
			}
			else if (man_1==2) {
				clearrectangle(man.center_x - fly_width / 2, man.center_y - fly_high / 2, man.center_x - fly_width / 2+fly_width, man.center_y - fly_high / 2 + fly_high);
				putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, fly_width + 1, fly_high + 1, &img_1, man.center_x - fly_width / 2, man.center_y - fly_high / 2);
			}
			putimage(man.left_x, man.top_y, &img_man_0, NOTSRCERASE);
			putimage(man.left_x, man.top_y, &img_man_00, SRCINVERT);
			man_1 = 1;
			FlushBatchDraw();
			Sleep(1);
		}
		//向上飞
		else if (fly_a < 0) {
			if (man_1 == 1) {
				clearrectangle(man.left_x,man.top_y, man.left_x+man_width,man.top_y+man_high);
				putimage(man.left_x,man.top_y, fly_width + 1, fly_high + 1, &img_1, man.left_x, man.top_y);
			}
			else if (man_1==2) {
				clearrectangle(man.center_x - fly_width / 2, man.center_y - fly_high / 2, man.center_x - fly_width / 2+fly_width, man.center_y - fly_high / 2 + fly_high);
				putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, fly_width + 1, fly_high + 1, &img_1, man.center_x - fly_width / 2, man.center_y - fly_high / 2);
			}
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);
			man_1 = 2;
			FlushBatchDraw();
			Sleep(1);
		}
		//没有挖时
		if (dig == 0 && digl == 3 && digr == 3 && fly_a == 0) {
			if (man_2 == 1) {
				if (man_1 == 1) {
					clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);
					putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);
				}
				else if (man_1 == 2) {
					clearrectangle(man.center_x - fly_width / 2, man.center_y - fly_high / 2, man.center_x - fly_width / 2 + fly_width, man.center_y - fly_high / 2 + fly_high);
					putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, fly_width + 1, fly_high + 1, &img_1, man.center_x - fly_width / 2, man.center_y - fly_high / 2);
				}
				putimage(man.left_x, man.top_y, &img_man_0, NOTSRCERASE);
				putimage(man.left_x, man.top_y, &img_man_00, SRCINVERT);
				man_2 = 1;
				FlushBatchDraw();
				Sleep(1);
			}
		}
		//向下挖	
		else if (dig == 1)
		{
			if (man_2 == 1)
			{
				clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);//用于从正面图案转变为向下挖图案
				putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);//用于消除黑色
			}
			else if (man_2 == 2)
			{
				clearrectangle(man.center_x - digd_width / 2, man.center_y - digd_high / 2, man.center_x - digd_width / 2 + digd_width, man.center_y - digd_high / 2 + digd_high);//保持向下挖状态时，消除上次的团
				putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, digd_width + 1, digd_high + 1, &img_1, man.center_x - digd_width / 2, man.center_y - digd_high / 2);//加入新的图案
			}
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_1, NOTSRCERASE);//人物正面黑白
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_2, SRCINVERT);//人物正面彩
			man_2 = 2;//当man为2时为向下挖图案
			FlushBatchDraw();
			Sleep(10);
		}

	}
	/*左边行走与左边挖土*/
	if (digl == 0 && scene == 1)
	{
		if (man_3 == 1)
		{
			clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);//当上一张图片是正面不动时清除原人物
			putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);//加入背景，用于消除黑色
		}
		else if (man_3 == 2)//用于从向左挖转变为向左走
		{
			clearrectangle(man.center_x - digl_width / 2, man.center_y - digl_high / 2, man.center_x - digl_width / 2 + digl_width, man.center_y - digl_high / 2 + digl_high);//消除飞行状态的图片
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, digl_width + 1, digl_high + 1, &img_1, man.center_x - digl_width / 2, man.center_y - digl_high / 2);//加上背景图
		}
		left_i++;
		man.center_x = man.center_x - 15;//人物的中心坐标x减少
		putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, left_i * man_width, 0, NOTSRCERASE);//放置向左走的黑白图片
		putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, left_i * man_width, 0, SRCINVERT);//放置向左走的彩图
		FlushBatchDraw();
		man_3 = 1;
		Sleep(100);
		if (left_i == 3)
			left_i = 0;
	}
	else if (digl == 1)
	{
		if (man_3 == 1)
		{
			clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);//用于从正面图案转变为向下挖图案
			putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);//用于消除黑色
		}
		else if (man_3 == 2)
		{
			clearrectangle(man.center_x - digl_width / 2, man.center_y - digl_high / 2, man.center_x - digl_width / 2 + digl_width, man.center_y - digl_high / 2 + digl_high);//消除飞行状态的图片
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, digl_width + 1, digl_high + 1, &img_1, man.center_x - digl_width / 2, man.center_y - digl_high / 2);//加上背景图
		}
		putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_1, NOTSRCERASE);//人物正面黑白
		putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_2, SRCINVERT);//人物正面彩
		man_3 = 2;//当man为2时为向下挖图案
		FlushBatchDraw();
		Sleep(1);
	}


	/*右边行走与右边挖土*/
	if (digr == 0 && scene == 1)
	{
		if (man_4 == 1)
		{
			clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);//当上一张图片是正面不动时清除原人物
			putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);//加入背景，用于消除黑色
		}
		else if (man_4 == 2)//用于从向左挖转变为向左走
		{
			clearrectangle(man.center_x - digr_width / 2, man.center_y - digr_high / 2, man.center_x - digr_width / 2 + digr_width, man.center_y - digr_high / 2 + digr_high);//消除飞行状态的图片
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, digr_width + 1, digr_high + 1, &img_1, man.center_x - digr_width / 2, man.center_y - digr_high / 2);//加上背景图
		}
		right_i++;//采用套图
		man.center_x = man.center_x + 15;//人物的中心坐标x减少
		putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, right_i * man_width, man_high, NOTSRCERASE);//放置向右走的黑白图片
		putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, right_i * man_width, man_high, SRCINVERT);//放置向右走的彩图
		FlushBatchDraw();
		man_4 = 1;
		Sleep(100);
		if (right_i == 3)
			right_i = 0;
	}
	else if (digr == 1)
	{
		if (man_4 == 1)
		{
			clearrectangle(man.left_x, man.top_y, man.left_x + man_width, man.top_y + man_high);//用于从正面图案转变为向下挖图案
			putimage(man.left_x, man.top_y, man_width + 1, man_high + 1, &img_1, man.left_x, man.top_y);//用于消除黑色
		}
		else if (man_4 == 2)
		{
			clearrectangle(man.center_x - digr_width / 2, man.center_y - digr_high / 2, man.center_x - digr_width / 2 + digr_width, man.center_y - digr_high / 2 + digr_high);//消除飞行状态的图片
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, digr_width + 1, digr_high + 1, &img_1, man.center_x - digr_width / 2, man.center_y - digr_high / 2);//加上背景图
		}
		putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_1, NOTSRCERASE);//人物正面黑白
		putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_2, SRCINVERT);//人物正面彩
		man_4 = 2;//当man为2时为向下挖图案
		FlushBatchDraw();
		Sleep(1);
	}
	fly_a = 0;//将加速度归为原值（按w改变）
	dig = 0;//向下挖回归原值（按s改变）
	digl = 3;//向左挖回归原值（按a改变）
	digr = 3;//向右挖回归原值（按d改变）
}

void updatewithinput(){
	//点击切换场景
	if (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONUP && scene == 0) {
			if (m.x <= 563 && m.x >= 316 && m.y <= 602 && m.y >= 570) {
				scene = 1;
			}
		}
	}
	if (scene == 1) {
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 0) {
			digl = 0;
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 1) {
			digl = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 0) {
			digr = 0;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 1) {
			digr = 1;
		}
		if (GetAsyncKeyState(0x57) & 0x8000)
		{
			fly_a = -2;
		}
		if (GetAsyncKeyState(0x53) & 0x8000)
		{
			dig = 1;
		}
	}
	is_leftstone = 0;
	is_rightstone = 0;
}

void gameover() {
	EndBatchDraw();
	getchar();
	closegraph();
}