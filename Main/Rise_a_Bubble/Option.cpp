#include "Scene.h"

void Scene::Option() {
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[decide]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[choose]);
	static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる
	
	DrawString(STRING_X, ADDPOS_Y, "Option", 0xffffff);
	DrawFormatString(CURSOR_X, CURSOR_Y * 17, 0xffffff, "BGM_vol = %d", BGM_vol);
	DrawFormatString(CURSOR_X, CURSOR_Y * 24, 0xffffff, " SE_vol = %d", SE_vol);
	/*DrawFormatString(0, 120, 0xffffff, "[←] Down");
	DrawFormatString(0, 140, 0xffffff, "[→] UP");*/

	DrawBox(CURSOR_X , CURSOR_Y * 20, (WINDOW_X - ADDPOS_X), CURSOR_Y * 21, 0xffffff, TRUE);
	DrawCircle((Bar * BGM_vol / Percent) + CURSOR_X,
		CURSOR_Y * 20.5, Radius, 0x00ff77);

	DrawBox(CURSOR_X , CURSOR_Y * 27, (WINDOW_X - ADDPOS_X), CURSOR_Y * 28, 0xffffff, TRUE);
	DrawCircle((Bar * SE_vol / Percent) + CURSOR_X,
		CURSOR_Y * 27.5, Radius, 0x00ff77);

	DrawString(CURSOR_X , CURSOR_Y * 34, "      Back", 0xffffff);

	DrawTriangle(CURSOR_X/2 ,CURSOR_Y * (19 + Cursor * 7),
		CURSOR_X/2, CURSOR_Y * (21 + Cursor * 7),
		CURSOR_X/2 + ADDPOS_X / 2, CURSOR_Y * (20 + Cursor * 7), 0xffff00, TRUE);
	/*処理*/

	//それぞれの前提範囲
	if (BGM_vol > 100)BGM_vol = 100;
	if (BGM_vol < 0)BGM_vol = 0;

	if (SE_vol > 100) SE_vol = 100;
	if (SE_vol < 0) SE_vol = 0;

	/*音声*/
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) {
		if (Cursor == 0) { BGM_vol--; }
		else if (Cursor == 1) { SE_vol--, PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK); }
		
	}
		
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) {
		if (Cursor == 0) BGM_vol++;
		else if (Cursor == 1) { SE_vol++, PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK); }
		
	}

	//カーソル
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}


	//画面遷移処理
	if ((input.Buttons[XINPUT_BUTTON_B] && OneShot == 0 && Cursor == 2)) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		Cursor = 0, Changer = Before, Before = OPTION;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
		 Flg = 0;
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Cursor = 0, Changer = Before, Before = OPTION;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
		Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}

}