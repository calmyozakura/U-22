#include "Scene.h"

void Scene::Option() {
	static int BGM = 75;
	static int SE = 75;
	static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる
	
	DrawString(STRING_X, ADDPOS_Y, "Option", 0xffffff);
	DrawFormatString(CURSOR_X, CURSOR_Y * 17, 0xffffff, "BGM = %d", BGM);
	DrawFormatString(CURSOR_X, CURSOR_Y * 24, 0xffffff, " SE = %d", SE);
	/*DrawFormatString(0, 120, 0xffffff, "[←] Down");
	DrawFormatString(0, 140, 0xffffff, "[→] UP");*/

	DrawBox(CURSOR_X , CURSOR_Y * 20, (WINDOW_X - ADDPOS_X), CURSOR_Y * 21, 0xffffff, TRUE);
	DrawCircle((Bar * BGM / Percent) + CURSOR_X,
		CURSOR_Y * 20.5, Radius, 0x00ff77);

	DrawBox(CURSOR_X , CURSOR_Y * 27, (WINDOW_X - ADDPOS_X), CURSOR_Y * 28, 0xffffff, TRUE);
	DrawCircle((Bar * SE / Percent) + CURSOR_X,
		CURSOR_Y * 27.5, Radius, 0x00ff77);

	DrawString(CURSOR_X , CURSOR_Y * 34, "      Back", 0xffffff);

	DrawTriangle(CURSOR_X/2 ,CURSOR_Y * (19 + Cursor * 7),
		CURSOR_X/2, CURSOR_Y * (21 + Cursor * 7),
		CURSOR_X/2 + ADDPOS_X / 2, CURSOR_Y * (20 + Cursor * 7), 0xffff00, TRUE);
	/*処理*/

	//それぞれの前提範囲
	if (BGM > 100)BGM = 100;
	if (BGM < 0)BGM = 0;

	if (SE > 100) SE = 100;
	if (SE < 0) SE = 0;

	/*音声*/
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])
		(Cursor == 0) ? BGM-- : SE--;
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])
		(Cursor == 0) ? BGM++ : SE++;

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
		Cursor = 0, Changer = Before, Before = OPTION;

		Cursor = 0, Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}

}