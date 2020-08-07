#include "Scene.h"
void Scene::getKeyInput() {

	GetJoypadXInputState(DX_INPUT_PAD1, &Input);

	DrawFormatString(0, 400, 0xffffff, "%d");
};