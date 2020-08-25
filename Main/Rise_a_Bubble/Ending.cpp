#include "Scene.h"

static int Cursor = 0, OneShot = 0, Flg = 0;//Cursor:カーソル用 OneShot:多重押しの防止 Flg:Bを離すとシーンが変わる　


void Scene::Ending() {
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[decide]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, se.Sound[choose]);
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
	DrawFormatString(0, 0, 0xffffff, "%d %d", Cursor,Flg);

	//処理

	//カーソル

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
		(Cursor > 0) ? Cursor-- : Cursor = 1;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}
	else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
		(Cursor < 1) ? Cursor++ : Cursor = 0;
		OneShot = 1;
		PlaySoundMem(se.Sound[choose], DX_PLAYTYPE_BACK);
	}

	//画面遷移処理
	if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
		OneShot = 1, Flg = 1;
	}
	else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
	{
		//(Cursor == 0) ? Before = Changer, Changer = END : Before = Changer, Changer = TITLE;
		(Cursor == 0) ? Before = Changer, Changer = END :  Changer = TITLE ;
		Cursor = 0, Flg = 0;
		PlaySoundMem(se.Sound[decide], DX_PLAYTYPE_BACK);
	}
	if (input.Buttons[XINPUT_BUTTON_A]) {
		Cursor = 0, Flg = 0;
		Changer = TITLE;
		PlaySoundMem(se.Sound[cancel], DX_PLAYTYPE_BACK);
	}

	if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
		|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
		|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

		OneShot = 0;
	}
}
