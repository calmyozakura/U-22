#include <iostream>
#include <fstream>
#include "DxLib.h"	//DrawFromatString�œǂݍ��߂����m�F���邾��(��ɏ���)
#include "text.h"

void TextWrite(void) {

	char test[20] = "testtext";	//�ϐ����珑�����߂邩�̉��u��

	ofstream ofs("Text.txt");	//�������݂�Text�t�@�C�����J��
	ofs << test;				//test�̓��e���㏑��
	ofs.close();					//�t�@�C�������
}

void TextRead(void) {

	char str[20];	//�t�@�C���̓��e�������

	ifstream ifs("Text.txt");		//�ǂݍ��݂�Test�t�@�C�����J��
	ifs >> str;					//str�ɕ�����������
	ifs.close();					//�t�@�C�������

	DrawFormatString(0, 200, 0x0000ff, "%s", str);	//�ǂݍ��߂����m�F���邾��(��ɏ���)
}