#include "Scene.h"

static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:�J�[�\���p OneShot:���d�����̖h�~ Flg:B�𗣂��ƃV�[�����ς��@


void Scene::Ending() {
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[decide]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[choose]);
	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//������
	DrawFillBox(MINIWINDOW_X, MINIWINDOW_Y, WINDOW_X - MINIWINDOW_X, MINIWINDOW_Y + (ADDPOS_Y * 5), 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// �s����

	DrawTriangle(CURSOR_X, CURSOR_Y * (36 + FixPos),
		CURSOR_X, CURSOR_Y * (38 + FixPos),
		CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (37 + FixPos), 0xffff00, TRUE);


	DrawString(STRING_X - ADDPOS_Y, STRING_Y - ADDPOS_Y, "�{���ɏI�����܂����H", 0xffffff);
	DrawString(STRING_X, STRING_Y, "YES", 0x00ff7f);
	DrawString(STRING_X, STRING_Y + ADDPOS_Y, "NO", 0xff7f00);
	DrawFormatString(0, 0, 0xffffff, "%d %d", Cursor,Flg);

	//����

	//�J�[�\��

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 1;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 1) ? Cursor++ : Cursor = 0;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}

	//��ʑJ�ڏ���
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		//(Cursor == 0) ? Before = Changer, Changer = END : Before = Changer, Changer = TITLE;
		(Cursor == 0) ? Before = Changer, Changer = END :  Changer = TITLE ;
		Cursor = 0, Flg = 0;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Cursor = 0, Flg = 0;
		Changer = TITLE;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}
}
