#include "stdafx.h"
#include "LoadFontlibrary.h"
void LoadFontlibrary(string word, ROMInfo &rom_info, TileInfoMask &tileinfomask, U8 & RomAddr, U8 &TEXADD)
{
	U8 wordlength =(U8)(word.length()) >>1;
	rom_info.tex[RomAddr].texel = new U64[wordlength * 4];
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = 16 ;
	tileinfomask.tileinfomask1[TEXADD].width = 16 * wordlength;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	//»º³åÇø
	U16 *buffer = new U16[wordlength * 4 * 4];
	U16 *bufferend = new U16[wordlength * 4 * 4];
	for (U8 i = 0; i < wordlength; i++)
	{
		U8 TEST = word[i * 2];
		U8 TEST2 = word[i * 2+1];
		U16 font_addr = (TEST-0XA1)*(0xff-0xa1)+(TEST2-0xa1);
		for (U8 j = 0; j < 4; j++)
		{
			*(buffer + i * 16 + j * 4     ) = (U16)((ziku[font_addr * 8 + j * 2] >> 16) & 0xffff);
			*(buffer + i * 16 + j * 4 + 1) = (U16)(ziku[font_addr * 8 + j * 2] & 0xffff);
			*(buffer + i * 16 + j * 4 + 2) = (U16)((ziku[font_addr * 8 + j * 2 + 1] >> 16)& 0xffff);
			*(buffer + i * 16 + j * 4 + 3) = (U16)(ziku[font_addr * 8 + j * 2 + 1] & 0xffff);
			//*(rom_info.tex[RomAddr].texel+i*4+j) = ((U64)ziku[(U32)font_addr * 8 + j * 2] << 32) + (U64)ziku[(U32)font_addr * 8 + j * 2 + 1];
			//*(rom_info.tex[RomAddr].texel + i * 4 + j) = ((U64)*(buffer + i * 16 + j * 4) << 48) | ((U64)*(buffer + i * 16 + j * 4 + 1) << 32) | ((U64)*(buffer + i * 16 + j * 4 + 2) << 16) | ((U64)*(buffer + i * 16 + j * 4 + 3));
		}
	}

	for (U8 j = 0; j < wordlength; j++)
		for (U8 i = 0; i <4 * 4; i++)
		{
		*(bufferend + j * 16 + i) = *(buffer + ((i+j*16)%wordlength)*16 + (i+j*16)/wordlength);
		}
	for (U8 i = 0; i < wordlength * 4; i++)
		*(rom_info.tex[RomAddr].texel + i) = ((U64)*(bufferend + i * 4) << 48) | ((U64)*(bufferend + i * 4 + 1) << 32) | ((U64)*(bufferend + i * 4 + 2) << 16) | (U64)*(bufferend + i * 4 + 3);
	RomAddr++;
}
