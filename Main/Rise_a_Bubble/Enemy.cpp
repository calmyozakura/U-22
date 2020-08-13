#include "DxLib.h"
#include "Scene.h"
#include "Enemy.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

Enemy MyEnemy;

//***************************************************
//	�G�Ə�Q���̏�����
//***************************************************
//Enemy::Enemy()
//{
//
//	rx = 0;
//	ry = 0;
//
//	// ��Q���̏����ݒ� 
//	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//
//		Entire_x[i] = rx * (WIDTH / 5) + 45;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
//		Entire_y[i] = ry * (HEIGHT / 2) / 5 + 50;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
//
//		rx += 1;	//x���W
//
//		if (i % 5 == 4) {	//5�z�u����邲�Ƃ�x���W�����ɖ߂�y���W��1�i������
//			rx = 0;
//			ry += 1;
//		}
//	}
//
//	// ��Q���̏����ݒ� 
//	for (int m = 0; m < MAPMAX; m++) {
//		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
//
//			g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
//			g_immovableobj[m][i].setflg = false;	//��Q����z�u���邩�̃t���O��S��false��
//			g_immovableobj[m][i].flg = FALSE;
//		}
//
//		// �G�̏����ݒ�  
//		for (int i = 0; i < ENEMYMAX; i++) {
//			g_enemy[m][i].sx = 50;	//�G�̉���
//			g_enemy[m][i].sy = 50;	//�G�̏c��
//			g_enemy[m][i].setflg = true;	////��Q����z�u���邩�̃t���O��S��false��
//			g_enemy[m][i].flg = FALSE;
//			g_enemy[m][i].move = FALSE;
//		}
//	}
//
//	//InitFlg = true;
//}

//***************************************
//	�G�ƃI�u�W�F�N�g�̐���
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//��Q���̐���
		case 0:
			for (int i = 0; i < 15; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//��Q����z�u���邩�̃t���O��true��
			}
			break;
		case 1:
			for (int i = 10; i < 20; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//��Q����z�u���邩�̃t���O��S��true��
			}
			break;
		case 2:
			for (int i = 20; i < 25; i++) {
				g_immovableobj[m][i].setflg = TRUE;	//��Q����z�u���邩�̃t���O��S��true��
			}
			break;
		}
	}
	for (int m = 0; m < MAPMAX; m++) {	//��Q���̐���
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				if (g_immovableobj[m][i].flg == FALSE) {
					g_immovableobj[m][i].x = Entire_x[i];
					g_immovableobj[m][i].y = Entire_y[i] + (-m * HEIGHT);
					g_immovableobj[m][i].flg = TRUE;
				}
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
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
//	�G�ƃI�u�W�F�N�g�̕`��
//***********************************************
void Enemy::DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == TRUE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), TRUE);
			}
			if (g_immovableobj[m][i].setflg == FALSE) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 0, 0), TRUE);
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].setflg == TRUE) {
				DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //�G�̕`��
			}
		}
	}
}
//************************************************
//	�G�̈ړ�
//************************************************
void Enemy::MoveEnemy(void) {

	for (int m = 0; m < MAPMAX; m++) {
		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].flg == true) {
				if (g_enemy[m][e].mx <= 50) g_enemy[m][e].move = true;	//x���W��50�ȉ��ŉE�ړ��t���Oon
				else if (g_enemy[m][e].mx >= WIDTH - 100) g_enemy[m][e].move = false; //x���W��WIDTH-100�ȏ�ō��ړ��t���Oon

				if (g_enemy[m][e].move == true)	g_enemy[m][e].mx += 3;
				else if (g_enemy[m][e].move == false) g_enemy[m][e].mx -= 3;
			}
		}
	}
}
//************************************************
//	�摜�ǂݍ���
//************************************************
int LoadImages() {

	if ((myEnemy.EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���

	return 0;
}