#include "Sound.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>

static bool playing = false;
int SOUND::SoundLoader() {
	if ((Sound.SE[choose] = LoadSoundMem("Sound/cursor1.ogg")) == -1) return -1;
	if ((Sound.SE[decide] = LoadSoundMem("Sound/decision29.ogg")) == -1) return -1;
	if ((Sound.SE[cancel] = LoadSoundMem("Sound/cancel2.ogg")) == -1) return -1;
	if ((Sound.SE[shot] = LoadSoundMem("Sound/Bubble.ogg")) == -1) return -1;
	if ((Sound.SE[explode] = LoadSoundMem("Sound/Explode.ogg")) == -1) return -1;
	if ((Sound.SE[broke] = LoadSoundMem("Sound/ta_ta_warekie02.ogg")) == -1) return -1;
	if ((Sound.SE[bound] = LoadSoundMem("Sound/ani_ta_biyon02.ogg")) == -1) return -1;
	if ((Sound.SE[goal] = LoadSoundMem("Sound/nc154032.ogg")) == -1) return -1;
	if ((Sound.SE[ready] = LoadSoundMem("Sound/ready.ogg")) == -1) return -1;
	if ((Sound.SE[go] = LoadSoundMem("Sound/go.ogg")) == -1) return -1;


	if ((Sound.BGM[title] = LoadSoundMem("Sound/MusMus-CT-NV-36.ogg")) == -1) return -1;
	if ((Sound.BGM[Game] = LoadSoundMem("Sound/MusMus-CT-NV-17.ogg")) == -1) return -1;
	if ((Sound.BGM[Result] = LoadSoundMem("Sound/MusMus-CT-NV-TT.ogg")) == -1) return -1;
	return 0;
}

void SOUND::SetVolumes() {
	
	if (BGM_vol > 100)BGM_vol = 100;
	if (BGM_vol < 0)BGM_vol = 0;

	if (SE_vol > 100) SE_vol = 100;
	if (SE_vol < 0) SE_vol = 0;

	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[choose]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[decide]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[cancel]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[shot]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[explode]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[broke]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[bound]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[goal]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[ready]);
	ChangeVolumeSoundMem(255 * SE_vol / 100, Sound.SE[go]);


	ChangeVolumeSoundMem(255 * BGM_vol / 100, Sound.BGM[title]);
	ChangeVolumeSoundMem(255 * BGM_vol / 100, Sound.BGM[Game]);
	ChangeVolumeSoundMem(255 * BGM_vol / 100, Sound.BGM[Result]);
}

void SOUND::PlaySE(int Playing) {
	PlaySoundMem(Sound.SE[Playing], DX_PLAYTYPE_BACK);//SEは短いので一度流すだけで良い
}
void SOUND::PlayBGM(int Playing) {
	if (!CheckSoundMem(Sound.BGM[Playing]) && !playing)//曲が流れてないなら再生、じゃないと冒頭から再生しようとループするため
		PlaySoundMem(Sound.BGM[Playing], DX_PLAYTYPE_BACK), playing = true;
	else if (playing);
	else playing = false;
	stack = Playing;
}
void SOUND::StopBGM(int Playing) {
	StopSoundMem(Sound.BGM[Playing]);//曲を止める、シーン切り替わっても流れ続けるため
	playing = false;
}

int SOUND::VolInit() {
	static bool WriteFlg = FALSE;
	//DrawFormatString(50, 200, 0xff0000, "%d", CODE);	//読み込めたか確認するだけ(後に消す)
	char Vol[4];
	
	std::string str;

	for (int i = 0; i < 4; i++) {//初期化
		
		(i!=3) ?Vol[i] = '0':Vol[i] = '\0';
	}
	
	if (WriteFlg == FALSE) {
			std::ifstream ifs("Sound/Volume.ini");		//読み込みで.iniファイルを開く

			if (ifs.fail()) {//読み込み失敗処理
				BGM_vol = 50, SE_vol = 50;
				//return 0;
			}
			else{
				for (unsigned short x = 0; x < 2; x++) {
					str.clear();
					std::getline(ifs,str);	//strに文字列行を入れる

					for (unsigned short y  = 0 ; y < str.length(); y++ )//文字列を最後尾から取得
					{
						if (isdigit(str.c_str()[str.length() - y])) {
								Vol[3- y] = str.c_str()[str.length() - y];
						}
					}
					tmp[x] = atoi(Vol);					
				}
				BGM_vol = tmp[BGM];
				SE_vol = tmp[SE];
			}
			ifs.close();//ファイルを閉じる
		
		WriteFlg = TRUE;
	}
	return 0;
}
int SOUND::VolWrite() {
	std::string str;
	if (tmp[BGM] != BGM_vol || tmp[SE] != SE_vol) {
		
		std::ofstream ofs("Sound/Volume.ini");
		if (ofs.fail()) {//読み込み失敗処理
			ofs.open("Sound/Volume.ini");
			ofs << "BGM = " << BGM_vol << std::endl << "SE = " << SE_vol << std::endl;

			return 0;
		}
		else {
			ofs << "BGM = " << BGM_vol << std::endl << "SE = "<< SE_vol << std::endl;

		}
		ofs.close();
	}
	return 0;
}