#ifndef _NSDRIVER
#define _NSDRIVER
#include <iostream>
#include <fstream>
using namespace std;

#include "ALLHeader.h"



class READTEX
{
public:
	void GetTexSize(TileInfoMask &tileinfomask, unsigned char &TEXADD);//��ȡ����Ĵ�СΪ֮����ռ�
	void GetTexPixel(U64 *&rominfo);//��������뵽roninfo��
	READTEX(char *filename);//������������
	~READTEX();
private:
	ifstream  infile;//��ȡ����
	char *filename;
	unsigned char flag;//�����ʽ���λ
	U64 PixelLength;
	unsigned short width;
	unsigned short height;
	void Determine();//�ж�����ĸ�ʽ
};
#endif