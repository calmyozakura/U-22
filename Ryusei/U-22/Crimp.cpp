#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

int Player;				//プレイヤーの画像をいれる
int ImmovableObj;		//動かない障害物の画像をいれる変数
int MovingEnemy;		//動く敵の画像をいれる変数

//-----------------------------------------------
int P_X = 320, P_Y = 400;					//プレイヤーの位置座標
int P_W = 79, P_H = 79;					//プレイヤーの横と縦の長さ

int MovingEnemy_X, MovingEnemy_Y;					//動く敵の位置座標(X,Y)
int MovingEnemy_W, MovingEnemy_H;					//動く敵の横と縦の長さ(W,H)
int Obj_X = 300, Obj_Y = 240;					//動かせる障害物の位置座標(X,Y)
int Obj_W = 50, Obj_H = 50;		//動かせる障害物の横と縦の長さ(W,H)

int color = (255, 255, 255);

bool CreateCheck = false;

int CreateEnemy() {

	if (CreateCheck == false) srand(time(NULL));

	for (int i = 0; i < 20; ++i) {
		Obj_X = rand() % 640;	//画面の横サイズ640内での乱数取得
		Obj_Y = rand() % 480;	//画面の縦サイズ480内での乱数取得
		DrawGraph(Obj_X, Obj_Y, ImmovableObj, TRUE); //動かせる障害物の描画
		DrawBox(Obj_X, Obj_Y, Obj_X + Obj_W, Obj_Y + Obj_H, color, FALSE);//動かせる障害物の当たり判定可視化
		if (i >= 20) CreateCheck = true;
	}

	DrawFormatString(0, 0, 0xff0000, "%d", CreateCheck);
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

	//画像読み込み ----------------------------------------------------------------
	Player = LoadGraph("images/Player.png");		//プレイヤー画像の読み込み
	ImmovableObj = LoadGraph("images/Move.png");	//動かせる障害物画像の読み込み
	//MovingEnemy = LoadGraph("images/Move.png");	//動く敵画像の読み込み
	//------------------------------------------------------------------------------

	//ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//画面を初期化

		//動かせる障害物とプレイヤーの当たり判定 ----------------------------------------
		if (((P_X > Obj_X && P_X < Obj_X + Obj_W) ||
			(Obj_X > P_X && Obj_X < P_X + P_W)) &&
			((P_Y > Obj_Y && P_Y < Obj_Y + Obj_H) ||
			(Obj_Y > P_Y && Obj_Y < P_Y + P_H))) {
			DrawFormatString(100, 0, 0xff0000, "当たり");	//当たり判定の検出(後に消す)
		}
		//--------------------------------------------------------------------------------

		DrawGraph(P_X, P_Y, Player, TRUE); //Playerの描画
		DrawBox(P_X, P_Y, P_X+ P_W, P_Y + P_H, color, FALSE);//プレイヤーの当たり判定可視化

		DrawGraph(Obj_X, Obj_Y, ImmovableObj, TRUE); //動かせる障害物の描画
		DrawBox(Obj_X, Obj_Y, Obj_X + Obj_W, Obj_Y + Obj_H, color, FALSE);//動かせる障害物の当たり判定可視化
		//CreateEnemy();	//動かせる障害物の生成

		//プレイヤーの移動と描画 --------------------------------------------
		// ↑キーを押していたらPlayerを上に移動させる
		if (CheckHitKey(KEY_INPUT_W) == 1) P_Y -= 3;

		// ↓キーを押していたらPlayerを下に移動させる
		if (CheckHitKey(KEY_INPUT_S) == 1) P_Y += 3;

		// ←キーを押していたらPlayerを左に移動させる
		if (CheckHitKey(KEY_INPUT_A) == 1) P_X -= 3;

		// →キーを押していたらPlayerを右に移動させる
		if (CheckHitKey(KEY_INPUT_D) == 1) P_X += 3;
		//---------------------------------------------------------------------

		ScreenFlip();	//裏画面の内容を表に反映
	}

	//WaitKey();					//キー入力待ち
	DxLib_End();				//DXライブラリ使用の終了処理
	return 0;					//ソフトの終了
}