#include "Scene.h"

static int Cursor= 0 ;

void Scene::Title() {
	DrawString(0,0,"Title",0xffffff);

	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "Game Start", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "Option", 0xffffff);
	DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "END", 0xffffff);

	DrawTriangle((WINDOW_X / 64) * 14,  (WINDOW_Y / 64) * (50 + Cursor * 2),
				 (WINDOW_X / 64) * 14,  (WINDOW_Y / 64) * (52 + Cursor * 2),
				 (WINDOW_X / 64) * 16,  (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00,TRUE);

	/*ˆ—*/

	//ƒJ[ƒ\ƒ‹
	if (setKeyInput()&PAD_INPUT_UP)
		(Cursor > 0) ? Cursor-- : Cursor = 2;
	if (setKeyInput()&PAD_INPUT_DOWN)
		(Cursor < 2) ? Cursor++ : Cursor = 0;

	//‰æ–Ê‘JˆÚˆ—
	if (setKeyInput()&PAD_INPUT_10) {
		if (Cursor == 0)Before = Changer, Changer = GAMEINIT;
		else if (Cursor == 1)Before = Changer, Changer = OPTION;
		else if (Cursor == 2)Before = Changer, Changer = ENDING;
		Cursor = 0;
	}
}