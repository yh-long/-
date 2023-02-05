#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<fstream> 
#include<iostream>
#pragma comment(lib,"Winmm.lib")
using namespace std;

void startup();
void mapstartup();
void show();
void associated();
void updatewithoutinput();
void status_change();
void updatewithinput();
void startmenu();
void pausemenu();
void readRecordFile();
void writeRecordFile();
void gameover();

#define high 670//游戏界面
#define width 900
#define man_high 72//角色大小
#define man_width 64
#define stone_width 64//石块大小
#define stone_high 64
#define fly_high 92//飞行距离
#define fly_width 64
#define digl_high 78//左挖距离
#define digl_width 64
#define digr_width 64//右挖距离
#define digr_high 78
#define digd_high 80//下挖距离
#define digd_width 64
#define num_scene 3//关卡个数
#define num_stonerow 11//石块行数<第一关>
#define num_stonecol 14
#define stone_1_position 423//石块出现的位置<第一关>
#define stone_2_position 0
#define monster_high 60//怪物大小
#define monster_width 56
#define monster_num 3
#define bomb_high 64//炸弹范围
#define bomb_width 64
#define bomb_money 50//炸弹的价格


IMAGE img_bk;//定义背景图片
IMAGE img_ebg;//游戏结束图片
IMAGE img_success;//游戏成功时的图片
IMAGE img_1;//定义第一关的图片
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7, img_stone_99, img_stone_1314;;//定义石块的图片
IMAGE img_coal_1, img_coal_2, img_coal_3, img_coal_4, img_coal_5, img_coal_0;//定义煤块的图片
IMAGE img_copper_1, img_copper_2, img_copper_3, img_copper_4, img_copper_5, img_copper_6, img_copper_0;//定义铜块的图片
IMAGE img_silver_1, img_silver_2, img_silver_3, img_silver_4, img_silver_5, img_silver_0;//定义银块的图片
IMAGE img_man_0, img_man_00;//定义挖地小子的正面图片 0表示黑白版 00表示彩版
IMAGE img_man_1, img_man_2;//定义挖地小子左右走的图片 1表示黑白版 2表示彩版
IMAGE img_shoes_1, img_shoes_2;//定义火箭鞋图片 1表示黑白版 2表示彩版
IMAGE img_digl_1, img_digl_2;//定义挖地小子向左挖的照片  1表示黑白版 2表示彩版
IMAGE img_digright_1, img_digright_2;//定义挖地小子向右挖的照片  1表示黑白版 2表示彩版
IMAGE img_digdown_1, img_digdown_2;//定义挖地小子向下挖的照片  1表示黑白版 2表示彩版
IMAGE img_shop;//商店
IMAGE img_bomb_1, img_bomb_boom, img_bwbomb_boom;//炸弹
IMAGE img_bwbomb_1;//炸弹黑白
IMAGE img_energy;//能量图片
IMAGE img_monsterrun_0, img_monsterrun_00;//定义怪物走路的图片  0表示黑白版  00表示彩版
IMAGE img_oxygen;//氧气图片
IMAGE img_ener_oxy1;//能氧黑白
IMAGE img_ener_oxy2;//能氧
MOUSEMSG m;//定义一个鼠标变量

class thing {
public:
	float left_x;
	float left_y;
	float right_x;
	float right_y;
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
	float center_x;
	float center_y;
	float status;
	//人
	int v;
	int bomb;
	int scene;
	int oxygen;
	int energy;
	int oxygen_level;//氧气等级
	int energy_level;//能量等级
	//怪
	int direction;
};
thing man;
thing monster[monster_num];//定义怪物

class stone {
public:
	float left_x;
	float left_y;
	float right_x;
	float right_y;
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
	float center_x;
	float center_y;
	int status;
	int scene;
};
stone stone1[num_scene][num_stonerow][num_stonecol];
stone bomb;

int scene;//创建
int left_i;//移动变量
int right_i;
int bomb_i;
int G;
int fly_a;//飞行判断
int dig;//挖地判断
int digl;
int digr;
int flyleft;
int flyright;
int is_leftstone;//石块判断
int is_rightstone;
int is_downstone;
int is_flyleftstone;
int is_flyrightstone;
int score;
int put_bomb;
int mleft_i[monster_num];//记录怪物向左移动的图片
int mright_i[monster_num];//记录怪物向右移动的图片
float energy_i;//能量变化横坐标
float energy_j;//能量变化纵坐标
float oxygen_i;
float oxygen_j;

int main() {
	//printf("welcome to you");
	startup();
	mapstartup();
	while (1) {
		show();
		associated();
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
	loadimage(&img_ebg, _T("..//images//endbackground.jpg"));//导入游戏结束界面
	loadimage(&img_success, _T("..//images//success.jpg"));//导入游戏胜利界面
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
	loadimage(&img_stone_99, _T("..//images//stone_99.jpg"));//导入破碎99的图片
	loadimage(&img_stone_1314, _T("..//images//stone_1314.jpg"));//导入破碎99的图片
	loadimage(&img_coal_1, _T("..//images//coal_1.jpg"));//导入完整煤
	loadimage(&img_coal_2, _T("..//images//coal_2.jpg"));//导入破碎1煤
	loadimage(&img_coal_3, _T("..//images//coal_3.jpg"));//导入破碎2,煤
	loadimage(&img_coal_4, _T("..//images//coal_4.jpg"));//导入破碎3煤
	loadimage(&img_coal_5, _T("..//images//coal_5.jpg"));//导入破碎4煤
	loadimage(&img_coal_0, _T("..//images//coal_0.jpg"));//完全破碎的煤
	loadimage(&img_copper_1, _T("..//images//Copper_1.jpg"));//导入完整铜
	loadimage(&img_copper_2, _T("..//images//Copper_2.jpg"));//导入破碎1铜
	loadimage(&img_copper_3, _T("..//images//Copper_3.jpg"));//导入破碎2铜
	loadimage(&img_copper_4, _T("..//images//Copper_4.jpg"));//导入破碎3铜
	loadimage(&img_copper_5, _T("..//images//Copper_5.jpg"));//导入破碎4铜
	loadimage(&img_copper_6, _T("..//images//Copper_6.jpg"));//导入破碎5铜
	loadimage(&img_copper_0, _T("..//images//Copper_0.jpg"));//完全破碎的铜
	loadimage(&img_silver_1, _T("..//images//silver_1.jpg"));//导入完整银
	loadimage(&img_silver_2, _T("..//images//silver_2.jpg"));//导入破碎1银
	loadimage(&img_silver_3, _T("..//images//silver_3.jpg"));//导入破碎2银
	loadimage(&img_silver_4, _T("..//images//silver_4.jpg"));//导入破碎3银
	loadimage(&img_silver_5, _T("..//images//silver_5.jpg"));//导入破碎4银
	loadimage(&img_silver_0, _T("..//images//silver_0.jpg"));//完全破碎的银
	loadimage(&img_shoes_1, _T("..//images//shoes_1.jpg"));//导入上升的图片黑白版
	loadimage(&img_shoes_2, _T("..//images//shoes_2.jpg"));//导入上升的图片彩版
	loadimage(&img_digl_1, _T("..//images//digleftperson_1.jpg"));//导入向左挖的图片的黑白版
	loadimage(&img_digl_2, _T("..//images//digleftperson_2.jpg"));//导入向左挖的图片的彩版
	loadimage(&img_digright_1, _T("..//images//digrightperson_1.jpg"));//导入向右挖的图片的黑白版
	loadimage(&img_digright_2, _T("..//images//digrightperson_2.jpg"));//导入向右挖的图片的彩版
	loadimage(&img_digdown_1, _T("..//images//digdownperson_1.jpg"));//导入向下挖的图片的黑白版
	loadimage(&img_digdown_2, _T("..//images//digdownperson_2.jpg"));//导入向下挖的图片的彩版
	loadimage(&img_shop, _T("..//images//shop.jpg"));//导入商店的图片
	loadimage(&img_monsterrun_0, _T("..//images//monsterrun_0.jpg"));//导入怪物走路图片的彩版
	loadimage(&img_monsterrun_00, _T("..//images//monsterrun_00.jpg"));//导入怪物走路图片的黑白版
	loadimage(&img_energy, _T("..//images//energy.jpg"));//导入能量的图片
	loadimage(&img_bomb_1, _T("..//images//bomb_1.jpg"));//炸弹原始
	loadimage(&img_bwbomb_1, _T("..//images//bwbomb_1.jpg"));//炸弹原始黑白
	loadimage(&img_bomb_boom, _T("..//images//bomb_boom.jpg"));//炸弹爆炸过程中过程图片
	loadimage(&img_bwbomb_boom, _T("..//images//bwbomb_boom.jpg"));//炸弹爆炸过程中过程黑白图片
	loadimage(&img_energy, _T("..//images//energy.jpg"));//导入能量的图片
	loadimage(&img_oxygen, _T("..//images//oxygen.jpg"));//导入能量的图片
	loadimage(&img_ener_oxy1, _T("..//images//ener_oxy1.jpg"));//导入能氧黑白照
	loadimage(&img_ener_oxy2, _T("..//images//ener_oxy2.jpg"));//导入能氧
	mciSendString(_T("open ..//images//bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//导入背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环背景音乐

	scene = 0;
	fly_a = 1;
	is_leftstone = 0;
	is_rightstone = 0;
	is_downstone = 0;
	is_flyleftstone = 0;
	is_flyrightstone = 0;
	digl = 0;
	digr = 0;
	flyleft = 0;
	flyright = 0;
	put_bomb = 0;
	//初始化炸弹

	bomb.center_x = -1000;
	bomb.center_y = -1000;
	bomb.left_x = -1000;
	bomb.left_y = -1000;
	bomb.right_x = -1000;
	bomb.right_y = -1000;
	bomb.top_x = -1000;
	bomb.top_y = -1000;
	bomb.bottom_x = -1000;
	bomb.bottom_y = -1000;
	bomb.status = 0;
	bomb.scene = 100;
	int i, j, k;
	//初始化石块位置
	for (k = 0; k < 3; k++) {
		for (i = 0; i < num_stonerow; i++) {
			for (j = 0; j < num_stonecol; j++) {
				stone1[k][i][j].center_x = -1000;
				stone1[k][i][j].center_y = -1000;
				stone1[k][i][j].top_x = -1000;
				stone1[k][i][j].top_y = -1000;
				stone1[k][i][j].bottom_x = -1000;
				stone1[k][i][j].bottom_y = -1000;
				stone1[k][i][j].left_x = -1000;
				stone1[k][i][j].left_y = -1000;
				stone1[k][i][j].right_x = -1000;
				stone1[k][i][j].right_y = -1000;
				stone1[k][i][j].status = -1000;
			}
		}
	}
	//初始化第一关石块位置
	for (i = 7; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			stone1[1][i][j].center_x = stone_width / 2 + j * stone_width;
			stone1[1][i][j].center_y = stone_1_position + stone_high / 2 + (i - 7) * stone_high;
			stone1[1][i][j].top_x = stone_width / 2 + j * stone_width;
			stone1[1][i][j].top_y = stone_1_position + stone_high * (i - 7);
			stone1[1][i][j].bottom_x = stone_width / 2 + j * stone_width;
			stone1[1][i][j].bottom_y = stone_1_position + stone_high * (i - 7);
			stone1[1][i][j].left_x = stone_width * j;
			stone1[1][i][j].left_y = stone_1_position + stone_high / 2 * (i - 7);
			stone1[1][i][j].right_x = stone_width * j + stone_width;
			stone1[1][i][j].right_y = stone_1_position + stone_high / 2 * (i - 7);
			stone1[1][i][j].status = 1;
		}
	}

	//初始化第二关石块位置
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			stone1[2][i][j].center_x = stone_width / 2 + j * stone_width;
			stone1[2][i][j].center_y = stone_2_position + stone_high / 2 + i * stone_high;
			stone1[2][i][j].top_x = stone_width / 2 + j * stone_width;
			stone1[2][i][j].top_y = stone_2_position + stone_high * i;
			stone1[2][i][j].bottom_x = stone_width / 2 + j * stone_width;
			stone1[2][i][j].bottom_y = stone_2_position + stone_high * i;
			stone1[2][i][j].left_x = stone_width * j;
			stone1[2][i][j].left_y = stone_2_position + stone_high / 2 * i;
			stone1[2][i][j].right_x = stone_width * j + stone_width;
			stone1[2][i][j].right_y = stone_2_position + stone_high / 2 * i;
			stone1[2][i][j].status = 1;
		}
	}

	//角色初始化位置
	man.center_x = width / 2;
	man.center_y = stone_1_position - man_high / 2;
	man.bomb = 0;//初始没有炸弹
	man.status = 1;//初始挖地小子活着
	man.oxygen_level = 1;//氧气等级	
	man.energy_level = 1;//能量等级
	man.oxygen = 1;//氧气包
	man.energy = 1;//能量包
	//怪物初始化位置
	for (i = 0; i < monster_num; i++) {
		monster[0].center_x = stone_width;
		monster[0].center_y = stone_high * 9 - monster_high / 2;
		monster[1].center_x = stone_width * 6;
		monster[1].center_y = stone_high * 4 - monster_high / 2;
		monster[2].center_x = stone_width * 10;
		monster[2].center_y = stone_high * 7 - monster_high / 2;
		monster[i].direction = 0;
		monster[i].status = 1;
	}
	//角色移动参数
	left_i = 0;
	right_i = 0;
	bomb_i = 0;
	man.v = 0;
	score = 500;
	energy_i = 120;//能量柱的长度
	energy_j = 19;
	oxygen_i = 107;//氧气柱的长度
	oxygen_j = 54;
	BeginBatchDraw();
}

void mapstartup() {
	int i, j;
	for (i = 7; i < 11; i++)
		for (j = 0; j < 2; j++)
		{
			stone1[1][i][j].status = 99;
		}
	for (i = 7; i < 8; i++)
		for (j = 8; j < 14; j++)
		{
			stone1[1][i][j].status = 99;
		}
	for (i = 9; i < 10; i++)
		for (j = 4; j < 6; j++)
		{
			stone1[1][i][j].status = 11;
		}
	for (i = 10; i < 11; i++)
		for (j = 2; j < 7; j++)
		{
			stone1[1][i][j].status = 11;
		}
	for (i = 10; i < 11; i++)
		for (j = 9; j < 14; j++)
		{
			stone1[1][i][j].status = 11;
		}
	for (i = 8; i < 9; i++)
		for (j = 1; j < 5; j++)//怪物
		{
			stone1[2][i][j].status = 0;
		}
	for (i = 3; i < 4; i++)
		for (j = 5; j < 9; j++)//怪物
		{
			stone1[2][i][j].status = 0;
		}
	for (i = 6; i < 7; i++)
		for (j = 9; j < 13; j++)//怪物
		{
			stone1[2][i][j].status = 0;
		}
	for (i = 2; i < 6; i++)
		for (j = 3; j < 5; j++)
		{
			stone1[2][i][j].status = 31;
		}
	for (i = 1; i < 5; i++)
		for (j = 12; j < 13; j++)
		{
			stone1[2][i][j].status = 11;
		}
	for (i = 9; i < 10; i++)
		for (j = 1; j < 5; j++)
		{
			stone1[2][i][j].status = 21;
		}
	for (i = 7; i < 8; i++)
		for (j = 7; j < 14; j++)
		{
			stone1[2][i][j].status = 21;
		}
	for (i = 6; i < 7; i++)
		for (j = 5; j < 9; j++)
		{
			stone1[2][i][j].status == 31;
		}
}

void associated() {
	int i;
	/*人物坐标关联 每个值都与人物坐标中心相关 增强坐标的相关性*/
	man.left_x = man.center_x - man_width / 2;
	man.left_y = man.center_y;
	man.right_x = man.center_x + man_width / 2;
	man.right_y = man.center_y;
	man.top_x = man.center_x;
	man.top_y = man.center_y - man_high / 2;
	man.bottom_x = man.center_x;
	man.bottom_y = man.center_y + man_high / 2;
	/*怪物坐标关联 每个值都与怪物坐标中心相关 增强坐标的相关性*/
	for (i = 0; i < monster_num; i++)
	{
		monster[i].left_x = monster[i].center_x - monster_width / 2;
		monster[i].left_y = monster[i].center_y;
		monster[i].right_x = monster[i].center_x + monster_width / 2;
		monster[i].right_y = monster[i].center_y;
		monster[i].top_x = monster[i].center_x;
		monster[i].top_y = monster[i].center_y - monster_high / 2;
		monster[i].bottom_x = monster[i].center_x;
		monster[i].bottom_y = monster[i].center_y - monster_high / 2;
	}
}

void show() {
	int i, j, k = 0;
	if (scene == 0) {
		putimage(0, 0, &img_bk);
		FlushBatchDraw();
	}
	while (scene == -2)
		startmenu();
	while (scene == -3)
		pausemenu();
	if (scene == 1) {
		putimage(0, 0, &img_1);
		k = 1;
	}
	else if (scene == 2) {
		putimage(0, 0, &img_1);
		k = 2;
	}
	for (i = 0; i < num_stonerow; i++)
	{
		for (j = 0; j < num_stonecol; j++) {
			//石块状态
			if (stone1[k][i][j].status == 1) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_1);
			}
			else if (stone1[k][i][j].status == 2) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_2);
			}
			else if (stone1[k][i][j].status == 3) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_3);
			}
			else if (stone1[k][i][j].status == 4) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_4);
			}
			else if (stone1[k][i][j].status == 5) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_5);
			}
			else if (stone1[k][i][j].status == 6) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_6);
			}
			else if (stone1[k][i][j].status == 7) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_7);
			}
			else if (stone1[k][i][j].status == 0) {
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_0);
			}
			//煤块状态
			else if (stone1[k][i][j].status == 11)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_1);
			else if (stone1[k][i][j].status == 12)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_2);
			else if (stone1[k][i][j].status == 13)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_3);
			else if (stone1[k][i][j].status == 14)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_4);
			else if (stone1[k][i][j].status == 15)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_5);
			else if (stone1[k][i][j].status == 16)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_coal_0);
			//铜块状态
			else if (stone1[k][i][j].status == 21)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_1);
			else if (stone1[k][i][j].status == 22)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_2);
			else if (stone1[k][i][j].status == 23)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_3);
			else if (stone1[k][i][j].status == 24)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_4);
			else if (stone1[k][i][j].status == 25)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_5);
			else if (stone1[k][i][j].status == 26)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_6);
			else if (stone1[k][i][j].status == 27)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_copper_0);
			//银块状态
			else if (stone1[k][i][j].status == 31)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_1);
			else if (stone1[k][i][j].status == 32)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_2);
			else if (stone1[k][i][j].status == 33)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_3);
			else if (stone1[k][i][j].status == 34)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_4);
			else if (stone1[k][i][j].status == 35)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_5);
			else if (stone1[k][i][j].status == 36)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_silver_0);
			else if (stone1[k][i][j].status == 99)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_99);
			else if (stone1[k][i][j].status == -1)
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_1314);//砖块初始化
		}
	}
	//商店
	if (scene == -1) {
		putimage(0, 0, &img_shop);
	}
	//能量槽与氧气槽
	if (scene == 1 || scene == 2) {
		putimage(735, 213, energy_i, energy_j, &img_energy, 0, 0);
		putimage(740, 246, oxygen_i, oxygen_j, &img_oxygen, 0, 0);
	}
	if (scene == 2)
	{
		putimage(width - 610, 0, &img_ener_oxy1, NOTSRCERASE);
		putimage(width - 610, 0, &img_ener_oxy2, SRCINVERT);
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
	//怪物五元组
	monster[i].left_x = monster[i].center_x - monster_width / 2;
	monster[i].left_y = monster[i].center_y;
	monster[i].right_x = monster[i].center_x + monster_width / 2;
	monster[i].right_y = monster[i].center_y;
	monster[i].top_x = monster[i].center_x;
	monster[i].top_y = monster[i].center_y - monster_high / 2;
	monster[i].bottom_x = monster[i].center_x;
	monster[i].bottom_y = monster[i].center_y - monster_high / 2;
	//关卡同步
	if (scene != -3 && scene != -2 && scene != 0)
		man.scene = scene;
	if (energy_i <= 0)
		fly_a = 0;
}

void updatewithoutinput() {
	//确定角色的位置
	int i, j, k;
	G = 1;
	if (scene == 1)
		k = 1;
	else if (scene == 2)
		k = 2;
	else
		k = 1;
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			//判断角色是否站在石块上
			if (stone1[k][i][j].center_y - man.center_y <= man_high / 2 + stone_high / 2 &&
				stone1[k][i][j].center_y - man.center_y >= (man_high / 2 + stone_high / 2) / 2 &&
				man.center_x <= stone1[k][i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
				man.center_x >= stone1[k][i][j].center_x - man_width / 2 - stone_width / 2 + 10 &&
				stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36) {
				is_downstone = 1;
				G = 0;
				man.v = 0;
				man.center_y = stone1[k][i][j].center_y - man_high / 2 - stone_high / 2;
				break;
			}
		}
	}
	//判断角色飞行时上方是否有石块
	if (fly_a == -2) {
		for (i = 0; i < num_stonerow; i++) {
			for (j = 0; j < num_stonecol; j++) {
				if (man.center_y - stone1[k][i][j].center_y <= stone_high - man_high / 2 + stone_high / 2 &&
					man.center_y - stone1[k][i][j].center_y >= (stone_high - man_high / 2 + stone_high / 2) / 2 &&
					man.center_x <= stone1[k][i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
					man.center_x >= stone1[k][i][j].center_x - man_width / 2 - stone_width / 2 + 10 &&
					stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36) {
					fly_a = -1;
					man.v = 0;
					break;
				}
			}
		}
	}
	//判断是否向下挖
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (stone1[k][i][j].center_y - man.center_y <= man_high / 2 + stone_high / 2 &&
				stone1[k][i][j].center_y - man.center_y >= (man_high / 2 + stone_high / 2) / 2 &&
				man.center_x <= stone1[k][i][j].center_x + man_width / 2 + stone_width / 2 - 10 &&
				man.center_x >= stone1[k][i][j].center_x - man_width / 2 - stone_width / 2 + 10)
			{
				if (dig == 1 && is_downstone == 1 && stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16
					&& stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36) {
					man.center_x = stone1[k][i][j].center_x;
					static int speed_2 = 0;
					if (speed_2 < 60) {
						speed_2++;
					}
					else if (speed_2 == 60) {
						stone1[k][i][j].status++;
						speed_2 = 0;
					}
					if (stone1[k][i][j].status == 8) {
						stone1[k][i][j].status = 0;
					}
					if (stone1[k][i][j].status == 100) {
						stone1[k][i][j].status = 99;
					}
				}
			}
		}
	}
	//判断是否向左挖
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (man.center_x - stone1[k][i][j].center_x <= stone_width / 2 + man_width / 2 &&
				man.center_x - stone1[k][i][j].center_x >= (stone_width / 2 + man_width / 2) / 2 &&
				stone1[k][i][j].center_y - man.center_y == man_high / 2 - stone_high / 2 &&
				stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36) {
				is_leftstone = 1;
				if (digl == 1) {
					man.center_x = stone1[k][i][j].center_x + stone_width / 2 + man_width / 2;
					static int speed_3 = 0;
					if (speed_3 < 60) {
						speed_3++;
					}
					else if (speed_3 == 60) {
						stone1[k][i][j].status++;
						speed_3 = 0;
					}
					if (stone1[k][i][j].status == 8) {
						stone1[k][i][j].status = 0;
					}
					if (stone1[k][i][j].status == 100) {
						stone1[k][i][j].status = 99;
					}
				}
			}
		}
	}
	//判断是否向右挖
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (stone1[k][i][j].center_x - man.center_x <= stone_width / 2 + man_width / 2 &&
				stone1[k][i][j].center_x - man.center_x >= (stone_width / 2 + man_width / 2) / 2 &&
				stone1[k][i][j].center_y - man.center_y == man_high / 2 - stone_high / 2 &&
				stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36) {
				is_rightstone = 1;
				if (digr == 1) {
					man.center_x = stone1[k][i][j].center_x - stone_width / 2 - man_width / 2;
					static int speed_3 = 0;
					if (speed_3 < 60) {
						speed_3++;
					}
					else if (speed_3 == 60) {
						stone1[k][i][j].status++;
						speed_3 = 0;
					}
					if (stone1[k][i][j].status == 8) {
						stone1[k][i][j].status = 0;
					}
					if (stone1[k][i][j].status == 100) {
						stone1[k][i][j].status = 99;
					}
				}
			}
		}
	}
	//判断飞行时左边是否有石块
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (man.left_x == stone1[k][i][j].right_x && man.left_y - stone1[k][i][j].right_y <= man_high / 2 + stone_high / 2 - 12 &&
				man.left_y - stone1[k][i][j].right_y <= -man_high / 2 - stone_high / 2 + 12 &&
				stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36 && fly_a < 0) {
				is_flyleftstone = 1;
				cout << is_flyleftstone << endl;
			}
		}
	}
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (man.right_x == stone1[k][i][j].left_x && man.right_y - stone1[k][i][j].left_y <= man_high / 2 + stone_high / 2 - 12 &&
				man.right_y - stone1[k][i][j].left_y <= -man_high / 2 - stone_high / 2 + 12 &&
				stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36 && fly_a < 0) {
				is_flyrightstone = 1;
				cout << is_flyrightstone+1 << endl;
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
	//怪物移动
	int m;
	for (m = 0; m < monster_num; m++)
		for (i = 0; i < num_stonerow; i++)
			for (j = 0; j < num_stonecol; j++)
			{
				if (monster[m].center_x - stone1[k][i][j].center_x <= stone_width / 2 + monster_width / 2 &&
					monster[m].center_x - stone1[k][i][j].center_x >= (stone_width / 2 + monster_width / 2) / 2 &&
					monster[m].center_y - stone1[k][i][j].center_y == stone_high / 2 - monster_high / 2 &&
					stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36)
				{
					monster[m].direction = 0;//左端存在砖块向右走  
				}
			}
	for (m = 0; m < monster_num; m++)
		for (i = 0; i < num_stonerow; i++)
			for (j = 0; j < num_stonecol; j++)
			{
				if (stone1[k][i][j].center_x - monster[m].center_x <= stone_width / 2 + monster_width / 2 &&
					stone1[k][i][j].center_x - monster[m].center_x >= (stone_width / 2 + monster_width / 2) / 2 &&
					monster[m].center_y - stone1[k][i][j].center_y == stone_high / 2 - monster_high / 2 &&
					stone1[k][i][j].status != 0 && stone1[k][i][j].status != 16 && stone1[k][i][j].status != 27 && stone1[k][i][j].status != 36)
				{
					monster[m].direction = 1;//右端存在砖块向左走   
				}
			}
	//拾取物品
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (stone1[k][i][j].status == 16 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//拾取煤块
			{
				stone1[k][i][j].status = 0;
				score = score + 10;//一个煤块10分
			}
			if (stone1[k][i][j].status == 27 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//拾取铜块
			{
				stone1[k][i][j].status = 0;
				score = score + 20;//一个铜块20分
			}
			if (stone1[k][i][j].status == 36 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//拾取银块
			{
				stone1[k][i][j].status = 0;
				score = score + 50;//一个银块50分
			}
		}
	}
	/*放置炸弹并控制炸弹的变化*/
	if (put_bomb == 1) {
		bomb.center_x = man.center_x;
		bomb.center_y = man.center_y;
	}
	if (bomb.center_x < 900 && bomb.center_x>0 && bomb.center_y < 670 && bomb.center_y>0) {
		static int speed_4 = 0;
		if (speed_4 < 200) {
			speed_4++;
		}
		else if (speed_4 == 200) {
			bomb.status++;
			speed_4 = 0;
		}
	}
	/*炸弹炸死怪物的判定*/
	for (i = 0; i < monster_num; i++) {
		if (bomb.status >= 6 && bomb.center_x - monster[i].center_x <= bomb_width / 2 + monster_width / 2 &&
			bomb.center_x - monster[i].center_x >= -bomb_width / 2 - monster_width / 2 &&
			bomb.center_y - monster[i].center_y <= bomb_high - monster_high + 4 &&
			bomb.center_y - monster[i].center_y >= -bomb_high + monster_high - 4) {
			score = (score + 500 * monster[i].status);
			monster[i].status = 0;
		}
	}
	/*人物碰到怪物掉血*/
	for (i = 0; i < monster_num; i++)
	{
		if (man.center_x - monster[i].center_x <= man_width / 2 + monster_width / 2
			&& man.center_x - monster[i].center_x >= -man_width / 2 - monster_width / 2 && man.center_y - monster[i].center_y <= man_high - monster_high + 4
			&& man.center_y - monster[i].center_y >= -man_high + monster_high - 4)
		{
			oxygen_i = oxygen_i - 0.1;//氧气柱的变化
		}
	}
	/*炸弹炸人物的判定*/
	if (bomb.status >= 6 && bomb.center_x - man.center_x <= bomb_width / 2 + man_width / 2 - 4
		&& bomb.center_x - man.center_x >= -bomb_width / 2 - man_width / 2 + 4 && bomb.center_y - man.center_y <= bomb_high / 2 + man_high / 2 - 4
		&& bomb.center_y - man.center_y >= -bomb_high / 2 - man_high / 2 + 4)
	{
		oxygen_i = oxygen_i - 4;//氧气柱的变化
	}
	/*煤块的恢复*/
	static int speed_10[num_scene][num_stonerow][num_stonecol] = { 0 };
	for (i = 0; i < num_stonerow; i++)
		for (j = 0; j < num_stonerow; j++)
		{
			if (stone1[k][i][j].status == -1)//砖块的状态变为完全破碎的
			{
				speed_10[k][i][j]++;
				if (speed_10[k][i][j] == 4000)//砖块恢复的速度
				{
					stone1[k][i][j].status = 11;//只能恢复一次
					speed_10[k][i][j] = 0;
				}
			}
		}
	/*能量消耗与恢复*/
	if (fly_a < 0)
	{
		if (energy_i > 0)
			energy_i = energy_i - 0.1;
	}
	else if (fly_a == 0)
	{
		if (energy_i < 120)
			energy_i = energy_i + 0.03;
	}
	/*氧气消耗与恢复*/
	if (scene == 1 && man.top_y <= stone_1_position)
	{
		if (oxygen_i <= 107)
			oxygen_i = oxygen_i + 0.03;
	}
	if ((scene == 1 && man.top_y > stone_1_position) || scene == 2)
	{
		oxygen_i = oxygen_i - 0.01;
	}
	/*人物死亡判定*/
	if (oxygen_i < 0)
	{
		man.status = 0;
		scene = -4; //-4游戏结束
		putimage(0, 0, &img_ebg);//游戏失败
	}
	/*人物胜利判定*/
	for (i = 0; i < monster_num; i++)
	{
		if (monster[i].status != 0)
			break;
		scene = -5; //-5游戏成功 
		putimage(0, 0, &img_success);//游戏成功
	}
	/*显示分数*/
	if (scene == 1 || scene == 2 || scene == -1)
	{
		TCHAR s[10], s1[10], s2[10], s3[10], s4[10], s5[10];
		setbkmode(TRANSPARENT);//背景透明
		_stprintf(s, _T("%d"), score);
		_stprintf(s1, _T("%d"), man.bomb);
		_stprintf(s2, _T("%d"), man.energy_level);
		_stprintf(s3, _T("%d"), man.oxygen_level);
		_stprintf(s4, _T("%d"), man.energy);
		_stprintf(s5, _T("%d"), man.oxygen);
		outtextxy(90, 12, s);
		outtextxy(150, 40, s1);
		outtextxy(150, 65, s2);
		outtextxy(130, 90, s3);
		outtextxy(100, 115, s4);
		outtextxy(100, 140, s5);
		outtextxy(10, 40, _T("炸弹个数："));
		outtextxy(10, 65, _T("喷火器等级："));
		outtextxy(10, 90, _T("体力等级："));
		outtextxy(10, 115, _T("能量包："));
		outtextxy(10, 140, _T("氧气包："));
		settextstyle(25, 0, _T("楷体"));
		settextcolor(BLACK);
	}
	/*分数自动增加*/
	{
		static int speed_9 = 0;
		if (speed_9 < 180)
			speed_9++;
		else if (speed_9 == 180)
		{
			speed_9 = 0;
			score = score + 1;
		}
	}
	/*游戏限制边界*/
	if (scene == 1)
	{
		if (man.left_x < 0)//限制左边界
			man.center_x = man_width / 2;
		else if (man.right_x > 900)//限制右边界
			man.center_x = 900 - man_width / 2;
		else if (man.top_y < 0)//限制上边界
			man.center_y = man_high / 2;
	}
	/*关卡跳跃*/
	if (scene == 1 && man.bottom_y > high)//第一关到第二关
	{
		scene = 2;
		man.center_y = -man_width / 2;
	}
	else if (scene == 2 && man.bottom_y < 0)//从第二关返回第一关
	{
		scene = 1;
		man.center_y = high - man_high;
	}
}

void status_change() {
	int i, j;
	if (scene == 1 || scene == 2) {
		if (fly_a == 0 && dig == 0 && digl == 3 && digr == 3) {
			putimage(man.left_x, man.top_y, &img_man_0, NOTSRCERASE);
			putimage(man.left_x, man.top_y, &img_man_00, SRCINVERT);
			Sleep(1);
		}
		//向上飞
		else if (fly_a < 0 && flyleft == 0 && flyright == 0) {
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);
			Sleep(1);
		}
		//左飞
		else if (fly_a < 0 && flyleft == 1)
		{
			if (is_flyleftstone == 0) {
				cout << "左" << endl;
				man.center_x = man.center_x - 1;//人物的中心坐标x减少
			}	
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			Sleep(1);
		}
		//右飞
		else if (fly_a < 0 && flyright == 1)
		{
			if (is_flyrightstone == 0) {
				man.center_x = man.center_x + 1;//人物的中心坐标x减少
			}	
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			
			Sleep(1);
		}
		//下挖
		else if (dig == 1)
		{
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_1, NOTSRCERASE);//人物正面黑白
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_2, SRCINVERT);//人物正面彩
			//FlushBatchDraw();
			//Sleep(10);
		}
		//左边行走
		else if (digl == 0)
		{
			man.center_x = man.center_x - 15;//人物的中心坐标x减少
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, left_i * man_width, 0, NOTSRCERASE);//放置向左走的黑白图片
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, left_i * man_width, 0, SRCINVERT);//放置向左走的彩图
			FlushBatchDraw();
			left_i++;
			Sleep(100);
			if (left_i == 3)
				left_i = 0;
		}
		//左挖
		else if (digl == 1)
		{
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_1, NOTSRCERASE);//人物正面黑白
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_2, SRCINVERT);//人物正面彩
			Sleep(1);
		}

		//右边行走
		else if (digr == 0)
		{
			man.center_x = man.center_x + 15;//人物的中心坐标x减少
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, right_i * man_width, man_high, NOTSRCERASE);//放置向右走的黑白图片
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, right_i * man_width, man_high, SRCINVERT);//放置向右走的彩图
			right_i++;
			Sleep(100);
			if (right_i == 3)
				right_i = 0;
		}
		//右挖
		else if (digr == 1)
		{
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_1, NOTSRCERASE);//人物正面黑白
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_2, SRCINVERT);//人物正面彩
			Sleep(1);
		}
	}
	if (bomb.status <= 5 && scene == bomb.scene)
	{
		putimage(bomb.center_x - 32, bomb.center_y - 32, &img_bwbomb_1, NOTSRCERASE);
		putimage(bomb.center_x - 32, bomb.center_y - 32, &img_bomb_1, SRCINVERT);
	}
	else if (bomb.status >= 6)
	{
		if (scene == bomb.scene)
		{
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bwbomb_boom, bomb_i * bomb_width, 0, NOTSRCERASE);//放置炸弹的黑白图片
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bomb_boom, bomb_i * bomb_width, 0, SRCINVERT);//放置炸弹的彩图
		}
		bomb_i++;
		Sleep(100);
		if (bomb_i == 8)
		{
			bomb.status = 0;
			bomb.center_x = -1000;
			bomb.center_y = -1000;
			bomb_i = 0;
			man.bomb--;//少一个炸弹
		}
	}
	/*怪物行走*/
	static int speed_5 = 0, speed_6 = 0;
	if (scene == 2)
	{
		if (speed_5 < 60)
			speed_5++;
		if (speed_6 < 60)
			speed_6++;
		for (i = 0; i < monster_num; i++)
		{
			if (monster[i].direction == 1 && monster[i].status == 1)
			{
				if (speed_5 == 60)
				{
					monster[i].center_x = monster[i].center_x - 10;//怪物的中心坐标x减少
					mleft_i[i]++;
					speed_5 = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mleft_i[i] * monster_width, monster_high, NOTSRCERASE);//放置向左走的黑白图片
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mleft_i[i] * monster_width, monster_high, SRCINVERT);//放置向左走的彩图

				if (mleft_i[i] == 3)
					mleft_i[i] = 0;
			}
			else if (monster[i].direction == 0 && monster[i].status == 1)
			{
				if (speed_6 == 60)
				{
					monster[i].center_x = monster[i].center_x + 10;//怪物的中心坐标x增加
					mright_i[i]++;
					speed_6 = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mright_i[i] * monster_width, 0, NOTSRCERASE);//放置向左走的黑白图片
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mright_i[i] * monster_width, 0, SRCINVERT);//放置向左走的彩图

				if (mright_i[i] == 3)
					mright_i[i] = 0;
			}
		}
	}
	FlushBatchDraw();
	fly_a = 0;//将加速度归为原值（按w改变）
	dig = 0;//向下挖回归原值（按s改变）
	digl = 3;//向左挖回归原值（按a改变）
	digr = 3;//向右挖回归原值（按d改变）
	flyleft = 0;//向左飞回归原值
	flyright = 0;//向右飞回归原值
	put_bomb = 0;
}

void updatewithinput() {
	//点击切换场景
	if (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONUP && scene == 0) {
			if (m.x <= 563 && m.x >= 316 && m.y <= 602 && m.y >= 570) {
				scene = -2;
			}
		}
	}
	if (scene == 1 || scene == 2) {
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 0 && is_downstone == 1) {//a
			digl = 0;
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 1) {
			digl = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 0 && is_downstone == 1) {//d
			digr = 0;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 1) {
			digr = 1;
		}
		if (GetAsyncKeyState(0x57) & 0x8000)//w
		{
			fly_a = -2;
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 0 && is_downstone == 0)//左飞
		{
			flyleft = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 0 && is_downstone == 0)//右飞
		{
			flyright = 1;
		}
		if (GetAsyncKeyState(0x53) & 0x8000 && is_downstone == 1)//s
		{
			dig = 1;
		}
		if (GetAsyncKeyState(0x20) & 0x8000 && man.bottom_y == stone_1_position && man.center_x < 570 && man.center_x>500)//按空格
		{
			scene = -1;//进入商店
		}
		if (GetAsyncKeyState(0x1B) & 0x8000 && (scene == 1 || scene == 2 || scene == -1))//游戏暂停按esc键
		{
			scene = -3;//游戏暂停界面
		}
		if (GetAsyncKeyState(0x4A) & 0x8000 && man.bomb > 0) {
			put_bomb = 1;
		}
	}
	if (scene == -1)
	{
		char input;
		if (_kbhit())
		{
			input = _getch();
			if (input == 'q')
				scene = 1;//退出商店
			if (input == '1' && score >= 50)//购买炸弹
			{
				man.bomb++;
				score = score - 50;
			}
			if (input == '2' && score >= 500)//购买能量等级
			{
				score = score - 500 * man.energy_level;
				man.energy_level++;
			}
			if (input == '3' && score >= 500)//购买氧气等级
			{
				score = score - 500 * man.oxygen_level;
				man.oxygen_level++;
			}
			if (input == '4' && score >= 200)//购买氧气包
			{
				score = score - 200;
				man.oxygen += 1;
			}
			if (input == '5' && score >= 200)//购买能量包
			{
				score = score - 200;
				man.energy += 1;
			}
		}
	}
	is_leftstone = 0;
	is_rightstone = 0;
	is_downstone = 0;
	is_flyleftstone = 0;
	is_flyrightstone = 0;
}

void startmenu() {
	setfillcolor(BLACK);//背景为黑色
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(width * 0.3, high * 0.2, _T("1 新游戏"));
	outtextxy(width * 0.3, high * 0.3, _T("2 读取游戏存档"));
	outtextxy(width * 0.3, high * 0.4, _T("3 退出"));
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (_kbhit())  // 判断是否有输入
	{
		input = _getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == '1')
			scene = 1;
		else if (input == '2')
		{
			readRecordFile();
		}
		else if (input == '3')
		{
			exit(0);
		}
	}
}
void pausemenu()
{
	setfillcolor(BLACK);//背景为黑色
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(width * 0.3, high * 0.2, _T("1 继续游戏"));
	outtextxy(width * 0.3, high * 0.3, _T("2 保存档案"));
	outtextxy(width * 0.3, high * 0.4, _T("3 退出"));
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == '1')
			scene = man.scene;
		else if (input == '2')
		{
			writeRecordFile();
		}
		else if (input == '3')
		{
			exit(0);
		}
	}
}
void readRecordFile() {
	FILE* fp;
	int i, j, k;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf(fp, "%f %f %d %d %d", &man.center_x, &man.center_y, &man.scene, &score, &scene);
	for (k = 0; k < 3; k++)
		for (i = 0; i < num_stonerow; i++)
			for (j = 0; j < num_stonecol; j++)
			{
				fscanf(fp, "%d", stone1[k][i][j].status);
			}
	scene = man.scene;
	fclose(fp);
	cout << "读取成功" << endl;
}

void writeRecordFile() {
	FILE* fp;
	int i, j, k;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf(fp, "%f %f %d %d %d", man.center_x, man.center_y, man.scene, score, scene);
	for (k = 0; k < 3; k++)
		for (i = 0; i < num_stonerow; i++)
			for (j = 0; j < num_stonecol; j++)
			{
				fprintf(fp, "%d", stone1[k][i][j].status);
			}
	scene = man.scene;
	fclose(fp);
	cout << "保存成功" << endl;
}

void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}