#include "stdafx.h"
#include "WriteEnglish.h"
#include "DrawTool.h"

void WriteNum(int value, U8 size, S16 tx, S16 ty,
	ROMInfo &rom_info,
	TileInfo &tile_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD, U8 r, U8 g, U8 b)
{
	string word;
	if (value == 0)
	{
		word.append("0.00");
	}
	else
	{
		char a[10];
		for (int i = 0; i < 10&&value; i++)
		{
			a[i] = static_cast<U8>(value % 10);
			value = value / 10;
			switch (a[i])
			{
			case 0:
				word.append("0");
				break;
			case 1:
				word.append("1");
				break;
			case 2:
				word.append("2");
				break;
			case 3:
				word.append("3");
				break;
			case 4:
				word.append("4");
				break;
			case 5:
				word.append("5");
				break;
			case 6:
				word.append("6");
				break;
			case 7:
				word.append("7");
				break;
			case 8:
				word.append("8");
				break;
			case 9:
				word.append("9");
				break;
			}
		}
		word.insert(0, "00.");
		int wordsize = word.length();
		for (int i = 0; i < wordsize/2; i++)
		{
			char a = word[i];
			word[i] = word[wordsize - 1 - i];
			word[wordsize - 1 - i] = a;
		}
	}
	WriteEnglish(word ,size,tx,ty,
		rom_info,
		tile_info,
		Matrixmask,
		tileinfomask,
		matrix,
		RomAddr,
		TEXADD,r,g,b);
}
void WriteEnglish(string word, U8 size, S16 tx, S16 ty,
	ROMInfo &rom_info,
	TileInfo &tile_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD, U8 r, U8 g, U8 b)
{
	U16 wordlength = word.length();
	U16 fontsize;
	U16 cx = 0;
	if (size >=32)
	{
		fontsize = 16;
		cx = (size << magnitude) >> 5;
	}
	else
	{
		fontsize = 8;
		cx = (size << magnitude) >> 4;
	}
	U16 romsize = wordlength*fontsize*fontsize * 2 >> 6;
	rom_info.tex[RomAddr].texel = new U64[romsize];
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = fontsize * 2;
	tileinfomask.tileinfomask1[TEXADD].width = fontsize*wordlength;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	
	if ((fontsize == 8) != 0)
	{
		//缓冲区
		U16 buffersize = wordlength*fontsize*fontsize * 2 >> 3;
		U8 *buffer = new U8[buffersize];
		U16 fontlibrarysize = fontsize * fontsize * 2 >> 5;//计算一个字符占用的U32空间的大小
		for (U16 i = 0; i < wordlength; i++)
		{
			U16 fontaddr = (U8)word[i] * fontlibrarysize;
			for (U16 j = 0; j < 4; j++)
			{//modified by darydou ,change the fontlibrary + st(means songti)
				buffer[i%wordlength + (j * 4)*wordlength]      = (U8)(englishfontlibrary8st[fontaddr + j] >> 24) & 0xff;
				buffer[i%wordlength + (j * 4 + 1)*wordlength]  = (U8)(englishfontlibrary8st[fontaddr + j] >> 16) & 0xff;
				buffer[i%wordlength + (j * 4 + 2)*wordlength]  = (U8)(englishfontlibrary8st[fontaddr + j] >> 8 ) & 0xff;
				buffer[i%wordlength + (j * 4 + 3)*wordlength]  = (U8)(englishfontlibrary8st[fontaddr + j]      ) & 0xff;
				int m = 0;
			}
		}

		for (U16 i = 0; i < romsize; i++)
			*(rom_info.tex[RomAddr].texel + i) = (U64)buffer[i * 8] << 56
			| (U64)buffer[i * 8 + 1] << 48
			| (U64)buffer[i * 8 + 2] << 40
			| (U64)buffer[i * 8 + 3] << 32
			| (U64)buffer[i * 8 + 4] << 24
			| (U64)buffer[i * 8 + 5] << 16
			| (U64)buffer[i * 8 + 6] << 8
			| (U64)buffer[i * 8 + 7];

		delete[] buffer;
	}
	else if ((fontsize == 16) != 0)
	{
		//缓冲区
		U16 buffersize = wordlength*fontsize*fontsize * 2 >> 4;
		U16 *buffer = new U16[buffersize];
		U16 fontlibrarysize = fontsize*fontsize * 2 >> 5;//计算一个字符占用的U32空间的大小
		for (U16 i = 0; i < wordlength; i++)
		{
			U16 fontaddr = (U8)word[i] * fontlibrarysize;
			for (U8 j = 0; j < 16; j++)
			{
				buffer[i%wordlength + (j * 2)*wordlength] = (U16)(englishfontlibrary16[fontaddr + j] >> 16) & 0xffff;
				buffer[i%wordlength + (j * 2 + 1)*wordlength] = (U16)(englishfontlibrary16[fontaddr + j]) & 0xffff;
			}
		}
		for (U16 i = 0; i < romsize; i++)
			*(rom_info.tex[RomAddr].texel + i) = (U64)buffer[i * 4] << 48
			| (U64)buffer[i * 4 + 1] << 32
			| (U64)buffer[i * 4 + 2] << 16 
			| (U64)buffer[i * 4 + 3];
		delete[] buffer;
	}
	RomAddr++;
	TOOL::MatrixGenerate matrixgenerate;
	matrixgenerate.Triscale(cx, cx);
	matrixgenerate.Tritranslate(tx, ty);//已测试
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);

	//为文字添加颜色
	TOOL::ADDPurity(tileinfomask, TEXADD, 1, r, g, b, tileinfomask.tileinfomask1[TEXADD - 1].width, tileinfomask.tileinfomask1[TEXADD - 1].height);
	TOOL::GetMatrix(matrix, TEXADD, TEXADD - 2);
}
