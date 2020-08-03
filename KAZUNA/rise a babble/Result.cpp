#include "Scene.h"


void Scene::Result() {
	DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[Å©] Title", 0xffffff);
	DrawString(0, 60, "[Å®] Replay Game", 0xffffff);
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] == TRUE)	 Before = Changer, Changer = TITLE;
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == TRUE) Before = Changer, Changer = GAMEINIT;
}