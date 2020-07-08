
#include <DxLib.h>

/************�񋓑̂̐錾*******************/

typedef enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_MAIN,
	GAME_END,
	GAME_RESULT,
	GAME_OPTION,
	END = 99
};
/************�萔�̐錾*********************/

/************�ϐ��̐錾*********************/

//"g_�c"�̓O���[�o���ϐ��ł���

int g_OldKey; // �O��̓��̓L�[
int g_NowKey; // ����̓��̓L�[
int g_KeyFlg; // ���̓L�[���
int g_GameState = GAME_TITLE; // �Q�[�����[�h
int g_TitleImage; // �^�C�g���摜 
/************�֐��̃v���g�^�C�v�錾*********/
void DrawGameTitle();
void GameInit();
void DrawEnd();
void GameMain();
void Option();
void DrawResult();

/************�v���O�����̊J�n***************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//SetMainWindowText(" �{ �� �� �X"); // �^�C�g����ݒ�
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ŋN��
	if (DxLib_Init() == -1) return -1; // DX ���C�u�����̏���������
	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ��� 

	//�Q�[�����[�v�̊J�n
	while (ProcessMessage() == 0
		&& g_GameState != END
		&& !(g_KeyFlg & PAD_INPUT_START)) {

		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);//PAD+�L�[���擾
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen(); // ��ʂ̏����� 

		/*�����œK�ȏ������ł͂Ȃ��̂͏��m*/

		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle(); //�^�C�g������
			break;

		case GAME_INIT:
			GameInit(); //�Q�[����������
			break;

		case GAME_END:
			DrawEnd(); //�G���h�`�揈��
			break;

		case GAME_MAIN:
			GameMain(); //�Q�[�����C������
			break;

		case GAME_RESULT:
			DrawResult(); //���U���g�`�揈��
			break;

		case GAME_OPTION:
			Option();
		}
		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End(); // DX ���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I�� 
}

/**********�^�C�g��***********/
void DrawGameTitle() {

	DrawString(0,0,"Title",0xffffff);
	DrawString(0, 40, "[Space] Start", 0xffffff);
	DrawString(0, 60, "[��] End", 0xffffff);
	DrawString(0, 80, "[��] Option", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_10) {
		g_GameState = GAME_INIT;
	}

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		g_GameState = GAME_END;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		g_GameState = GAME_OPTION;
	}
}

/**********������***********/
void GameInit() {

	DrawString(0, 0, "initing...", 0xffffff);
	WaitTimer(60);
	g_GameState = GAME_MAIN;
}
/*********�Q�[�����C��***********/
void GameMain() {
	static int flg = 0;
	


	switch(flg){
	case 1:
		DrawString(0, 0, "Pause", 0xffffff);
		DrawString(0, 40, "[Space] Return to Game", 0xffffff);
		DrawString(0, 60, "[��] Option", 0xffffff);
		DrawString(0, 80, "[��] Return to Title", 0xffffff);

		if (g_KeyFlg&PAD_INPUT_10) {
			flg = 0;
		}

		if (g_KeyFlg&PAD_INPUT_LEFT) {
			g_GameState = GAME_OPTION;
		}

		if (g_KeyFlg&PAD_INPUT_RIGHT) {
			g_GameState = GAME_TITLE;
		}
	break;
		
	
	default:
		DrawString(0, 0, "Game Main", 0xffffff);
		DrawString(0, 40, "[Space] Pause", 0xffffff);
		DrawString(0, 60, "[��] Result", 0xffffff);

		if (g_KeyFlg&PAD_INPUT_10) {
			flg = 1;
		}

		if (g_KeyFlg&PAD_INPUT_LEFT) {
			g_GameState = GAME_RESULT;
		}
		break;
	}
}
/*�I�v�V�����iVolume�����j*/
void Option() {
	static int BGMVol = 75;
	DrawString(0, 0, "Option", 0xffffff);
	DrawFormatString(0, 180, 0xffffff, "BGMVol:%d",BGMVol);
	DrawString(0, 40, "[Space] Back Pause", 0xffffff);
	DrawString(0, 60, "[��] BGMVol Down", 0xffffff);
	DrawString(0, 80, "[��] BGMVol UP", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		BGMVol--;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		BGMVol++;
	}
	if (g_KeyFlg&PAD_INPUT_10) {
		g_GameState = GAME_MAIN;
	}
}
/*�Q�[�����U���g*/
void DrawResult() {
	DrawString(0, 0, "Result", 0xffffff);
	DrawString(0, 60, "[��] Replay", 0xffffff);
	DrawString(0, 80, "[��] Return to Title", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		g_GameState = GAME_MAIN;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		g_GameState = GAME_TITLE;
	}
}
/*�G���h*/
void DrawEnd() {
	DrawString(0, 0, "ENDING", 0xffffff);
	WaitTimer(120);
	g_GameState = END;
}