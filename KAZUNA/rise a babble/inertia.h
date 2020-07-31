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
	float x, y;				//座標
	int size;				//半径
	int w, h;				//画像の高さ、幅
	double angle;			//プレイヤーの向き
	float max_speed;		//プレイヤーの最大速度
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
//	定数の宣言
//********************************************
#define WIDTH 480
#define HEIGHT 640
#define IMMOVABLEOBJMAX 5	//動かせるオブジェクトの最大表示数
#define ENEMYMAX 1			//動く敵の最大表示数
#define MAPMAX 5			//マップの最大数
//********************************************
//	変数の宣言
//********************************************
int Player;				//プレイヤーの画像をいれる
int ImmovableObj;		//動かない障害物の画像をいれる変数
int Enemy;		//動く敵の画像をいれる変数

float hit_x[IMMOVABLEOBJMAX];	//円の当たり判定_x
float hit_y[IMMOVABLEOBJMAX];	//円の辺り判定_y
float hit_r[IMMOVABLEOBJMAX];

float hit_ex[ENEMYMAX];	//円の当たり判定_x
float hit_ey[ENEMYMAX];	//円の辺り判定_y
float hit_er[ENEMYMAX];

int color = (255, 255, 255);
int red = GetColor(255, 0, 0);	//赤色
int yellow = GetColor(0, 255, 0);	//赤色
int White = GetColor(255, 255, 255);	//白

int Pattern[MAPMAX];		//敵や障害物などのパターン

bool CreateCheck = false;
bool InitFlg = false;				//初期処理をしたかの判定

struct PLAYER_ {

	float x, y, r;	//x座標,y座標,半径
};
struct PLAYER_ g_player;

typedef struct IMMOVABLEOBJ {

	float x, y, r;	//x座標,y座標,半径

	int flg;		//使用フラグ
};
struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];

typedef struct ENEMY {
	int mx, my;
	int sx, sy;
	int flg;	//使用フラグ
	int move;	//移動フラグ(false=右,true=左)
};
ENEMY g_enemy[MAPMAX][ENEMYMAX];