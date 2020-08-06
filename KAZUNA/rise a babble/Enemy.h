#ifndef ENEMY_H

#define ENEMY_H
#include "DxLib.h"

#define IMMOVABLEOBJMAX 25	//��������I�u�W�F�N�g�̍ő�\����
#define ENEMYMAX 1			//�����G�̍ő�\����
#define MAPMAX 5			//�}�b�v�̍ő吔


using namespace std;

class Hit {
public:
	void HitCheck(void);
};

class Enemy : public Hit {
private:

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
		int mx, my;
		int sx, sy;
		int flg;	//�g�p�t���O
		int move;	//�ړ��t���O(false=�E,true=��)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
};

class Player : public Hit {
public:

	Player();				//�v���C���[�̃R���X�g���N�^
	void DrawPlayer(void);	//�v���C���[�̕`��
	void MovePlayer(void);	//�v���C���[�̈ړ�

	struct PLAYER {

		float x, y, r;	//x���W,y���W,���a
	};
	struct PLAYER g_player;
};


Enemy myEnemy;		//Enemy�I�u�W�F�N�g�𐶐�
Player myPlayer;	//Player�I�u�W�F�N�g�Ɛ���
Hit myHit;
//********************************************
//	�萔�̐錾
//********************************************
#define WIDTH 480
#define HEIGHT 640
//********************************************
//	�ϐ��̐錾
//********************************************
int PlayerImage;				//�v���C���[�̉摜�������
int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
int EnemyImage;		//�����G�̉摜�������ϐ�

int color = (255, 255, 255);
int red = GetColor(255, 0, 0);	//�ԐF
int yellow = GetColor(0, 255, 0);	//�ԐF
int White = GetColor(255, 255, 255);	//��

//int Pattern[MAPMAX];		//�G���Q���Ȃǂ̃p�^�[��

bool InitFlg = false;				//�����������������̔���

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
			g_enemy[m][i].sx = 50;
			g_enemy[m][i].sy = 50;
			g_enemy[m][i].flg = FALSE;
			g_enemy[m][i].move = FALSE;
		}
	}

	//InitFlg = true;
}
Player::Player() {
	g_player.x = (WIDTH / 2);		//�v���C���[��x���W
	g_player.y = (HEIGHT - 100);	//�v���C���[��y���W
	g_player.r = 20.0f;	//�v���C���[�̔��a
}
//***************************************************
//	�~�Ǝl�p�̓����蔻����Ƃ邽�߂̏���
//***************************************************
float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r)
{
	if (L - r > x || R + r < x || T - r > y || B + r < y) {//��`�̗̈攻��1
		return false;
	}
	if (L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < r * r)) {//����̓����蔻��
		return false;
	}
	if (R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < r * r)) {//�E��̓����蔻��
		return false;
	}
	if (L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < r * r)) {//�����̓����蔻��
		return false;
	}
	if (R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < r * r)) {//�E���̓����蔻��
		return false;
	}
	return true;//���ׂĂ̏������O�ꂽ�Ƃ��ɓ������Ă���
}


#endif // !ENEMY_H