#ifndef ENEMY_H

#define ENEMY_H
#include "DxLib.h"

#define IMMOVABLEOBJMAX 25	//動かせるオブジェクトの最大表示数
#define ENEMYMAX 1			//動く敵の最大表示数
#define MAPMAX 5			//マップの最大数


using namespace std;

class Hit {
public:
	void HitCheck(void);
};

class Enemy : public Hit {
private:

	int Entire_x[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標
	int Entire_y[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標

public:
	float hit_x[IMMOVABLEOBJMAX];	//円の当たり判定_x
	float hit_y[IMMOVABLEOBJMAX];	//円の辺り判定_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//円の当たり判定_x
	float hit_ey[ENEMYMAX];	//円の辺り判定_y
	float hit_er[ENEMYMAX];

	int Pattern[MAPMAX];		//敵や障害物などのパターン

	int rx, ry;	//障害物の配置列をずらすための変数

	Enemy();						//Enemyのコンストラクタ
	void CreateImmovableObj(void);	//敵と動かせる障害物生成
	void DrawImmovableObj(void);	//敵と動かせる障害物の描画
	void MoveEnemy(void);	//敵の移動

	typedef struct IMMOVABLEOBJ {

		float x, y, r;	//x座標,y座標,半径
		bool setflg;	//障害物を配置するかのフラグ
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
};

class Player : public Hit {
public:

	Player();				//プレイヤーのコンストラクタ
	void DrawPlayer(void);	//プレイヤーの描画
	void MovePlayer(void);	//プレイヤーの移動

	struct PLAYER {

		float x, y, r;	//x座標,y座標,半径
	};
	struct PLAYER g_player;
};


Enemy myEnemy;		//Enemyオブジェクトを生成
Player myPlayer;	//Playerオブジェクトと生成
Hit myHit;
//********************************************
//	定数の宣言
//********************************************
#define WIDTH 480
#define HEIGHT 640
//********************************************
//	変数の宣言
//********************************************
int PlayerImage;				//プレイヤーの画像をいれる
int ImmovableObj;		//動かない障害物の画像をいれる変数
int EnemyImage;		//動く敵の画像をいれる変数

int color = (255, 255, 255);
int red = GetColor(255, 0, 0);	//赤色
int yellow = GetColor(0, 255, 0);	//赤色
int White = GetColor(255, 255, 255);	//白

//int Pattern[MAPMAX];		//敵や障害物などのパターン

bool InitFlg = false;				//初期処理をしたかの判定

//***************************************************
//	敵と障害物の初期化
//***************************************************
Enemy::Enemy()
{

	rx = 0;
	ry = 0;

	// 障害物の初期設定 
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {

		Entire_x[i] = rx * (WIDTH / 5) + 45;		//障害物の座標に入れる前にあらかじめ取っておく座標
		Entire_y[i] = ry * (HEIGHT / 2) / 5 + 50;		//障害物の座標に入れる前にあらかじめ取っておく座標

		rx += 1;	//x座標

		if (i % 5 == 4) {	//5個配置されるごとにx座標を左に戻しy座標を1段下げる
			rx = 0;
			ry += 1;
		}
	}

	// 障害物の初期設定 
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {

			g_immovableobj[m][i].r = 30.0f;	//障害物の円の半径
			g_immovableobj[m][i].setflg = false;	//障害物を配置するかのフラグを全てfalseに
			g_immovableobj[m][i].flg = FALSE;
		}

		// 敵の初期設定  
		for (int i = 0; i < ENEMYMAX; i++) {
			g_enemy[m][i].sx = 50;
			g_enemy[m][i].sy = 50;
			g_enemy[m][i].flg = FALSE;
			g_enemy[m][i].move = FALSE;
		}
	}

	//InitFlg = true;
}
Player::Player() {
	g_player.x = (WIDTH / 2);		//プレイヤーのx座標
	g_player.y = (HEIGHT - 100);	//プレイヤーのy座標
	g_player.r = 20.0f;	//プレイヤーの半径
}
//***************************************************
//	円と四角の当たり判定をとるための処理
//***************************************************
float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r)
{
	if (L - r > x || R + r < x || T - r > y || B + r < y) {//矩形の領域判定1
		return false;
	}
	if (L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < r * r)) {//左上の当たり判定
		return false;
	}
	if (R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < r * r)) {//右上の当たり判定
		return false;
	}
	if (L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < r * r)) {//左下の当たり判定
		return false;
	}
	if (R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < r * r)) {//右下の当たり判定
		return false;
	}
	return true;//すべての条件が外れたときに当たっている
}


#endif // !ENEMY_H