#pragma once
#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 8000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7
#define INFINITY_X 24
#define INFINITY_Y 2

#define DEBUG


float StickX, StickY;
int infinity[INFINITY_X][INFINITY_Y]{
	{1,-1},{1,-1},{1,0},{1,0},{1,1},{0,1},{0,1},{-1,1},{-1,0},{-1,0},{-1,-1},{-1,-1},
	{-1,-1},{-1,-1},{-1,0},{-1,0},{-1,1},{0,1},{0,1},{1,1},{1,0},{1,0},{1,-1},{1,-1}
};

typedef enum {
	SET,
	MAIN
}state;
typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	VEC_SIZE
};
state g_GameState = SET;

struct IMAGES {
	int muzzle;
	int player;
	int back[10];
	int bubble;
}images;

struct PLAYER {
	float x, y;				//���W
	int size;				//���a
	int w, h;				//�摜�̍����A��
	double angle;			//�v���C���[�̌���
	float max_speed;		//�v���C���[�̍ő呬�x
	float scl;
};
struct PLAYER player;

struct BULLET {
	int x, y;
	int time;
	double angle;
	float speed;
	int c_flg;
	int m_flg;
};
struct BULLET bullet[BULLET_MAX];

struct _VECTOR
{
	float Inertia;
	int Add_Flg;
	int Add_Cnt;
	int De_Flg;
	int De_Cnt;
};
struct _VECTOR Vec[VEC_SIZE];

XINPUT_STATE input;



//********************************************
//	�萔�̐錾
//********************************************
#define WIDTH 480
#define HEIGHT 640
#define IMMOVABLEOBJMAX 5	//��������I�u�W�F�N�g�̍ő�\����
#define ENEMYMAX 1			//�����G�̍ő�\����
#define MAPMAX 5			//�}�b�v�̍ő吔
//********************************************
//	�ϐ��̐錾
//********************************************
int Player;				//�v���C���[�̉摜�������
int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
int Enemy;		//�����G�̉摜�������ϐ�

float hit_x[IMMOVABLEOBJMAX];	//�~�̓����蔻��_x
float hit_y[IMMOVABLEOBJMAX];	//�~�̕ӂ蔻��_y
float hit_r[IMMOVABLEOBJMAX];

float hit_ex[ENEMYMAX];	//�~�̓����蔻��_x
float hit_ey[ENEMYMAX];	//�~�̕ӂ蔻��_y
float hit_er[ENEMYMAX];

int color = (255, 255, 255);
int red = GetColor(255, 0, 0);	//�ԐF
int yellow = GetColor(0, 255, 0);	//�ԐF
int White = GetColor(255, 255, 255);	//��

int Pattern[MAPMAX];		//�G���Q���Ȃǂ̃p�^�[��

bool CreateCheck = false;
bool InitFlg = false;				//�����������������̔���

struct PLAYER_ {

	float x, y, r;	//x���W,y���W,���a
};
struct PLAYER_ g_player;

typedef struct IMMOVABLEOBJ {

	float x, y, r;	//x���W,y���W,���a

	int flg;		//�g�p�t���O
};
struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];

typedef struct ENEMY {
	int mx, my;
	int sx, sy;
	int flg;	//�g�p�t���O
	int move;	//�ړ��t���O(false=�E,true=��)
};
ENEMY g_enemy[MAPMAX][ENEMYMAX];