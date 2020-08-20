#include "Scene.h"
static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　

void Scene::Result() {
	/*DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[←] Title", 0xffffff);
	DrawString(0, 60, "[→] Replay Game", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = TITLE;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = GAMEINIT;*/

	DrawString(STRING_X,TITLE_Y, "GameClear!!", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 18, "タイム：00:00:00", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "to Title", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "replay Game", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "new Game", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
		(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
		(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);

	/*処理*/

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
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		if (Cursor == 0)Before = Changer, Changer = TITLE;
		else if (Cursor == 1)Before = Changer, Changer = GAMEMODE;
		else Before = Changer, Changer = GAMEINIT;

		Cursor = 0, Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
		/*	//カーソル
			if (Input.Buttons[XINPUT_BUTTON_DPAD_UP])
				(Cursor > 0) ? Cursor-- : Cursor = 1;
			if (Input.Buttons[XINPUT_BUTTON_DPAD_DOWN])
				(Cursor < 1) ? Cursor++ : Cursor = 0;

			//画面遷移処理
			if (Input.Buttons[XINPUT_BUTTON_B]) {
				if (Cursor == 0)Before = Changer, Changer = TITLE;
				else if (Cursor == 1)Before = Changer, Changer = GAMEINIT;
				Cursor = 0;*/
	}
}