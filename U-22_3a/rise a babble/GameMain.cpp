#include "Scene.h"

static int Cursor = 0;

void Scene::GameInit() {
	DrawString(0, 0, "Now Roading...", 0xffffff);
	WaitTimer(300);
	Before = Changer, Changer = GAMEMAIN;
}

void Scene::GameMain() {
	static int SwitchFlg = 0;
	switch (SwitchFlg)
	{
		//ポーズ
		case 1:
		{
			/*
			DrawString(0, 0, "P A U S E", 0xffffff);
			DrawString(0, 40, "[←] Title", 0xffffff);
			DrawString(0, 60, "[→] Option", 0xffffff);
			DrawString(0, 80, "[SPACE] Return Game", 0xffffff);*/
			DrawString(0, 0, "P A U S E", 0xffffff);
			DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "Title", 0xffffff);
			DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "Option", 0xffffff);
			DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "Return Game", 0xffffff);

			DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
				(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
				(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);

		
			 /*処理*/
		
			 //カーソル
			if (setKeyInput()&PAD_INPUT_UP)
				(Cursor > 0) ? Cursor-- : Cursor = 2;
			if (setKeyInput()&PAD_INPUT_DOWN)
				(Cursor < 2) ? Cursor++ : Cursor = 0;
		
			//画面遷移処理
			/*if (setKeyInput()&PAD_INPUT_LEFT)   Cursor = 0, SwitchFlg = 0,Before = Changer, Changer = TITLE;
			if (setKeyInput()&PAD_INPUT_RIGHT)  Cursor = 0, Before = Changer, Changer = OPTION;
			if (setKeyInput()&PAD_INPUT_10)     Cursor = 0,  SwitchFlg = 0;*/

			if (setKeyInput()&PAD_INPUT_10) {
					 if (Cursor == 0)SwitchFlg = 0, Before = Changer, Changer = TITLE;
				else if (Cursor == 1)Before = Changer, Changer = OPTION;
				else if (Cursor == 2)SwitchFlg = 0;
						 Cursor = 0;
			}
		}
		break;

	default:
		{
			/*DrawString(0, 0, "GameMain", 0xffffff);
			DrawString(0, 40, "[←] Result", 0xffffff);
			DrawString(0, 60, "[→] PAUSE", 0xffffff);*/

			DrawString(0, 0, "GameMain", 0xffffff);
			DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "Result", 0xffffff);
			DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "PAUSE", 0xffffff);

			DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
						 (WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
						 (WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);
			/*処理*/

			//カーソル
			if (setKeyInput()&PAD_INPUT_UP)
				(Cursor > 0) ? Cursor-- : Cursor = 1;
			if (setKeyInput()&PAD_INPUT_DOWN)
				(Cursor < 1) ? Cursor++ : Cursor = 0;

			//画面遷移処理
			if (setKeyInput()&PAD_INPUT_LEFT) Cursor = 0, Before = Changer, Changer = RESULT;
			if (setKeyInput()&PAD_INPUT_RIGHT)Cursor = 0, SwitchFlg = 1;

			if (setKeyInput()&PAD_INPUT_10) {
					 if (Cursor == 0)Before = Changer, Changer = RESULT;
				else if (Cursor == 1)SwitchFlg = 1;

				Cursor = 0;
			}
		
		}
	break;
	}
	

}