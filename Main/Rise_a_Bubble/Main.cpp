//#include "DxLib.h"
#include "scene.h"
#include <cmath>
#include <math.h>
#include "Fps.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble");			// �^�C�g����ݒ�
	ChangeWindowMode(TRUE);						// �E�B���h�E���[�h�ŋN��
	SetGraphMode(WINDOW_X, WINDOW_Y, COLOR_BIT);
	SetDrawScreen(DX_SCREEN_BACK);				// �`����ʂ𗠂ɂ���
	if (DxLib_Init() == -1)return -1;

	Scene S;//�V�[���N���X���Ăяo��
	C_FPS F;
	if (S.LoadImages() == -1)return -1;

	while (ProcessMessage() == 0 && S.Changer != 99) {


		S.getKeyInput();
		ClearDrawScreen(); // ��ʂ̏�����
		switch (S.Changer)
		{
		case 0:S.Title(); break;//�^�C�g��
		case 1:S.GameMode(); break;
		case 2:S.GameInit(); break;//�Q�[���O�̏�����
		case 3:S.GameMain(); break;//�Q�[��
		case 4:S.Result(); break;//���U���g
		case 5:S.Option(); break;//�I�v�V����
		case 6:S.Ending(); break;//�I��

		default:goto finish; break;//�����܂ł����}����
		}
		F.Update();
		F.Draw();
		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f 
		F.Wait();
	}
finish://goto����̉��}����
	DxLib_End();				// DX ���C�u�����g�p�̏I������
	return 0;					// �\�t�g�̏I��
}