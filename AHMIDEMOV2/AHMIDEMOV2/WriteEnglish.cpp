#include "stdafx.h"
#include "WriteEnglish.h"

void WriteEnglish(string word,
	ROMInfo &rom_info,
	TileInfo &tile_info,
	MatrixMask &Matrixmask,
	TileInfoMask &tileinfomask,
	U8(&matrix)[MatrixSize],
	U8 &RomAddr,
	U8 &TEXADD,
	U8 size)
{
	U16 wordlength = word.length();
	U16 fontsize;
	if (size > 12)
		fontsize = 16;
	else
		fontsize = 8;
	U16 romsize = wordlength*fontsize*fontsize * 2 >> 6;
	rom_info.tex[RomAddr].texel = new U64[romsize];
	tileinfomask.tileinfomask1[TEXADD].flag = 2;
	tileinfomask.tileinfomask1[TEXADD].height = fontsize * 2;
	tileinfomask.tileinfomask1[TEXADD].width = fontsize*wordlength;
	tileinfomask.tileinfomask1[TEXADD].mask = 0;
	TEXADD++;
	
	if ((fontsize == 8) != 0)
	{
		//»º³åÇø
		U16 buffersize = wordlength*fontsize*fontsize * 2 >> 3;
		U8 *buffer = new U8[buffersize];
		U16 fontlibrarysize = fontsize * fontsize * 2 >> 5;
		for (U16 i = 0; i < wordlength; i++)
		{
			U16 fontaddr = (U8)word[i] * fontlibrarysize;
			for (U16 j = 0; j < 4; j++)
			{
				buffer[i%wordlength + (j * 4)*wordlength]      = (U8)(englishfontlibrary[fontaddr + j] >> 24) & 0xff;
				buffer[i%wordlength + (j * 4 + 1)*wordlength]  = (U8)(englishfontlibrary[fontaddr + j] >> 16) & 0xff;
				buffer[i%wordlength + (j * 4 + 2)*wordlength]  = (U8)(englishfontlibrary[fontaddr + j] >> 8 ) & 0xff;
				buffer[i%wordlength + (j * 4 + 3)*wordlength]  = (U8)(englishfontlibrary[fontaddr + j]      ) & 0xff;
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
	}
	else
	{
		//»º³åÇø
	}
	RomAddr++;
	MatrixGenerate matrixgenerate;
	//matrixgenerate.Trirotate(180);
	matrixgenerate.Triscale(4 << 4, 4 << 4);
	matrixgenerate.Tritranslate(((S1_B_4)200) << 4, ((S1_B_4)300) << 4);//ÒÑ²âÊÔ
	//if (size == 0)
	//	size = 1;
	//matrixgenerate.Triscale(4<< 4, 4 << 4);
	//matrixgenerate.Trirotate(45);
	matrixgenerate.GetMatrix(tile_info, Matrixmask, matrix, TEXADD);
}