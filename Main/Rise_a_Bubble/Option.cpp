#include "Scene.h"

void Scene::Option() {
	static int BGM = 75;
	static int SE = 75;
	if(BGM > 100)BGM = 100;
	if (BGM < 0)BGM = 0;

	DrawString(0, 0, "Option", 0xffffff);
	DrawFormatString(0, 60, 0xffffff, "BGM = %d", BGM);
	DrawFormatString(0, 120, 0xffffff, "[©] BGM Down", SE);
	DrawFormatString(0, 140, 0xffffff, "[¨] BGM UP", SE);
	DrawFormatString(0, 160, 0xffffff, "[Space] Back", SE);
	if (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]==TRUE)	BGM--;
	if (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == TRUE) BGM++;
	if (input.Buttons[XINPUT_BUTTON_B] == TRUE) Changer = Before, Before = OPTION ;
}