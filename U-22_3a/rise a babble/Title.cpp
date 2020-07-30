#include "Scene.h"


void Scene::Title() {
	DrawString(0,0,"Title",0xffffff);
	DrawString(0, 40, "[Å©] END",0xffffff);
	DrawString(0, 60, "[Å®] Option", 0xffffff);
	DrawString(0, 80, "[SPACE] Game Start", 0xffffff);
	if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = ENDING;
	if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = OPTION;
	if (setKeyInput()&PAD_INPUT_10)  Before = Changer, Changer = GAMEINIT;

}