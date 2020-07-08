
#include <DxLib.h>

/************列挙体の宣言*******************/

typedef enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_MAIN,
	GAME_END,
	GAME_RESULT,
	GAME_OPTION,
	END = 99
};
/************定数の宣言*********************/

/************変数の宣言*********************/

//"g_…"はグローバル変数である

int g_OldKey; // 前回の入力キー
int g_NowKey; // 今回の入力キー
int g_KeyFlg; // 入力キー情報
int g_GameState = GAME_TITLE; // ゲームモード
int g_TitleImage; // タイトル画像 
/************関数のプロトタイプ宣言*********/
void DrawGameTitle();
void GameInit();
void DrawEnd();
void GameMain();
void Option();
void DrawResult();

/************プログラムの開始***************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//SetMainWindowText(" ボ ム リ ス"); // タイトルを設定
	ChangeWindowMode(TRUE); // ウィンドウモードで起動
	if (DxLib_Init() == -1) return -1; // DX ライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする 

	//ゲームループの開始
	while (ProcessMessage() == 0
		&& g_GameState != END
		&& !(g_KeyFlg & PAD_INPUT_START)) {

		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);//PAD+キーを取得
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen(); // 画面の初期化 

		/*多分最適な書き方ではないのは承知*/

		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle(); //タイトル処理
			break;

		case GAME_INIT:
			GameInit(); //ゲーム初期処理
			break;

		case GAME_END:
			DrawEnd(); //エンド描画処理
			break;

		case GAME_MAIN:
			GameMain(); //ゲームメイン処理
			break;

		case GAME_RESULT:
			DrawResult(); //リザルト描画処理
			break;

		case GAME_OPTION:
			Option();
		}
		ScreenFlip(); // 裏画面の内容を表画面に反映
	}
	DxLib_End(); // DX ライブラリ使用の終了処理

	return 0; // ソフトの終了 
}

/**********タイトル***********/
void DrawGameTitle() {

	DrawString(0,0,"Title",0xffffff);
	DrawString(0, 40, "[Space] Start", 0xffffff);
	DrawString(0, 60, "[←] End", 0xffffff);
	DrawString(0, 80, "[→] Option", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_10) {
		g_GameState = GAME_INIT;
	}

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		g_GameState = GAME_END;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		g_GameState = GAME_OPTION;
	}
}

/**********初期化***********/
void GameInit() {

	DrawString(0, 0, "initing...", 0xffffff);
	WaitTimer(60);
	g_GameState = GAME_MAIN;
}
/*********ゲームメイン***********/
void GameMain() {
	static int flg = 0;
	


	switch(flg){
	case 1:
		DrawString(0, 0, "Pause", 0xffffff);
		DrawString(0, 40, "[Space] Return to Game", 0xffffff);
		DrawString(0, 60, "[←] Option", 0xffffff);
		DrawString(0, 80, "[→] Return to Title", 0xffffff);

		if (g_KeyFlg&PAD_INPUT_10) {
			flg = 0;
		}

		if (g_KeyFlg&PAD_INPUT_LEFT) {
			g_GameState = GAME_OPTION;
		}

		if (g_KeyFlg&PAD_INPUT_RIGHT) {
			g_GameState = GAME_TITLE;
		}
	break;
		
	
	default:
		DrawString(0, 0, "Game Main", 0xffffff);
		DrawString(0, 40, "[Space] Pause", 0xffffff);
		DrawString(0, 60, "[←] Result", 0xffffff);

		if (g_KeyFlg&PAD_INPUT_10) {
			flg = 1;
		}

		if (g_KeyFlg&PAD_INPUT_LEFT) {
			g_GameState = GAME_RESULT;
		}
		break;
	}
}
/*オプション（Volume内蔵）*/
void Option() {
	static int BGMVol = 75;
	DrawString(0, 0, "Option", 0xffffff);
	DrawFormatString(0, 180, 0xffffff, "BGMVol:%d",BGMVol);
	DrawString(0, 40, "[Space] Back Pause", 0xffffff);
	DrawString(0, 60, "[←] BGMVol Down", 0xffffff);
	DrawString(0, 80, "[→] BGMVol UP", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		BGMVol--;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		BGMVol++;
	}
	if (g_KeyFlg&PAD_INPUT_10) {
		g_GameState = GAME_MAIN;
	}
}
/*ゲームリザルト*/
void DrawResult() {
	DrawString(0, 0, "Result", 0xffffff);
	DrawString(0, 60, "[←] Replay", 0xffffff);
	DrawString(0, 80, "[→] Return to Title", 0xffffff);

	if (g_KeyFlg&PAD_INPUT_LEFT) {
		g_GameState = GAME_MAIN;
	}

	if (g_KeyFlg&PAD_INPUT_RIGHT) {
		g_GameState = GAME_TITLE;
	}
}
/*エンド*/
void DrawEnd() {
	DrawString(0, 0, "ENDING", 0xffffff);
	WaitTimer(120);
	g_GameState = END;
}