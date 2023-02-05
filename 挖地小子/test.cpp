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

#define high 670//��Ϸ����
#define width 900
#define man_high 72//��ɫ��С
#define man_width 64
#define stone_width 64//ʯ���С
#define stone_high 64
#define fly_high 92//���о���
#define fly_width 64
#define digl_high 78//���ھ���
#define digl_width 64
#define digr_width 64//���ھ���
#define digr_high 78
#define digd_high 80//���ھ���
#define digd_width 64
#define num_scene 3//�ؿ�����
#define num_stonerow 11//ʯ������<��һ��>
#define num_stonecol 14
#define stone_1_position 423//ʯ����ֵ�λ��<��һ��>
#define stone_2_position 0
#define monster_high 60//�����С
#define monster_width 56
#define monster_num 3
#define bomb_high 64//ը����Χ
#define bomb_width 64
#define bomb_money 50//ը���ļ۸�


IMAGE img_bk;//���屳��ͼƬ
IMAGE img_ebg;//��Ϸ����ͼƬ
IMAGE img_success;//��Ϸ�ɹ�ʱ��ͼƬ
IMAGE img_1;//�����һ�ص�ͼƬ
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7, img_stone_99, img_stone_1314;;//����ʯ���ͼƬ
IMAGE img_coal_1, img_coal_2, img_coal_3, img_coal_4, img_coal_5, img_coal_0;//����ú���ͼƬ
IMAGE img_copper_1, img_copper_2, img_copper_3, img_copper_4, img_copper_5, img_copper_6, img_copper_0;//����ͭ���ͼƬ
IMAGE img_silver_1, img_silver_2, img_silver_3, img_silver_4, img_silver_5, img_silver_0;//���������ͼƬ
IMAGE img_man_0, img_man_00;//�����ڵ�С�ӵ�����ͼƬ 0��ʾ�ڰװ� 00��ʾ�ʰ�
IMAGE img_man_1, img_man_2;//�����ڵ�С�������ߵ�ͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_shoes_1, img_shoes_2;//������ЬͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digl_1, img_digl_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digright_1, img_digright_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digdown_1, img_digdown_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_shop;//�̵�
IMAGE img_bomb_1, img_bomb_boom, img_bwbomb_boom;//ը��
IMAGE img_bwbomb_1;//ը���ڰ�
IMAGE img_energy;//����ͼƬ
IMAGE img_monsterrun_0, img_monsterrun_00;//���������·��ͼƬ  0��ʾ�ڰװ�  00��ʾ�ʰ�
IMAGE img_oxygen;//����ͼƬ
IMAGE img_ener_oxy1;//�����ڰ�
IMAGE img_ener_oxy2;//����
MOUSEMSG m;//����һ��������

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
	//��
	int v;
	int bomb;
	int scene;
	int oxygen;
	int energy;
	int oxygen_level;//�����ȼ�
	int energy_level;//�����ȼ�
	//��
	int direction;
};
thing man;
thing monster[monster_num];//�������

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

int scene;//����
int left_i;//�ƶ�����
int right_i;
int bomb_i;
int G;
int fly_a;//�����ж�
int dig;//�ڵ��ж�
int digl;
int digr;
int flyleft;
int flyright;
int is_leftstone;//ʯ���ж�
int is_rightstone;
int is_downstone;
int is_flyleftstone;
int is_flyrightstone;
int score;
int put_bomb;
int mleft_i[monster_num];//��¼���������ƶ���ͼƬ
int mright_i[monster_num];//��¼���������ƶ���ͼƬ
float energy_i;//�����仯������
float energy_j;//�����仯������
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
	initgraph(width, high);//����
	loadimage(&img_bk, _T("..//images//background.jpg"));//������Ϸ��ʼ����
	loadimage(&img_ebg, _T("..//images//endbackground.jpg"));//������Ϸ��������
	loadimage(&img_success, _T("..//images//success.jpg"));//������Ϸʤ������
	loadimage(&img_1, _T("..//images//level_1.jpg"));//�����һ�ص�ͼƬ
	loadimage(&img_man_0, _T("..//images//person_0.jpg"));//�������������ͼƬ�ڰװ�
	loadimage(&img_man_00, _T("..//images//person_00.jpg"));//�������������ͼƬ�ʰ�
	loadimage(&img_man_1, _T("..//images//person_1.jpg"));//��������������·��ͼƬ�ĺڰװ�
	loadimage(&img_man_2, _T("..//images//person_2.jpg"));//��������������·��ͼƬ�ʰ�
	loadimage(&img_stone_0, _T("..//images//stone_0.jpg"));//����յ�ͼƬ
	loadimage(&img_stone_1, _T("..//images//stone_1.jpg"));//����ʯ��ԭͼ��ͼƬ
	loadimage(&img_stone_2, _T("..//images//stone_2.jpg"));//��������1��ͼƬ
	loadimage(&img_stone_3, _T("..//images//stone_3.jpg"));//��������2��ͼƬ
	loadimage(&img_stone_4, _T("..//images//stone_4.jpg"));//��������3��ͼƬ
	loadimage(&img_stone_5, _T("..//images//stone_5.jpg"));//��������4��ͼƬ
	loadimage(&img_stone_6, _T("..//images//stone_6.jpg"));//��������5��ͼƬ
	loadimage(&img_stone_7, _T("..//images//stone_7.jpg"));//��������6��ͼƬ
	loadimage(&img_stone_99, _T("..//images//stone_99.jpg"));//��������99��ͼƬ
	loadimage(&img_stone_1314, _T("..//images//stone_1314.jpg"));//��������99��ͼƬ
	loadimage(&img_coal_1, _T("..//images//coal_1.jpg"));//��������ú
	loadimage(&img_coal_2, _T("..//images//coal_2.jpg"));//��������1ú
	loadimage(&img_coal_3, _T("..//images//coal_3.jpg"));//��������2,ú
	loadimage(&img_coal_4, _T("..//images//coal_4.jpg"));//��������3ú
	loadimage(&img_coal_5, _T("..//images//coal_5.jpg"));//��������4ú
	loadimage(&img_coal_0, _T("..//images//coal_0.jpg"));//��ȫ�����ú
	loadimage(&img_copper_1, _T("..//images//Copper_1.jpg"));//��������ͭ
	loadimage(&img_copper_2, _T("..//images//Copper_2.jpg"));//��������1ͭ
	loadimage(&img_copper_3, _T("..//images//Copper_3.jpg"));//��������2ͭ
	loadimage(&img_copper_4, _T("..//images//Copper_4.jpg"));//��������3ͭ
	loadimage(&img_copper_5, _T("..//images//Copper_5.jpg"));//��������4ͭ
	loadimage(&img_copper_6, _T("..//images//Copper_6.jpg"));//��������5ͭ
	loadimage(&img_copper_0, _T("..//images//Copper_0.jpg"));//��ȫ�����ͭ
	loadimage(&img_silver_1, _T("..//images//silver_1.jpg"));//����������
	loadimage(&img_silver_2, _T("..//images//silver_2.jpg"));//��������1��
	loadimage(&img_silver_3, _T("..//images//silver_3.jpg"));//��������2��
	loadimage(&img_silver_4, _T("..//images//silver_4.jpg"));//��������3��
	loadimage(&img_silver_5, _T("..//images//silver_5.jpg"));//��������4��
	loadimage(&img_silver_0, _T("..//images//silver_0.jpg"));//��ȫ�������
	loadimage(&img_shoes_1, _T("..//images//shoes_1.jpg"));//����������ͼƬ�ڰװ�
	loadimage(&img_shoes_2, _T("..//images//shoes_2.jpg"));//����������ͼƬ�ʰ�
	loadimage(&img_digl_1, _T("..//images//digleftperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digl_2, _T("..//images//digleftperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	loadimage(&img_digright_1, _T("..//images//digrightperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digright_2, _T("..//images//digrightperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	loadimage(&img_digdown_1, _T("..//images//digdownperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digdown_2, _T("..//images//digdownperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	loadimage(&img_shop, _T("..//images//shop.jpg"));//�����̵��ͼƬ
	loadimage(&img_monsterrun_0, _T("..//images//monsterrun_0.jpg"));//���������·ͼƬ�Ĳʰ�
	loadimage(&img_monsterrun_00, _T("..//images//monsterrun_00.jpg"));//���������·ͼƬ�ĺڰװ�
	loadimage(&img_energy, _T("..//images//energy.jpg"));//����������ͼƬ
	loadimage(&img_bomb_1, _T("..//images//bomb_1.jpg"));//ը��ԭʼ
	loadimage(&img_bwbomb_1, _T("..//images//bwbomb_1.jpg"));//ը��ԭʼ�ڰ�
	loadimage(&img_bomb_boom, _T("..//images//bomb_boom.jpg"));//ը����ը�����й���ͼƬ
	loadimage(&img_bwbomb_boom, _T("..//images//bwbomb_boom.jpg"));//ը����ը�����й��̺ڰ�ͼƬ
	loadimage(&img_energy, _T("..//images//energy.jpg"));//����������ͼƬ
	loadimage(&img_oxygen, _T("..//images//oxygen.jpg"));//����������ͼƬ
	loadimage(&img_ener_oxy1, _T("..//images//ener_oxy1.jpg"));//���������ڰ���
	loadimage(&img_ener_oxy2, _T("..//images//ener_oxy2.jpg"));//��������
	mciSendString(_T("open ..//images//bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//���뱳������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ����������

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
	//��ʼ��ը��

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
	//��ʼ��ʯ��λ��
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
	//��ʼ����һ��ʯ��λ��
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

	//��ʼ���ڶ���ʯ��λ��
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

	//��ɫ��ʼ��λ��
	man.center_x = width / 2;
	man.center_y = stone_1_position - man_high / 2;
	man.bomb = 0;//��ʼû��ը��
	man.status = 1;//��ʼ�ڵ�С�ӻ���
	man.oxygen_level = 1;//�����ȼ�	
	man.energy_level = 1;//�����ȼ�
	man.oxygen = 1;//������
	man.energy = 1;//������
	//�����ʼ��λ��
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
	//��ɫ�ƶ�����
	left_i = 0;
	right_i = 0;
	bomb_i = 0;
	man.v = 0;
	score = 500;
	energy_i = 120;//�������ĳ���
	energy_j = 19;
	oxygen_i = 107;//�������ĳ���
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
		for (j = 1; j < 5; j++)//����
		{
			stone1[2][i][j].status = 0;
		}
	for (i = 3; i < 4; i++)
		for (j = 5; j < 9; j++)//����
		{
			stone1[2][i][j].status = 0;
		}
	for (i = 6; i < 7; i++)
		for (j = 9; j < 13; j++)//����
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
	/*����������� ÿ��ֵ������������������� ��ǿ����������*/
	man.left_x = man.center_x - man_width / 2;
	man.left_y = man.center_y;
	man.right_x = man.center_x + man_width / 2;
	man.right_y = man.center_y;
	man.top_x = man.center_x;
	man.top_y = man.center_y - man_high / 2;
	man.bottom_x = man.center_x;
	man.bottom_y = man.center_y + man_high / 2;
	/*����������� ÿ��ֵ������������������ ��ǿ����������*/
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
			//ʯ��״̬
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
			//ú��״̬
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
			//ͭ��״̬
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
			//����״̬
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
				putimage(stone1[k][i][j].left_x, stone1[k][i][j].top_y, &img_stone_1314);//ש���ʼ��
		}
	}
	//�̵�
	if (scene == -1) {
		putimage(0, 0, &img_shop);
	}
	//��������������
	if (scene == 1 || scene == 2) {
		putimage(735, 213, energy_i, energy_j, &img_energy, 0, 0);
		putimage(740, 246, oxygen_i, oxygen_j, &img_oxygen, 0, 0);
	}
	if (scene == 2)
	{
		putimage(width - 610, 0, &img_ener_oxy1, NOTSRCERASE);
		putimage(width - 610, 0, &img_ener_oxy2, SRCINVERT);
	}
	//��ɫ��Ԫ��
	man.left_x = man.center_x - man_width / 2;
	man.left_y = man.center_y;
	man.right_x = man.center_x + man_width / 2;
	man.right_y = man.center_y;
	man.top_x = man.center_x;
	man.top_y = man.center_y - man_high / 2;
	man.bottom_x = man.center_x;
	man.bottom_y = man.center_y + man_high / 2;
	//������Ԫ��
	monster[i].left_x = monster[i].center_x - monster_width / 2;
	monster[i].left_y = monster[i].center_y;
	monster[i].right_x = monster[i].center_x + monster_width / 2;
	monster[i].right_y = monster[i].center_y;
	monster[i].top_x = monster[i].center_x;
	monster[i].top_y = monster[i].center_y - monster_high / 2;
	monster[i].bottom_x = monster[i].center_x;
	monster[i].bottom_y = monster[i].center_y - monster_high / 2;
	//�ؿ�ͬ��
	if (scene != -3 && scene != -2 && scene != 0)
		man.scene = scene;
	if (energy_i <= 0)
		fly_a = 0;
}

void updatewithoutinput() {
	//ȷ����ɫ��λ��
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
			//�жϽ�ɫ�Ƿ�վ��ʯ����
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
	//�жϽ�ɫ����ʱ�Ϸ��Ƿ���ʯ��
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
	//�ж��Ƿ�������
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
	//�ж��Ƿ�������
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
	//�ж��Ƿ�������
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
	//�жϷ���ʱ����Ƿ���ʯ��
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
	//��ɫ����
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
	//�����ƶ�
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
					monster[m].direction = 0;//��˴���ש��������  
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
					monster[m].direction = 1;//�Ҷ˴���ש��������   
				}
			}
	//ʰȡ��Ʒ
	for (i = 0; i < num_stonerow; i++) {
		for (j = 0; j < num_stonecol; j++) {
			if (stone1[k][i][j].status == 16 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//ʰȡú��
			{
				stone1[k][i][j].status = 0;
				score = score + 10;//һ��ú��10��
			}
			if (stone1[k][i][j].status == 27 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//ʰȡͭ��
			{
				stone1[k][i][j].status = 0;
				score = score + 20;//һ��ͭ��20��
			}
			if (stone1[k][i][j].status == 36 && man.center_x <stone1[k][i][j].center_x + 10
				&& man.center_x > stone1[k][i][j].center_x - 10)//ʰȡ����
			{
				stone1[k][i][j].status = 0;
				score = score + 50;//һ������50��
			}
		}
	}
	/*����ը��������ը���ı仯*/
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
	/*ը��ը��������ж�*/
	for (i = 0; i < monster_num; i++) {
		if (bomb.status >= 6 && bomb.center_x - monster[i].center_x <= bomb_width / 2 + monster_width / 2 &&
			bomb.center_x - monster[i].center_x >= -bomb_width / 2 - monster_width / 2 &&
			bomb.center_y - monster[i].center_y <= bomb_high - monster_high + 4 &&
			bomb.center_y - monster[i].center_y >= -bomb_high + monster_high - 4) {
			score = (score + 500 * monster[i].status);
			monster[i].status = 0;
		}
	}
	/*�������������Ѫ*/
	for (i = 0; i < monster_num; i++)
	{
		if (man.center_x - monster[i].center_x <= man_width / 2 + monster_width / 2
			&& man.center_x - monster[i].center_x >= -man_width / 2 - monster_width / 2 && man.center_y - monster[i].center_y <= man_high - monster_high + 4
			&& man.center_y - monster[i].center_y >= -man_high + monster_high - 4)
		{
			oxygen_i = oxygen_i - 0.1;//�������ı仯
		}
	}
	/*ը��ը������ж�*/
	if (bomb.status >= 6 && bomb.center_x - man.center_x <= bomb_width / 2 + man_width / 2 - 4
		&& bomb.center_x - man.center_x >= -bomb_width / 2 - man_width / 2 + 4 && bomb.center_y - man.center_y <= bomb_high / 2 + man_high / 2 - 4
		&& bomb.center_y - man.center_y >= -bomb_high / 2 - man_high / 2 + 4)
	{
		oxygen_i = oxygen_i - 4;//�������ı仯
	}
	/*ú��Ļָ�*/
	static int speed_10[num_scene][num_stonerow][num_stonecol] = { 0 };
	for (i = 0; i < num_stonerow; i++)
		for (j = 0; j < num_stonerow; j++)
		{
			if (stone1[k][i][j].status == -1)//ש���״̬��Ϊ��ȫ�����
			{
				speed_10[k][i][j]++;
				if (speed_10[k][i][j] == 4000)//ש��ָ����ٶ�
				{
					stone1[k][i][j].status = 11;//ֻ�ָܻ�һ��
					speed_10[k][i][j] = 0;
				}
			}
		}
	/*����������ָ�*/
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
	/*����������ָ�*/
	if (scene == 1 && man.top_y <= stone_1_position)
	{
		if (oxygen_i <= 107)
			oxygen_i = oxygen_i + 0.03;
	}
	if ((scene == 1 && man.top_y > stone_1_position) || scene == 2)
	{
		oxygen_i = oxygen_i - 0.01;
	}
	/*���������ж�*/
	if (oxygen_i < 0)
	{
		man.status = 0;
		scene = -4; //-4��Ϸ����
		putimage(0, 0, &img_ebg);//��Ϸʧ��
	}
	/*����ʤ���ж�*/
	for (i = 0; i < monster_num; i++)
	{
		if (monster[i].status != 0)
			break;
		scene = -5; //-5��Ϸ�ɹ� 
		putimage(0, 0, &img_success);//��Ϸ�ɹ�
	}
	/*��ʾ����*/
	if (scene == 1 || scene == 2 || scene == -1)
	{
		TCHAR s[10], s1[10], s2[10], s3[10], s4[10], s5[10];
		setbkmode(TRANSPARENT);//����͸��
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
		outtextxy(10, 40, _T("ը��������"));
		outtextxy(10, 65, _T("������ȼ���"));
		outtextxy(10, 90, _T("�����ȼ���"));
		outtextxy(10, 115, _T("��������"));
		outtextxy(10, 140, _T("��������"));
		settextstyle(25, 0, _T("����"));
		settextcolor(BLACK);
	}
	/*�����Զ�����*/
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
	/*��Ϸ���Ʊ߽�*/
	if (scene == 1)
	{
		if (man.left_x < 0)//������߽�
			man.center_x = man_width / 2;
		else if (man.right_x > 900)//�����ұ߽�
			man.center_x = 900 - man_width / 2;
		else if (man.top_y < 0)//�����ϱ߽�
			man.center_y = man_high / 2;
	}
	/*�ؿ���Ծ*/
	if (scene == 1 && man.bottom_y > high)//��һ�ص��ڶ���
	{
		scene = 2;
		man.center_y = -man_width / 2;
	}
	else if (scene == 2 && man.bottom_y < 0)//�ӵڶ��ط��ص�һ��
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
		//���Ϸ�
		else if (fly_a < 0 && flyleft == 0 && flyright == 0) {
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);
			Sleep(1);
		}
		//���
		else if (fly_a < 0 && flyleft == 1)
		{
			if (is_flyleftstone == 0) {
				cout << "��" << endl;
				man.center_x = man.center_x - 1;//�������������x����
			}	
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);//�������Ϸɺڰװ�
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);//�������Ϸɲʰ�
			Sleep(1);
		}
		//�ҷ�
		else if (fly_a < 0 && flyright == 1)
		{
			if (is_flyrightstone == 0) {
				man.center_x = man.center_x + 1;//�������������x����
			}	
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_1, NOTSRCERASE);//�������Ϸɺڰװ�
			putimage(man.center_x - fly_width / 2, man.center_y - fly_high / 2, &img_shoes_2, SRCINVERT);//�������Ϸɲʰ�
			
			Sleep(1);
		}
		//����
		else if (dig == 1)
		{
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_1, NOTSRCERASE);//��������ڰ�
			putimage(man.center_x - digd_width / 2, man.center_y - digd_high / 2, &img_digdown_2, SRCINVERT);//���������
			//FlushBatchDraw();
			//Sleep(10);
		}
		//�������
		else if (digl == 0)
		{
			man.center_x = man.center_x - 15;//�������������x����
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, left_i * man_width, 0, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, left_i * man_width, 0, SRCINVERT);//���������ߵĲ�ͼ
			FlushBatchDraw();
			left_i++;
			Sleep(100);
			if (left_i == 3)
				left_i = 0;
		}
		//����
		else if (digl == 1)
		{
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_1, NOTSRCERASE);//��������ڰ�
			putimage(man.center_x - digl_width / 2, man.center_y - digl_high / 2, &img_digl_2, SRCINVERT);//���������
			Sleep(1);
		}

		//�ұ�����
		else if (digr == 0)
		{
			man.center_x = man.center_x + 15;//�������������x����
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_1, right_i * man_width, man_high, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
			putimage(man.left_x, man.top_y, man_width, man_high, &img_man_2, right_i * man_width, man_high, SRCINVERT);//���������ߵĲ�ͼ
			right_i++;
			Sleep(100);
			if (right_i == 3)
				right_i = 0;
		}
		//����
		else if (digr == 1)
		{
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_1, NOTSRCERASE);//��������ڰ�
			putimage(man.center_x - digr_width / 2, man.center_y - digr_high / 2, &img_digright_2, SRCINVERT);//���������
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
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bwbomb_boom, bomb_i * bomb_width, 0, NOTSRCERASE);//����ը���ĺڰ�ͼƬ
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bomb_boom, bomb_i * bomb_width, 0, SRCINVERT);//����ը���Ĳ�ͼ
		}
		bomb_i++;
		Sleep(100);
		if (bomb_i == 8)
		{
			bomb.status = 0;
			bomb.center_x = -1000;
			bomb.center_y = -1000;
			bomb_i = 0;
			man.bomb--;//��һ��ը��
		}
	}
	/*��������*/
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
					monster[i].center_x = monster[i].center_x - 10;//�������������x����
					mleft_i[i]++;
					speed_5 = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mleft_i[i] * monster_width, monster_high, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mleft_i[i] * monster_width, monster_high, SRCINVERT);//���������ߵĲ�ͼ

				if (mleft_i[i] == 3)
					mleft_i[i] = 0;
			}
			else if (monster[i].direction == 0 && monster[i].status == 1)
			{
				if (speed_6 == 60)
				{
					monster[i].center_x = monster[i].center_x + 10;//�������������x����
					mright_i[i]++;
					speed_6 = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mright_i[i] * monster_width, 0, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mright_i[i] * monster_width, 0, SRCINVERT);//���������ߵĲ�ͼ

				if (mright_i[i] == 3)
					mright_i[i] = 0;
			}
		}
	}
	FlushBatchDraw();
	fly_a = 0;//�����ٶȹ�Ϊԭֵ����w�ı䣩
	dig = 0;//�����ڻع�ԭֵ����s�ı䣩
	digl = 3;//�����ڻع�ԭֵ����a�ı䣩
	digr = 3;//�����ڻع�ԭֵ����d�ı䣩
	flyleft = 0;//����ɻع�ԭֵ
	flyright = 0;//���ҷɻع�ԭֵ
	put_bomb = 0;
}

void updatewithinput() {
	//����л�����
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
		if ((GetAsyncKeyState(0x41) & 0x8000) && is_leftstone == 0 && is_downstone == 0)//���
		{
			flyleft = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && is_rightstone == 0 && is_downstone == 0)//�ҷ�
		{
			flyright = 1;
		}
		if (GetAsyncKeyState(0x53) & 0x8000 && is_downstone == 1)//s
		{
			dig = 1;
		}
		if (GetAsyncKeyState(0x20) & 0x8000 && man.bottom_y == stone_1_position && man.center_x < 570 && man.center_x>500)//���ո�
		{
			scene = -1;//�����̵�
		}
		if (GetAsyncKeyState(0x1B) & 0x8000 && (scene == 1 || scene == 2 || scene == -1))//��Ϸ��ͣ��esc��
		{
			scene = -3;//��Ϸ��ͣ����
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
				scene = 1;//�˳��̵�
			if (input == '1' && score >= 50)//����ը��
			{
				man.bomb++;
				score = score - 50;
			}
			if (input == '2' && score >= 500)//���������ȼ�
			{
				score = score - 500 * man.energy_level;
				man.energy_level++;
			}
			if (input == '3' && score >= 500)//���������ȼ�
			{
				score = score - 500 * man.oxygen_level;
				man.oxygen_level++;
			}
			if (input == '4' && score >= 200)//����������
			{
				score = score - 200;
				man.oxygen += 1;
			}
			if (input == '5' && score >= 200)//����������
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
	setfillcolor(BLACK);//����Ϊ��ɫ
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("����"));
	outtextxy(width * 0.3, high * 0.2, _T("1 ����Ϸ"));
	outtextxy(width * 0.3, high * 0.3, _T("2 ��ȡ��Ϸ�浵"));
	outtextxy(width * 0.3, high * 0.4, _T("3 �˳�"));
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (_kbhit())  // �ж��Ƿ�������
	{
		input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
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
	setfillcolor(BLACK);//����Ϊ��ɫ
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("����"));
	outtextxy(width * 0.3, high * 0.2, _T("1 ������Ϸ"));
	outtextxy(width * 0.3, high * 0.3, _T("2 ���浵��"));
	outtextxy(width * 0.3, high * 0.4, _T("3 �˳�"));
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
	cout << "��ȡ�ɹ�" << endl;
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
	cout << "����ɹ�" << endl;
}

void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}