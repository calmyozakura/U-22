#include "Scene.h"

static int Cursor = 0;//Cursor:カーソル用
bool Ld_OneShot = false, Ld_Flg = false;// OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　
bool LBk_OneShot = false, LBk_Flg = false;	//Aボタン(バック)用の多重押し防止
void Scene::Load() {
	//音量
	sound.SetVolumes();

	DrawGraph(0, 0, images.back[14], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawFillBox(25, 220, WINDOW_X - 25, 450, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// 不透明

	DrawString(STRING_X, TITLE_Y, "COURSE LOAD", 0xffffff);
	//DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 18, 0xff00ff, "%.2f", Score);
	DrawString(100, (WINDOW_Y / 32) * 13, "COURSE１", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 13, "COURSE２", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 15, "COURSE３", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 15, "COURSE４", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 17, "COURSE５", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 17, "COURSE６", 0xffffff);
	DrawString(100, (WINDOW_Y / 32) * 19, "COURSE７", 0xffffff);
	DrawString(260, (WINDOW_Y / 32) * 19, "COURSE８", 0xffffff);

	//DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (42 + Cursor * 2),
	//	(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (44 + Cursor * 2),
	//	(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (43 + Cursor * 2), 0xffff00, TRUE);
	DrawTriangle(4 * (17 + (Cursor % 2) * 40), 13 * (20 + (Cursor / 2) * 3),
		4 * (17 + (Cursor % 2) * 40), 13 * (22 + (Cursor / 2) * 3),
		4 * (22 + (Cursor % 2) * 40), 13 * (21 + (Cursor / 2) * 3), 0xffff00, TRUE);
	//カーソル
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Ld_OneShot == false) {
		(Cursor <= 1) ? Cursor += 6 : Cursor -= 2;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Ld_OneShot == false) {
		(Cursor >= 6) ? Cursor -= 6 : Cursor += 2;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && Ld_OneShot == false) {
		((Cursor % 2) == 1) ? Cursor-- : Cursor++;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && Ld_OneShot == false) {
		((Cursor % 2) == 0) ? Cursor++ : Cursor--;
		Ld_OneShot = true;
		sound.PlaySE(sound.choose);
	}


	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Ld_OneShot == false) {
		Ld_OneShot = true, Ld_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Ld_Flg == true)
	{
		//if (Cursor == 0)Before = Changer, Changer = TITLE;
		//else if (Cursor == 1)Before = Changer, Changer = GAMEINIT;
		//else Before = Changer, Changer = GAMEMODE;
		Difficulty = 0;			//本来保存した難易度をいれる
		LoadNumber = Cursor;	//カーソル位置の番号をいれる
		CodeRnd_flg = FALSE, Pass_Flg = FALSE, Load_Flg = TRUE, Before = Changer, Changer = GAMEINIT;		//難易度選択
		sound.PlaySE(sound.decide);
		Cursor = 0, Ld_Flg = false;
	}


	if (input.Buttons[XINPUT_BUTTON_A] && LBk_OneShot == false) {
		LBk_OneShot = true, LBk_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_A] && LBk_Flg == true)
	{
		Before = Changer, Changer = GAMEMODE;
		sound.PlaySE(sound.cancel);
		Cursor = 0, LBk_OneShot = false, LBk_Flg = false;
	}

	if (Ld_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN]
		|| input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]
		|| input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {

		Ld_OneShot = false;
	}
}