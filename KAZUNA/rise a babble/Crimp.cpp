#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include "inertia.h"


using namespace std;



/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit(void)
{

	g_player.x = (WIDTH / 2);		//プレイヤーのx座標
	g_player.y = (HEIGHT - 100);	//プレイヤーのy座標
	g_player.r = 20.0f;	//プレイヤーの半径

	// 障害物の初期設定 
	for(int m = 0; m < MAPMAX; m++){
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			g_immovableobj[m][i].x = 0;	//障害物のx座標
			g_immovableobj[m][i].y = 0;	//障害物のy座標
			g_immovableobj[m][i].r = 30.0f;	//障害物の円の半径
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

	InitFlg = true;
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
void HitCheck(void)
{

	//	プレイヤーと障害物の当たり判定
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//プレイヤーと動かせるオブジェクト(円と円)
			hit_x[i] = g_player.x - g_immovableobj[m][i].x;	//プレイヤーと障害物のx座標の差
			hit_y[i] = g_player.y - g_immovableobj[m][i].y;	//プレイヤーと障害物のy座標の差
			hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//プレイヤーと障害物の円の半径の和

			if (hit_r[i] <= g_player.r + g_immovableobj[m][i].r)		//当たっているか判定
			{
				DrawString(100, HEIGHT - 20, "障害物とヒット", White);
			}
		}

	//プレイヤーと敵の当たり判定
		for (int e = 0; e < ENEMYMAX; e++) {	//円と四角
			if ((DistanceSqrf(g_enemy[m][e].mx, (g_enemy[m][e].mx + g_enemy[m][e].sx), g_enemy[m][e].my, (g_enemy[m][e].my + g_enemy[m][e].sy), g_player.x, g_player.y, g_player.r) == true)) {
				DrawString(100, HEIGHT - 40, "敵とヒット", White);
			}
		}
	}

}
//**********************************************
//	プレイヤーの描画
//**********************************************
//void DrawPlayer(void) {
//	DrawCircle(g_player.x, g_player.y, g_player.r, GetColor(0, 255, 255), true);
//	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//プレイヤーの当たり判定可視化
//}

//**************************************************
//	プレイヤーの移動
//**************************************************
//void MovePlayer(void) {
//	// ↑キーを押していたらPlayerを上に移動させる
//	if (CheckHitKey(KEY_INPUT_UP) == 1) {
//		if (g_player.y >= 400) {
//			g_player.y -= 3;
//		}
//		else {
//			for (int m = 0; m < MAPMAX; m++) {
//				for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//					g_immovableobj[m][i].y += 3;
//				}
//			
//				for (int e = 0; e < ENEMYMAX; e++) {
//					g_enemy[m][e].my += 3;
//				}
//			}
//		}
//	}
//
//	// ↓キーを押していたらPlayerを下に移動させる
//	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
//		if (g_player.y <= (HEIGHT - 100)) {
//			g_player.y += 3;
//		}
//		else {
//			for (int m = 0; m < MAPMAX; m++) {
//				for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//					g_immovableobj[m][i].y -= 3;
//				}
//			
//				for (int e = 0; e < ENEMYMAX; e++) {
//					g_enemy[m][e].my -= 3;
//				}
//			}
//		}
//	}
//
//	// ←キーを押していたらPlayerを左に移動させる
//	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
//		g_player.x -= 3;
//	}
//
//	// →キーを押していたらPlayerを右に移動させる
//	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
//		g_player.x += 3;
//	}
//}

//***************************************
//	敵とオブジェクトの生成
//***************************************
void CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//障害物の生成
		case 0:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = i * 100;
					g_immovableobj[m][i].y = (i * 70 + 10) + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
		case 1:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = WIDTH + (i * -100);
					g_immovableobj[m][i].y = (i * 70 + 10) + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
		case 2:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = WIDTH + (i * -100);
					g_immovableobj[m][i].y = (-m * HEIGHT) + 200;
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
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
void DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
			DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), true);
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, Enemy, TRUE); //敵の描画
		}
	}
}
//************************************************
//	敵の移動
//************************************************
void MoveEnemy(void) {

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
	if((Player = LoadGraph("images/Player.png")) == -1) return -1;		//プレイヤー画像の読み込み
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//動かせる障害物画像の読み込み
	if ((Enemy = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}

//プログラムは WinMain から始まります
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
//
//	SetGraphMode(WIDTH, HEIGHT, 16);		//ウィンドウサイズの設定
//	ChangeWindowMode(TRUE);	//ウィンドウモードの設定
//
//	SetMainWindowText("DXライブラリテストプログラム");	//("タイトル名")
//	SetDrawScreen(DX_SCREEN_BACK);	//描画先を裏画面に設定
//
//	if (DxLib_Init() == -1)	return-1;	//DXライブラリ初期化処理
//	if (LoadImages() == -1) return -1; // 画像読込み関数を呼び出し
//
//	srand((unsigned)time(NULL));	//時刻でランダムの初期値を決める
//	for (int p = 0; p < MAPMAX; p++) {
//		Pattern[p] = GetRand(2);	//0～3のランダムな値
//	}
//
//	//ループ
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
//
//		ClearDrawScreen();			//画面を初期化
//
//		if(InitFlg == false) GameInit();	//初期化処理
//		DrawPlayer();			//プレイヤーの描画
//		MovePlayer();			//プレイヤーの移動
//		CreateImmovableObj();	//障害物と敵の生成
//		DrawImmovableObj();		//障害物と敵の描画
//		MoveEnemy();			//敵の移動
//		HitCheck();				//当たり判定
//
//		ScreenFlip();	//裏画面の内容を表に反映
//	}
//
//	//WaitKey();					//キー入力待ち
//	DxLib_End();				//DXライブラリ使用の終了処理
//	return 0;					//ソフトの終了
//}