#include <iostream>
#include <fstream>
#include "DxLib.h"	//DrawFromatStringで読み込めたか確認するだけ(後に消す)
#include "text.h"


char C_Num[8][17]{
	{ "Course/One.txt" },
	{ "Course/Two.txt" },
	{ "Course/Three.txt" },
	{ "Course/Four.txt" },
	{ "Course/Five.txt" },
	{ "Course/Six.txt" },
	{ "Course/Seven.txt" },
	{ "Course/Eight.txt" }
};

int TextWrite(char CODE) {
	char Code_ch = NULL;
	Code_ch = (char)malloc(sizeof(char) * 20);
	for (int n = 7; n < 1; n--) {
		ofstream ofs(C_Num[n]);	//書き込みでTextファイルを開く
		ifstream ifs(C_Num[n - 1]);		//読み込みでTestファイルを開く
		ifs >> Code_ch;					//Codeに文字列をいれる
		ofs << Code_ch;
		ofs.close();
		ifs.close();
	}
	ofstream ofs(C_Num[0]);	//書き込みでTextファイルを開く
	ofs << CODE;				//testの内容を上書き
	ofs.close();					//ファイルを閉じる
	return 0;
}

char* TextRead() {
	char* Code_Back = NULL;
	Code_Back = (char*)malloc(sizeof(char) * 20);
	ifstream ifs(C_Num[0]);		//読み込みでTestファイルを開く
	ifs >> Code_Back;					//Codeに文字列をいれる
	ifs.close();					//ファイルを閉じる

	DrawFormatString(0, 200, 0x0000ff, "%s", Code_Back);	//読み込めたか確認するだけ(後に消す)

	return Code_Back;
}