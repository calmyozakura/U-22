#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

#define WIDTH 640
#define HEIGHT 480

using namespace std;

//********************************************
//	定数の宣言
//********************************************
const int IMMOVABLEOBJMAX = 5;	//動かせるオブジェクトのMAX表示数
const int ENEMYMAX = 1;			//動く敵のMAX表示数
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

int Pattern = GetRand(2);		//敵や障害物などのパターン

bool CreateCheck = false;
bool InitFlg = false;				//初期処理をしたかの判定

//-円のテスト
// 円１の情報
int Cilcle = false;

float circle1_pos_x;
float circle1_pos_y;
float circle1_radius;

// 円２の情報
float circle2_pos_x;
float circle2_pos_y;
float circle2_radius;
//--------------------

struct PLAYER {
	int mx = 320, my = 400;	//	動く処理の座標
	int sx = 79, sy = 79;	//画像のサイズ

	float x = (WIDTH / 2);		//プレイヤーのx座標
	float y = (HEIGHT - 100);	//プレイヤーのy座標
	float r = 20.0f;	//プレイヤーの大きさ
};
struct PLAYER g_player;

typedef struct IMMOVABLEOBJ {
	int mx, my;	//	動く処理の座標
	int sx = 50, sy = 50;	//画像のサイズ

	float x = 150.0f;	//障害物のx座標
	float y = 200.0f;	//障害物のy座標
	float r = 25.0f;	//障害物の円の大きさ

	int flg;		//使用フラグ
};
struct IMMOVABLEOBJ g_immovableobj[IMMOVABLEOBJMAX];

typedef struct ENEMY{
	int mx,my;
	int sx = 50, sy = 50;
	int flg;
	int move;	//移動フラグ
};
ENEMY g_enemy[ENEMYMAX];

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit(void)
{
	// 障害物の初期設定 
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
		g_immovableobj[i].flg = FALSE;
	}

	// 敵の初期設定  
	for (int i = 0; i < ENEMYMAX; i++) {
		g_enemy[i].flg = FALSE;
		g_enemy[i].move = FALSE;
	}

	InitFlg = true;
}
//***************************************************
//	円と四角の当たり判定をとるための処理
//***************************************************
float DistanceSqrf(float L, float R, float T, float B ,float x, float y, float radius)
{
	if(L - radius > x || R + radius < x || T - radius > y || B + radius < y){//矩形の領域判定1
        return false;
    } 
    if(L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < radius * radius)){//左上の当たり判定
        return false;
    }
    if(R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < radius * radius)){//右上の当たり判定
        return false;
    }
    if(L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < radius * radius)){//左下の当たり判定
        return false;
    }
    if(R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < radius * radius)){//右下の当たり判定
        return false;
    }
    return true;//すべての条件が外れたときに当たっている
}

/***********************************************
 * 当たり判定
 ***********************************************/
void HitCheck(void)
{

	//	プレイヤーと障害物の当たり判定
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//プレイヤーと動かせるオブジェクト(円と円)
		hit_x[i] = g_player.x - g_immovableobj[i].x;	//プレイヤーと障害物のx座標の差
		hit_y[i] = g_player.y - g_immovableobj[i].y;	//プレイヤーと障害物のy座標の差
		hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//プレイヤーと障害物の円の半径の和

		if (hit_r[i] <= g_player.r + g_immovableobj[i].r)		//当たっているか判定
		{
			DrawString(10, HEIGHT - 20, "障害物とヒット", color);
		}
	}

	//プレイヤーと敵の当たり判定
	for (int e = 0; e < ENEMYMAX; e++) {	//円と四角
		if ((DistanceSqrf(g_enemy[e].mx, (g_enemy[e].mx + g_enemy[e].sx), g_enemy[e].my, (g_enemy[e].my + g_enemy[e].sy), g_player.x, g_player.y ,g_player.r) == true)) {
			DrawString(10, HEIGHT - 40, "敵とヒット", color);
		}

	}

}
//**********************************************
//	プレイヤーの描画
//**********************************************
void DrawPlayer(void) {
	DrawCircle(g_player.x, g_player.y, g_player.r, GetColor(0, 255, 255), true);
	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//プレイヤーの当たり判定可視化
}

//**************************************************
//	プレイヤーの移動
//**************************************************
void MovePlayer(void) {
	// ↑キーを押していたらPlayerを上に移動させる
	if (CheckHitKey(KEY_INPUT_UP) == 1) {
		g_player.y -= 3;
	}

	// ↓キーを押していたらPlayerを下に移動させる
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
		g_player.y += 3;
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
void CreateImmovableObj(void) {

	switch (Pattern) {		//障害物の生成
	case 0:
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[i].flg == false) {
				g_immovableobj[i].x = i * 100;
				g_immovableobj[i].y = i * 70 + 10;
			}
		}
		break;
	case 1:
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[i].flg == false) {
				g_immovableobj[i].x = i * -100;
				g_immovableobj[i].y = i * 70 + 10;
			}
		}
		break;
	}

	for (int e = 0; e < ENEMYMAX; e++) {	//敵の生成
		if (g_enemy[e].flg == false) {
			g_enemy[e].mx = 0;
			g_enemy[e].my = 100;
			g_enemy[e].flg = true;
		}
	}
}
//***********************************************
//	敵とオブジェクトの描画
//***********************************************
void DrawImmovableObj(void) {
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
		//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
		DrawCircle(g_immovableobj[i].x, g_immovableobj[i].y, g_immovableobj[i].r, (200, 200, 200), true);
	}

	for (int e = 0; e < ENEMYMAX; e++) {
		DrawGraph(g_enemy[e].mx, g_enemy[e].my, Enemy, TRUE); //敵の描画
	}
}
//************************************************
//	敵の移動
//************************************************
void MoveEnemy(void) {

	for (int e = 0; e < ENEMYMAX; e++) {
		if (g_enemy[e].flg == true) {
			if (g_enemy[e].mx <= 50) g_enemy[e].move = true;	//x座標が50以下で右移動フラグon
			else if (g_enemy[e].mx >= WIDTH - 100) g_enemy[e].move = false; //x座標がWIDTH-100以上で左移動フラグon

			if(g_enemy[e].move == true)	g_enemy[e].mx += 3;
			else if(g_enemy[e].move == false) g_enemy[e].mx -= 3;
		}
	}
}
//************************************************
//	画像読み込み
//************************************************
int LoadImages() {
	if((Player = LoadGraph("images/Player.png")) == -1) return -1;		//プレイヤー画像の読み込み
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//動かせる障害物画像の読み込み
	if ((Enemy = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);		//ウィンドウサイズの設定
	ChangeWindowMode(TRUE);	//ウィンドウモードの設定

	SetMainWindowText("DXライブラリテストプログラム");	//("タイトル名")
	SetDrawScreen(DX_SCREEN_BACK);	//描画先を裏画面に設定

	if (DxLib_Init() == -1)	return-1;	//DXライブラリ初期化処理
	if (LoadImages() == -1) return -1; // 画像読込み関数を呼び出し

	//ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//画面を初期化

		if(InitFlg == false) GameInit();	//初期化処理
		DrawPlayer();			//プレイヤーの描画
		MovePlayer();			//プレイヤーの移動
		CreateImmovableObj();	//障害物と敵の生成
		DrawImmovableObj();		//障害物と敵の描画
		MoveEnemy();			//敵の移動
		HitCheck();				//当たり判定

		ScreenFlip();	//裏画面の内容を表に反映
	}

	//WaitKey();					//キー入力待ち
	DxLib_End();				//DXライブラリ使用の終了処理
	return 0;					//ソフトの終了
}