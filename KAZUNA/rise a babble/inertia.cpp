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
	int Start;						//����J�n����
	int Cnt;						//�J�E���^
	float Frame;					//fps
	static const int Sample = 60;	//���ς����T���v����
	static const int FPS = 60;		//�ݒ肵��FPS

public:
	Fps() {
		Start = 0;
		Cnt = 0;
		Frame = 0;
	}

	bool Update() {
		if (Cnt == 0) {				//1�t���[���ڂȂ玞�����L��
			Start = GetNowCount();
		}
		if (Cnt == Sample) {		//60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			Frame = 1000.f / ((t - Start) / (float)Sample);
			Cnt = 0;
			Start = t;
		}
		Cnt++;
		return TRUE;
	}

	void Wait() {
		int Took = GetNowCount() - Start;		//������������
		int Wait = Cnt * 1000 / FPS - Took;		//�҂ׂ�����
		if (Wait > 0) {
			Sleep(Wait);			//�ҋ@
		}
	}

	void Draw() {
		DrawFormatString(0,45,0x000000,"%.2f",Frame);
	}

}fps;

//�ϐ��錾


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
	float x, y;				//���W
	int size;				//���a
	int w, h;				//�摜�̍����A��
	double angle;			//�v���C���[�̌���
	float max_speed;		//�v���C���[�̍ő呬�x
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

//�v���g�^�C�v�錾

void Main();				//�Q�[�����C��
int LoadImages();			//�摜�ǂݍ��݊֐�
void PlayerMove();			//�v���C���[�̓���Ɋւ��鏈��
void Setting();				//�����ݒ�
void DrawPlayer();			//�v���C���[�̕`��
void Bound();				//�v���C���[���ǂŃo�E���h���鏈��
int Cnt(int n);				//���ꂽ�l���J�E���g���鏈��
void CreateBubble();		//����ڂ�e����
void FireBubble();			//����ڂ�e����
void Angle();				//�v���C���[�̌����̏���
void FloatBubble();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble");			// �^�C�g����ݒ�
	ChangeWindowMode(TRUE);						// �E�B���h�E���[�h�ŋN��
	SetGraphMode(WINDOW_X,WINDOW_Y,COLOR_BIT);
	if (DxLib_Init() == -1) return -1;			// DX ���C�u�����̏���������
	if (LoadImages() == -1) return -1;			// �摜�Ǎ��݊֐����Ăяo��
	//if (LoadMusic() == -1) return -1;			// �����Ǎ��݊֐����Ăяo��
	SetDrawScreen(DX_SCREEN_BACK);				// �`����ʂ𗠂ɂ���

	while (ProcessMessage() == 0 && g_GameState != 99) {
		// ���̓L�[�擾
		
		
		GetJoypadXInputState(DX_INPUT_PAD1,&input);
		
		ClearDrawScreen();		// ��ʂ̏����� 

		switch (g_GameState)
		{
		case SET:
			Setting();
		case MAIN:
			Main();
			break;
		}
		fps.Update();			//�X�V
		fps.Draw();
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
		fps.Wait();
	}
	DxLib_End();				// DX ���C�u�����g�p�̏I������
	return 0;					// �\�t�g�̏I��
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
	//���X�e�B�b�N���f�b�h�]�[�����Ȃ�����t���O��FALSE
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

	//���X�e�B�b�N���f�b�h�]�[���O�Ȃ�ړ����A�����ĉ����A�e�����ւ̈ړ��A�����t���O���I��
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
