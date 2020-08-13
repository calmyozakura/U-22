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
		int mx, my;
		int sx, sy;
		int flg;	//�g�p�t���O
		int move;	//�ړ��t���O(false=�E,true=��)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
};

class Player : public Hit{
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
	for(int m = 0; m < MAPMAX; m++){
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
float DistanceSqrf(float L, float R, float T, float B ,float x, float y, float r)
{
	if(L - r > x || R + r < x || T - r > y || B + r < y){//��`�̗̈攻��1
        return false;
    } 
    if(L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < r * r)){//����̓����蔻��
        return false;
    }
    if(R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < r * r)){//�E��̓����蔻��
        return false;
    }
    if(L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < r * r)){//�����̓����蔻��
        return false;
    }
    if(R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < r * r)){//�E���̓����蔻��
        return false;
    }
    return true;//���ׂĂ̏������O�ꂽ�Ƃ��ɓ������Ă���
}

/***********************************************
 * �����蔻��
 ***********************************************/
void Hit::HitCheck(void)
{

	//	�v���C���[�Ə�Q���̓����蔻��
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			myEnemy.hit_x[i] = myPlayer.g_player.x - myEnemy.g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
			myEnemy.hit_y[i] = myPlayer.g_player.y - myEnemy.g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
			myEnemy.hit_r[i] = sqrt(myEnemy.hit_x[i] * myEnemy.hit_x[i] + myEnemy.hit_y[i] * myEnemy.hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

			if (myEnemy.hit_r[i] <= myPlayer.g_player.r + myEnemy.g_immovableobj[m][i].r)		//�������Ă��邩����
			{
				DrawString(100, HEIGHT - 20, "��Q���ƃq�b�g", White);
			}
		}

	//�v���C���[�ƓG�̓����蔻��
		for (int e = 0; e < ENEMYMAX; e++) {	//�~�Ǝl�p
			if ((DistanceSqrf(myEnemy.g_enemy[m][e].mx, (myEnemy.g_enemy[m][e].mx + myEnemy.g_enemy[m][e].sx), myEnemy.g_enemy[m][e].my, (myEnemy.g_enemy[m][e].my + myEnemy.g_enemy[m][e].sy), myPlayer.g_player.x, myPlayer.g_player.y, myPlayer.g_player.r) == true)) {
				DrawString(100, HEIGHT - 40, "�G�ƃq�b�g", White);
			}
		}
	}

}
//**********************************************
//	�v���C���[�̕`��
//**********************************************
void Player::DrawPlayer(void) {
	DrawCircle(g_player.x, g_player.y, g_player.r, yellow, true);
	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//�v���C���[�̓����蔻�����
}

//**************************************************
//	�v���C���[�̈ړ�
//**************************************************
void Player::MovePlayer(void) {
	// ���L�[�������Ă�����Player����Ɉړ�������
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

	// ���L�[�������Ă�����Player�����Ɉړ�������
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

	// ���L�[�������Ă�����Player�����Ɉړ�������
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		g_player.x -= 3;
	}

	// ���L�[�������Ă�����Player���E�Ɉړ�������
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		g_player.x += 3;
	}
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

	//	for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
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

			for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
				if (g_enemy[m][e].flg == false) {
					g_enemy[m][e].mx = 0;
					g_enemy[m][e].my = (-m * HEIGHT) + 100;
					g_enemy[m][e].flg = true;
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
			DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, EnemyImage, TRUE); //�G�̕`��
		}
	}
}
//************************************************
//	�G�̈ړ�
//************************************************
void Enemy::MoveEnemy(void) {

	for(int m = 0; m <MAPMAX; m++){
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
	if((PlayerImage = LoadGraph("images/Player.png")) == -1) return -1;		//�v���C���[�摜�̓ǂݍ���
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
	if ((EnemyImage = LoadGraph("images/Obje.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���

	return 0;
}

//�v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetGraphMode(WIDTH, HEIGHT, 16);		//�E�B���h�E�T�C�Y�̐ݒ�
	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�̐ݒ�

	SetMainWindowText("DX���C�u�����e�X�g�v���O����");	//("�^�C�g����")
	SetDrawScreen(DX_SCREEN_BACK);	//�`���𗠉�ʂɐݒ�

	if (DxLib_Init() == -1)	return-1;	//DX���C�u��������������
	if (LoadImages() == -1) return -1; // �摜�Ǎ��݊֐����Ăяo��

	srand((unsigned)time(NULL));	//�����Ń����_���̏����l�����߂�
	for (int p = 0; p < MAPMAX; p++) {
		myEnemy.Pattern[p] = GetRand(2);	//0�`3�̃����_���Ȓl
	}

	//���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//��ʂ�������

		myPlayer.DrawPlayer();			//�v���C���[�̕`��
		myPlayer. MovePlayer();			//�v���C���[�̈ړ�
		myEnemy.CreateImmovableObj();	//��Q���ƓG�̐���
		myEnemy.DrawImmovableObj();		//��Q���ƓG�̕`��
		myEnemy.MoveEnemy();			//�G�̈ړ�
		myHit.HitCheck();				//�����蔻��

		ScreenFlip();	//����ʂ̓��e��\�ɔ��f
	}

	//WaitKey();					//�L�[���͑҂�
	DxLib_End();				//DX���C�u�����g�p�̏I������
	return 0;					//�\�t�g�̏I��
}