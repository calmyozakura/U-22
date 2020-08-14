//#include "DxLib.h"
#include "scene.h"
#include <cmath>
#include <math.h>
#include "Fps.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble");			// タイトルを設定
	ChangeWindowMode(TRUE);						// ウィンドウモードで起動
	SetGraphMode(WINDOW_X, WINDOW_Y, COLOR_BIT);
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先画面を裏にする
	if (DxLib_Init() == -1)return -1;

	Scene S;//シーンクラスを呼び出し
	C_FPS F;
	if (S.LoadImages() == -1)return -1;

	while (ProcessMessage() == 0 && S.Changer != 99) {


		S.getKeyInput();
		ClearDrawScreen(); // 画面の初期化
		switch (S.Changer)
		{
		case 0:S.Title(); break;//タイトル
		case 1:S.GameMode(); break;
		case 2:S.GameInit(); break;//ゲーム前の初期化
		case 3:S.GameMain(); break;//ゲーム
		case 4:S.Result(); break;//リザルト
		case 5:S.Option(); break;//オプション
		case 6:S.Ending(); break;//終了

		default:goto finish; break;//あくまでも応急処理
		}
		F.Update();
		F.Draw();
		ScreenFlip(); // 裏画面の内容を表画面に反映 
		F.Wait();
	}
finish://gotoからの応急処理
	DxLib_End();				// DX ライブラリ使用の終了処理
	return 0;					// ソフトの終了
}