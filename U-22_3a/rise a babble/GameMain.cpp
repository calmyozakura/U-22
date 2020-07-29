#include "Scene.h"

void Scene::GameInit() {
	DrawString(0, 0, "Now Roading...", 0xffffff);
	WaitTimer(300);
	Before = Changer, Changer = GAMEMAIN;
}

void Scene::GameMain() {
	static int SwitchFlg = 0;
	switch (SwitchFlg)
	{
		//É|Å[ÉY
	case 1:
		DrawString(0, 0, "P A U S E", 0xffffff);
		DrawString(0, 40, "[Å©] Title", 0xffffff);
		DrawString(0, 60, "[Å®] Option", 0xffffff);
		DrawString(0, 80, "[SPACE] Return Game", 0xffffff);
		if (setKeyInput()&PAD_INPUT_LEFT)  SwitchFlg = 0,Before = Changer, Changer = TITLE;
		if (setKeyInput()&PAD_INPUT_RIGHT) Before = Changer, Changer = OPTION;
		if (setKeyInput()&PAD_INPUT_10)  SwitchFlg = 0;
		
		break;

	default:

		DrawString(0, 0, "GameMain", 0xffffff);
		DrawString(0, 40, "[Å©] Result", 0xffffff);
		DrawString(0, 60, "[Å®] PAUSE", 0xffffff);
		//DrawString(0, 80, "[SPACE] GameMain", 0xffffff);
		if (setKeyInput()&PAD_INPUT_LEFT)  Before = Changer, Changer = RESULT;
		if (setKeyInput()&PAD_INPUT_RIGHT) SwitchFlg = 1;
		//if (setKeyInput()&PAD_INPUT_10)  Before = Changer, Changer = ENDING;
	break;
	}
	

}