#ifndef FPS_H
#define FPS_H

class C_FPS {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS
	
public:
	C_FPS();
	bool Update();
	void Draw();
	void Wait();
};
#endif // !FPS_H
