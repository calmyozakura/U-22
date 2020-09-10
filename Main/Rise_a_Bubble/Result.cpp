#include "Scene.h"
static int Cursor = 0;//Cursor:カーソル用
bool Rs_OneShot = false, Rs_Flg = false;// OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　
bool Cp_OneShot = false, Cp_Flg = false ,Copy_Flg = false;
void Scene::Result() {
	SetFontSize(24);

	sound.StopBGM(sound.Game);
	sound.PlayBGM(sound.Result);

	/*DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[←] Title", 0xffffff);
	DrawString(0, 60, "[→] Replay Game", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = TITLE;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = GAMEINIT;*/

	DrawGraph(0, 0, images.back[19], FALSE);

	DrawString(STRING_X,100, "GameClear!!", 0xffff00);
	SetFontSize(25);
	DrawFormatString(180, 180, 0x98fb98, "TIME:%.2f", Score);
	DrawString(200, (WINDOW_Y / 48) * 18, "PASS", 0x98fb98);
	DrawFormatString(0, (WINDOW_Y / 42) * 18, 0x98fb98, "%s", Code);
	SetFontSize(24);
	DrawString(180, (WINDOW_Y / 32) * 20, "to Title", 0xffffff);
	DrawString(180, (WINDOW_Y / 32) * 22, "replay Game", 0xffffff);
	DrawString(180, (WINDOW_Y / 32) * 24, "new Game", 0xffffff);

	(Copy_Flg == true) ? DrawString(120, (WINDOW_Y / 32) * 28, "I copied the code", 0xffffff) : DrawString(60, (WINDOW_Y / 32) * 28, "Copy code with Y button", 0xffffff);

	//DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
	//	(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
	//	(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);

	DrawTriangle(CURSOR_X, CURSOR_Y * (40 + Cursor * 4),
		CURSOR_X, CURSOR_Y * (42 + Cursor * 4),
		CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (41 + Cursor * 4), 0xffff00, TRUE);

	/*処理*/

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Rs_OneShot == false) {
		(Cursor > 0) ? Cursor-- : Cursor = 2;
		Rs_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Rs_OneShot == false) {
		(Cursor < 2) ? Cursor++ : Cursor = 0;
		Rs_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Rs_OneShot == false) {
		Rs_OneShot = true, Rs_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Rs_Flg == true)
	{
		if (Cursor == 0) Copy_Flg = false, Before = Changer, Changer = TITLE;
		else if (Cursor == 1) Copy_Flg = false, Before = Changer, Changer = GAMEINIT;
		else Copy_Flg = false, Before = Changer, Changer = GAMEMODE;
		sound.PlaySE(sound.decide);
		Cursor = 0, Rs_Flg = false;
	}
	if(input.Buttons[XINPUT_BUTTON_A] && Rs_Flg == true) {
		Copy_Flg = false, Before = Changer, Changer = GAMEMODE;
		sound.PlaySE(sound.cancel);
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

	if (input.Buttons[XINPUT_BUTTON_Y] && Cp_OneShot == false) {
		Cp_OneShot = true, Cp_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_Y] && Cp_Flg == true)
	{
		Copy_Flg = true;
		SetClipboardText(Code);
		sound.PlaySE(sound.decide);
		Cp_OneShot = false, Cp_Flg = false;
	}
}