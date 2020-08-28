#include "Scene.h"
#include "Enemy.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

//***************************************
//	敵とオブジェクトの生成
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Difficulty) {
		case 0:
			switch (Pattern[m]) {		//障害物のパターン決め
				case 0:
					g_immovableobj[m][1].setflg = TRUE;
					g_immovableobj[m][2].setflg = TRUE;
					g_immovableobj[m][23].setflg = TRUE;
					break;
				case 1:
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					break;
				case 2:
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					break;
				case 3:
					g_immovableobj[m][0].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					g_immovableobj[m][21].setflg = TRUE;
					break;
				case 4:
					g_immovableobj[m][10].setflg = TRUE;
					g_immovableobj[m][13].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					break;
				case 5:
					g_immovableobj[m][4].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][20].setflg = TRUE;
					break;
				case 6:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][15].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 7:
					g_immovableobj[m][0].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					g_immovableobj[m][17].setflg = TRUE;
					break;
				case 8:
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					break;
				case 9:
					g_immovableobj[m][5].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					break;
			}
			break;
			case 1:
				switch (Pattern[m]) {		//障害物のパターン決め
				case 0:
					g_immovableobj[m][0].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][17].setflg = TRUE;
					break;
				case 1:
					g_immovableobj[m][2].setflg = TRUE;
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][10].setflg = TRUE;
					g_immovableobj[m][18].setflg = TRUE;
					break;
				case 2:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					g_immovableobj[m][15].setflg = TRUE;
					g_immovableobj[m][22].setflg = TRUE;
					break;
				case 3:
					g_immovableobj[m][4].setflg = TRUE;
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][18].setflg = TRUE;
					break;
				case 4:
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					g_immovableobj[m][21].setflg = TRUE;
					break;
				case 5:
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][13].setflg = TRUE;
					g_immovableobj[m][15].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					break;
				case 6:
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					g_immovableobj[m][12].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 7:
					g_immovableobj[m][2].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 8:
					g_immovableobj[m][0].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 9:
					g_immovableobj[m][1].setflg = TRUE;
					g_immovableobj[m][12].setflg = TRUE;
					g_immovableobj[m][15].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					break;
				}
				break;
			case 2:
				switch (Pattern[m]) {		//障害物のパターン決め
				case 0:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					g_immovableobj[m][10].setflg = TRUE;
					g_immovableobj[m][17].setflg = TRUE;
					g_immovableobj[m][21].setflg = TRUE;
					break;
				case 1:
					g_immovableobj[m][5].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][13].setflg = TRUE;
					g_immovableobj[m][22].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
					g_immovableobj[m][2].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][9].setflg = TRUE;
					g_immovableobj[m][10].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
				case 2:
					g_immovableobj[m][12].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					g_immovableobj[m][20].setflg = TRUE;
					g_immovableobj[m][21].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 3:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][22].setflg = TRUE;
					break;
				case 4:
					g_immovableobj[m][0].setflg = TRUE;
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][14].setflg = TRUE;
					g_immovableobj[m][17].setflg = TRUE;
					break;
				case 5:
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][11].setflg = TRUE;
					g_immovableobj[m][13].setflg = TRUE;
					g_immovableobj[m][18].setflg = TRUE;
					g_immovableobj[m][24].setflg = TRUE;
					break;
				case 6:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][10].setflg = TRUE;
					g_immovableobj[m][15].setflg = TRUE;
					g_immovableobj[m][21].setflg = TRUE;
					break;
				case 7:
					g_immovableobj[m][2].setflg = TRUE;
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][8].setflg = TRUE;
					g_immovableobj[m][12].setflg = TRUE;
					g_immovableobj[m][22].setflg = TRUE;
					break;
				case 8:
					g_immovableobj[m][3].setflg = TRUE;
					g_immovableobj[m][4].setflg = TRUE;
					g_immovableobj[m][7].setflg = TRUE;
					g_immovableobj[m][16].setflg = TRUE;
					g_immovableobj[m][20].setflg = TRUE;
					break;
				case 9:
					g_immovableobj[m][4].setflg = TRUE;
					g_immovableobj[m][5].setflg = TRUE;
					g_immovableobj[m][6].setflg = TRUE;
					g_immovableobj[m][18].setflg = TRUE;
					g_immovableobj[m][19].setflg = TRUE;
					break;
				}
				break;
		}
	}

	//for (int m = 0; m < MAPMAX; m++) {	//敵の生成
	//	for (int e = 0; e < IMMOVABLEOBJMAX; e++) {
	//		g_enemy[m][e].setflg = TRUE;
	//	}
	//}


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

		//for (int e = 0; e < ENEMYMAX; e++) {	//敵の生成
		//	if (g_enemy[m][e].setflg == TRUE) {
		//		if (g_enemy[m][e].flg == FALSE) {
		//			g_enemy[m][e].mx = 0;
		//			g_enemy[m][e].my = (-m * HEIGHT) + 100;
		//			g_enemy[m][e].flg = TRUE;
		//		}
		//	}
		//}
	}
}
//***********************************************
//	敵とオブジェクトの描画
//***********************************************
void Enemy::DrawImmovableObj(void) {
	static int Bf = 0;
	static int Cf = 0;
	static int Df = 0;
	static int Co = 0;
	Co++;
	if (Co % 3 == 0) {
		Cf++;
		Df++;
	}
	if (Co % 2 == 0)Bf++;
	if (Bf == 12)Bf = 0;
	if (Cf == 16)Cf = 0;
	if (Df == 4)Df = 0;
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
				//DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, 0x00ff00, TRUE);
				if(m<8)DrawRotaGraph(g_immovableobj[m][i].x, g_immovableobj[m][i].y, 1,0,ButImg[Bf],TRUE);
				else if (m < 13)DrawRotaGraph(g_immovableobj[m][i].x, g_immovableobj[m][i].y, 1, 0, DroImg[Df], TRUE);
				else if (m < MAPMAX)DrawRotaGraph(g_immovableobj[m][i].x, g_immovableobj[m][i].y, 1, 0, CloImg[Cf], TRUE);
			}
			if (g_immovableobj[m][i].setflg == FALSE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //動かせる障害物の描画
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 0, 0), TRUE);
			}
		}

		//for (int e = 0; e < ENEMYMAX; e++) {
		//	if (g_enemy[m][e].setflg == TRUE) {
		//		DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //敵の描画
		//	}
		//}
	}
}
//************************************************
//	敵の移動
//************************************************
//void Enemy::MoveEnemy(void) {
//
//	for (int m = 0; m < MAPMAX; m++) {
//		for (int e = 0; e < ENEMYMAX; e++) {
//			if (g_enemy[m][e].flg == true) {
//				if (g_enemy[m][e].mx <= 50) g_enemy[m][e].move = true;	//x座標が50以下で右移動フラグon
//				else if (g_enemy[m][e].mx >= WIDTH - 100) g_enemy[m][e].move = false; //x座標がWIDTH-100以上で左移動フラグon
//
//				if (g_enemy[m][e].move == true)	g_enemy[m][e].mx += 3;
//				else if (g_enemy[m][e].move == false) g_enemy[m][e].mx -= 3;
//			}
//		}
//	}
//}
//************************************************
//	画像読み込み
//************************************************
int LoadImages() {

	if ((myEnemy.EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//動かせる障害物画像の読み込み

	return 0;
}