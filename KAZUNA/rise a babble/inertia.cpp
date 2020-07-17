#include "DxLib.h"
#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 8000

#define _DEBUG



//�ϐ��錾
int g_OldKey; // �O��̓��̓L�[
int g_NowKey; // ����̓��̓L�[
int g_KeyFlg; // ���̓L�[��� 


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

struct PLAYER {
	float x, y; //���W
	int size; //���a
	int w, h; //�摜�̍����A��
	double angle; //�v���C���[�̌���
	float max_speed;
};
struct PLAYER player;

struct _VECTOR
{
	float Inertia;
	int Add_Flg;
	int Add_Cnt;
	int De_Flg;
	int De_Cnt;
	int Vec_Flg;
	int Ine_Flg;
};
struct _VECTOR Vec[VEC_SIZE];

XINPUT_STATE input;

//�v���g�^�C�v�錾
void Main();
void PlayerMove();
void Setting();
void DrawPlayer();
void Bound();
int Cnt(int n);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Rise a babble"); // �^�C�g����ݒ�
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ŋN��
	SetGraphMode(WINDOW_X,WINDOW_Y,COLOR_BIT);
	if (DxLib_Init() == -1) return -1; // DX ���C�u�����̏���������
	//if (LoadImages() == -1) return -1; // �摜�Ǎ��݊֐����Ăяo��
	//if (LoadMusic() == -1) return -1; // �����Ǎ��݊֐����Ăяo��
	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���

	while (ProcessMessage() == 0 && g_GameState != 99) {
		// ���̓L�[�擾
		
		
		GetJoypadXInputState(DX_INPUT_PAD1,&input);
		
		ClearDrawScreen(); // ��ʂ̏����� 

		switch (g_GameState)
		{
		case SET:
			Setting();
		case 1:
			Main();
			break;
		}



		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End(); // DX ���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}


void Main() {
	DrawPlayer();
	Bound();
	PlayerMove();
	

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xff0000, "%d", input.ThumbLY);
	DrawFormatString(0, 15, 0xff0000, "%d", input.ThumbLX);
	DrawFormatString(0, 30, 0x0000ff, "%2.2f", player.x);

#endif // _DEBUG

}



void DrawPlayer() {
	DrawCircle(player.x, player.y, player.size, 0x0000ff, TRUE);
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
		Vec[UP].Vec_Flg = TRUE;
		Vec[UP].De_Flg = FALSE;

	}
	if (input.ThumbLX >= DEADZONE) {
		player.x += Vec[RIGHT].Inertia;
		Vec[RIGHT].Add_Flg = TRUE;
		Vec[RIGHT].Vec_Flg = TRUE;
		Vec[RIGHT].De_Flg = FALSE;

	}
	if (input.ThumbLY <= -DEADZONE) {
		player.y += Vec[DOWN].Inertia;
		Vec[DOWN].Add_Flg = TRUE;
		Vec[DOWN].Vec_Flg = TRUE;
		Vec[DOWN].De_Flg = FALSE;

	}
	if (input.ThumbLX <= -DEADZONE) {
		player.x -= Vec[LEFT].Inertia;
		Vec[LEFT].Vec_Flg = TRUE;
		Vec[LEFT].Add_Flg = TRUE;
		Vec[LEFT].De_Flg = FALSE;

	}

	for (int i = UP; i < VEC_SIZE;i++) {
		if (Vec[i].Add_Flg == TRUE) {
			Vec[i].Add_Cnt = Cnt(Vec[i].Add_Cnt);

			if (Vec[i].Add_Cnt % 3 == 0) {
				Vec[i].Inertia += 0.15f;
			}

			/*switch (Vec[i].Add_Cnt) {
			case 5:
			case 10:
			case 15:
			case 20:
			case 25:
			case 30:
			case 40:
			case 60:
				Vec[i].Inertia += 0.4f;
				break;
			}*/
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
			/*switch (Vec[i].De_Cnt) {
			case 20:
				Vec[i].Inertia -= 1.0f;
				break;
			case 40:
				Vec[i].Inertia -= 1.0f;
				break;
			case 60:
				Vec[i].Inertia -= 1.0f;
				break;
				}
			*/
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

	

		/*if (Inertia > 1) {
			De_Inertia_flg = TRUE;
		}
		else if (Inertia == 1) {
			De_Inertia_flg = FALSE;
		}
		if (De_Inertia_Cnt == 0) {
			Vector_Flg[UP] = FALSE;
			Vector_Flg[DOWN] = FALSE;
			Vector_Flg[LEFT] = FALSE;
			Vector_Flg[RIGHT] = FALSE;
		}*/


	/*

	if (De_Inertia_flg == TRUE) {
		De_Inertia_Cnt = Cnt(De_Inertia_Cnt);
		if (De_Inertia_Cnt == 10)Inertia -= 1;
		else if (De_Inertia_Cnt == 20)Inertia -= 1;
		else if (De_Inertia_Cnt == 50)Inertia -= 1;
	}
	else if (De_Inertia_flg == FALSE) {
		De_Inertia_Cnt = 0;

		Vector_Flg[UP] = FALSE;
		Vector_Flg[DOWN] = FALSE;
		Vector_Flg[LEFT] = FALSE;
		Vector_Flg[RIGHT] = FALSE;
	}


	if (Inertia_Flg == TRUE && De_Inertia_flg == TRUE) {
		if (Vector_Flg[UP] == TRUE) player.y -= Inertia;
		if (Vector_Flg[DOWN] == TRUE) player.y += Inertia;
		if (Vector_Flg[LEFT] == TRUE) player.x -= Inertia;
		if (Vector_Flg[RIGHT] == TRUE) player.x += Inertia;
	}
	*/

#ifdef _DEBUG
	DrawFormatString(player.x - 3, player.y - 50 - 3, 0xff0000, "%2.2f", Vec[UP].Inertia);
	DrawFormatString(player.x - 3, player.y - 60 - 3, 0x0000ff, "%d", Vec[UP].De_Flg);
	DrawFormatString(player.x - 3, player.y + 50 - 3, 0xff0000, "%2.2f", Vec[DOWN].Inertia);
	DrawFormatString(player.x - 3, player.y + 60 - 3, 0x0000ff, "%d", Vec[DOWN].De_Flg);
	DrawFormatString(player.x - 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[LEFT].Inertia);
	DrawFormatString(player.x - 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[LEFT].De_Flg);
	DrawFormatString(player.x + 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[RIGHT].Inertia);
	DrawFormatString(player.x + 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[RIGHT].De_Flg);
#endif // _DEBUG

}

void Setting() {
	player.x = WINDOW_X / 2;
	player.y = WINDOW_Y / 4 * 3;
	player.size = 30;
	g_GameState = MAIN;
	Vec[UP].De_Flg = TRUE;
	Vec[DOWN].De_Flg = TRUE;
	Vec[RIGHT].De_Flg = TRUE;
	Vec[LEFT].De_Flg = TRUE;
	player.max_speed = 6;
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
		if (Vec[LEFT].Ine_Flg) {

		}
	}
	else if (player.x+player.size >= WINDOW_X) {
		player.x = WINDOW_X - player.size;
		Vec[LEFT].Inertia = Vec[RIGHT].Inertia;
		Vec[RIGHT].Inertia = 0;
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