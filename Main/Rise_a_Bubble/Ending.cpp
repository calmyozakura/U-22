#include "Scene.h"

static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　


void Scene::Ending() {
	DrawString(0, 0, "本当に終了しますか？", 0xffffff);


	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "YES", 0xffffff);
	DrawString((WINDOW_X / 4 * 3), (WINDOW_Y / 32) * 25, "NO", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * (10 + Cursor * 35), (WINDOW_Y / 64) * (50),
		(WINDOW_X / 64) * (10 + Cursor * 35), (WINDOW_Y / 64) * (52),
		(WINDOW_X / 64) * (11 + Cursor * 35), (WINDOW_Y / 64) * (51), 0xffff00, TRUE);

	/*処理*/

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 1;
		OneShot = 1;
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && OneShot == 0) {
		(Cursor < 1) ? Cursor++ : Cursor = 0;
		OneShot = 1;
	}

	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		(Cursor == 0) ? Before = Changer, Changer = END : Changer = Before, Before = ENDING;
		Cursor = 0, Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_LEFT]
		|| input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) {

		OneShot = 0;
	}
}
