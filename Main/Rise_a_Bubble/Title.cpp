#include "Scene.h"


static int Cursor = 0, Cursor2 = 0;//Cursor/Cursor2 :�J�[�\���p
static int OneShot = 0, Flg = 0; //OneShot:���d�����̖h�~ Flg:B�𗣂��ƃV�[�����ς��
//static bool State = false;//End�p

void Scene::Title() {
	//�`��
	SetFontSize(24);

	DrawString(STRING_X, TITLE_Y, "�^�C�g�����S", 0xffffff);

	DrawString(STRING_X, STRING_Y, "Game Start", 0xffffff);
	DrawString(STRING_X, STRING_Y + ADDPOS_Y, "  Option  ", 0xffffff);
	DrawString(STRING_X, STRING_Y + (ADDPOS_Y * 2), "    END   ", 0xffffff);

	//if (State != true)
	DrawTriangle(CURSOR_X, CURSOR_Y * (36 + FixPos),
		CURSOR_X, CURSOR_Y * (38 + FixPos),
		CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (37 + FixPos), 0xffff00, TRUE);


#ifdef DEBUG
	for (int i = 0; i < 16; i++) {
		DrawFormatString(50, 200 + (i * 20), 0xffffff, "%d", input.Buttons[i]);
	}
	/*
	//ENDING����
	if (State == true) {
		//�`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//������
		DrawFillBox(MINIWINDOW_X, MINIWINDOW_Y, WINDOW_X - MINIWINDOW_X, MINIWINDOW_Y + (ADDPOS_Y * 5), 0xffffff);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// �s����

		DrawTriangle(CURSOR_X  , CURSOR_Y * (36 + FixPos2),
			CURSOR_X , CURSOR_Y * (38 + FixPos2),
			CURSOR_X +ADDPOS_Y/2, CURSOR_Y * (37 + FixPos2), 0xffff00, TRUE);


		DrawString(STRING_X-ADDPOS_Y, STRING_Y - ADDPOS_Y, "�{���ɏI�����܂����H", 0xffffff);
		DrawString(STRING_X, STRING_Y, "YES", 0x00ff7f);
		DrawString(STRING_X, STRING_Y+ADDPOS_Y, "NO", 0xff7f00);

		//����

		//�J�[�\��

		if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
			(Cursor2 > 0) ? Cursor2-- : Cursor2 = 1;
			OneShot = 1;
		}
		else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
			(Cursor2 < 1) ? Cursor2++ : Cursor2 = 0;
			OneShot = 1;
		}

		//��ʑJ�ڏ���
		if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
			OneShot = 1, Flg = 1;
		}
		else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
		{
			(Cursor2 == 0) ? Before = Changer, Changer = END : State = false;
			Cursor2 = 0, Flg = 0;
		}

		if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
			|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
			|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

			OneShot = 0;
		}
	}*/




#endif // DEBUG

	/*����*/

	//�J�[�\��

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0 /*&& State != true*/) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		OneShot = 1;
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0 /*&& State != true*/) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		OneShot = 1;
	}
	//��ʑJ�ڏ���
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0 /*&& State != true*/) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1 /*&& State != true*/)
	{
		if (Cursor == 0)Before = Changer, Changer = GAMEMODE;
		else if (Cursor == 1)Before = Changer, Changer = OPTION;
		else if (Cursor == 2)Before = Changer, Changer = ENDING;//State = true;

		Cursor = 0, Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}


}