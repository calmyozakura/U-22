#ifndef _SCENE_H_
#define _SCENE_H_

#include "DxLib.h"
#include <string>

#define WINDOW_X 480
#define WINDOW_Y 640
#define COLOR_BIT 16
#define DEADZONE 8000
#define PI 3.14159265358979323846264338f
#define BULLET_MAX 24
#define BULLET_SIZE 10
#define BULLET_SPEED 7
#define INFINITY_X 24
#define INFINITY_Y 2


#define DEBUG

std::string MODE[] = { "EASY","NORMAL","HARD","EXHARD","CODE","MAKE","Back" };


class Scene {
public:
	
	int Changer = 0;//�V�[���p�ϐ�
	int Before = 0;//�O��ʂ̕ϐ�
	int Difficulty = 0;//��Փx
	void Title();//�^�C�g���@�@
	void GameInit();//�Q�[���O�̏�����
	void GameMode();//�Q�[�����[�h�I��
	void GameMain();//�Q�[��
	void Result();//���U���g
	void Option();//�I�v�V����
	void Ending();//�G���h

	void getKeyInput();//�L�[���́@�����̋��ꂠ��
	
	
private:
protected:

	typedef enum {EASY=0,NORMAL,HARD,EXHARD,CODE,MAKE}diff;

typedef	enum {_INIT=-1,TITLE=0,GAMEMODE,GAMEINIT,GAMEMAIN,RESULT,OPTION,ENDING,END=99} num;

XINPUT_STATE Input;

};
#endif

