#include "Scene.h"

void Scene::Option() {
	static int BGM = 75;
	static int SE  = 75;
	static int Cursor = 0;

	DrawString(0, 0, "Option", 0xffffff);
	DrawFormatString(0, 60, 0xffffff, "BGM = %d", BGM);
	DrawFormatString(0, 80, 0xffffff, " SE = %d", SE);
	DrawFormatString(0, 120, 0xffffff, "[←] Down");
	DrawFormatString(0, 140, 0xffffff, "[→] UP");
	DrawFormatString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, 0xffffff, "[Space] Back");

	DrawBox((WINDOW_X / 8), (WINDOW_Y / 64) * 20, (WINDOW_X / 2), (WINDOW_Y / 64) * 21, 0xffffff, TRUE);
	DrawCircle((((WINDOW_X / 2) - (WINDOW_X / 8)) * BGM / 100) + (WINDOW_X / 8),
				 (WINDOW_Y / 64) * 20.5, 8, 0x00ff77);

	DrawBox((WINDOW_X / 8), (WINDOW_Y / 64) * 25, (WINDOW_X / 2), (WINDOW_Y / 64) * 26, 0xffffff, TRUE);
	DrawCircle((((WINDOW_X / 2) - (WINDOW_X / 8)) *  SE / 100) + (WINDOW_X / 8),
				 (WINDOW_Y / 64) * 25.5, 8, 0x0ff770);

	DrawTriangle((WINDOW_X / 64) * 4, (WINDOW_Y / 64) * (19 + Cursor * 5),
				 (WINDOW_X / 64) * 4, (WINDOW_Y / 64) * (21 + Cursor * 5),
				 (WINDOW_X / 64) * 6, (WINDOW_Y / 64) * (20 + Cursor * 5), 0xffff00, TRUE);

	/*処理*/

	//それぞれの前提範囲
	if (BGM > 100)BGM = 100;
	if (BGM < 0)BGM = 0;

	if (SE > 100) SE = 100;
	if (SE < 0) SE = 0;

	//カーソル
	if (setKeyInput()&PAD_INPUT_UP)
		(Cursor > 0) ? Cursor-- : Cursor = 1;
	if (setKeyInput()&PAD_INPUT_DOWN)
		(Cursor < 1) ? Cursor++ : Cursor = 0;
	
	if (setKeyInput()&PAD_INPUT_LEFT)
		(Cursor == 0) ? BGM-- : SE--;
	if (setKeyInput()&PAD_INPUT_RIGHT)
		(Cursor == 0) ? BGM++ : SE++;

	//画面遷移処理
	if (setKeyInput()&PAD_INPUT_10) Cursor = 0, Changer = Before, Before = OPTION ;
}