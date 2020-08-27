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
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
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
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}
