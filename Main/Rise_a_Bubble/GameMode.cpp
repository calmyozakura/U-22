#include "Scene.h"

static int Cursor = 0;//Cursor:カーソル用 
bool GMo_OneShot = 0, GMo_Flg = 0;//OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる
std::string MODE[]= {"EASY","NORMAL","HARD","EXHARD","PASSCODE","MAKE","Back"};

void Scene::GameMode() {
	DrawString(0, 0, "GameMode", 0xffffff);

	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 21, "EASY", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 22, "NORMAL", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 23, "HARD", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 24, "PASSCODE", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "MAKE", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "BACK", 0xffffff);

	DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 30, 0xffffff, "GameMode:%s", MODE[Difficulty].c_str());
	DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (42 + Cursor * 2),
		(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (44 + Cursor * 2),
		(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (43 + Cursor * 2), 0xffff00, TRUE);


#ifdef DEBUG
	/*for (int i = 0; i < 16; i++) {
		DrawFormatString(50, 200 + (i * 20), 0xffffff, "%d", input.Buttons[i]);
	}*/
	
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 28, "Result(X+Start)", 0xffffff);
	if (input.Buttons[XINPUT_BUTTON_X] && input.Buttons[XINPUT_BUTTON_START]) {
	Before = Changer, Changer = RESULT;
	}
#endif // DEBUG

	/*処理*/

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && GMo_OneShot == false) {
		(Cursor > 0) ? Cursor-- : Cursor = 5;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
		GMo_OneShot = true;
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && GMo_OneShot == false) {
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
		(Cursor < 5) ? Cursor++ : Cursor = 0;
		GMo_OneShot = true;
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && GMo_OneShot == false) {
		GMo_OneShot = true, GMo_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && GMo_Flg == true)
	{	Difficulty = Cursor;

 		if (Cursor != 6) CodeRnd_flg = TRUE, Pass_Flg = FALSE,Before = Changer, Changer = GAMEINIT;
		//else if (Cursor == 1)Before = Changer, Changer = RESULT;
		else if (Cursor == 6)Before = Changer, Changer = TITLE;
		

		Cursor = 0, GMo_Flg = false;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Before = Changer, Changer = TITLE;

		Cursor = 0, GMo_Flg = false;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
	}

	if (GMo_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		GMo_OneShot = false;
	}

}