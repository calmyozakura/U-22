
#ifndef _SOUND_H_

#define _SOUND_H_

class SOUND {
public:

	typedef enum {
		choose,
		decide,
		cancel,
		shot,
		explode,
		broke,
		bound,
		goal,
		ready,
		go
	}SE;

	typedef enum {
		title,
		Game,
		Result
	}BGM;

	typedef enum {
		bgm,
		se
	};

	struct SoundEffect
	{
		int SE[10];
		int BGM[3];
	}Sound;

	int BGM_vol, SE_vol;
	int tmp[2];
	short stack;
	int SoundLoader();//音を読み込む
	
	void SetVolumes();//ボリュームを調整　/optionから出る際に
	void PlaySE(int Playing);//SEを鳴らす
	void PlayBGM(int Playing);//BGMを鳴らす / 各シーンの始まりにでも
	void StopBGM(int Playing);//BGMを止める / 各シーンで遷移する前に

	int VolInit();//音声量の読み取り、および初期化
	int VolWrite();//変更された場合、音量を上書き

	


};



#endif	//_SCENE_H_