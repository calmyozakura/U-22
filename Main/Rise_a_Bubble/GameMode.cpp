#include "Scene.h"

static int Cursor = 0;//Cursor:カーソル用 
bool GMo_OneShot = 0, GMo_Flg = 0, GMo_Once;//OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる
std::string MODE[]= {"EASY","NORMAL","HARD","EXHARD","PASSCODE","MAKE","Back"};

void Scene::GameMode() {
	//一度だけ読み込む
	if (GMo_Once == false) {
		SetFontSize(24);

		GMo_Once = true;
	}

	DrawGraph(0, 0, images.back[10], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//半透明
	DrawFillBox(MINIWINDOW_X, 280, WINDOW_X - MINIWINDOW_X, 540, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// 不透明
	DrawString(WINDOW_HALF_X - 40, ADDPOS_Y + 30, "GameMode", 0x444444);

	DrawString(STRING_X, (WINDOW_Y / 32) * 15, "EASY", 0xffffff);
	DrawString(STRING_X, (WINDOW_Y / 32) * 17, "NORMAL", 0xffffff);
	DrawString(STRING_X, (WINDOW_Y / 32) * 19, "HARD", 0xffffff);
	DrawString(STRING_X, (WINDOW_Y / 32) * 21, "PASSCODE", 0xffffff);
	DrawString(STRING_X, (WINDOW_Y / 32) * 23, "LOAD", 0xffffff);
	DrawString(STRING_X, (WINDOW_Y / 32) * 25, "BACK", 0xffffff);

	DrawTriangle(CURSOR_X, CURSOR_Y * (30 + Cursor * 4),
		CURSOR_X, CURSOR_Y * (32 + Cursor * 4),
		CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (31+ Cursor * 4), 0xffff00, TRUE);


	DrawFormatString(STRING_X, (WINDOW_Y / 32) * 30, 0x444444, "GameMode:%s", MODE[Difficulty].c_str());

#ifdef DEBUG
	/*for (int i = 0; i < 16; i++) {
		DrawFormatString(50, 200 + (i * 20), 0xffffff, "%d", input.Buttons[i]);
	}*/
	
	DrawString(STRING_X, (WINDOW_Y / 32) * 28, "Result(X+Start)", 0x444444);
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

	if (Cursor <= 2) CodeRnd_flg = TRUE, Pass_Flg = FALSE, Load_Flg = FALSE, Before = Changer, Changer = GAMEINIT;		//難易度選択
	else if (Cursor == 3) Before = Changer, Changer = PASS;	//コースロード
	else if (Cursor == 4) Before = Changer, Changer = LOAD;	//コースロード
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