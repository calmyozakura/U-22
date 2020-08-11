#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

int EnemyImage;		//動く敵の画像をいれる変数

class Enemy{
private:
#define IMMOVABLEOBJMAX 25	//動かせるオブジェクトの最大表示数
#define ENEMYMAX 1			//動く敵の最大表示数
#define MAPMAX 5			//マップの最大数

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
		int mx, my;		//x座標,y座標
		int sx, sy;		//縦、横幅
		bool setflg;	//敵を配置するかのフラグ
		int flg;	//使用フラグ
		int move;	//移動フラグ(false=右,true=左)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
}; 

Enemy myEnemy;		//Enemyオブジェクトを生成

//********************************************
//	定数の宣言
//********************************************
#define WIDTH 480
#define HEIGHT 640

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
			g_enemy[m][i].sx = 50;	//敵の横幅
			g_enemy[m][i].sy = 50;	//敵の縦幅
			g_enemy[m][i].setflg = true;	////障害物を配置するかのフラグを全てfalseに
			g_enemy[m][i].flg = FALSE;
			g_enemy[m][i].move = FALSE;
		}
	}

	//InitFlg = true;
}
//***************************************
//	敵とオブジェクトの生成
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//障害物の生成
		case 0:
			for (int i = 0; i < 15; i++) {
				g_immovableobj[m][i].setflg = true;	//障害物を配置するかのフラグをtrueに
			}
			break;
		case 1:
			for (int i = 10; i < 20; i++) {
				g_immovableobj[m][i].setflg = true;	//障害物を配置するかのフラグを全てtrueに
			}
			break;
		case 2:
			for (int i = 20; i < 25; i++) {
				g_immovableobj[m][i].setflg = true;	//障害物を配置するかのフラグを全てtrueに
			}
			break;
		}
	}
	for (int m = 0; m < MAPMAX; m++) {	//障害物の生成
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == true) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = Entire_x[i];
					g_immovableobj[m][i].y = Entire_y[i] + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//敵の生成
			if (g_enemy[m][e].setflg == true) {
				if (g_enemy[m][e].flg == false) {
					g_enemy[m][e].mx = 0;
					g_enemy[m][e].my = (-m * HEIGHT) + 100;
					g_enemy[m][e].flg = true;
				}
			}
		}
	}
}
//***********************************************
//	敵とオブジェクトの描画
//***********************************************
void Enemy::DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == true) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), true);
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].setflg == true) {
				DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //敵の描画
			}
		}
	}
}
//************************************************
//	敵の移動
//************************************************
void Enemy::MoveEnemy(void) {

	for (int m = 0; m < MAPMAX; m++) {
		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].flg == true) {
				if (g_enemy[m][e].mx <= 50) g_enemy[m][e].move = true;	//x座標が50以下で右移動フラグon
				else if (g_enemy[m][e].mx >= WIDTH - 100) g_enemy[m][e].move = false; //x座標がWIDTH-100以上で左移動フラグon

				if (g_enemy[m][e].move == true)	g_enemy[m][e].mx += 3;
				else if (g_enemy[m][e].move == false) g_enemy[m][e].mx -= 3;
			}
		}
	}
}
//************************************************
//	画像読み込み
//************************************************
int LoadImages() {

	if ((EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}