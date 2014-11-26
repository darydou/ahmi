#include "stdafx.h"
#include "WriteChinese.h"

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
	 	U16 font_addr = (TEST - 0XA1)*(0xff - 0xa1) + (TEST2 - 0xa1);
	 	for (U16 j = 0; j < 32; j++)
			buffer[ i%wordlength +   j * wordlength ] = ziku32[font_addr * 32 + j];
	 }
	for (U16 i = 0; i < wordlength * 16; i++)
		*(rom_info.tex[RomAddr].texel + i) =  (U64)*(buffer + i * 2) << 32  |   (U64)*(buffer + i * 2 + 1);
	RomAddr++;
}