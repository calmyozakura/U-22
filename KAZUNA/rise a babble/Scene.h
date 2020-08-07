#ifndef _SCENE_H_

#define _SCENE_H_

#include "DxLib.h"

#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 5000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7
#define INFINITY_X 24
#define INFINITY_Y 2
#define WIDTH 480
#define HEIGHT 640
#define IMMOVABLEOBJMAX 25	//動かせるオブジェクトの最大表示数
#define ENEMYMAX 1			//動く敵の最大表示数
#define MAPMAX 5			//マップの最大数


#define DEBUG



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

typedef struct IMMOVABLEOBJ {

	float x, y, r;	//x座標,y座標,半径
	bool setflg;	//障害物を配置するかのフラグ
	int flg;		//使用フラグ
};

typedef struct ENEMY {
	int mx, my;
	int sx, sy;
	int flg;	//使用フラグ
	int move;	//移動フラグ(false=右,true=左)
};


struct PLAYER {
	float x, y;				//座標
	int size;				//半径
	int w, h;				//画像の高さ、幅
	double angle;			//プレイヤーの向き
	float max_speed;		//プレイヤーの最大速度
	float scl;
};


struct BULLET {
	int x, y;
	int time;
	double angle;
	float speed;
	int c_flg;
	int m_flg;
};


struct _VECTOR
{
	float Inertia;
	int Add_Flg;
	int Add_Cnt;
	int De_Flg;
	int De_Cnt;
};

class Hit {
public:
	void HitCheck(void);
};

class Scene :public Hit {
public:

	int Changer = 0;//シーン用変数
	int Before = 0;//前画面の変数

	void Title();//タイトル　　
	void GameInit();//ゲーム前の初期化
	void GameMain();//ゲーム
	void Result();//リザルト
	void Option();//オプション
	void Ending();//エンド

	XINPUT_STATE input;
	float StickX, StickY;

	int CodeOrigin[3];
	char Code[MAPMAX];

	int CodeRnd_flg = FALSE;


	int infinity[INFINITY_X][INFINITY_Y]{
	{1,-1},{1,-1},{1,0},{1,0},{1,1},{0,1},{0,1},{-1,1},{-1,0},{-1,0},{-1,-1},{-1,-1},
	{-1,-1},{-1,-1},{-1,0},{-1,0},{-1,1},{0,1},{0,1},{1,1},{1,0},{1,0},{1,-1},{1,-1}
	};
	state g_GameState = SET;
	struct PLAYER player;
	struct BULLET bullet[BULLET_MAX];
	struct _VECTOR Vec[VEC_SIZE];
	struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];
	struct IMAGES {
		int muzzle;
		int player;
		int back[10];
		int bubble;
	}images;

	ENEMY g_enemy[MAPMAX][ENEMYMAX];

	int Player;				//プレイヤーの画像をいれる
	int ImmovableObj;		//動かない障害物の画像をいれる変数
	int enemy;		//動く敵の画像をいれる変数

	float hit_x[IMMOVABLEOBJMAX];	//円の当たり判定_x
	float hit_y[IMMOVABLEOBJMAX];	//円の辺り判定_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//円の当たり判定_x
	float hit_ey[ENEMYMAX];	//円の辺り判定_y
	float hit_er[ENEMYMAX];

	int rx, ry;	//障害物の配置列をずらすための変数
	int Entire_x[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標
	int Entire_y[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標


	int color = (255, 255, 255);
	int red = GetColor(255, 0, 0);	//赤色
	int yellow = GetColor(0, 255, 0);	//赤色
	int White = GetColor(255, 255, 255);	//白

	int Pattern[MAPMAX];		//敵や障害物などのパターン

	void PlayerMove();			//プレイヤーの動作に関する処理
	void DrawPlayer();			//プレイヤーの描画
	void Bound();				//プレイヤーが壁でバウンドする処理
	int Cnt(int n);				//入れた値をカウントする処理
	void CreateBubble();		//しゃぼん弾生成
	void FireBubble();			//しゃぼん弾発射
	void Angle();				//プレイヤーの向きの処理
	void FloatBubble();
	void ScrollMap();
	void HitCheck(void);
	int LoadImages();
	void CreateCode();

	void CreateImmovableObj();
	void DrawImmovableObj();
	void MoveEnemy();
	float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r);

protected:

private:

	typedef	enum {
		_INIT = -1,
		TITLE = 0,
		GAMEINIT,
		GAMEMAIN,
		RESULT,
		OPTION,
		ENDING,
		END = 99
	}num;

	int g_OldKey, g_NowKey, g_KeyFlg;



};



#endif