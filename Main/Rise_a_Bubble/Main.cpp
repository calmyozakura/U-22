//#include "DxLib.h"
#include "Scene.h"
#include <cmath>
#include <math.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble");			// タイトルを設定
	ChangeWindowMode(TRUE);						// ウィンドウモードで起動
	SetGraphMode(WINDOW_X, WINDOW_Y, COLOR_BIT);
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先画面を裏にする
	if (DxLib_Init() == -1)return -1;
	Scene S;//シーンクラスを呼び出し
	if (S.LoadImages() == -1) return -1;
	
	 
	while (ProcessMessage() == 0 && S.Changer != 99) {
		
		 
		GetJoypadXInputState(DX_INPUT_PAD1, &S.input);
		ClearDrawScreen(); // 画面の初期化
		switch (S.Changer)
		{
		case 0:S.Title(); break;//タイトル　　
		case 1:S.GameInit(); break;//ゲーム前の初期化
		case 2:S.GameMain(); break;//ゲーム
		case 3:S.Result(); break;//リザルト
		case 4:S.Option(); break;//オプション
		case 5:S.Ending(); break;
		default:
			break;
		}
		ScreenFlip(); // 裏画面の内容を表画面に反映 

	}
	DxLib_End();				// DX ライブラリ使用の終了処理
	return 0;					// ソフトの終了
}