#include "Scene.h"

void Scene::Option() {
	static int BGM = 75;
	static int SE = 75;
	static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる

	DrawString(0, 0, "Option", 0xffffff);
	DrawFormatString(0, 60, 0xffffff, "BGM = %d", BGM);
	DrawFormatString(0, 80, 0xffffff, " SE = %d", SE);
	DrawFormatString(0, 120, 0xffffff, "[←] Down");
	DrawFormatString(0, 140, 0xffffff, "[→] UP");
	DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, 0xffffff, "[Space] Back");

	DrawBox((WINDOW_X / 8), (WINDOW_Y / 64) * 20, (WINDOW_X / 2), (WINDOW_Y / 64) * 21, 0xffffff, TRUE);
	DrawCircle((((WINDOW_X / 2) - (WINDOW_X / 8)) * BGM / 100) + (WINDOW_X / 8),
		(WINDOW_Y / 64) * 20.5, 8, 0x00ff77);

	DrawBox((WINDOW_X / 8), (WINDOW_Y / 64) * 25, (WINDOW_X / 2), (WINDOW_Y / 64) * 26, 0xffffff, TRUE);
	DrawCircle((((WINDOW_X / 2) - (WINDOW_X / 8)) *  SE / 100) + (WINDOW_X / 8),
		(WINDOW_Y / 64) * 25.5, 8, 0x0ff770);

	DrawTriangle((WINDOW_X / 64) * 4, (WINDOW_Y / 64) * (19 + Cursor * 5),
		(WINDOW_X / 64) * 4, (WINDOW_Y / 64) * (21 + Cursor * 5),
		(WINDOW_X / 64) * 6, (WINDOW_Y / 64) * (20 + Cursor * 5), 0xffff00, TRUE);

	DrawString((WINDOW_X / 8), (WINDOW_Y / 64) * 30, "Back", 0xffffff);

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