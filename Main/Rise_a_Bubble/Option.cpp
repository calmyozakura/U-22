#include "Scene.h"
static int Cursor = 0;//Cursor:�J�[�\���p 
bool  Op_OneShot = false, Op_Flg = false; //OneShot:���d�����̖h�~ Flg : B�𗣂��ƃV�[�����ς��
void Scene::Option() {
	//����
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[decide]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[choose]);
	
	DrawGraph(0, 0, images.back[14], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//������
	DrawFillBox(25, 220, WINDOW_X - 25, 450, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// �s����
	//�`��
	DrawString(WINDOW_HALF_X - 40, ADDPOS_Y + 30, "Option", 0x222222);
	DrawFormatString(CURSOR_X, CURSOR_Y * 24, 0xffffff, "BGM_vol = %d", BGM_vol);
	DrawFormatString(CURSOR_X, CURSOR_Y * 31, 0xffffff, " SE_vol = %d", SE_vol);
	/*DrawFormatString(0, 120, 0xffffff, "[��] Down");
	DrawFormatString(0, 140, 0xffffff, "[��] UP");*/

	DrawBox(CURSOR_X , CURSOR_Y * 28, (WINDOW_X - ADDPOS_X), CURSOR_Y * 29, 0xffffff, TRUE);
	DrawCircle((Bar * BGM_vol / Percent) + CURSOR_X,
		CURSOR_Y * 28.5, Radius, 0x00ff77);

	DrawBox(CURSOR_X , CURSOR_Y * 35, (WINDOW_X - ADDPOS_X), CURSOR_Y * 36, 0xffffff, TRUE);
	DrawCircle((Bar * SE_vol / Percent) + CURSOR_X,
		CURSOR_Y * 35.5, Radius, 0x00ff77);

	DrawString(CURSOR_X , CURSOR_Y * 41, "Back", 0xffffff);

	DrawTriangle(CURSOR_X/2 ,CURSOR_Y * (27 + Cursor * 7),
		CURSOR_X/2, CURSOR_Y * (29 + Cursor * 7),
		CURSOR_X/2 + ADDPOS_X / 2, CURSOR_Y * (28 + Cursor * 7), 0xffff00, TRUE);

	/*����*/

	//���ꂼ��̑O��͈�
	if (BGM_vol > 100)BGM_vol = 100;
	if (BGM_vol < 0)BGM_vol = 0;

	if (SE_vol > 100) SE_vol = 100;
	if (SE_vol < 0) SE_vol = 0;

	/*����*/
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) {
		if (Cursor == 0) { BGM_vol--; }
		else if (Cursor == 1) { SE_vol--, PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK); }
		
	}
		
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) {
		if (Cursor == 0) BGM_vol++;
		else if (Cursor == 1) { SE_vol++, PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK); }
		
	}

	//�J�[�\��
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Op_OneShot == false) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		Op_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Op_OneShot == false) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		Op_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}


	//��ʑJ�ڏ���
	if ((input.Buttons[XINPUT_BUTTON_B] && Op_OneShot == false && Cursor == 2)) {
		Op_OneShot = true, Op_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Op_Flg == true)
	{
		Cursor = 0, Changer = Before, Before = OPTION;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
		Op_Flg = false;
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Cursor = 0, Changer = Before, Before = OPTION;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
		Op_Flg = false;
	}

	if (Op_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		Op_OneShot = false;
	}

}