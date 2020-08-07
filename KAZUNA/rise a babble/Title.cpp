#include "Scene.h"


void Scene::Title() {
	DrawString(0,0,"Title",0xffffff);
	DrawString(0, 40, "[Å©] END",0xffffff);
	DrawString(0, 60, "[Å®] Option", 0xffffff);
	DrawString(0, 80, "[B] Game Start", 0xffffff);
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] == TRUE)	 Before = Changer, Changer = ENDING;
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == TRUE) Before = Changer, Changer = OPTION;
	if (input.Buttons[XINPUT_BUTTON_B] == TRUE)  Before = Changer, Changer = GAMEINIT;

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] == TRUE) CodeRnd_flg = TRUE;
	DrawString(0, 100, "[Å™] Option", 0xffffff);
}