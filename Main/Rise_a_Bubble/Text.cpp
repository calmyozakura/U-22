#include <iostream>
#include <fstream>
#include "DxLib.h"	//DrawFromatString�œǂݍ��߂����m�F���邾��(��ɏ���)
#include "text.h"


char C_Num[8][20]{
	{ "Course/One.txt" },
	{ "Course/Two.txt" },
	{ "Course/Three.txt" },
	{ "Course/Four.txt" },
	{ "Course/Five.txt" },
	{ "Course/Six.txt" },
	{ "Course/Seven.txt" },
	{ "Course/Eight.txt" }
};

void TextWrite(const char *CODE) {
	static bool WriteFlg = FALSE;
	DrawFormatString(50, 200, 0xff0000, "%d", CODE);	//�ǂݍ��߂����m�F���邾��(��ɏ���)
	char* Code_ch = NULL;
	int n = 0;
	Code_ch = (char*)malloc(sizeof(char) * 20);

	if (WriteFlg == FALSE) {
		for (int n = 7; n > 0; n--) {
			ofstream ofs(C_Num[n]);	//�������݂�Text�t�@�C�����J��
			ifstream ifs(C_Num[n - 1]);		//�ǂݍ��݂�Test�t�@�C�����J��
			ifs >> Code_ch;					//Code�ɕ�����������
			ofs << Code_ch;
			DrawFormatString(100, 300, 0x00ff00, "%d", Code_ch);	//�ǂݍ��߂����m�F���邾��(��ɏ���)
			DrawFormatString(100, 400, 0x00ff00, "aaaaaaaaaaaaaaa");	//�ǂݍ��߂����m�F���邾��(��ɏ���)
			ofs.close();
			ifs.close();
		}
		WriteFlg = TRUE;
	}
	ofstream ofs(C_Num[0]);	//�������݂�Text�t�@�C�����J��
	ofs << CODE;				//test�̓��e���㏑��
	ofs.close();					//�t�@�C�������
	//return 0;
}

char* TextRead() {
	char* Code_Back = NULL;
	Code_Back = (char*)malloc(sizeof(char) * 20);
	ifstream ifs(C_Num[0]);		//�ǂݍ��݂�Test�t�@�C�����J��
	ifs >> Code_Back;					//Code�ɕ�����������
	ifs.close();					//�t�@�C�������

	DrawFormatString(0, 200, 0x00ff00, "%s", Code_Back);	//�ǂݍ��߂����m�F���邾��(��ɏ���)

	return Code_Back;
}