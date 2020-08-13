#include "DxLib.h"
#include "Scene.h"
#include "Enemy.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

Enemy MyEnemy;

//***************************************************
//	敵と障害物の初期化
//***************************************************
//Enemy::Enemy()
//{
//
//	rx = 0;
//	ry = 0;
//
//	// 障害物の初期設定 
//	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//
//		Entire_x[i] = rx * (WIDTH / 5) + 45;		//障害物の座標に入れる前にあらかじめ取っておく座標
//		Entire_y[i] = ry * (HEIGHT / 2) / 5 + 50;		//障害物の座標に入れる前にあらかじめ取っておく座標
//
//		rx += 1;	//x座標
//
//		if (i % 5 == 4) {	//5個配置されるごとにx座標を左に戻しy座標を1段下げる
//			rx = 0;
//			ry += 1;
//		}
//	}
//
//	// 障害物の初期設定 
//	for (int m = 0; m < MAPMAX; m++) {
//		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//
//			g_immovableobj[m][i].r = 30.0f;	//障害物の円の半径
//			g_immovableobj[m][i].setflg = false;	//障害物を配置するかのフラグを全てfalseに
//			g_immovableobj[m][i].flg = FALSE;
//		}
//
//		// 敵の初期設定  
//		for (int i = 0; i < ENEMYMAX; i++) {
//			g_enemy[m][i].sx = 50;	//敵の横幅
//			g_enemy[m][i].sy = 50;	//敵の縦幅
//			g_enemy[m][i].setflg = true;	////障害物を配置するかのフラグを全てfalseに
//			g_enemy[m][i].flg = FALSE;
//			g_enemy[m][i].move = FALSE;
//		}
//	}
//
//	//InitFlg = true;
//}

//***************************************
//	敵とオブジェクトの生成
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//障害物の生成
		case 0:
			for (int i = 0; i < 15; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//障害物を配置するかのフラグをtrueに
			}
			break;
		case 1:
			for (int i = 10; i < 20; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//障害物を配置するかのフラグを全てtrueに
			}
			break;
		case 2:
			for (int i = 20; i < 25; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//障害物を配置するかのフラグを全てtrueに
			}
			break;
		}
	}
	for (int m = 0; m < MAPMAX; m++) {	//障害物の生成
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				if (g_immovableobj[m][i].flg == FALSE) {
					g_immovableobj[m][i].x = Entire_x[i];
					g_immovableobj[m][i].y = Entire_y[i] + (-m * HEIGHT);
					g_immovableobj[m][i].flg = TRUE;
				}
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//敵の生成
			if (g_enemy[m][e].setflg == TRUE) {
				if (g_enemy[m][e].flg == FALSE) {
					g_enemy[m][e].mx = 0;
					g_enemy[m][e].my = (-m * HEIGHT) + 100;
					g_enemy[m][e].flg = TRUE;
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
			if (g_immovableobj[m][i].setflg == TRUE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), TRUE);
			}
			if (g_immovableobj[m][i].setflg == FALSE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 0, 0), TRUE);
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].setflg == TRUE) {
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

	if ((myEnemy.EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}