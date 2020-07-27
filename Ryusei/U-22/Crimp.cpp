#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

#define WIDTH 640
#define HEIGHT 480

using namespace std;

//********************************************
//	�萔�̐錾
//********************************************
const int IMMOVABLEOBJMAX = 5;	//��������I�u�W�F�N�g��MAX�\����
const int ENEMYMAX = 1;			//�����G��MAX�\����
//********************************************
//	�ϐ��̐錾
//********************************************
int Player;				//�v���C���[�̉摜�������
int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
int Enemy;		//�����G�̉摜�������ϐ�

float hit_x[IMMOVABLEOBJMAX];	//�~�̓����蔻��_x
float hit_y[IMMOVABLEOBJMAX];	//�~�̕ӂ蔻��_y
float hit_r[IMMOVABLEOBJMAX];

float hit_ex[ENEMYMAX];	//�~�̓����蔻��_x
float hit_ey[ENEMYMAX];	//�~�̕ӂ蔻��_y
float hit_er[ENEMYMAX];

int color = (255, 255, 255);
int red = GetColor(255, 0, 0);	//�ԐF
int yellow = GetColor(0, 255, 0);	//�ԐF

int Pattern = GetRand(2);		//�G���Q���Ȃǂ̃p�^�[��

bool CreateCheck = false;
bool InitFlg = false;				//�����������������̔���

//-�~�̃e�X�g
// �~�P�̏��
int Cilcle = false;

float circle1_pos_x;
float circle1_pos_y;
float circle1_radius;

// �~�Q�̏��
float circle2_pos_x;
float circle2_pos_y;
float circle2_radius;
//--------------------

struct PLAYER {
	int mx = 320, my = 400;	//	���������̍��W
	int sx = 79, sy = 79;	//�摜�̃T�C�Y

	float x = (WIDTH / 2);		//�v���C���[��x���W
	float y = (HEIGHT - 100);	//�v���C���[��y���W
	float r = 20.0f;	//�v���C���[�̑傫��
};
struct PLAYER g_player;

typedef struct IMMOVABLEOBJ {
	int mx, my;	//	���������̍��W
	int sx = 50, sy = 50;	//�摜�̃T�C�Y

	float x = 150.0f;	//��Q����x���W
	float y = 200.0f;	//��Q����y���W
	float r = 25.0f;	//��Q���̉~�̑傫��

	int flg;		//�g�p�t���O
};
struct IMMOVABLEOBJ g_immovableobj[IMMOVABLEOBJMAX];

typedef struct ENEMY{
	int mx,my;
	int sx = 50, sy = 50;
	int flg;
	int move;	//�ړ��t���O
};
ENEMY g_enemy[ENEMYMAX];

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit(void)
{
	// ��Q���̏����ݒ� 
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
		g_immovableobj[i].flg = FALSE;
	}

	// �G�̏����ݒ�  
	for (int i = 0; i < ENEMYMAX; i++) {
		g_enemy[i].flg = FALSE;
		g_enemy[i].move = FALSE;
	}

	InitFlg = true;
}
//***************************************************
//	�~�Ǝl�p�̓����蔻����Ƃ邽�߂̏���
//***************************************************
float DistanceSqrf(float L, float R, float T, float B ,float x, float y, float radius)
{
	if(L - radius > x || R + radius < x || T - radius > y || B + radius < y){//��`�̗̈攻��1
        return false;
    } 
    if(L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < radius * radius)){//����̓����蔻��
        return false;
    }
    if(R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < radius * radius)){//�E��̓����蔻��
        return false;
    }
    if(L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < radius * radius)){//�����̓����蔻��
        return false;
    }
    if(R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < radius * radius)){//�E���̓����蔻��
        return false;
    }
    return true;//���ׂĂ̏������O�ꂽ�Ƃ��ɓ������Ă���
}

/***********************************************
 * �����蔻��
 ***********************************************/
void HitCheck(void)
{

	//	�v���C���[�Ə�Q���̓����蔻��
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
		hit_x[i] = g_player.x - g_immovableobj[i].x;	//�v���C���[�Ə�Q����x���W�̍�
		hit_y[i] = g_player.y - g_immovableobj[i].y;	//�v���C���[�Ə�Q����y���W�̍�
		hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

		if (hit_r[i] <= g_player.r + g_immovableobj[i].r)		//�������Ă��邩����
		{
			DrawString(10, HEIGHT - 20, "��Q���ƃq�b�g", color);
		}
	}

	//�v���C���[�ƓG�̓����蔻��
	for (int e = 0; e < ENEMYMAX; e++) {	//�~�Ǝl�p
		if ((DistanceSqrf(g_enemy[e].mx, (g_enemy[e].mx + g_enemy[e].sx), g_enemy[e].my, (g_enemy[e].my + g_enemy[e].sy), g_player.x, g_player.y ,g_player.r) == true)) {
			DrawString(10, HEIGHT - 40, "�G�ƃq�b�g", color);
		}

	}

}
//**********************************************
//	�v���C���[�̕`��
//**********************************************
void DrawPlayer(void) {
	DrawCircle(g_player.x, g_player.y, g_player.r, GetColor(0, 255, 255), true);
	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//�v���C���[�̓����蔻�����
}

//**************************************************
//	�v���C���[�̈ړ�
//**************************************************
void MovePlayer(void) {
	// ���L�[�������Ă�����Player����Ɉړ�������
	if (CheckHitKey(KEY_INPUT_UP) == 1) {
		g_player.y -= 3;
	}

	// ���L�[�������Ă�����Player�����Ɉړ�������
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
		g_player.y += 3;
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
void CreateImmovableObj(void) {

	switch (Pattern) {		//��Q���̐���
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

	for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
		if (g_enemy[e].flg == false) {
			g_enemy[e].mx = 0;
			g_enemy[e].my = 100;
			g_enemy[e].flg = true;
		}
	}
}
//***********************************************
//	�G�ƃI�u�W�F�N�g�̕`��
//***********************************************
void DrawImmovableObj(void) {
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
		//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
		DrawCircle(g_immovableobj[i].x, g_immovableobj[i].y, g_immovableobj[i].r, (200, 200, 200), true);
	}

	for (int e = 0; e < ENEMYMAX; e++) {
		DrawGraph(g_enemy[e].mx, g_enemy[e].my, Enemy, TRUE); //�G�̕`��
	}
}
//************************************************
//	�G�̈ړ�
//************************************************
void MoveEnemy(void) {

	for (int e = 0; e < ENEMYMAX; e++) {
		if (g_enemy[e].flg == true) {
			if (g_enemy[e].mx <= 50) g_enemy[e].move = true;	//x���W��50�ȉ��ŉE�ړ��t���Oon
			else if (g_enemy[e].mx >= WIDTH - 100) g_enemy[e].move = false; //x���W��WIDTH-100�ȏ�ō��ړ��t���Oon

			if(g_enemy[e].move == true)	g_enemy[e].mx += 3;
			else if(g_enemy[e].move == false) g_enemy[e].mx -= 3;
		}
	}
}
//************************************************
//	�摜�ǂݍ���
//************************************************
int LoadImages() {
	if((Player = LoadGraph("images/Player.png")) == -1) return -1;		//�v���C���[�摜�̓ǂݍ���
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
	if ((Enemy = LoadGraph("images/Obje.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���

	return 0;
}

//�v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);		//�E�B���h�E�T�C�Y�̐ݒ�
	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�̐ݒ�

	SetMainWindowText("DX���C�u�����e�X�g�v���O����");	//("�^�C�g����")
	SetDrawScreen(DX_SCREEN_BACK);	//�`���𗠉�ʂɐݒ�

	if (DxLib_Init() == -1)	return-1;	//DX���C�u��������������
	if (LoadImages() == -1) return -1; // �摜�Ǎ��݊֐����Ăяo��

	//���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//��ʂ�������

		if(InitFlg == false) GameInit();	//����������
		DrawPlayer();			//�v���C���[�̕`��
		MovePlayer();			//�v���C���[�̈ړ�
		CreateImmovableObj();	//��Q���ƓG�̐���
		DrawImmovableObj();		//��Q���ƓG�̕`��
		MoveEnemy();			//�G�̈ړ�
		HitCheck();				//�����蔻��

		ScreenFlip();	//����ʂ̓��e��\�ɔ��f
	}

	//WaitKey();					//�L�[���͑҂�
	DxLib_End();				//DX���C�u�����g�p�̏I������
	return 0;					//�\�t�g�̏I��
}