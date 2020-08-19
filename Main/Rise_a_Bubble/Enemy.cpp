#include "DxLib.h"
#include "Scene.h"
#include "Enemy.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

Enemy MyEnemy;

//***************************************
//	“G‚ÆƒIƒuƒWƒFƒNƒg‚Ì¶¬
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//áŠQ•¨‚Ìƒpƒ^[ƒ“Œˆ‚ß
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
	}

	for (int m = 0; m < MAPMAX; m++) {	//“G‚Ì¶¬
		for (int e = 0; e < IMMOVABLEOBJMAX; e++) {
			g_enemy[m][e].setflg = TRUE;
		}
	}


	for (int m = 0; m < MAPMAX; m++) {	//áŠQ•¨‚Ì¶¬
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				if (g_immovableobj[m][i].flg == FALSE) {
					g_immovableobj[m][i].x = Entire_x[i];
					g_immovableobj[m][i].y = Entire_y[i] + (-m * HEIGHT);
					g_immovableobj[m][i].flg = TRUE;
				}
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//“G‚Ì¶¬
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
//	“G‚ÆƒIƒuƒWƒFƒNƒg‚Ì•`‰æ
//***********************************************
void Enemy::DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //“®‚©‚¹‚éáŠQ•¨‚Ì•`‰æ
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), TRUE);
			}
			if (g_immovableobj[m][i].setflg == FALSE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //“®‚©‚¹‚éáŠQ•¨‚Ì•`‰æ
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 0, 0), TRUE);
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].setflg == TRUE) {
				DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //“G‚Ì•`‰æ
			}
		}
	}
}
//************************************************
//	“G‚ÌˆÚ“®
//************************************************
void Enemy::MoveEnemy(void) {

	for (int m = 0; m < MAPMAX; m++) {
		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].flg == true) {
				if (g_enemy[m][e].mx <= 50) g_enemy[m][e].move = true;	//xÀ•W‚ª50ˆÈ‰º‚Å‰EˆÚ“®ƒtƒ‰ƒOon
				else if (g_enemy[m][e].mx >= WIDTH - 100) g_enemy[m][e].move = false; //xÀ•W‚ªWIDTH-100ˆÈã‚Å¶ˆÚ“®ƒtƒ‰ƒOon

				if (g_enemy[m][e].move == true)	g_enemy[m][e].mx += 3;
				else if (g_enemy[m][e].move == false) g_enemy[m][e].mx -= 3;
			}
		}
	}
}
//************************************************
//	‰æ‘œ“Ç‚İ‚İ
//************************************************
int LoadImages() {

	if ((myEnemy.EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//“®‚©‚¹‚éáŠQ•¨‰æ‘œ‚Ì“Ç‚İ‚İ

	return 0;
}