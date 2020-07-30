#include "Scene.h"

static int Cursor = 0;

void Scene::Result() {
	/*DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[©] Title", 0xffffff);
	DrawString(0, 60, "[¨] Replay Game", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = TITLE;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = GAMEINIT;*/

	DrawString(0, 0, "Result", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "to Title", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "replay Game", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
		(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
		(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);

	/*ˆ—*/

	//ƒJ[ƒ\ƒ‹
	if (setKeyInput()&PAD_INPUT_UP)
		(Cursor > 0) ? Cursor-- : Cursor = 1;
	if (setKeyInput()&PAD_INPUT_DOWN)
		(Cursor < 1) ? Cursor++ : Cursor = 0;

	//‰æ–Ê‘JˆÚˆ—
	if (setKeyInput()&PAD_INPUT_10) {
		if (Cursor == 0)Before = Changer, Changer = TITLE;
		else if (Cursor == 1)Before = Changer, Changer = GAMEINIT;
		Cursor = 0;
	}
}