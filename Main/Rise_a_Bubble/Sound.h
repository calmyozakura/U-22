
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
	int SoundLoader();//����ǂݍ���
	
	void SetVolumes();//�{�����[���𒲐��@/option����o��ۂ�
	void PlaySE(int Playing);//SE��炷
	void PlayBGM(int Playing);//BGM��炷 / �e�V�[���̎n�܂�ɂł�
	void StopBGM(int Playing);//BGM���~�߂� / �e�V�[���őJ�ڂ���O��

	int VolInit();//�����ʂ̓ǂݎ��A����я�����
	int VolWrite();//�ύX���ꂽ�ꍇ�A���ʂ��㏑��

	


};



#endif	//_SCENE_H_