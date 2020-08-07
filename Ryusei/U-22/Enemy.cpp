#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

int EnemyImage;		//�����G�̉摜�������ϐ�

class Enemy{
private:
#define IMMOVABLEOBJMAX 25	//��������I�u�W�F�N�g�̍ő�\����
#define ENEMYMAX 1			//�����G�̍ő�\����
#define MAPMAX 5			//�}�b�v�̍ő吔

	int Entire_x[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
	int Entire_y[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W

public:
	float hit_x[IMMOVABLEOBJMAX];	//�~�̓����蔻��_x
	float hit_y[IMMOVABLEOBJMAX];	//�~�̕ӂ蔻��_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//�~�̓����蔻��_x
	float hit_ey[ENEMYMAX];	//�~�̕ӂ蔻��_y
	float hit_er[ENEMYMAX];

	int Pattern[MAPMAX];		//�G���Q���Ȃǂ̃p�^�[��

	int rx, ry;	//��Q���̔z�u������炷���߂̕ϐ�

	Enemy();						//Enemy�̃R���X�g���N�^
	void CreateImmovableObj(void);	//�G�Ɠ��������Q������
	void DrawImmovableObj(void);	//�G�Ɠ��������Q���̕`��
	void MoveEnemy(void);	//�G�̈ړ�

	typedef struct IMMOVABLEOBJ {

		float x, y, r;	//x���W,y���W,���a
		bool setflg;	//��Q����z�u���邩�̃t���O
		int flg;		//�g�p�t���O
	};
	struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];

	typedef struct ENEMY {
		int mx, my;		//x���W,y���W
		int sx, sy;		//�c�A����
		bool setflg;	//�G��z�u���邩�̃t���O
		int flg;	//�g�p�t���O
		int move;	//�ړ��t���O(false=�E,true=��)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
}; 

Enemy myEnemy;		//Enemy�I�u�W�F�N�g�𐶐�

//********************************************
//	�萔�̐錾
//********************************************
#define WIDTH 480
#define HEIGHT 640

//***************************************************
//	�G�Ə�Q���̏�����
//***************************************************
Enemy::Enemy()
{

	rx = 0;
	ry = 0;

	// ��Q���̏����ݒ� 
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {

		Entire_x[i] = rx * (WIDTH / 5) + 45;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
		Entire_y[i] = ry * (HEIGHT / 2) / 5 + 50;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W

		rx += 1;	//x���W

		if (i % 5 == 4) {	//5�z�u����邲�Ƃ�x���W�����ɖ߂�y���W��1�i������
			rx = 0;
			ry += 1;
		}
	}

	// ��Q���̏����ݒ� 
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {

			g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
			g_immovableobj[m][i].setflg = false;	//��Q����z�u���邩�̃t���O��S��false��
			g_immovableobj[m][i].flg = FALSE;
		}

		// �G�̏����ݒ�  
		for (int i = 0; i < ENEMYMAX; i++) {
			g_enemy[m][i].sx = 50;	//�G�̉���
			g_enemy[m][i].sy = 50;	//�G�̏c��
			g_enemy[m][i].setflg = true;	////��Q����z�u���邩�̃t���O��S��false��
			g_enemy[m][i].flg = FALSE;
			g_enemy[m][i].move = FALSE;
		}
	}

	//InitFlg = true;
}
//***************************************
//	�G�ƃI�u�W�F�N�g�̐���
//***************************************
void Enemy::CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//��Q���̐���
		case 0:
			for (int i = 0; i < 15; i++) {
				g_immovableobj[m][i].setflg = true;	//��Q����z�u���邩�̃t���O��true��
			}
			break;
		case 1:
			for (int i = 10; i < 20; i++) {
				g_immovableobj[m][i].setflg = true;	//��Q����z�u���邩�̃t���O��S��true��
			}
			break;
		case 2:
			for (int i = 20; i < 25; i++) {
				g_immovableobj[m][i].setflg = true;	//��Q����z�u���邩�̃t���O��S��true��
			}
			break;
		}
	}
	for (int m = 0; m < MAPMAX; m++) {	//��Q���̐���
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == true) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = Entire_x[i];
					g_immovableobj[m][i].y = Entire_y[i] + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
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
//	�G�ƃI�u�W�F�N�g�̕`��
//***********************************************
void Enemy::DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			if (g_immovableobj[m][i].setflg == true) {
				//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
				DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), true);
			}
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].setflg == true) {
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

	if ((EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���

	return 0;
}