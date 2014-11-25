#ifndef _NSDRIVER
#define _NSDRIVER
#include <iostream>
#include <fstream>
using namespace std;

#include "ALLHeader.h"



class READTEX
{
public:
	void GetTexSize(TileInfoMask &tileinfomask, unsigned char &TEXADD);//获取纹理的大小为之分配空间
	void GetTexPixel(U64 *&rominfo);//将纹理读入到roninfo中
	READTEX(char *filename);//传递纹理名称
	~READTEX();
private:
	ifstream  infile;//读取纹理
	char *filename;
	unsigned char flag;//纹理格式标记位
	U64 PixelLength;
	unsigned short width;
	unsigned short height;
	void Determine();//判断纹理的格式
};
#endif