#ifndef _ENEMY_H_
#define _ENEMY_H_

class Enemy {
private:
#define IMMOVABLEOBJMAX 25	//��������I�u�W�F�N�g�̍ő�\����
#define ENEMYMAX 1			//�����G�̍ő�\����
#define MAPMAX 5			//�}�b�v�̍ő吔

public:

	int EnemyImage;		//�����G�̉摜�������ϐ�

	int Entire_x[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W
	int Entire_y[IMMOVABLEOBJMAX];		//��Q���̍��W�ɓ����O�ɂ��炩���ߎ���Ă������W

	float hit_x[IMMOVABLEOBJMAX];	//�~�̓����蔻��_x
	float hit_y[IMMOVABLEOBJMAX];	//�~�̕ӂ蔻��_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//�~�̓����蔻��_x
	float hit_ey[ENEMYMAX];	//�~�̕ӂ蔻��_y
	float hit_er[ENEMYMAX];

	int Pattern[MAPMAX];		//�G���Q���Ȃǂ̃p�^�[��

	int rx, ry;	//��Q���̔z�u������炷���߂̕ϐ�

	//Enemy();						//Enemy�̃R���X�g���N�^
	void CreateImmovableObj(void);	//�G�Ɠ��������Q������
	void DrawImmovableObj(void);	//�G�Ɠ��������Q���̕`��
	void MoveEnemy(void);	//�G�̈ړ�

	bool InitFlg = true;

	typedef struct IMMOVABLEOBJ {

		float x, y, r;	//x���W,y���W,���a
		bool setflg;	//��Q����z�u���邩�̃t���O
		int flg;		//�g�p�t���O
	};
	struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];

	typedef struct ENEMY {
		int mx, my;		//x���W,y���W
		int sx, sy;		//�c�A����
		bool setflg;	//�G��z�u���邩�̃t���O
		int flg;	//�g�p�t���O
		int move;	//�ړ��t���O(false=�E,true=��)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
};

static Enemy myEnemy;		//Enemy�I�u�W�F�N�g�𐶐�


#endif // !_ENEMY_H_
