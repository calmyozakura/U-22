#include"Scene.h"
static int OneShot = 0, Flg = 0;//OneShot:���d�����̖h�~ Flg:B�𗣂��ƃV�[�����ς��@
bool FontFlg = FALSE;
void Scene::Goal() {

	DrawFormatString(WINDOW_HALF_X, WINDOW_Y - 15, 0xffff00, "%.2f", player.scl);
	if (-player.scl > ((MAPMAX-1)*WINDOW_Y))GoalFlg = TRUE;
	if (GoalFlg == TRUE) {

		if (FontFlg == FALSE) {
			FontFlg = TRUE;
			SetFontSize(30);
		}
		DrawFormatString(WINDOW_HALF_X - 50, 150, 0xffffff, "Goal�I");
		DrawFormatString(WINDOW_HALF_X - 100, WINDOW_HALF_Y - 100, 0xffffff, "Time : %.2f", Score);	//�^�C��
		DrawFormatString(WINDOW_HALF_X - 200, WINDOW_HALF_Y + 200, 0xffffff, "B button to the result");

		////��ʑJ�ڏ���
		if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
			OneShot = 1, Flg = 1;
		}
		else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
		{
			sound.StopBGM(sound.Game);
			Before = Changer, Changer = RESULT;
			OneShot = 0 ,Flg = 0;
			SetFontSize(16);
			FontFlg = FALSE;
		}
	}
}