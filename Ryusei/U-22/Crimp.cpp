#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

using namespace std;

int Player;				//�v���C���[�̉摜�������
int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
int MovingEnemy;		//�����G�̉摜�������ϐ�

//-----------------------------------------------
int P_X = 320, P_Y = 400;					//�v���C���[�̈ʒu���W
int P_W = 79, P_H = 79;					//�v���C���[�̉��Əc�̒���

int MovingEnemy_X, MovingEnemy_Y;					//�����G�̈ʒu���W(X,Y)
int MovingEnemy_W, MovingEnemy_H;					//�����G�̉��Əc�̒���(W,H)
int Obj_X = 300, Obj_Y = 240;					//���������Q���̈ʒu���W(X,Y)
int Obj_W = 50, Obj_H = 50;		//���������Q���̉��Əc�̒���(W,H)

int color = (255, 255, 255);

bool CreateCheck = false;

int CreateEnemy() {

	if (CreateCheck == false) srand(time(NULL));

	for (int i = 0; i < 20; ++i) {
		Obj_X = rand() % 640;	//��ʂ̉��T�C�Y640���ł̗����擾
		Obj_Y = rand() % 480;	//��ʂ̏c�T�C�Y480���ł̗����擾
		DrawGraph(Obj_X, Obj_Y, ImmovableObj, TRUE); //���������Q���̕`��
		DrawBox(Obj_X, Obj_Y, Obj_X + Obj_W, Obj_Y + Obj_H, color, FALSE);//���������Q���̓����蔻�����
		if (i >= 20) CreateCheck = true;
	}

	DrawFormatString(0, 0, 0xff0000, "%d", CreateCheck);
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

	//�摜�ǂݍ��� ----------------------------------------------------------------
	Player = LoadGraph("images/Player.png");		//�v���C���[�摜�̓ǂݍ���
	ImmovableObj = LoadGraph("images/Move.png");	//���������Q���摜�̓ǂݍ���
	//MovingEnemy = LoadGraph("images/Move.png");	//�����G�摜�̓ǂݍ���
	//------------------------------------------------------------------------------

	//���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();			//��ʂ�������

		//���������Q���ƃv���C���[�̓����蔻�� ----------------------------------------
		if (((P_X > Obj_X && P_X < Obj_X + Obj_W) ||
			(Obj_X > P_X && Obj_X < P_X + P_W)) &&
			((P_Y > Obj_Y && P_Y < Obj_Y + Obj_H) ||
			(Obj_Y > P_Y && Obj_Y < P_Y + P_H))) {
			DrawFormatString(100, 0, 0xff0000, "������");	//�����蔻��̌��o(��ɏ���)
		}
		//--------------------------------------------------------------------------------

		DrawGraph(P_X, P_Y, Player, TRUE); //Player�̕`��
		DrawBox(P_X, P_Y, P_X+ P_W, P_Y + P_H, color, FALSE);//�v���C���[�̓����蔻�����

		DrawGraph(Obj_X, Obj_Y, ImmovableObj, TRUE); //���������Q���̕`��
		DrawBox(Obj_X, Obj_Y, Obj_X + Obj_W, Obj_Y + Obj_H, color, FALSE);//���������Q���̓����蔻�����
		//CreateEnemy();	//���������Q���̐���

		//�v���C���[�̈ړ��ƕ`�� --------------------------------------------
		// ���L�[�������Ă�����Player����Ɉړ�������
		if (CheckHitKey(KEY_INPUT_W) == 1) P_Y -= 3;

		// ���L�[�������Ă�����Player�����Ɉړ�������
		if (CheckHitKey(KEY_INPUT_S) == 1) P_Y += 3;

		// ���L�[�������Ă�����Player�����Ɉړ�������
		if (CheckHitKey(KEY_INPUT_A) == 1) P_X -= 3;

		// ���L�[�������Ă�����Player���E�Ɉړ�������
		if (CheckHitKey(KEY_INPUT_D) == 1) P_X += 3;
		//---------------------------------------------------------------------

		ScreenFlip();	//����ʂ̓��e��\�ɔ��f
	}

	//WaitKey();					//�L�[���͑҂�
	DxLib_End();				//DX���C�u�����g�p�̏I������
	return 0;					//�\�t�g�̏I��
}