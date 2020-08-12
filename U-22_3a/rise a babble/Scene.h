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
	
	int Changer = 0;//シーン用変数
	int Before = 0;//前画面の変数
	int Difficulty = 0;//難易度
	void Title();//タイトル　　
	void GameInit();//ゲーム前の初期化
	void GameMode();//ゲームモード選択
	void GameMain();//ゲーム
	void Result();//リザルト
	void Option();//オプション
	void Ending();//エンド

	void getKeyInput();//キー入力　分割の恐れあり
	
	
private:
protected:

	typedef enum {EASY=0,NORMAL,HARD,EXHARD,CODE,MAKE}diff;

typedef	enum {_INIT=-1,TITLE=0,GAMEMODE,GAMEINIT,GAMEMAIN,RESULT,OPTION,ENDING,END=99} num;

XINPUT_STATE Input;

};
#endif

