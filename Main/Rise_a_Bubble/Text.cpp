#include <iostream>
#include <fstream>
#include "DxLib.h"	//DrawFromatStringで読み込めたか確認するだけ(後に消す)
#include "text.h"

void TextWrite(void) {

	char test[20] = "testtext";	//変数から書き込めるかの仮置き

	ofstream ofs("Text.txt");	//書き込みでTextファイルを開く
	ofs << test;				//testの内容を上書き
	ofs.close();					//ファイルを閉じる
}

void TextRead(void) {

	char str[20];	//ファイルの内容をいれる

	ifstream ifs("Text.txt");		//読み込みでTestファイルを開く
	ifs >> str;					//strに文字列をいれる
	ifs.close();					//ファイルを閉じる

	DrawFormatString(0, 200, 0x0000ff, "%s", str);	//読み込めたか確認するだけ(後に消す)
}