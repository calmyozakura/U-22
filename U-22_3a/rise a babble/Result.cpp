#include "Scene.h"


void Scene::Result() {
	DrawString(0,0,"Result",0xffffff);
	DrawString(0, 40, "[Å©] Title", 0xffffff);
	DrawString(0, 60, "[Å®] Replay Game", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = TITLE;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = GAMEINIT;
}