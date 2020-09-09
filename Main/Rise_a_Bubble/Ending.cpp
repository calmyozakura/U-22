#include "Scene.h"

static int Cursor = 0; //Cursor:カーソル用 
bool Ed_OneShot = 0, Ed_Flg = 0;//OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　

void Scene::Ending() {
	sound.SetVolumes();
	sound.PlayBGM(sound.stack);
	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//半透明
	DrawFillBox(MINIWINDOW_X, MINIWINDOW_Y, WINDOW_X - MINIWINDOW_X, MINIWINDOW_Y + (ADDPOS_Y * 5), 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// 不透明

	DrawTriangle(CURSOR_X, CURSOR_Y * (36 + FixPos),
		CURSOR_X, CURSOR_Y * (38 + FixPos),
		CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (37 + FixPos), 0xffff00, TRUE);


	DrawString(STRING_X - ADDPOS_Y, STRING_Y - ADDPOS_Y, "本当に終了しますか？", 0xffffff);
	DrawString(STRING_X, STRING_Y, "YES", 0x00ff7f);
	DrawString(STRING_X, STRING_Y + ADDPOS_Y, "NO", 0xff7f00);
	//DrawFormatString(0, 0, 0xffffff, "%d %d", Cursor, Ed_Flg);

	//処理

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && Ed_OneShot == false) {
		(Cursor > 0) ? Cursor-- : Cursor = 1;
		Ed_OneShot = true;
		sound.PlaySE(sound.choose);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && Ed_OneShot == false) {
		(Cursor < 1) ? Cursor++ : Cursor = 0;
		Ed_OneShot = true;
		sound.PlaySE(sound.choose);
	}

	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && Ed_OneShot == false) {
		Ed_OneShot = true, Ed_Flg = true;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Ed_Flg == true)
	{
		//(Cursor == 0) ? Before = Changer, Changer = END : Before = Changer, Changer = TITLE;
		(Cursor == 0) ? Before = Changer, Changer = END :  Changer = TITLE ;
		Cursor = 0, Ed_Flg = false;
		sound.PlaySE(sound.decide);
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Cursor = 0, Ed_Flg = false;
		Changer = TITLE;
		sound.PlaySE(sound.cancel);
	}

	if (Ed_OneShot == true && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		Ed_OneShot = false;
	}
}
