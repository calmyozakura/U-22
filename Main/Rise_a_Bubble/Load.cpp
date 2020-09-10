#include "Scene.h"

static int Cursor = 0;//Cursor:�J�[�\���p
bool Ld_OneShot = false, Ld_Flg = false;// OneShot:���d�����̖h�~ Flg:B�𗣂��ƃV�[�����ς��@
bool LBk_OneShot = false, LBk_Flg = false;	//A�{�^��(�o�b�N)�p�̑��d�����h�~
void Scene::Load() {
	sound.PlayBGM(sound.stack);

	DrawGraph(0, 0, images.back[14], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawFillBox(25, 220, WINDOW_X - 25, 450, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// �s����

	DrawString(140, TITLE_Y, "COURSE LOAD", 0xffffff);
	//DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 18, 0xff00ff, "%.2f", Score);
	DrawString(100, (WINDOW_Y / 32) * 13, "CourseA", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 13, "CourseB", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 15, "CourseC", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 15, "CourseD", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 17, "CourseE", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 17, "CourseF", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 19, "CourseG", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 19, "CourseH", 0xffffff);

	//DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (42 + Cursor * 2),
	//	(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (44 + Cursor * 2),
	//	(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (43 + Cursor * 2), 0xffff00, TRUE);
	DrawTriangle(4 * (17 + (Cursor % 2) * 40), 13 * (20 + (Cursor / 2) * 3),
		4 * (17 + (Cursor % 2) * 40), 13 * (22 + (Cursor / 2) * 3),
		4 * (22 + (Cursor % 2) * 40), 13 * (21 + (Cursor / 2) * 3), 0xffff00, TRUE);
	//�J�[�\��
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Ld_OneShot == false) {
		(Cursor <= 1) ? Cursor += 6 : Cursor -= 2;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Ld_OneShot == false) {
		(Cursor >= 6) ? Cursor -= 6 : Cursor += 2;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && Ld_OneShot == false) {
		((Cursor % 2) == 1) ? Cursor-- : Cursor++;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && Ld_OneShot == false) {
		((Cursor % 2) == 0) ? Cursor++ : Cursor--;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}


	//��ʑJ�ڏ���
	if (input.Buttons[XINPUT_BUTTON_B] && Ld_OneShot == false) {
		Ld_OneShot = true, Ld_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Ld_Flg == true)
	{
		//if (Cursor == 0)Before = Changer, Changer = TITLE;
		//else if (Cursor == 1)Before = Changer, Changer = GAMEINIT;
		//else Before = Changer, Changer = GAMEMODE;
		Difficulty = 0;			//�{���ۑ�������Փx�������
		LoadNumber = Cursor;	//�J�[�\���ʒu�̔ԍ��������
		CodeRnd_flg = FALSE, Pass_Flg = FALSE, Load_Flg = TRUE, Before = Changer, Changer = GAMEINIT;		//��Փx�I��
		sound.PlaySE(sound.decide);
		Cursor = 0, Ld_Flg = false;
	}


	if (input.Buttons[XINPUT_BUTTON_A] && LBk_OneShot == false) {
		LBk_OneShot = true, LBk_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_A] && LBk_Flg == true)
	{
		Before = Changer, Changer = GAMEMODE;
		sound.PlaySE(sound.cancel);
		Cursor = 0, LBk_OneShot = false, LBk_Flg = false;
	}

	if (Ld_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN]
		|| input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]
		|| input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {

		Ld_OneShot = false;
	}
}