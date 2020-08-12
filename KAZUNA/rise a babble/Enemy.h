#ifndef _ENEMY_H_
#define _ENEMY_H_

class Enemy {
private:
#define IMMOVABLEOBJMAX 25	//動かせるオブジェクトの最大表示数
#define ENEMYMAX 1			//動く敵の最大表示数
#define MAPMAX 5			//マップの最大数

public:

	int EnemyImage;		//動く敵の画像をいれる変数

	int Entire_x[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標
	int Entire_y[IMMOVABLEOBJMAX];		//障害物の座標に入れる前にあらかじめ取っておく座標

	float hit_x[IMMOVABLEOBJMAX];	//円の当たり判定_x
	float hit_y[IMMOVABLEOBJMAX];	//円の辺り判定_y
	float hit_r[IMMOVABLEOBJMAX];

	float hit_ex[ENEMYMAX];	//円の当たり判定_x
	float hit_ey[ENEMYMAX];	//円の辺り判定_y
	float hit_er[ENEMYMAX];

	int Pattern[MAPMAX];		//敵や障害物などのパターン

	int rx, ry;	//障害物の配置列をずらすための変数

	//Enemy();						//Enemyのコンストラクタ
	void CreateImmovableObj(void);	//敵と動かせる障害物生成
	void DrawImmovableObj(void);	//敵と動かせる障害物の描画
	void MoveEnemy(void);	//敵の移動

	bool InitFlg = true;

	typedef struct IMMOVABLEOBJ {

		float x, y, r;	//x座標,y座標,半径
		bool setflg;	//障害物を配置するかのフラグ
		int flg;		//使用フラグ
	};
	struct IMMOVABLEOBJ g_immovableobj[MAPMAX][IMMOVABLEOBJMAX];

	typedef struct ENEMY {
		int mx, my;		//x座標,y座標
		int sx, sy;		//縦、横幅
		bool setflg;	//敵を配置するかのフラグ
		int flg;	//使用フラグ
		int move;	//移動フラグ(false=右,true=左)
	};
	ENEMY g_enemy[MAPMAX][ENEMYMAX];
};

static Enemy myEnemy;		//Enemyオブジェクトを生成


#endif // !_ENEMY_H_
