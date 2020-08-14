#include <math.h>
#include "Fps.h"
#include"DxLib.h"


C_FPS::C_FPS()
{
	mStartTime = 0;
	mFps = 0;
	mCount = 0;
}

bool C_FPS::Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void C_FPS::Draw() {
	DrawFormatString(0, 625,0x0000ff, "%.1f", mFps);
}

void C_FPS::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}
