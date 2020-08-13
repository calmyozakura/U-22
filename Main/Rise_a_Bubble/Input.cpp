#include "Scene.h"
void Scene::getKeyInput() {

	/*g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;*/
};

int Scene::setKeyInput() {

	return g_KeyFlg;
};