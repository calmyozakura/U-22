#include "DxLib.h"
#include <math.h>
#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 8000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7;

#define DEBUG


class Fps {
	int Start;						//測定開始時刻
	int Cnt;						//カウンタ
	float Frame;					//fps
	static const int Sample = 60;	//平均を取るサンプル数
	static const int FPS = 60;		//設定したFPS

public:
	Fps() {
		Start = 0;
		Cnt = 0;
		Frame = 0;
	}

	bool Update() {
		if (Cnt == 0) {				//1フレーム目なら時刻を記憶
			Start = GetNowCount();
		}
		if (Cnt == Sample) {		//60フレーム目なら平均を計算する
			int t = GetNowCount();
			Frame = 1000.f / ((t - Start) / (float)Sample);
			Cnt = 0;
			Start = t;
		}
		Cnt++;
		return TRUE;
	}

	void Wait() {
		int Took = GetNowCount() - Start;		//かかった時間
		int Wait = Cnt * 1000 / FPS - Took;		//待つべき時間
		if (Wait > 0) {
			Sleep(Wait);			//待機
		}
	}

	void Draw() {
		DrawFormatString(0,45,0x000000,"%.2f",Frame);
	}

}fps;

//変数宣言


float StickX, StickY;

typedef enum {
	SET,
	MAIN
}state;
typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	VEC_SIZE
};
state g_GameState = SET;

struct IMAGES {
	int muzzle;
	int player;
	int back;
	int bubble;
}images;

struct PLAYER {
	float x, y;				//座標
	int size;				//半径
	int w, h;				//画像の高さ、幅
	double angle;			//プレイヤーの向き
	float max_speed;		//プレイヤーの最大速度
};
struct PLAYER player;

struct BULLET {
	int x, y;
	int time;
	double angle;
	float speed;
	int c_flg;
	int m_flg;
};
struct BULLET bullet[BULLET_MAX];

struct _VECTOR
{
	float Inertia;
	int Add_Flg;
	int Add_Cnt;
	int De_Flg;
	int De_Cnt;
};
struct _VECTOR Vec[VEC_SIZE];

XINPUT_STATE input;

//プロトタイプ宣言

void Main();				//ゲームメイン
int LoadImages();			//画像読み込み関数
void PlayerMove();			//プレイヤーの動作に関する処理
void Setting();				//初期設定
void DrawPlayer();			//プレイヤーの描画
void Bound();				//プレイヤーが壁でバウンドする処理
int Cnt(int n);				//入れた値をカウントする処理
void CreateBubble();		//しゃぼん弾生成
void FireBubble();			//しゃぼん弾発射
void Angle();				//プレイヤーの向きの処理
void FloatBubble();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble");			// タイトルを設定
	ChangeWindowMode(TRUE);						// ウィンドウモードで起動
	SetGraphMode(WINDOW_X,WINDOW_Y,COLOR_BIT);
	if (DxLib_Init() == -1) return -1;			// DX ライブラリの初期化処理
	if (LoadImages() == -1) return -1;			// 画像読込み関数を呼び出し
	//if (LoadMusic() == -1) return -1;			// 音声読込み関数を呼び出し
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先画面を裏にする

	while (ProcessMessage() == 0 && g_GameState != 99) {
		// 入力キー取得
		
		
		GetJoypadXInputState(DX_INPUT_PAD1,&input);
		
		ClearDrawScreen();		// 画面の初期化 

		switch (g_GameState)
		{
		case SET:
			Setting();
		case MAIN:
			Main();
			break;
		}
		fps.Update();			//更新
		fps.Draw();
		ScreenFlip();			// 裏画面の内容を表画面に反映
		fps.Wait();
	}
	DxLib_End();				// DX ライブラリ使用の終了処理
	return 0;					// ソフトの終了
}

int LoadImages() {
	if ((images.muzzle = LoadGraph("Images/muzzle.png")) == -1) return -1;
	if ((images.player = LoadGraph("Images/player___.png")) == -1) return -1;
	if ((images.back = LoadGraph("Images/stick.png")) == -1) return -1;
	if ((images.bubble = LoadGraph("Images/bubble.png")) == -1) return -1;
}

void Main() {
	DrawPlayer();
	Bound();
	PlayerMove();
	CreateBubble();
	FireBubble();
	FloatBubble();
	

#ifdef DEBUG
	DrawFormatString(0, 0, 0xff0000, "%d", input.ThumbLY);
	DrawFormatString(0, 15, 0xff0000, "%d", input.ThumbLX);
	DrawFormatString(0, 30, 0x0000ff, "%2.2f", player.x);

#endif // DEBUG

}



void DrawPlayer() {
	DrawGraph(0, 0, images.back, FALSE);
	Angle();
	//DrawCircle(player.x, player.y, player.size, 0x0000ff, TRUE);
	DrawRotaGraph(player.x, player.y, 1, 0, images.player, TRUE);
	DrawRotaGraph(player.x, player.y, 1,  player.angle, images.muzzle, TRUE);
	
#ifdef DEBUG
	DrawFormatString(0,75,0x00ff00,"%f",player.angle);
	DrawFormatString(0, 90, 0x00ff00, "%f", StickX);
	DrawFormatString(0, 105, 0x00ff00, "%f", StickY);
#endif // DEBUG

}

void PlayerMove() {
	//左スティックがデッドゾーン内なら加速フラグをFALSE
	if (input.ThumbLX <= DEADZONE) {
		Vec[RIGHT].Add_Flg = FALSE;
		Vec[RIGHT].De_Flg = TRUE;
	}
	if (input.ThumbLX >= -DEADZONE) {
		Vec[LEFT].Add_Flg = FALSE;
		Vec[LEFT].De_Flg = TRUE;
	}
	if (input.ThumbLY <= DEADZONE) {
		Vec[UP].Add_Flg = FALSE;
		Vec[UP].De_Flg = TRUE;
	}
	if (input.ThumbLY >= -DEADZONE) {
		Vec[DOWN].Add_Flg = FALSE;
		Vec[DOWN].De_Flg = TRUE;
	}

	//左スティックがデッドゾーン外なら移動し、そして加速、各方向への移動、慣性フラグをオン
	if (input.ThumbLY >= DEADZONE) {
		player.y-=Vec[UP].Inertia;
		Vec[UP].Add_Flg = TRUE;
		Vec[UP].De_Flg = FALSE;
	}
	if (input.ThumbLX >= DEADZONE) {
		player.x += Vec[RIGHT].Inertia;
		Vec[RIGHT].Add_Flg = TRUE;
		Vec[RIGHT].De_Flg = FALSE;
	}
	if (input.ThumbLY <= -DEADZONE) {
		player.y += Vec[DOWN].Inertia;
		Vec[DOWN].Add_Flg = TRUE;
		Vec[DOWN].De_Flg = FALSE;
	}
	if (input.ThumbLX <= -DEADZONE) {
		player.x -= Vec[LEFT].Inertia;
		Vec[LEFT].Add_Flg = TRUE;
		Vec[LEFT].De_Flg = FALSE;
	}

	for (int i = UP; i < VEC_SIZE;i++) {
		if (Vec[i].Add_Flg == TRUE) {
			Vec[i].Add_Cnt = Cnt(Vec[i].Add_Cnt);

			if (Vec[i].Add_Cnt % 3 == 0) {
				Vec[i].Inertia += 0.15f;
			}
		}
		else if (Vec[i].Add_Flg == FALSE) {
			Vec[i].Add_Cnt = 0;
		}

		if (Vec[i].Inertia > player.max_speed)Vec[i].Inertia = player.max_speed;


		if (Vec[i].De_Flg == TRUE) {
			Vec[i].De_Cnt = Cnt(Vec[i].De_Cnt);
			if (Vec[i].De_Cnt % 5 == 0) {
				Vec[i].Inertia -= 0.2f;
			}
		}
		if (Vec[i].De_Flg == FALSE) {
			Vec[i].De_Cnt = 0;
		}
		if (Vec[i].Inertia < 0) {
			Vec[i].Inertia = 0;
		}

		if (Vec[i].Add_Flg == FALSE) {
			if (i == UP)player.y-=Vec[UP].Inertia;
			if (i == DOWN)player.y += Vec[DOWN].Inertia;
			if (i == RIGHT)player.x+= Vec[RIGHT].Inertia;
			if (i == LEFT)player.x -= Vec[LEFT].Inertia;
		
		}
		
	}

#ifdef DEBUG
	DrawFormatString(player.x - 3, player.y - 50 - 3, 0xff0000, "%2.2f", Vec[UP].Inertia);
	DrawFormatString(player.x - 3, player.y - 60 - 3, 0x0000ff, "%d", Vec[UP].De_Flg);
	DrawFormatString(player.x - 3, player.y + 50 - 3, 0xff0000, "%2.2f", Vec[DOWN].Inertia);
	DrawFormatString(player.x - 3, player.y + 60 - 3, 0x0000ff, "%d", Vec[DOWN].De_Flg);
	DrawFormatString(player.x - 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[LEFT].Inertia);
	DrawFormatString(player.x - 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[LEFT].De_Flg);
	DrawFormatString(player.x + 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[RIGHT].Inertia);
	DrawFormatString(player.x + 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[RIGHT].De_Flg);
#endif // DEBUG

}

void Setting() {
	player.x = WINDOW_X / 2;
	player.y = WINDOW_Y / 4 * 3;
	player.size = 30;
	Vec[UP].De_Flg = TRUE;
	Vec[DOWN].De_Flg = TRUE;
	Vec[RIGHT].De_Flg = TRUE;
	Vec[LEFT].De_Flg = TRUE;
	player.max_speed = 6;

	g_GameState = MAIN;
}

int Cnt(int n) {
 	int i=n;
	i++;
	return i;
}

void Bound() {
	if (player.x-player.size <= 0) {
		player.x = player.size;
		Vec[RIGHT].Inertia=Vec[LEFT].Inertia;
		Vec[LEFT].Inertia = 0;

		if (Vec[UP].Inertia != 0) {
			Vec[DOWN].Inertia = Vec[UP].Inertia;
			Vec[UP].Inertia = 0;
		}
		else if (Vec[DOWN].Inertia != 0)
		{
			Vec[UP].Inertia = Vec[DOWN].Inertia;
			Vec[DOWN].Inertia = 0;
		}
	}
	else if (player.x+player.size >= WINDOW_X) {
		player.x = WINDOW_X - player.size;
		Vec[LEFT].Inertia = Vec[RIGHT].Inertia;
		Vec[RIGHT].Inertia = 0;

		if (Vec[UP].Inertia != 0) {
			Vec[DOWN].Inertia = Vec[UP].Inertia;
			Vec[UP].Inertia = 0;
		}
		else if (Vec[DOWN].Inertia != 0)
		{
			Vec[UP].Inertia = Vec[DOWN].Inertia;
			Vec[DOWN].Inertia = 0;
		}
	}

	if (player.y - player.size <= 0) {
		player.y = player.size;
		Vec[DOWN].Inertia = Vec[UP].Inertia;
		Vec[UP].Inertia = 0;
	}
	else if (player.y+ player.size >= WINDOW_Y) {
		player.y = WINDOW_Y - player.size;
		Vec[UP].Inertia = Vec[DOWN].Inertia;
		Vec[DOWN].Inertia = 0;
	}
}

void CreateBubble() {
	static int i = 0;
	static int m = 0;
	if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]==TRUE || input.Buttons[XINPUT_BUTTON_B] == TRUE) {
		if(i<BULLET_MAX) {
			if (bullet[i].c_flg == FALSE ) {
				bullet[i].x = player.x;
				bullet[i].y = player.y;
				bullet[i].c_flg = TRUE;
				bullet[i].angle = player.angle-1.5f;
			}
			if(m % (BULLET_MAX / 2) == 0)i++;
			m = Cnt(m);
		}
		if (i >= BULLET_MAX)i = 0;
		if (m == BULLET_MAX)m = 0;
#ifdef DEBUG
		DrawString(WINDOW_X - 55, 0, "GetKey", 0x00ff00);
		DrawFormatString(WINDOW_X-20,15,0x00ff00,"%d",m);
		DrawFormatString(WINDOW_X - 20, 30, 0x00ff00, "%d", i);
#endif // DEBUG
	}
	else if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] == FALSE || input.Buttons[XINPUT_BUTTON_B] == FALSE) {
		m = 0;
	}
}

void FireBubble() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].c_flg == TRUE) {
			//DrawCircle(bullet[i].x, bullet[i].y, BULLET_SIZE, 0x00ff00, TRUE);
			DrawRotaGraph(bullet[i].x, bullet[i].y, 1, 0, images.bubble, TRUE);
#ifdef DEBUG
			DrawFormatString(bullet[i].x - 5, bullet[i].y - 5, 0x000000, "%d", i);
#endif // DEBUG
			bullet[i].m_flg = TRUE;
		}

		if (bullet[i].m_flg == TRUE) {
			bullet[i].x += cos(bullet[i].angle)*BULLET_SPEED;
			bullet[i].y += sin(bullet[i].angle)*BULLET_SPEED;
			if (bullet[i].x > WINDOW_X + BULLET_SIZE || bullet[i].y > WINDOW_Y + BULLET_SIZE || bullet[i].x<0-BULLET_SIZE || bullet[i].y < 0 - BULLET_SIZE) {
				bullet[i].c_flg = FALSE;
				bullet[i].m_flg = FALSE;
			}
		}
	}
}

void Angle() {
	if (input.ThumbLX >= DEADZONE || input.ThumbLX <= -DEADZONE || input.ThumbLY >= DEADZONE || input.ThumbLY <= -DEADZONE) {
		StickX = (input.ThumbLX / 3.2767);
		StickY = (input.ThumbLY / 3.2767);
	}
	float rad = atan2(StickX, StickY);
	player.angle = rad;
}

void FloatBubble()
{
	static int f=0;
	f = Cnt(f);
	if ((Vec->Add_Flg == FALSE || Vec->De_Flg == FALSE) && f%15==0) {
		f = Cnt(f);
		player.x += (rand() % 2) *0.5f;
		player.y += (rand() % 2) *0.5f;
		player.x -= (rand() % 2) *0.5f;
		player.y -= (rand() % 2) *0.5f;
	}
}
