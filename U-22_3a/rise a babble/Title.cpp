#include "Scene.h"

static int Cursor= 0, OneShot=0, Flg=0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　

void Scene::Title() {
	DrawString(0,0,"Title",0xffffff);

	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "Game Start", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "Option", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "END", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * 14,  (WINDOW_Y / 64) * (50 + Cursor * 2),
				 (WINDOW_X / 64) * 14,  (WINDOW_Y / 64) * (52 + Cursor * 2),
				 (WINDOW_X / 64) * 16,  (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00,TRUE);


#ifdef DEBUG
	for(int i = 0;i<16;i++){
	DrawFormatString(50, 200+(i*20), 0xffffff, "%d", Input.Buttons[i]);
	}
#endif // DEBUG

	/*処理*/

	//カーソル

	if (Input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		OneShot = 1;
	}
	else if (Input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		OneShot = 1;
	}
	//画面遷移処理
	if (Input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!Input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		if (Cursor == 0)Before = Changer, Changer = GAMEINIT;
		else if (Cursor == 1)Before = Changer, Changer = OPTION;
		else if (Cursor == 2)Before = Changer, Changer = ENDING;

		Cursor = 0, Flg = 0;
	}

	if (OneShot == 1 && !(Input.Buttons[XINPUT_BUTTON_B]
		|| Input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| Input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}
	
}