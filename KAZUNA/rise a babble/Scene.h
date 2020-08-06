#ifndef _SCENE_H_

#define _SCENE_H_

#include "DxLib.h"

#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 5000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7
#define INFINITY_X 24
#define INFINITY_Y 2
#define WIDTH 480
#define HEIGHT 640
#define IMMOVABLEOBJMAX 25	//��������I�u�W�F�N�g�̍ő�\����
#define ENEMYMAX 1			//�����G�̍ő�\����
#define MAPMAX 5			//�}�b�v�̍ő吔


#define DEBUG



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

typedef struct IMMOVABLEOBJ {

	float x, y, r;	//x���W,y���W,���a
	bool setflg;	//��Q����z�u���邩�̃t���O
	int flg;		//�g�p�t���O
};

typedef struct ENEMY {
	int mx, my;
	int sx, sy;
	int flg;	//�g�p�t���O
	int move;	//�ړ��t���O(false=�E,true=��)
};


struct PLAYER {
	float x, y;				//���W
	int size;				//���a
	int w, h;				//�摜�̍����A��
	double angle;			//�v���C���[�̌���
	float max_speed;		//�v���C���[�̍ő呬�x
	float scl;
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

class Hit {
public:
	void HitCheck(void);
};

class Scene :public Hit {
public:

	int Changer = 0;//�V�[���p�ϐ�
	int Before = 0;//�O��ʂ̕ϐ�

	void Title();//�^�C�g���@�@
	void GameInit();//�Q�[���O�̏�����
	void GameMain();//�Q�[��
	void Result();//���U���g
	void Option();//�I�v�V����
	void Ending();//�G���h

	XINPUT_STATE input;
	float StickX, StickY;

	int CodeOrigin[3];
	char Code[MAPMAX];

	int CodeRnd_flg = FALSE;


	int infinity[INFINITY_X][INFINITY_Y]{
	{1,-1},{1,-1},{1,0},{1,0},{1,1},{0,1},{0,1},{-1,1},{-1,0},{-1,0},{-1,-1},{-1,-1},
	{-1,-1},{-1,-1},{-1,0},{-1,0},{-1,1},{0,1},{0,1},{1,1},{1,0},{1,0},{1,-1},{1,-1}
	};
	state g_GameState = SET;
	struct PLAYER player;
	struct BULLET bullet[BULLET_MAX];
	struct _VECTOR Vec[VEC_SIZE];
	struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];
	struct IMAGES {
		int muzzle;
		int player;
		int back[10];
		int bubble;
	}images;

	ENEMY g_enemy[MAPMAX][ENEMYMAX];

	int Player;				//�v���C���[�̉摜�������
	int ImmovableObj;		//�����Ȃ���Q���̉摜�������ϐ�
	int enemy;		//�����G�̉摜�������ϐ�

	float hit_x[IMMOVABLEOBJMAX];	//�~�̓����蔻��_x
	float hit_y[IMMOVABLEOBJMAX];	//�~�̕ӂ蔻��_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//�~�̓����蔻��_x
	float hit_ey[ENEMYMAX];	//�~�̕ӂ蔻��_y
	float hit_er[ENEMYMAX];

	int rx, ry;	//��Q���̔z�u������炷���߂̕ϐ�
	int Entire_x[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
	int Entire_y[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W


	int color = (255, 255, 255);
	int red = GetColor(255, 0, 0);	//�ԐF
	int yellow = GetColor(0, 255, 0);	//�ԐF
	int White = GetColor(255, 255, 255);	//��

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

	void CreateImmovableObj();
	void DrawImmovableObj();
	void MoveEnemy();
	float DistanceSqrf(float L, float R, float T, float B, float x, float y, float r);

protected:

private:

	typedef	enum {
		_INIT = -1,
		TITLE = 0,
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