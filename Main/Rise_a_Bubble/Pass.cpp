#include <iostream>
#include "Scene.h"

static int Cursor = 0;//Cursor:カーソル用
bool Ps_OneShot = false, Ps_Flg = false;// OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　
bool PBk_OneShot = false, PBk_Flg = false;	//Aボタン(バック)用の多重押し防止
int p = 0;	//パスの番地をみる
void Scene::Pass() {

	DrawGraph(0, 0, images.back[14], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//半透明
	DrawFillBox(10, 270, WINDOW_X - 10, 430, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// 不透明

	SetFontSize(30);
	DrawString(50, (WINDOW_Y / 32) * 15, "A", 0xffffff);
	DrawString(145, (WINDOW_Y / 32) * 15, "B", 0xffffff);
	DrawString(240, (WINDOW_Y / 32) * 15, "C", 0xffffff);
	DrawString(335, (WINDOW_Y / 32) * 15, "D", 0xffffff);
	DrawString(50, (WINDOW_Y / 32) * 17, "E", 0xffffff);
	DrawString(145, (WINDOW_Y / 32) * 17, "F", 0xffffff);
	DrawString(240, (WINDOW_Y / 32) * 17, "G", 0xffffff);
	DrawString(335, (WINDOW_Y / 32) * 17, "H", 0xffffff);
	DrawString(50, (WINDOW_Y / 32) * 19, "I", 0xffffff);
	DrawString(145, (WINDOW_Y / 32) * 19, "J", 0xffffff);
	DrawString(240, (WINDOW_Y / 32) * 19, "Back", 0xffffff);
	DrawString(335, (WINDOW_Y / 32) * 19, "Create", 0xffffff);

	DrawTriangle(4 * (7 + (Cursor % 4) * 23), 13 * (23 + (Cursor / 4) * 3),
		4 * (7 + (Cursor % 4) * 23), 13 * (25 + (Cursor / 4) * 3),
		4 * (12 + (Cursor % 4) * 23), 13 * (24 + (Cursor / 4) * 3), 0xffff00, TRUE);

	//カーソル
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && Ps_OneShot == false) {
		((Cursor % 4) == 0) ? Cursor += 3 : Cursor--;
		Ps_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && Ps_OneShot == false) {
		((Cursor % 4) == 3) ? Cursor -= 3 : Cursor++;
		Ps_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Ps_OneShot == false) {
		(Cursor <= 3) ? Cursor += 8 : Cursor -= 4;
		Ps_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Ps_OneShot == false) {
		(Cursor >= 8) ? Cursor -= 8 : Cursor += 4;
		Ps_OneShot = true;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Ps_OneShot == false) {
		Ps_OneShot = true, Ps_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Ps_Flg == true)
	{
		Difficulty = 0;			//本来保存した難易度をいれる
		//LoadNumber = Cursor;	//カーソル位置の番号をいれる
		if (Cursor <= 9){
			if (p < 20) {
				PassNumber[p] = 'A' + Cursor;
				p++;
				PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
			}
		}
		else if (Cursor == 10)PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK), Cursor = 0, Before = Changer, Changer = GAMEMODE;
		else if (Cursor == 11) CodeRnd_flg = FALSE, Pass_Flg = TRUE, Load_Flg = FALSE, Before = Changer, Changer = GAMEINIT;		//難易度選択

		Ps_Flg = false;
	}


	if (input.Buttons[XINPUT_BUTTON_A] && PBk_OneShot == false) {
		PBk_OneShot = true, PBk_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_A] && PBk_Flg == true)
	{
		if (p > 0) {
			PassNumber[p - 1] = NULL;
			p--;
		}
		else if (p == 0) {
			Cursor = 0, Before = Changer, Changer = GAMEMODE;
		}
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
		PBk_OneShot = false, PBk_Flg = false;
	}

	if (Ps_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN]
		|| input.Buttons[XINPUT_BUTTON_DPAD_LEFT]
		|| input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) {

		Ps_OneShot = false;
	}
	SetFontSize(32);
	DrawFormatString(20, 150, 0xffffff, "PASS:%s", PassNumber);
}