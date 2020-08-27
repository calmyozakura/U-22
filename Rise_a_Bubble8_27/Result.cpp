#include "Scene.h"
static int Cursor = 0;//Cursor:カーソル用
bool Rs_OneShot = false, Rs_Flg = false;// OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　

void Scene::Result() {
	//音量
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[choose]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[decide]);

	/*DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[←] Title", 0xffffff);
	DrawString(0, 60, "[→] Replay Game", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = TITLE;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = GAMEINIT;*/

	DrawString(STRING_X,TITLE_Y, "GameClear!!", 0xffffff);
	DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 18,0xff00ff, "%.2f", Score);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "to Title", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "replay Game", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "new Game", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
		(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
		(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);

	/*処理*/

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Rs_OneShot == false) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		Rs_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Rs_OneShot == false) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		Rs_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Rs_OneShot == false) {
		Rs_OneShot = true, Rs_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Rs_Flg == true)
	{
		if (Cursor == 0)Before = Changer, Changer = TITLE;
		else if (Cursor == 1)Before = Changer, Changer = GAMEINIT;
		else Before = Changer, Changer = GAMEMODE;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
		Cursor = 0, Rs_Flg = false;
	}
	if(input.Buttons[XINPUT_BUTTON_A] && Rs_Flg == true) {
		Before = Changer, Changer = GAMEMODE;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
		Cursor = 0, Rs_Flg = false;
	}

	if (Rs_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		Rs_OneShot = false;
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