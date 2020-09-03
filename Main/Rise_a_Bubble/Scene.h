#ifndef _SCENE_H_

#define _SCENE_H_

#include "DxLib.h"
#include "Enemy.h"
#include <string>

#define WINDOW_X 480
#define WINDOW_Y 640
#define WINDOW_HALF_X 240
#define WINDOW_HALF_Y 320
#define COLOR_BIT 16
#define DEADZONE 8000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7
#define INFINITY_X 24
#define INFINITY_Y 2
#define WIDTH 480
#define HEIGHT 640
#define PLAYER_IMAGE 16
#define TORNADO_SIZE 64

#define CURSOR_X 105
#define CURSOR_Y 10
#define FixPos Cursor * 6
#define FixPos2 Cursor2 * 6
#define TITLE_Y 160
#define STRING_X 170
#define STRING_Y 360
#define ADDPOS_X 50
#define ADDPOS_Y 60
#define MINIWINDOW_X 75
#define MINIWINDOW_Y 230
#define Bar ((WINDOW_X - ADDPOS_X) - CURSOR_X)//((WINDOW_X / 2) - (WINDOW_X / 8)),STRING_Y
#define Radius 8
#define Percent 100

//#define IMMOVABLEOBJMAX 25	//��������I�u�W�F�N�g�̍ő�\����
//#define ENEMYMAX 1			//�����G�̍ő�\����
//#define MAPMAX 5			//�}�b�v�̍ő吔


#define DEBUG

typedef enum {
	choose,
	decide,
	cancel
}SE; 


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

//typedef struct IMMOVABLEOBJ {
//
//	float x, y, r;	//x���W,y���W,���a
//	bool setflg;	//��Q����z�u���邩�̃t���O
//	int flg;		//�g�p�t���O
//};
//
//typedef struct ENEMY {
//	int mx, my;
//	int sx, sy;
//	int flg;	//�g�p�t���O
//	int move;	//�ړ��t���O(false=�E,true=��)
//};


struct PLAYER {
	float x, y;				//���W
	int size;				//���a
	int w, h;				//�摜�̍����A��
	double angle;			//�v���C���[�̌���
	float max_speed;		//�v���C���[�̍ő呬�x
	float scl;
	int place = 0;
};


struct BULLET {
	int x, y;
	int time;
	double angle;
	float speed;
	int c_flg;
	int m_flg;
};


struct _VECTOR
{
	float Inertia;
	int Add_Flg;
	int Add_Cnt;
	int De_Flg;
	int De_Cnt;
};
class TIME
{
public:
	LONGLONG StartTime;
	float ScoreTime;
	float PauseTime;

	float ScoreTimer();
	void PauseTimer();
};
static TIME T;
class MAP {
public:
	
};
static MAP M;

class Hit {
public:
	void HitCheck(void);
};

class Scene :public Hit {
public:

	int Changer = 0;//�V�[���p�ϐ�
	int Before = 0;//�O��ʂ̕ϐ�
	int Difficulty = 0;//��Փx

	void getKeyInput();

	void Title();//�^�C�g���@�@
	void GameInit();//�Q�[���O�̏�����
	void GameMode();//�Q�[�����[�h�I��
	void Pass();	//�p�X���͉��
	void Load();	//�R�[�X�̃��[�h
	void GameMain();//�Q�[��
	void Result();//���U���g
	void Option();//�I�v�V����
	void Ending();//�G���h

	XINPUT_STATE input;
	float StickX, StickY;

	bool GoalFlg;

	float Score=0;

	int B_Count;
	int B_Num;

	int CodeOrigin[3];
	char* Code;

	bool Pass_Flg = FALSE;

	int CodeRnd_flg = FALSE;

	bool Load_Flg = FALSE;

	int LoadNumber;	//�ǂ̃R�[�X��ǂނ��̕ϐ�
	char PassNumber[20];	//�p�X���͎��Ɏg���ϐ�

	int infinity[INFINITY_X][INFINITY_Y]{
	{1,-1},{1,-1},{1,0},{1,0},{1,1},{0,1},{0,1},{-1,1},{-1,0},{-1,0},{-1,-1},{-1,-1},
	{-1,-1},{-1,-1},{-1,0},{-1,0},{-1,1},{0,1},{0,1},{1,1},{1,0},{1,0},{1,-1},{1,-1}
	};
	state g_GameState = SET;
	struct PLAYER player;
	struct BULLET bullet[BULLET_MAX];
	struct _VECTOR Vec[VEC_SIZE];
	//struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];
	struct IMAGES {
		int muzzle;
		int back[20];
		int bubble;
		int player[PLAYER_IMAGE];
		int play;
		int Tornado[3];
	}images;

	//ENEMY g_enemy[MAPMAX][ENEMYMAX];
	int Map_place[MAPMAX];

	int Player;				//�v���C���[�̉摜�������
	int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
	int enemy;		//�����G�̉摜�������ϐ�


	int color = (255, 255, 255);
	int red = GetColor(255, 0, 0);	//�ԐF
	int yellow = GetColor(0, 255, 0);	//�ԐF
	int White = GetColor(255, 255, 255);	//��

	struct SoundEffect
	{
		int Sound[3];
	}se;
	
	int BGM_vol = 50 , SE_vol = 50;
	int SoundLoader();


	int Pattern[MAPMAX];		//�G���Q���Ȃǂ̃p�^�[��

	void PlayerMove();			//�v���C���[�̓���Ɋւ��鏈��
	void DrawPlayer();			//�v���C���[�̕`��
	void Bound();				//�v���C���[���ǂŃo�E���h���鏈��
	int Cnt(int n);				//���ꂽ�l���J�E���g���鏈��
	void CreateBubble();		//����ڂ�e����
	void FireBubble();			//����ڂ�e����
	void Angle();				//�v���C���[�̌����̏���
	void FloatBubble();
	void ScrollMap();
	void HitCheck(void);
	int LoadImages();
	void CreateCode();
	void Goal();

	//void CreateImmovableObj();
	//void DrawImmovableObj();
	//void MoveEnemy();
	float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r);

protected:

private:

	typedef	enum {
		_INIT = -1,
		TITLE = 0,
		GAMEMODE,
		PASS,
		LOAD,
		GAMEINIT,
		GAMEMAIN,
		RESULT,
		OPTION,
		ENDING,
		END = 99
	}num;

	int g_OldKey, g_NowKey, g_KeyFlg;



};

#endif