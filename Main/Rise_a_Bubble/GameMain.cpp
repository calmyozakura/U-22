#include "Scene.h"
#include "Enemy.h"
#include <iostream>     // cout
#include <ctime>        // time
#include <cstdlib>      // srand,rand

static int Cursor = 0, Cursor2 = 0, OneShot = 0, Flg = 0;//Cursor:�J�[�\���p OneShot:���d�����̖h�~ Flg:B�𗣂��ƃV�[�����ς��@
bool  Check = false;//�^�C�g���ւ̊m�F��ʁA
static int StartCount;	//�X�^�[�g���̃J�E���g�_�E��
void Scene::GameInit() {
	//DrawString(0, 0, "Now Roading...", 0xffffff);

	int rx = 0;			//x���̍��W�ʒu
	int ry = 0;			//y���̍��W�ʒu

	// ��Q���̏����ݒ� 
	for (int i = 0; i < IMMOVABLEOBJMAX; i++) {

		myEnemy.Entire_x[i] = rx * (WIDTH / 5) + 45;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
		myEnemy.Entire_y[i] = ry * (HEIGHT / 2) / 5 + 50;		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W

		rx += 1;	//x���W

		if (i % 5 == 4) {	//5�z�u����邲�Ƃ�x���W�����ɖ߂�y���W��1�i������
			rx = 0;
			ry += 1;
		}
	}

	// ��Q���̏����ݒ� 
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
			myEnemy.g_immovableobj[m][i].x = -100;
			myEnemy.g_immovableobj[m][i].y = 0;
			myEnemy.g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
			myEnemy.g_immovableobj[m][i].setflg = FALSE;	//��Q����z�u���邩�̃t���O��S��false��
			myEnemy.g_immovableobj[m][i].flg = FALSE;
		}

		// �G�̏����ݒ�  
		for (int i = 0; i < ENEMYMAX; i++) {
			myEnemy.g_enemy[m][i].sx = 50;
			myEnemy.g_enemy[m][i].sy = 50;
			myEnemy.g_enemy[m][i].flg = FALSE;
			myEnemy.g_enemy[m][i].move = FALSE;
		}
	}

	for (int c = 0; c < BULLET_MAX; c++)bullet[c].c_flg = FALSE;

	player.x = WINDOW_X / 2;		//Player���W�̏�����
	player.y = WINDOW_Y / 4 * 3;	//Player���W�̏�����
	player.size = 30;				//Player�T�C�Y�̏�����
	player.max_speed = 6;			//Player�̍ő�X�s�[�h�̏�����
	player.scl = (WINDOW_Y - player.y);		//Scroll�̏�����
	for (int i = 0; i < 4; i++) {
		Vec[i].Inertia = 0;			//�����̏�����
		Vec[i].De_Flg = TRUE;		//�����t���O�̏�����
	}
	srand((unsigned)time(NULL));	//�����Ń����_���̏����l�����߂�
	for (int p = 0; p < MAPMAX; p++) {
		myEnemy.Pattern[p] = GetRand(9);	//0�`3�̃����_���Ȓl
	}

	for (int moji = 0; moji < 3; moji++) {
		CodeOrigin[moji] = moji*moji;		
	}

	StartCount = TRUE;
	T.ScoreTime = 0;
	T.PauseTime = 0;
	T.StartTime = GetNowHiPerformanceCount();
	GoalFlg = FALSE;
	player.place = 0;
	B_Count = 0;
	B_Num = 0;
	Score=0;
	//WaitTimer(300);
	Before = Changer, Changer = GAMEMAIN;		//�V�[���̐؂�ւ�
}

void Scene::GameMain() {
	static int SwitchFlg = 0;
	switch (SwitchFlg)
	{
		//�|�[�Y
	case 1:
	{
		if(Check == true) {
			//�`��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//������
			DrawFillBox(MINIWINDOW_X, MINIWINDOW_Y, WINDOW_X - MINIWINDOW_X, MINIWINDOW_Y + (ADDPOS_Y * 5), 0xffffff);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);// �s����

			DrawTriangle(CURSOR_X, CURSOR_Y * (36 + FixPos2),
				CURSOR_X, CURSOR_Y * (38 + FixPos2),
				CURSOR_X + ADDPOS_Y / 2, CURSOR_Y * (37 + FixPos2), 0xffff00, TRUE);


			DrawString(STRING_X - ADDPOS_Y, STRING_Y - ADDPOS_Y, "�^�C�g���ɖ߂�܂����H", 0xffffff);
			DrawString(STRING_X, STRING_Y, "YES", 0x00ff7f);
			DrawString(STRING_X, STRING_Y + ADDPOS_Y, "NO", 0xff7f00);

			//����

			//�J�[�\��

			if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
				(Cursor2 > 0) ? Cursor2-- : Cursor2 = 1;
				OneShot = 1;
			}
			else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
				(Cursor2 < 1) ? Cursor2++ : Cursor2 = 0;
				OneShot = 1;
			}

			//��ʑJ�ڏ���
			if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
				OneShot = 1, Flg = 1;
			}
			else if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1)
			{
				(Cursor2 == 0) ? Before = Changer, Changer = TITLE, SwitchFlg = 0, Check = false : Check = false;
				 Cursor2 = 0, Flg = 0; 
			}

			if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
				|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
				|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

				OneShot = 0;
			}
		}
		/*
		DrawString(0, 0, "P A U S E", 0xffffff);
		DrawString(0, 40, "[��] Title", 0xffffff);
		DrawString(0, 60, "[��] Option", 0xffffff);
		DrawString(0, 80, "[SPACE] Return Game", 0xffffff);*/
		DrawString(0, 0, "P A U S E", 0xffffff);
		DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 25, "Title", 0xffffff);
		DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 26, "Option", 0xffffff);
		DrawString((WINDOW_X / 4), (WINDOW_Y / 32) * 27, "Return Game", 0xffffff);

		DrawTriangle((WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (50 + Cursor * 2),
			(WINDOW_X / 64) * 14, (WINDOW_Y / 64) * (52 + Cursor * 2),
			(WINDOW_X / 64) * 16, (WINDOW_Y / 64) * (51 + Cursor * 2), 0xffff00, TRUE);


		/*����*/

		T.PauseTimer();

		//�J�[�\��
		if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && OneShot == 0) {
			(Cursor > 0) ? Cursor-- : Cursor = 2;
			OneShot = 1;
		}
		else if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && OneShot == 0) {
			(Cursor < 2) ? Cursor++ : Cursor = 0;
			OneShot = 1;
		}

		//��ʑJ�ڏ���
		/*if (setKeyinput()&PAD_input_LEFT)   Cursor = 0, SwitchFlg = 0,Before = Changer, Changer = TITLE;
		if (setKeyinput()&PAD_input_RIGHT)  Cursor = 0, Before = Changer, Changer = OPTION;
		if (setKeyinput()&PAD_input_10)     Cursor = 0,  SwitchFlg = 0;*/

		if (input.Buttons[XINPUT_BUTTON_B] && OneShot == 0) {
			OneShot = 1, Flg = 1;
		}
		if (!input.Buttons[XINPUT_BUTTON_B] && Flg == 1) {
			if (Cursor == 0)Check = true;
			else if (Cursor == 1)Before = Changer, Changer = OPTION;
			else if (Cursor == 2)SwitchFlg = 0;
			Cursor = 0, Flg = 0;
		}

		if (OneShot == 1 && !(input.Buttons[XINPUT_BUTTON_B]
			|| input.Buttons[XINPUT_BUTTON_DPAD_UP]
			|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])) {

			OneShot = 0;
		}
	}
	break;

	default:
	{
		if (StartCount == TRUE) {
			T.PauseTimer();
			ScrollMap();
			DrawPlayer();
			myEnemy.CreateImmovableObj();
			myEnemy.DrawImmovableObj();

			if (T.PauseTime >= 5) {
				SetFontSize(16);
				StartCount = FALSE;
			}
			else if (T.PauseTime >= 4) DrawFormatString(WINDOW_HALF_X, 150, 0x000000, "1");
			else if (T.PauseTime >= 3) DrawFormatString(WINDOW_HALF_X, 150, 0x000000, "2");
			else if (T.PauseTime >= 2) {
				SetFontSize(50);
				DrawFormatString(WINDOW_HALF_X, 150, 0x000000, "3");
			}
		}else {
			ScrollMap();
			DrawPlayer();
			Bound();
			PlayerMove();
			CreateBubble();
			FireBubble();
			FloatBubble();
			myEnemy.CreateImmovableObj();
			myEnemy.DrawImmovableObj();
			myEnemy.MoveEnemy();
			Goal();
			Score=T.ScoreTimer();
			HitCheck();
			CreateCode();
			if (input.Buttons[XINPUT_BUTTON_START]) { SwitchFlg = 1; }
#ifdef DEBUG
			DrawFormatString(0, 0, 0xff0000, "%d", input.ThumbLY);
			DrawFormatString(0, 15, 0xff0000, "%d", input.ThumbLX);
			DrawFormatString(0, 30, 0x0000ff, "%2.2f", player.x);
			DrawFormatString(0, 75, 0x00ff00, "%f", player.angle);
			DrawFormatString(0, 90, 0x00ff00, "%f", StickX);
			DrawFormatString(0, 105, 0x00ff00, "%f", StickY);
			DrawFormatString(0, 120, 0xff0000, "%2.2f", player.scl);
			DrawFormatString(0, 135, 0xff0000, "%d", MAPMAX*WINDOW_Y);
			DrawFormatString(0, 150, 0xff0000, "%d", GoalFlg);
			DrawString(WINDOW_X - 150,WINDOW_Y - 20,"'20/8/20_00:00",0x000000);
			DrawFormatString(WINDOW_HALF_X, 15, 0xff00ff, "%.2f", T.ScoreTime);


			DrawFormatString(player.x - 3, player.y - 50 - 3, 0xff0000, "%2.2f", Vec[UP].Inertia);
			DrawFormatString(player.x - 3, player.y - 60 - 3, 0x0000ff, "%d", Vec[UP].De_Flg);
			DrawFormatString(player.x - 3, player.y + 50 - 3, 0xff0000, "%2.2f", Vec[DOWN].Inertia);
			DrawFormatString(player.x - 3, player.y + 60 - 3, 0x0000ff, "%d", Vec[DOWN].De_Flg);
			DrawFormatString(player.x - 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[LEFT].Inertia);
			DrawFormatString(player.x - 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[LEFT].De_Flg);
			DrawFormatString(player.x + 50 - 3, player.y - 3, 0xff0000, "%2.2f", Vec[RIGHT].Inertia);
			DrawFormatString(player.x + 60 - 3, player.y - 3, 0x0000ff, "%d", Vec[RIGHT].De_Flg);

			DrawFormatString(0, 165, 0x0000ff, "%d", myEnemy.Entire_x[0]);
			DrawFormatString(0, 180, 0x0000ff, "%d", myEnemy.Entire_x[1]);
#endif // DEBUG
		}
	}break;
	}

}

int Scene::LoadImages() {
	if ((images.muzzle = LoadGraph("Images/muzzle.png")) == -1) return -1;		//���ˌ����̉摜
	if ((images.play = LoadGraph("Images/bubble___1.png")) == -1) return -1;		//���ˌ����̉摜
	LoadDivGraph("Images/Player_Color.png", 16, 4, 4, 63, 63, images.player);
	if ((images.bubble = LoadGraph("Images/bubble.png")) == -1) return -1;		//����ڂ�e�̉摜
	for (int i = 4; i < 10; i++) {
		if ((images.back[i] = LoadGraph("Images/stick.png")) == -1) return -1;	//�w�i�摜
	}
	if ((images.back[0] = LoadGraph("Images/Back1.png")) == -1) return -1;
	if ((images.back[1] = LoadGraph("Images/Back2.png")) == -1) return -1;
	if ((images.back[2] = LoadGraph("Images/Back3.png")) == -1) return -1;
	if ((images.back[3] = LoadGraph("Images/Back4.png")) == -1) return -1;
	if ((ImmovableObj = LoadGraph("Images/Player__.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
	if ((myEnemy.EnemyImage = LoadGraph("Images/bubble.png")) == -1) return -1;	//���������Q���摜�̓ǂݍ���
}

int Scene::Cnt(int n) {		//�^����ꂽ���l��1�𑫂��ĕԂ�
	int i = n;
	i++;
	return i;
}

void Scene::ScrollMap() {	//�w�i����
	for (int i = 0; i < MAPMAX; i++) {
		DrawGraph(0, 0 - (player.scl - (WINDOW_Y*-i)) + (WINDOW_Y / 4), images.back[i], FALSE);
		Map_place[i] = 0 - (player.scl - (WINDOW_Y*-i)) + (WINDOW_Y / 4)+WINDOW_Y;
		if (player.y > Map_place[i] && player.y < Map_place[i] + 20) {
			player.place = i;
		}

	}
}

void Scene::DrawPlayer() {	//Player�̕`��
	static int p = 0;
	static int c = 0;
	Angle();
	c = Cnt(c);
	if (c % 8 == 0)p++;
	if (p == PLAYER_IMAGE)p = 1;
	DrawRotaGraph(player.x, player.y, 1, 0, images.player[p], TRUE);
	DrawRotaGraph(player.x, player.y, 1, player.angle, images.muzzle, TRUE);
}

void Scene::Angle() {		//Player�̌��������߂�
	if (input.ThumbLX >= DEADZONE || input.ThumbLX <= -DEADZONE || input.ThumbLY >= DEADZONE || input.ThumbLY <= -DEADZONE) {
		StickX = (input.ThumbLX / 3.2767);		
		StickY = (input.ThumbLY / 3.2767);		
	}
	float rad = atan2(StickX, StickY);
	player.angle = rad;
}

void Scene::Bound() {		//Player�̕ǂł̔��ˏ���
	if (player.x - player.size <= 0) {					//Player�����̕ǂɓ��������Ƃ��̏���
		player.x = player.size;
		Vec[RIGHT].Inertia = (Vec[LEFT].Inertia - Vec[RIGHT].Inertia);
		Vec[LEFT].Inertia = 0;

		if (Vec[UP].Inertia != 0) {
			Vec[DOWN].Inertia = (Vec[UP].Inertia - Vec[DOWN].Inertia);
			Vec[UP].Inertia = 0;
		}
		else if (Vec[DOWN].Inertia != 0)
		{
			Vec[UP].Inertia = (Vec[DOWN].Inertia - Vec[UP].Inertia);
			Vec[DOWN].Inertia = 0;
		}
	}
	else if (player.x + player.size >= WINDOW_X) {		//Player���E�̕ǂɓ��������Ƃ��̏���
		player.x = WINDOW_X - player.size;
		Vec[LEFT].Inertia = (Vec[RIGHT].Inertia - Vec[LEFT].Inertia);
		Vec[RIGHT].Inertia = 0;

		if (Vec[UP].Inertia != 0) {
			Vec[DOWN].Inertia = (Vec[UP].Inertia - Vec[DOWN].Inertia);
			Vec[UP].Inertia = 0;
		}
		else if (Vec[DOWN].Inertia != 0)
		{
			Vec[UP].Inertia = (Vec[DOWN].Inertia - Vec[UP].Inertia);
			Vec[DOWN].Inertia = 0;
		}
	}
}

void Scene::PlayerMove() {		//Player�̈ړ�����
	//���X�e�B�b�N���f�b�h�]�[�����Ȃ�����t���O��FALSE
	if (input.ThumbLX <= DEADZONE) {
		Vec[RIGHT  ].Add_Flg = FALSE;
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
				myEnemy.g_immovableobj[m][i].y += Vec[UP].Inertia;
			}
			for (int e = 0; e < ENEMYMAX; e++) {
				myEnemy.g_enemy[m][e].my += Vec[UP].Inertia;
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
				myEnemy.g_immovableobj[m][i].y -= Vec[DOWN].Inertia;
			}
			for (int e = 0; e < ENEMYMAX; e++) {
				myEnemy.g_enemy[m][e].my -= Vec[DOWN].Inertia;
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

	for (int i = UP; i < VEC_SIZE; i++) {		//�S�������ʂ̏���
		if (Vec[i].Add_Flg == TRUE) {		//�����t���O���I���ɂȂ��Ă�������Ԋu���Ƃɉ����x�𑝉�
			Vec[i].Add_Cnt = Cnt(Vec[i].Add_Cnt);

			if (Vec[i].Add_Cnt % 3 == 0) {
				Vec[i].Inertia += 0.15f;
			}
		}
		else if (Vec[i].Add_Flg == FALSE) {	//�����t���O���I�t�Ȃ�J�E���g���[���ɂ���
			Vec[i].Add_Cnt = 0;
		}

		if (Vec[i].Inertia > player.max_speed)Vec[i].Inertia = player.max_speed;	//�ő�X�s�[�h�𒴂��Ă���ő�X�s�[�h�ɂ���


		if (Vec[i].De_Flg == TRUE) {		//�����t���O���I���ɂȂ��Ă�����Ԋu���Ƃɉ����x������
			Vec[i].De_Cnt = Cnt(Vec[i].De_Cnt);
			if (Vec[i].De_Cnt % 5 == 0) {
				Vec[i].Inertia -= 0.2f;
			}
		}
		if (Vec[i].De_Flg == FALSE) {		//�����t���O���I�t�Ȃ�J�E���g���[���ɂ���
			Vec[i].De_Cnt = 0;
		}
		if (Vec[i].Inertia < 0) {			//�����x���[���������Ȃ��悤�ɂ���
			Vec[i].Inertia = 0;
		}

		if (Vec[i].Add_Flg == FALSE) {		//�����t���O���I�t�ł����̕����ɐi�ޏ���
			if (i == UP) {
				player.y -= Vec[UP].Inertia;
				player.scl -= Vec[UP].Inertia;
				for (int m = 0; m < MAPMAX; m++) {
					for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
						myEnemy.g_immovableobj[m][i].y += Vec[UP].Inertia;
					}
					for (int e = 0; e < ENEMYMAX; e++) {
						myEnemy.g_enemy[m][e].my += Vec[UP].Inertia;
					}
				}

			}
			if (i == DOWN) {
				player.y += Vec[DOWN].Inertia;
				player.scl += Vec[DOWN].Inertia;
				for (int m = 0; m < MAPMAX; m++) {
					for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
						myEnemy.g_immovableobj[m][i].y -= Vec[DOWN].Inertia;
					}
					for (int e = 0; e < ENEMYMAX; e++) {
						myEnemy.g_enemy[m][e].my -= Vec[DOWN].Inertia;
					}
				}
			}
			if (i == RIGHT)player.x += Vec[RIGHT].Inertia;
			if (i == LEFT)player.x -= Vec[LEFT].Inertia;

		}

		if (Vec[i].Inertia == 0.00f) {	//�����x���[���Ȃ猸������߂�
			Vec[i].De_Flg = FALSE;
		}

		if (player.y <= (WINDOW_Y / 5) * 3) {	//Player�̈ړ��͈͂̐���
			player.y = (WINDOW_Y / 5) * 3;
		}
		if (player.y >= (WINDOW_Y / 5) * 4) {
			player.y = (WINDOW_Y / 5) * 4;
		}

	}
}

void Scene::CreateBubble() {		//����ڂ�e�̐���
	
	if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] == TRUE || input.Buttons[XINPUT_BUTTON_B] == TRUE) {		//RB��������B�Œe�𐶐�
		if (B_Num < BULLET_MAX) {
			if (bullet[B_Num].c_flg == FALSE) {
				bullet[B_Num].x = player.x;
				bullet[B_Num].y = player.y;
				bullet[B_Num].c_flg = TRUE;
				bullet[B_Num].angle = player.angle - 1.5f;
			}
			if (B_Count % (BULLET_MAX / 2) == 0)B_Num++;
			B_Count = Cnt(B_Count);
		}
		if (B_Num >= BULLET_MAX)B_Num = 0;
		if (B_Count == BULLET_MAX)B_Count = 0;
#ifdef DEBUG
		DrawString(WINDOW_X - 55, 0, "GetKey", 0x00ff00);
		DrawFormatString(WINDOW_X - 20, 15, 0x00ff00, "%d", B_Count);
		DrawFormatString(WINDOW_X - 20, 30, 0x00ff00, "%d", B_Num);
		DrawFormatString(WINDOW_X - 20, 45, 0x00ff00, "%d", bullet[B_Num].c_flg);
#endif // DEBUG
	}
	else if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] == FALSE || input.Buttons[XINPUT_BUTTON_B] == FALSE) {
		B_Count = 0;
	}
}

void Scene::FireBubble() {		//�������ꂽ����ڂ�e�𔭎�
	for (int i = 0; i < BULLET_MAX; i++) {		//��������Ă��Ȃ��ꍇ�z��̏���������
		if (bullet[i].c_flg == FALSE && bullet[i].m_flg == FALSE) {
			bullet[i].x = 0;
			bullet[i].y = 0;
			bullet[i].angle = 0;
			bullet[i].speed = 0;
			bullet[i].time = 0;
		}

		if (bullet[i].c_flg == TRUE) {		//��������Ă�����`��
			//DrawCircle(bullet[i].x, bullet[i].y, BULLET_SIZE, 0x00ff00, TRUE);
			DrawRotaGraph(bullet[i].x, bullet[i].y, 1, 0, images.bubble, TRUE);
#ifdef DEBUG
			DrawFormatString(bullet[i].x - 5, bullet[i].y - 5, 0x000000, "%d", i);
#endif // DEBUG
			bullet[i].m_flg = TRUE;
		}

		if (bullet[i].m_flg == TRUE) {		//�����A�`�悪���ꂽ����ڂ�e��Player�̌����ɔ���
			bullet[i].x += cos(bullet[i].angle)*BULLET_SPEED;
			bullet[i].y += sin(bullet[i].angle)*BULLET_SPEED;
			if (bullet[i].x > WINDOW_X + BULLET_SIZE || bullet[i].y > WINDOW_Y + BULLET_SIZE
				|| bullet[i].x < 0 - BULLET_SIZE || bullet[i].y < 0 - BULLET_SIZE) {	//����ڂ�e����ʊO�ɍs���Ə���
				bullet[i].c_flg = FALSE;
				bullet[i].m_flg = FALSE;
			}
		}
	}
}

void Scene::FloatBubble()		//�����쎞��Player���ӂ�ӂ�Ɠ�������
{
	static int f = 0;
	static int x = 0, y = 0;
	f = Cnt(f);
	if ((Vec->Add_Flg == FALSE && Vec->De_Flg == FALSE) && f % 6 == 0) {
		player.x += infinity[x][y];
		y++;
		player.y += infinity[x][y];
		x++;
		y--;
		if (x == INFINITY_X)x = 0;
	}
}

void Scene::HitCheck(void)
{
	static int i_f = 0;
	if (i_f != 0) {
		player.scl = (WINDOW_Y - player.y) - player.place*WINDOW_Y;
		i_f = 0;
		for (int m = 0; m < MAPMAX; m++) {
			for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
				myEnemy.g_immovableobj[m][i].y += player.place*WINDOW_Y;
			}
			for (int e = 0; e < ENEMYMAX; e++) {
				myEnemy.g_enemy[m][e].my += player.place*WINDOW_Y;
			}
		}
	}
	//	�v���C���[�Ə�Q���̓����蔻��
	for (int m = 0; m < MAPMAX; m++) {
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			myEnemy.hit_x[i] = player.x - myEnemy.g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
			myEnemy.hit_y[i] = player.y - myEnemy.g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
			myEnemy.hit_r[i] = sqrt(myEnemy.hit_x[i] * myEnemy.hit_x[i] + myEnemy.hit_y[i] * myEnemy.hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

			if (myEnemy.hit_r[i] <= player.size + myEnemy.g_immovableobj[m][i].r)		//�������Ă��邩����
			{
				DrawString(100, HEIGHT - 20, "��Q���ƃq�b�g", White);
				player.x = WINDOW_X / 2;		//Player���W�̏�����
				player.y = WINDOW_Y / 4 * 3;
				player.scl = (WINDOW_Y - player.y);
				i_f = 1;
				for (int i = 0; i < 4; i++) {
					Vec[i].Inertia = 0;			//�����̏�����
					Vec[i].De_Flg = TRUE;		//�����t���O�̏�����
				}
				B_Count = 0;
				B_Num = 0;

				// ��Q���̏����ݒ� 
				for (int m = 0; m < MAPMAX; m++) {
					for (int i = 0; i < IMMOVABLEOBJMAX; i++) {
						myEnemy.g_immovableobj[m][i].x = -100;
						myEnemy.g_immovableobj[m][i].y = 0;
						myEnemy.g_immovableobj[m][i].r = 30.0f;	//��Q���̉~�̔��a
						myEnemy.g_immovableobj[m][i].setflg = FALSE;	//��Q����z�u���邩�̃t���O��S��false��
						myEnemy.g_immovableobj[m][i].flg = FALSE;
					}

					// �G�̏����ݒ�  
					for (int i = 0; i < ENEMYMAX; i++) {
						myEnemy.g_enemy[m][i].sx = 50;
						myEnemy.g_enemy[m][i].sy = 50;
						myEnemy.g_enemy[m][i].flg = FALSE;
						myEnemy.g_enemy[m][i].move = FALSE;
					}
				}

				for (int c = 0; c < BULLET_MAX; c++)bullet[c].c_flg = FALSE;
			}
		}

		//�v���C���[�ƓG�̓����蔻��
		for (int e = 0; e < ENEMYMAX; e++) {	//�~�Ǝl�p
			if ((DistanceSqrf(myEnemy.g_enemy[m][e].mx, (myEnemy.g_enemy[m][e].mx + myEnemy.g_enemy[m][e].sx), myEnemy.g_enemy[m][e].my, (myEnemy.g_enemy[m][e].my + myEnemy.g_enemy[m][e].sy), player.x, player.y, player.size) == true)) {
				DrawString(100, HEIGHT - 40, "�G�ƃq�b�g", White);
			}
		}

		//����ڂ�e�Ƃ̓����蔻��
		for (int i = 0; i < IMMOVABLEOBJMAX; i++) {		//�v���C���[�Ɠ�������I�u�W�F�N�g(�~�Ɖ~)
			for (int b = 0; b < BULLET_MAX; b++) {
				myEnemy.hit_x[i] = bullet[b].x - myEnemy.g_immovableobj[m][i].x;	//�v���C���[�Ə�Q����x���W�̍�
				myEnemy.hit_y[i] = bullet[b].y - myEnemy.g_immovableobj[m][i].y;	//�v���C���[�Ə�Q����y���W�̍�
				myEnemy.hit_r[i] = sqrt(myEnemy.hit_x[i] * myEnemy.hit_x[i] + myEnemy.hit_y[i] * myEnemy.hit_y[i]);	//�v���C���[�Ə�Q���̉~�̔��a�̘a

				if (myEnemy.hit_r[i] <= BULLET_SIZE + myEnemy.g_immovableobj[m][i].r)		//�������Ă��邩����
				{
					DrawString(100, HEIGHT - 20, "��Q���Ƀq�b�g", White);
					myEnemy.g_immovableobj[m][i].x += cos(bullet[b].angle)*BULLET_SPEED;
					myEnemy.g_immovableobj[m][i].y += sin(bullet[b].angle)*BULLET_SPEED;
					bullet[b].c_flg = FALSE;
					bullet[b].m_flg = FALSE;
				}
			}
		}
	}

}

float Scene::DistanceSqrf(float L, float R, float T, float B, float x, float y, float r)
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

void Scene::CreateCode() {		//�}�b�v�R�[�h�̐���
	if (CodeRnd_flg == TRUE) {
		for (int co = 0; co < MAPMAX; co++) {
			DrawFormatString(0 + co * 10, 150, 0xff0000, "%c\n", Code[co]);
		}

		for (int m = 0; m < MAPMAX; m++) {
			Code[m] = 'A' + myEnemy.Pattern[m];
			if (m == MAPMAX - 1)Code[MAPMAX] = '\n';
		}
	}
	if (CodeRnd_flg == FALSE) {

	}
}
