#include "Scene.h"

static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　

std::string MODE[]= {"EASY","NORMAL","HARD","EXHARD","PASSCODE","MAKE","Back"};

void Scene::GameMode() {
	DrawString(0, 0, "GameMode", 0xffffff);

	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 21, "ゲームへ", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 22, "NORMAL", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 23, "HARD", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 24, "EXHARD", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "PASSCODE", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "MAKE", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "BACK", 0xffffff);

	DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 30, 0xffffff, "GameMode:%s", MODE[Difficulty].c_str());
	DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (42 + Cursor * 2),
		(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (44 + Cursor * 2),
		(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (43 + Cursor * 2), 0xffff00, TRUE);


#ifdef DEBUG
	for (int i = 0; i < 16; i++) {
		DrawFormatString(50, 200 + (i * 20), 0xffffff, "%d", input.Buttons[i]);
	}
#endif // DEBUG

	/*処理*/

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 6;
		OneShot = 1;
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 6) ? Cursor++ : Cursor = 0;
		OneShot = 1;
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
 		if (Cursor == 0)Before = Changer, Changer = GAMEINIT;
		if (Cursor == 6)Before = Changer, Changer = TITLE;
		else Difficulty = Cursor;

		Cursor = 0,	Flg = 0;
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}

}