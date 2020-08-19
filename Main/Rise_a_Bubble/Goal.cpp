#include"Scene.h"


void Scene::Goal() {

	DrawFormatString(WINDOW_HALF_X, WINDOW_Y - 15, 0xffff00, "%.2f", player.scl);
	if (-player.scl > (MAPMAX*WINDOW_Y))GoalFlg = TRUE;
	if (GoalFlg == TRUE) {
		Before = Changer, Changer = RESULT;
	}
}