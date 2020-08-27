#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

class Hit {
public:
	void HitCheck(void);
};

class Enemy : public Hit{
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
		int mx, my;
		int sx, sy;
		int flg;	//使用フラグ
		int move;	//移動フラグ(false=右,true=左)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
};

class Player : public Hit{
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
	for(int m = 0; m < MAPMAX; m++){
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
float DistanceSqrf(float L, float R, float T, float B ,float x, float y, float r)
{
	if(L - r > x || R + r < x || T - r > y || B + r < y){//矩形の領域判定1
        return false;
    } 
    if(L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < r * r)){//左上の当たり判定
        return false;
    }
    if(R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < r * r)){//右上の当たり判定
        return false;
    }
    if(L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < r * r)){//左下の当たり判定
        return false;
    }
    if(R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < r * r)){//右下の当たり判定
        return false;
    }
    return true;//すべての条件が外れたときに当たっている
}

/***********************************************
 * 当たり判定
 ***********************************************/
void Hit::HitCheck(void)
{

	//	プレイヤーと障害物の当たり判定
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//プレイヤーと動かせるオブジェクト(円と円)
			myEnemy.hit_x[i] = myPlayer.g_player.x - myEnemy.g_immovableobj[m][i].x;	//プレイヤーと障害物のx座標の差
			myEnemy.hit_y[i] = myPlayer.g_player.y - myEnemy.g_immovableobj[m][i].y;	//プレイヤーと障害物のy座標の差
			myEnemy.hit_r[i] = sqrt(myEnemy.hit_x[i] * myEnemy.hit_x[i] + myEnemy.hit_y[i] * myEnemy.hit_y[i]);	//プレイヤーと障害物の円の半径の和

			if (myEnemy.hit_r[i] <= myPlayer.g_player.r + myEnemy.g_immovableobj[m][i].r)		//当たっているか判定
			{
				DrawString(100, HEIGHT - 20, "障害物とヒット", White);
			}
		}

	//プレイヤーと敵の当たり判定
		for (int e = 0; e < ENEMYMAX; e++) {	//円と四角
			if ((DistanceSqrf(myEnemy.g_enemy[m][e].mx, (myEnemy.g_enemy[m][e].mx + myEnemy.g_enemy[m][e].sx), myEnemy.g_enemy[m][e].my, (myEnemy.g_enemy[m][e].my + myEnemy.g_enemy[m][e].sy), myPlayer.g_player.x, myPlayer.g_player.y, myPlayer.g_player.r) == true)) {
				DrawString(100, HEIGHT - 40, "敵とヒット", White);
			}
		}
	}

}
//**********************************************
//	プレイヤーの描画
//**********************************************
void Player::DrawPlayer(void) {
	DrawCircle(g_player.x, g_player.y, g_player.r, yellow, true);
	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//プレイヤーの当たり判定可視化
}

//**************************************************
//	プレイヤーの移動
//**************************************************
void Player::MovePlayer(void) {
	// ↑キーを押していたらPlayerを上に移動させる
	if (CheckHitKey(KEY_INPUT_UP) == 1) {
		if (g_player.y >= 400) {
			g_player.y -= 3;
		}
		else {
			for (int m = 0; m < MAPMAX; m++) {
				for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
					myEnemy.g_immovableobj[m][i].y += 3;
				}
			
				for (int e = 0; e < ENEMYMAX; e++) {
					myEnemy.g_enemy[m][e].my += 3;
				}
			}
		}
	}

	// ↓キーを押していたらPlayerを下に移動させる
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
		if (g_player.y <= (HEIGHT - 100)) {
			g_player.y += 3;
		}
		else {
			for (int m = 0; m < MAPMAX; m++) {
				for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
					myEnemy.g_immovableobj[m][i].y -= 3;
				}
			
				for (int e = 0; e < ENEMYMAX; e++) {
					myEnemy.g_enemy[m][e].my -= 3;
				}
			}
		}
	}

	// ←キーを押していたらPlayerを左に移動させる
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		g_player.x -= 3;
	}

	// →キーを押していたらPlayerを右に移動させる
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		g_player.x += 3;
	}
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

	//	for (int e = 0; e < ENEMYMAX; e++) {	//敵の生成
	//		if (g_enemy[m][e].flg == false) {
	//			g_enemy[m][e].mx = 0;
	//			g_enemy[m][e].my = (-m * HEIGHT) + 100;
	//			g_enemy[m][e].flg = true;
	//		}
	//	}
	//}
		for (int m = 0; m < MAPMAX; m++) {
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
				if (g_enemy[m][e].flg == false) {
					g_enemy[m][e].mx = 0;
					g_enemy[m][e].my = (-m * HEIGHT) + 100;
					g_enemy[m][e].flg = true;
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
			DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //敵の描画
		}
	}
}
//************************************************
//	敵の移動
//************************************************
void Enemy::MoveEnemy(void) {

	for(int m = 0; m <MAPMAX; m++){
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
	if((PlayerImage = LoadGraph("images/Player.png")) == -1) return -1;		//プレイヤー画像の読み込み
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//動かせる障害物画像の読み込み
	if ((EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetGraphMode(WIDTH, HEIGHT, 16);		//ウィンドウサイズの設定
	ChangeWindowMode(TRUE);	//ウィンドウモードの設定

	SetMainWindowText("DXライブラリテストプログラム");	//("タイトル名")
	SetDrawScreen(DX_SCREEN_BACK);	//描画先を裏画面に設定

	if (DxLib_Init() == -1)	return-1;	//DXライブラリ初期化処理
	if (LoadImages() == -1) return -1; // 画像読込み関数を呼び出す

	srand((unsigned)time(NULL));	//時刻でランダムの初期値を決める
	for (int p = 0; p < MAPMAX; p++) {
		myEnemy.Pattern[p] = GetRand(2);	//0～3のランダムな値
	}

	//ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//画面を初期化

		myPlayer.DrawPlayer();			//プレイヤーの描画
		myPlayer. MovePlayer();			//プレイヤーの移動
		myEnemy.CreateImmovableObj();	//障害物と敵の生成
		myEnemy.DrawImmovableObj();		//障害物と敵の描画
		myEnemy.MoveEnemy();			//敵の移動
		myHit.HitCheck();				//当たり判定

		ScreenFlip();	//裏画面の内容を表に反映
	}

	//WaitKey();					//キー入力待ち
	DxLib_End();				//DXライブラリ使用の終了処理
	return 0;					//ソフトの終了
}