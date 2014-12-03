#include "stdafx.h"
#include "JoggleLayer.h"

void ReadROMinfo(char*filename, ROMInfo &rom_info, TileInfoMask &tileinfomask, U8 &RomAddr, U8 &TEXADD,BOOL mask)
{
	tileinfomask.tileinfomask1[TEXADD].mask = mask;
	READTEX readtex(filename);
	readtex.GetTexSize(tileinfomask,TEXADD);
	rom_info.tex[RomAddr].texel = new U64[tileinfomask.tileinfomask1[RomAddr].PixelLength];
	readtex.GetTexPixel(rom_info.tex[RomAddr].texel);//读取时间过长，可以采取并行机制，减少读取的时间
	RomAddr++;
}
void TileInfoMaskIng(TileInfoMask &tileinfomask)
{
	for (int i = 0; i < TextureIndexSize; i++)
	{
		tileinfomask.tileinfomask1[i].flag = 0;
		tileinfomask.tileinfomask1[i].height = 0;
		tileinfomask.tileinfomask1[i].width= 0; 
		tileinfomask.tileinfomask1[i].mask = 0;
		tileinfomask.tileinfomask1[i].PixelLength = 0;
	}
}
void ADDPurity(TileInfoMask &tileinfomask, 
	           U8 &TEXADD,
	           BOOL mask,
	           U8 r,
	           U8 g,
	           U8 b,
	           U16 width,
	           U16 height)
{
	tileinfomask.tileinfomask1[TEXADD].flag   = 3;
	tileinfomask.tileinfomask1[TEXADD].height = height;
	tileinfomask.tileinfomask1[TEXADD].width  = width;
	tileinfomask.tileinfomask1[TEXADD].PixelLength = (U64)((U8)r <<10&0x7c00) + (U64)((U8)g << 5 &0x3e0) + (U64)((U8)b>>3 &0x1f);
	tileinfomask.tileinfomask1[TEXADD].mask = mask;
	TEXADD++;
}
void GetMatrix(U8 (&matrix)[MatrixSize],
	U8 TEXADD,
	U8 num)
{
	matrix[TEXADD - 1] = num;
}
void TileInfoGenrate(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 TEXADD,
	ROMInfo &rom_info)
{
	LoadTextureIndex(tile_info, matrix, tileinfomask, TEXADD, rom_info);
	LoadIndexSoueAddr(tile_info,Matrixmask,matrix,tileinfomask,TEXADD);
}
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info)
{
	my_ahmi_p->DrawFrame(tile_info, rom_info, FrameBuffer);
}


