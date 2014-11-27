#include "stdafx.h"
#include "WriteChinese.h"
#include "MatrixGenerate.h"

// void WriteChinese(string word, ROMInfo &rom_info, TileInfoMask &tileinfomask, U8 & RomAddr, U8 &TEXADD)
// {
// 	U8 wordlength = (U8)(word.length()) >> 1;
// 	rom_info.tex[RomAddr].texel = new U64[wordlength * 4];
// 	tileinfomask.tileinfomask1[TEXADD].flag = 2;
// 	tileinfomask.tileinfomask1[TEXADD].height = 16;
// 	tileinfomask.tileinfomask1[TEXADD].width = 16 * wordlength;
// 	tileinfomask.tileinfomask1[TEXADD].mask = 0;
// 	TEXADD++;
// 	//»º³åÇø
// 	U16 *buffer = new U16[wordlength * 4 * 4];
// 	for (U8 i = 0; i < wordlength; i++)
// 	{
// 		U8 TEST = word[i * 2];
// 		U8 TEST2 = word[i * 2 + 1];
// 		U16 font_addr = (TEST - 0XA1)*(0xff - 0xa1) + (TEST2 - 0xa1);
// 		for (U8 j = 0; j < 4; j++)
// 		{
// 			*(buffer + i %wordlength + (j * 4      )*wordlength) = (U16)((ziku16[font_addr * 8 + j * 2] >> 16) & 0xffff);
// 			*(buffer + i %wordlength + (j * 4 + 1 )*wordlength) = (U16)(ziku16[font_addr * 8 + j * 2] & 0xffff);
// 			*(buffer + i %wordlength + (j * 4 + 2)*wordlength) = (U16)((ziku16[font_addr * 8 + j * 2 + 1] >> 16) & 0xffff);
// 			*(buffer + i %wordlength + (j * 4 + 3)*wordlength) = (U16)(ziku16[font_addr * 8 + j * 2 + 1] & 0xffff);
// 		}
// 	}
// 	for (U8 i = 0; i < wordlength * 4; i++)
// 		*(rom_info.tex[RomAddr].texel + i) = ((U64)*(buffer + i * 4) << 48) | ((U64)*(buffer + i * 4 + 1) << 32) | ((U64)*(buffer+ i * 4 + 2) << 16) | (U64)*(buffer + i * 4 + 3);
// 	RomAddr++;
// } 
void WriteChinese(string word, ROMInfo &rom_info, TileInfoMask &tileinfomask, U8 & RomAddr, U8 &TEXADD)
{
	 U16 wordlength = (U16)(word.length()) >> 1;
	 rom_info.tex[RomAddr].texel = new U64[wordlength * 16];
	 tileinfomask.tileinfomask1[TEXADD].flag = 2;
	 tileinfomask.tileinfomask1[TEXADD].height = 32;
	 tileinfomask.tileinfomask1[TEXADD].width = 32 * wordlength;
	 tileinfomask.tileinfomask1[TEXADD].mask = 0;
	 TEXADD++;
	 //»º³åÇø
	 U32 *buffer       = new U32[wordlength * 32];
	 for (U16 i = 0; i < wordlength; i++)
	 {
	 	U8 TEST = word[i * 2];
	 	U8 TEST2 = word[i * 2 + 1];
	 	U16 font_addr = (TEST - 0xA1)*(0xff - 0xa1) + (TEST2 - 0xa1);
	 	for (U16 j = 0; j < 32; j++)
			buffer[ i%wordlength +   j * wordlength ] = ziku32[font_addr * 32 + j];
	 }
	for (U16 i = 0; i < wordlength * 16; i++)
		*(rom_info.tex[RomAddr].texel + i) =  (U64)*(buffer + i * 2) << 32  |   (U64)*(buffer + i * 2 + 1);
	RomAddr++;
	delete buffer;
}

void WriteChinese(string word, 
	ROMInfo &rom_info,
	TileInfo &tile_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask, 
	U8 (&matrix)[MatrixSize],
	U8 &RomAddr, 
	U8 &TEXADD,
	U8 size)
{
	U16 wordlength = word.length() >> 1;
	U16  fontsize = 0;
	if (size > 24)
		fontsize = 32;
	else
		fontsize = 16;
	U16 romsize = wordlength*fontsize*fontsize >> 6;
	rom_info.tex[RomAddr].texel = new U64[romsize];
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = fontsize;
	tileinfomask.tileinfomask1[TEXADD].width = fontsize*wordlength;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	if (fontsize == 16)
	{
		//»º³åÇø
		size = size >> 4;
		U16 *buffer = new U16[wordlength * 4 * 4];
		for (U8 i = 0; i < wordlength; i++)
		{
			U8 TEST = word[i * 2];
			U8 TEST2 = word[i * 2 + 1];
			U16 font_addr = (TEST - 0XA1)*(0xff - 0xa1) + (TEST2 - 0xa1);
			for (U8 j = 0; j < 4; j++)
			{
				*(buffer + i %wordlength + (j * 4)*wordlength) = (U16)((ziku16[font_addr * 8 + j * 2] >> 16) & 0xffff);
				*(buffer + i %wordlength + (j * 4 + 1)*wordlength) = (U16)(ziku16[font_addr * 8 + j * 2] & 0xffff);
				*(buffer + i %wordlength + (j * 4 + 2)*wordlength) = (U16)((ziku16[font_addr * 8 + j * 2 + 1] >> 16) & 0xffff);
				*(buffer + i %wordlength + (j * 4 + 3)*wordlength) = (U16)(ziku16[font_addr * 8 + j * 2 + 1] & 0xffff);
			}
		}
		for (U8 i = 0; i < wordlength * 4; i++)
			*(rom_info.tex[RomAddr].texel + i) = ((U64)*(buffer + i * 4) << 48) 
			| ((U64)*(buffer + i * 4 + 1) << 32)
			| ((U64)*(buffer + i * 4 + 2) << 16)
			| (U64)*(buffer + i * 4 + 3);
		delete[] buffer;
	}
	else
	{
		size = size >> 5;
		//»º³åÇø
		U32 *buffer = new U32[wordlength * 32];
		for (U16 i = 0; i < wordlength; i++)
		{
			U8 TEST = word[i * 2];
			U8 TEST2 = word[i * 2 + 1];
			U16 font_addr = (TEST - 0xA1)*(0xff - 0xa1) + (TEST2 - 0xa1);
			for (U16 j = 0; j < 32; j++)
				buffer[i%wordlength + j * wordlength] = ziku32[font_addr * 32 + j];
		}
		for (U16 i = 0; i < wordlength * 16; i++)
			*(rom_info.tex[RomAddr].texel + i) = (U64)*(buffer + i * 2) << 32 | (U64)*(buffer + i * 2 + 1);
		delete[] buffer;
	}
	RomAddr++;
	MatrixGenerate matrixgenerate;
	//matrixgenerate.Tritranslate(((S1_B_4)100) << 4, ((S1_B_4)300) << 4);//ÒÑ²âÊÔ
	if (size == 0)
		size = 1;
	matrixgenerate.Triscale(size<<4,size<<4);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}