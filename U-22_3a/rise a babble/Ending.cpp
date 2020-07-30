#include "Scene.h"

static int Count;

void Scene::Ending() {
	DrawString(0, 0, "Ending", 0xffffff);

	if (Count++ > 60)	Changer = END;
}