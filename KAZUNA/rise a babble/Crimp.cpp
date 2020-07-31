#include "DxLib.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include "inertia.h"


using namespace std;



/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit(void)
{

	g_player.x = (WIDTH / 2);		//�v���C���[��x���W
	g_player.y = (HEIGHT - 100);	//�v���C���[��y���W
	g_player.r = 20.0f;	//�v���C���[�̔��a

	// ��Q���̏����ݒ� 
	for(int m = 0; m < MAPMAX; m++){
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			g_immovableobj[m][i].x = 0;	//��Q����x���W
			g_immovableobj[m][i].y = 0;	//��Q����y���W
			g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
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

	InitFlg = true;
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
void HitCheck(void)
{

	//	�v���C���[�Ə�Q���̓����蔻��
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			hit_x[i] = g_player.x - g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
			hit_y[i] = g_player.y - g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
			hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

			if (hit_r[i] <= g_player.r + g_immovableobj[m][i].r)		//�������Ă��邩����
			{
				DrawString(100, HEIGHT - 20, "��Q���ƃq�b�g", White);
			}
		}

	//�v���C���[�ƓG�̓����蔻��
		for (int e = 0; e < ENEMYMAX; e++) {	//�~�Ǝl�p
			if ((DistanceSqrf(g_enemy[m][e].mx, (g_enemy[m][e].mx + g_enemy[m][e].sx), g_enemy[m][e].my, (g_enemy[m][e].my + g_enemy[m][e].sy), g_player.x, g_player.y, g_player.r) == true)) {
				DrawString(100, HEIGHT - 40, "�G�ƃq�b�g", White);
			}
		}
	}

}
//**********************************************
//	�v���C���[�̕`��
//**********************************************
//void DrawPlayer(void) {
//	DrawCircle(g_player.x, g_player.y, g_player.r, GetColor(0, 255, 255), true);
//	//DrawBox(g_player.mx, g_player.my, g_player.mx + g_player.sx, g_player.my + g_player.sy, color, FALSE);//�v���C���[�̓����蔻�����
//}

//**************************************************
//	�v���C���[�̈ړ�
//**************************************************
//void MovePlayer(void) {
//	// ���L�[�������Ă�����Player����Ɉړ�������
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
//	// ���L�[�������Ă�����Player�����Ɉړ�������
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
//	// ���L�[�������Ă�����Player�����Ɉړ�������
//	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
//		g_player.x -= 3;
//	}
//
//	// ���L�[�������Ă�����Player���E�Ɉړ�������
//	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
//		g_player.x += 3;
//	}
//}

//***************************************
//	�G�ƃI�u�W�F�N�g�̐���
//***************************************
void CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//��Q���̐���
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
void DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
			DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), true);
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, Enemy, TRUE); //�G�̕`��
		}
	}
}
//************************************************
//	�G�̈ړ�
//************************************************
void MoveEnemy(void) {

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
	if((Player = LoadGraph("images/Player.png")) == -1) return -1;		//�v���C���[�摜�̓ǂݍ���
	if ((ImmovableObj = LoadGraph("images/Move.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
	if ((Enemy = LoadGraph("images/Obje.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���

	return 0;
}

//�v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
//
//	SetGraphMode(WIDTH, HEIGHT, 16);		//�E�B���h�E�T�C�Y�̐ݒ�
//	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�̐ݒ�
//
//	SetMainWindowText("DX���C�u�����e�X�g�v���O����");	//("�^�C�g����")
//	SetDrawScreen(DX_SCREEN_BACK);	//�`���𗠉�ʂɐݒ�
//
//	if (DxLib_Init() == -1)	return-1;	//DX���C�u��������������
//	if (LoadImages() == -1) return -1; // �摜�Ǎ��݊֐����Ăяo��
//
//	srand((unsigned)time(NULL));	//�����Ń����_���̏����l�����߂�
//	for (int p = 0; p < MAPMAX; p++) {
//		Pattern[p] = GetRand(2);	//0�`3�̃����_���Ȓl
//	}
//
//	//���[�v
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
//
//		ClearDrawScreen();			//��ʂ�������
//
//		if(InitFlg == false) GameInit();	//����������
//		DrawPlayer();			//�v���C���[�̕`��
//		MovePlayer();			//�v���C���[�̈ړ�
//		CreateImmovableObj();	//��Q���ƓG�̐���
//		DrawImmovableObj();		//��Q���ƓG�̕`��
//		MoveEnemy();			//�G�̈ړ�
//		HitCheck();				//�����蔻��
//
//		ScreenFlip();	//����ʂ̓��e��\�ɔ��f
//	}
//
//	//WaitKey();					//�L�[���͑҂�
//	DxLib_End();				//DX���C�u�����g�p�̏I������
//	return 0;					//�\�t�g�̏I��
//}