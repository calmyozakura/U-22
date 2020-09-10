#include <iostream>
#include "Scene.h"

static int Cursor = 0;//Cursor:カーソル用
bool Ps_OneShot = false, Ps_Flg = false;// OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　
bool PBk_OneShot = false, PBk_Flg = false;	//Aボタン(バック)用の多重押し防止
int p = 0;	//パスの番地をみる
bool ErrorPass = FALSE;
char DummyNumber[20];	//パス入力時に使う変数
bool Onece = FALSE;	//最初に一度だけする処理
void Scene::Pass() {
	sound.PlayBGM(sound.stack);
	if(Onece == FALSE) Difficulty = 0 ,Onece = TRUE;

	DrawGraph(0, 0, images.back[14], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//半透明
	DrawFillBox(10, 270, WINDOW_X - 10, 470, 0xaaaaaa);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// 不透明

	if (ErrorPass == TRUE) DrawString(30, 50, "Paste the 20 - character code", 0xffffff);
	SetFontSize(19);
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
	DrawString(335, (WINDOW_Y / 32) * 19, "Paste", 0xffffff);
	DrawString(50, (WINDOW_Y / 32) * 21, "Easy", 0xffffff);
	DrawString(145, (WINDOW_Y / 32) * 21, "Normal", 0xffffff);
	DrawString(240, (WINDOW_Y / 32) * 21, "Hard", 0xffffff);
	DrawString(335, (WINDOW_Y / 32) * 21, "Create", 0xffffff);

	DrawTriangle(4 * (7 + (Cursor % 4) * 23), 13 * (23 + (Cursor / 4) * 3),
		4 * (7 + (Cursor % 4) * 23), 13 * (25 + (Cursor / 4) * 3),
		4 * (12 + (Cursor % 4) * 23), 13 * (24 + (Cursor / 4) * 3), 0xffff00, TRUE);

	//カーソル
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && Ps_OneShot == false) {
		((Cursor % 4) == 0) ? Cursor += 3 : Cursor--;
		Ps_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && Ps_OneShot == false) {
		((Cursor % 4) == 3) ? Cursor -= 3 : Cursor++;
		Ps_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Ps_OneShot == false) {
		(Cursor <= 3) ? Cursor += 12 : Cursor -= 4;
		Ps_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Ps_OneShot == false) {
		(Cursor >= 12) ? Cursor -= 12 : Cursor += 4;
		Ps_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Ps_OneShot == false) {
		Ps_OneShot = true, Ps_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Ps_Flg == true)
	{
		//LoadNumber = Cursor;	//カーソル位置の番号をいれる
		if (Cursor <= 9){
			if (p < 20) {
				PassNumber[p] = 'A' + Cursor;
				p++;
				sound.PlaySE(sound.decide);
			}
			else if (p == 20) {
				PassNumber[p] = NULL;
			}
		}
		else if (Cursor == 10)sound.PlaySE(sound.cancel) , Onece = FALSE, Cursor = 0, Before = Changer, Changer = GAMEMODE;
		else if (Cursor == 11) {
			GetClipboardText(DummyNumber);	//ダミー変数でクリップボードの文字数が条件を満たしているか調べる
			if (DummyNumber[19] == NULL || DummyNumber[20] != NULL) { //20文字未満or21文字以上でエラー文表示
				ErrorPass = TRUE;
			}
			else {
				ErrorPass = FALSE;
				GetClipboardText(PassNumber);
				p = 20;
			}
		}
		else if (Cursor == 12) sound.PlaySE(sound.decide), Difficulty = 0;
		else if (Cursor == 13) sound.PlaySE(sound.decide), Difficulty = 1;
		else if (Cursor == 14) sound.PlaySE(sound.decide), Difficulty = 2;
		else if (Cursor == 15) Onece = FALSE, CodeRnd_flg = FALSE, Pass_Flg = TRUE, Load_Flg = FALSE, Before = Changer, Changer = GAMEINIT;	//難易度選択

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
			Onece = FALSE, Cursor = 0, Before = Changer, Changer = GAMEMODE;
		}
		sound.PlaySE(sound.cancel);
		PBk_OneShot = false, PBk_Flg = false;
	}

	if (Ps_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN]
		|| input.Buttons[XINPUT_BUTTON_DPAD_LEFT]
		|| input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) {

		Ps_OneShot = false;
	}
	SetFontSize(25);
	DrawString(200, 150, "PASS", 0xffffff);
	DrawFormatString(0, 200, 0xffffff, "%s", PassNumber);

	if(Difficulty == 0) DrawString(200, 100, "Easy", 0xffffff);
	else if (Difficulty == 1) DrawString(200, 100, "Normal", 0xffffff);
	else if (Difficulty == 2) DrawString(200, 100, "Hard", 0xffffff);
}