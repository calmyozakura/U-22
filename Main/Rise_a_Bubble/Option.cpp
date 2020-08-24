#include "Scene.h"

void Scene::Option() {
	static int BGM = 75;
	static int SE = 75;
	static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる
	
	int Option_moji = LoadGraph("Images/option_moji.png");
	int BGM_moji = LoadGraph("Images/bgm_moji.png");
	int SE_moji = LoadGraph("Images/se_moji.png");
	int Back_moji = LoadGraph("Images/back_moji.png");

	/*DrawString(STRING_X, ADDPOS_Y, "Option", 0xffffff);
	DrawFormatString(CURSOR_X, CURSOR_Y * 17, 0xffffff, "BGM = %d", BGM);
	DrawFormatString(CURSOR_X, CURSOR_Y * 24, 0xffffff, " SE = %d", SE);
	DrawFormatString(0, 120, 0xffffff, "[←] Down");
	DrawFormatString(0, 140, 0xffffff, "[→] UP");*/

	DrawRotaGraph(WINDOW_X / 2, TITLE_Y, 1, 0, Option_moji, TRUE);

	DrawRotaGraph(WINDOW_X / 2, STRING_Y + (ADDPOS_Y * 3), 1, 0, Back_moji, TRUE);

	DrawGraph(CURSOR_X + ADDPOS_X, STRING_Y - ADDPOS_Y*2, BGM_moji, TRUE);
	DrawGraph(CURSOR_X + ADDPOS_X, STRING_Y, SE_moji, TRUE);

	DrawBox(CURSOR_X, STRING_Y - ADDPOS_Y, (WINDOW_X - ADDPOS_X*2), STRING_Y - ADDPOS_Y + 10, 0xffffff, TRUE);
	DrawCircle((Bar * BGM / Percent) + CURSOR_X,
		STRING_Y - ADDPOS_Y +5, Radius, 0x00ff77);

	DrawBox(CURSOR_X, STRING_Y + ADDPOS_Y, (WINDOW_X - ADDPOS_X*2), STRING_Y + ADDPOS_Y + 10, 0xffffff, TRUE);
	DrawCircle((Bar * SE / Percent) + CURSOR_X,
		STRING_Y + ADDPOS_Y + 5, Radius, 0x00ff77);

	//DrawString(STRING_X, STRING_Y + (ADDPOS_Y * 3), "      Back", 0xffffff);

	DrawTriangle(CURSOR_X-ADDPOS_X, STRING_Y - ADDPOS_Y + (ADDPOS_Y * Cursor * 2) - 10,
		CURSOR_X , STRING_Y - ADDPOS_Y + (ADDPOS_Y * Cursor * 2),
		CURSOR_X - ADDPOS_X, STRING_Y - ADDPOS_Y + (ADDPOS_Y * Cursor * 2) + 10, 0xffff00, TRUE);
	/*処理*/

	//それぞれの前提範囲
	if (BGM > 100)BGM = 100;
	if (BGM < 0)BGM = 0;

	if (SE > 100) SE = 100;
	if (SE < 0) SE = 0;

	/*音声*/
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])
		if (Cursor == 0)
			--BGM;
		else if (Cursor == 1)
			--SE;
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])
		if (Cursor == 0)
			++BGM;
		else if (Cursor == 1)
			++SE;

	//カーソル
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		OneShot = 1;
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		OneShot = 1;
	}


	//画面遷移処理
	if ((input.Buttons[XINPUT_BUTTON_B] && OneShot == 0 && Cursor == 2) || (input.Buttons[XINPUT_BUTTON_A])) {
		OneShot = 1, Flg = 1;
	}
	else if (!(input.Buttons[XINPUT_BUTTON_B] || input.Buttons[XINPUT_BUTTON_A]) && Flg == 1)
	{
		Cursor = -1, Changer = Before, Before = OPTION;

		 Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}

}