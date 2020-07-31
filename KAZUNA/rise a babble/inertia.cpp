#include "DxLib.h"
#include <math.h>
#include "inertia.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand



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
void ScrollMap();
void HitCheck(void);

void CreateImmovableObj();
void DrawImmovableObj();
void MoveEnemy();
float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r);
void GameInit(void);



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
		
		
		
		
		ClearDrawScreen();		// ��ʂ̏����� 

		switch (g_GameState)
		{
		case SET:
			GameInit();
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
	if ((images.player = LoadGraph("Images/player_b.png")) == -1) return -1;
	if ((images.bubble = LoadGraph("Images/bubble.png")) == -1) return -1;
	for (int i = 0; i < 10; i++) {
		if ((images.back[i] = LoadGraph("Images/stick.png")) == -1) return -1;
	}
	if ((Player = LoadGraph("Images/Player.png")) == -1) return -1;		//�v���C���[�摜�̓ǂݍ���
	if ((ImmovableObj = LoadGraph("Images/Player__.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
	if ((Enemy = LoadGraph("Images/bubble.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
}

void Main() {
	ScrollMap();
	DrawPlayer();
	Bound();
	PlayerMove();
	CreateBubble();
	FireBubble();
	FloatBubble();
	CreateImmovableObj();	
	DrawImmovableObj();		
	MoveEnemy();
	HitCheck();
	

#ifdef DEBUG
	DrawFormatString(0, 0, 0xff0000, "%d", input.ThumbLY);
	DrawFormatString(0, 15, 0xff0000, "%d", input.ThumbLX);
	DrawFormatString(0, 30, 0x0000ff, "%2.2f", player.x);

	DrawFormatString(0, 120, 0xff0000, "%2.2f", player.scl);

	DrawFormatString(0, 75, 0x00ff00, "%f", player.angle);
	DrawFormatString(0, 90, 0x00ff00, "%f", StickX);
	DrawFormatString(0, 105, 0x00ff00, "%f", StickY);

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



void DrawPlayer() {
	Angle();
	DrawRotaGraph(player.x, player.y, 1, 0, images.player, TRUE);
	DrawRotaGraph(player.x, player.y, 1,  player.angle, images.muzzle, TRUE);
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
		player.y -= Vec[UP].Inertia;
		player.scl -= Vec[UP].Inertia;
		for (int m = 0; m < MAPMAX; m++) {
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				g_immovableobj[m][i].y += Vec[UP].Inertia;
			}
			for (int e = 0; e < ENEMYMAX; e++) {
				g_enemy[m][e].my += Vec[UP].Inertia;
			}
		}
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
		player.scl += Vec[DOWN].Inertia;
		for (int m = 0; m < MAPMAX; m++) {
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				g_immovableobj[m][i].y -= Vec[DOWN].Inertia;
			}
			for (int e = 0; e < ENEMYMAX; e++) {
				g_enemy[m][e].my -= Vec[DOWN].Inertia;
			}
		}
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
			if (i == UP) {
				player.y -= Vec[UP].Inertia;
				player.scl-= Vec[UP].Inertia;
				for (int m = 0; m < MAPMAX; m++) {
					for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
						g_immovableobj[m][i].y+= Vec[UP].Inertia;
					}
					for (int e = 0; e < ENEMYMAX; e++) {
						g_enemy[m][e].my += Vec[UP].Inertia;
					}
				}
				
			}
			if (i == DOWN) {
				player.y += Vec[DOWN].Inertia;
				player.scl += Vec[DOWN].Inertia;
				for (int m = 0; m < MAPMAX; m++) {
					for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
						g_immovableobj[m][i].y -= Vec[DOWN].Inertia;
					}
					for (int e = 0; e < ENEMYMAX; e++) {
						g_enemy[m][e].my -= Vec[DOWN].Inertia;
					}
				}
			}
			if (i == RIGHT)player.x+= Vec[RIGHT].Inertia;
			if (i == LEFT)player.x -= Vec[LEFT].Inertia;
		
		}

		if (Vec[i].Inertia == 0.00f) {
			Vec[i].De_Flg = FALSE;
		}

		if (player.y <= (WINDOW_Y/5)*3) {
			player.y = (WINDOW_Y / 5)*3;
		}
		if (player.y >= (WINDOW_Y / 5)*4) {
			player.y = (WINDOW_Y / 5)*4;
		}
		
	}
}

void Setting() {
	player.x = WINDOW_X / 2;
	player.y = WINDOW_Y / 4 * 3;
	player.size = 31;
	Vec[UP].De_Flg = TRUE;
	Vec[DOWN].De_Flg = TRUE;
	Vec[RIGHT].De_Flg = TRUE;
	Vec[LEFT].De_Flg = TRUE;
	player.max_speed = 6;
	player.scl = (WINDOW_Y - player.y);
	for (int i = 0; i < 4; i++) {
		Vec[i].Inertia=0;
	}
	srand((unsigned)time(NULL));	//�����Ń����_���̏����l�����߂�
	for (int p = 0; p < MAPMAX; p++) {
		Pattern[p] = GetRand(2);	//0�`3�̃����_���Ȓl
	}
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
		if (bullet[i].c_flg == FALSE && bullet[i].m_flg == FALSE) {
			bullet[i].x = 0;
			bullet[i].y = 0;
			bullet[i].angle = 0;
			bullet[i].speed = 0;
			bullet[i].time = 0;
		}

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
			if (bullet[i].x > WINDOW_X + BULLET_SIZE || bullet[i].y > WINDOW_Y + BULLET_SIZE || bullet[i].x < 0 - BULLET_SIZE || bullet[i].y < 0 - BULLET_SIZE) {
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
	static int x = 0, y = 0;
	f = Cnt(f);
	if ((Vec->Add_Flg == FALSE && Vec->De_Flg == FALSE) && f%6==0) {
		player.x += infinity[x][y];
		y++;
		player.y += infinity[x][y];
		x++;
		y--;
		if (x == INFINITY_X)x = 0;
	}
}

void ScrollMap() {
	for (int i = 0; i < 10; i++) {
		DrawGraph(0, 0 - (player.scl - (WINDOW_Y*-i)) + (WINDOW_Y / 4), images.back[i], FALSE);
	}
}



//***************************************
//	�G�ƃI�u�W�F�N�g�̐���
//***************************************
void CreateImmovableObj(void) {

	for (int m = 0; m < MAPMAX; m++) {
		switch (Pattern[m]) {		//��Q���̐���
		case 0:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = i * 130;
					g_immovableobj[m][i].y = (i * 70 + 10) + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
		case 1:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = WIDTH + (i * -130);
					g_immovableobj[m][i].y = (i * 70 + 10) + (-m * HEIGHT);
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
		case 2:
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				if (g_immovableobj[m][i].flg == false) {
					g_immovableobj[m][i].x = WIDTH + (i * -140);
					g_immovableobj[m][i].y = (-m * HEIGHT) + 200;
					g_immovableobj[m][i].flg = true;
				}
			}
			break;
		}

		for (int e = 0; e < ENEMYMAX; e++) {	//�G�̐���
			if (g_enemy[m][e].flg == false) {
				g_enemy[m][e].mx = 0;
				g_enemy[m][e].my = (-m * HEIGHT) + 100;
				g_enemy[m][e].flg = true;
			}
		}
	}
}
//***********************************************
//	�G�ƃI�u�W�F�N�g�̕`��
//***********************************************
void DrawImmovableObj(void) {
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			//DrawGraph(g_immovableobj[i].x, g_immovableobj[i].y, ImmovableObj, TRUE); //���������Q���̕`��
			DrawCircle(g_immovableobj[m][i].x, g_immovableobj[m][i].y, g_immovableobj[m][i].r, (200, 200, 200), true);
		}

		for (int e = 0; e < ENEMYMAX; e++) {
			DrawGraph(g_enemy[m][e].mx, g_enemy[m][e].my, Enemy, TRUE); //�G�̕`��
		}
	}
}
//************************************************
//	�G�̈ړ�
//************************************************
void MoveEnemy(void) {

	for (int m = 0; m < MAPMAX; m++) {
		for (int e = 0; e < ENEMYMAX; e++) {
			if (g_enemy[m][e].flg == true) {
				if (g_enemy[m][e].mx <= 50) g_enemy[m][e].move = true;	//x���W��50�ȉ��ŉE�ړ��t���Oon
				else if (g_enemy[m][e].mx >= WIDTH - 100) g_enemy[m][e].move = false; //x���W��WIDTH-100�ȏ�ō��ړ��t���Oon

				if (g_enemy[m][e].move == true)	g_enemy[m][e].mx += 3;
				else if (g_enemy[m][e].move == false) g_enemy[m][e].mx -= 3;
			}
		}
	}
}

void GameInit(void)
{

	// ��Q���̏����ݒ� 
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			g_immovableobj[m][i].x = 0;	//��Q����x���W
			g_immovableobj[m][i].y = 0;	//��Q����y���W
			g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
			g_immovableobj[m][i].flg = FALSE;
		}

		// �G�̏����ݒ�  
		for (int i = 0; i < ENEMYMAX; i++) {
			g_enemy[m][i].sx = 50;
			g_enemy[m][i].sy = 50;
			g_enemy[m][i].flg = FALSE;
			g_enemy[m][i].move = FALSE;
		}
	}

	InitFlg = true;
}

void HitCheck(void)
{

	//	�v���C���[�Ə�Q���̓����蔻��
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			hit_x[i] = player.x - g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
			hit_y[i] = player.y - g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
			hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

			if (hit_r[i] <= player.size + g_immovableobj[m][i].r)		//�������Ă��邩����
			{
				DrawString(100, HEIGHT - 20, "��Q���ƃq�b�g", White);
				/*if (Vec[UP].Inertia != 0) {
					Vec[DOWN].Inertia = Vec[UP].Inertia;
					player.y -= Vec[DOWN].Inertia;
					Vec[UP].Inertia = 0;
				}
				else if (Vec[DOWN].Inertia != 0) {
					Vec[UP].Inertia = Vec[DOWN].Inertia;
					player.y += Vec[UP].Inertia;
					Vec[DOWN].Inertia = 0;
				}
				if (Vec[RIGHT].Inertia != 0) {
					Vec[LEFT].Inertia = Vec[RIGHT].Inertia;
					player.x -= Vec[LEFT].Inertia;
					Vec[RIGHT].Inertia = 0;
				}
				else if (Vec[LEFT].Inertia != 0) {
					Vec[RIGHT].Inertia = Vec[LEFT].Inertia;
					player.x += Vec[RIGHT].Inertia;
					Vec[LEFT].Inertia = 0;
				}*/

				/*if (Vec[UP].Inertia != 0)Vec[UP].Inertia = 0;
				if (Vec[DOWN].Inertia != 0)Vec[DOWN].Inertia = 0;
				if (Vec[RIGHT].Inertia != 0)Vec[RIGHT].Inertia = 0;
				if (Vec[LEFT].Inertia != 0)Vec[LEFT].Inertia = 0;*/

				g_GameState = SET;
			}
		}

		//�v���C���[�ƓG�̓����蔻��
		for (int e = 0; e < ENEMYMAX; e++) {	//�~�Ǝl�p
			if ((DistanceSqrf(g_enemy[m][e].mx, (g_enemy[m][e].mx + g_enemy[m][e].sx), g_enemy[m][e].my, (g_enemy[m][e].my + g_enemy[m][e].sy), player.x, player.y, player.size) == true)) {
				DrawString(100, HEIGHT - 40, "�G�ƃq�b�g", White);
			}
		}

		//����ڂ�e�Ƃ̓����蔻��
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			for (int b = 0; b < BULLET_MAX; b++) {
				hit_x[i] = bullet[b].x - g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
				hit_y[i] = bullet[b].y - g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
				hit_r[i] = sqrt(hit_x[i] * hit_x[i] + hit_y[i] * hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

				if (hit_r[i] <= BULLET_SIZE + g_immovableobj[m][i].r)		//�������Ă��邩����
				{
					DrawString(100, HEIGHT - 20, "��Q���Ƀq�b�g", White);
					g_immovableobj[m][i].x += cos(bullet[b].angle)*BULLET_SPEED;
					g_immovableobj[m][i].y += sin(bullet[b].angle)*BULLET_SPEED;
					bullet[b].c_flg = FALSE;
					bullet[b].m_flg = FALSE;
				}
			}
		}
	}

}

float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r)
{
	if (L - r > x || R + r < x || T - r > y || B + r < y) {//��`�̗̈攻��1
		return false;
	}
	if (L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < r * r)) {//����̓����蔻��
		return false;
	}
	if (R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < r * r)) {//�E��̓����蔻��
		return false;
	}
	if (L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < r * r)) {//�����̓����蔻��
		return false;
	}
	if (R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < r * r)) {//�E���̓����蔻��
		return false;
	}
	return true;//���ׂĂ̏������O�ꂽ�Ƃ��ɓ������Ă���
}