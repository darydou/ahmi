#include "stdafx.h"
#include "SNSDriver.h"
#include "DNSDriver.h"
#include "JoggleLayer.h"
//加载rominfo信息
void LoadROMinfo(char *filename, ROMInfo *&rom_info, TileInfoMask1 &tileinfomask, U8 &RomAddr, U8 &TEXADD, BOOL mask)
{
	//地址读取文件
	tileinfomask.mask = mask;
	READTEX readtex(filename);
	readtex.GetTexSize(tileinfomask, TEXADD);
	(*rom_info).tex[RomAddr].texel = new U64[tileinfomask.PixelLength];
	readtex.GetTexPixel((*rom_info).tex[RomAddr].texel);//读取时间过长，可以采取并行机制，减少读取的时间
	RomAddr++;
}
//tileinfo标记结构体初始化
void TileInfoMaskIng(TileInfoMask *&tileinfomask)
{
	for (int i = 0; i < TextureIndexSize; i++)
	{
		tileinfomask->tileinfomask1[i].flag = 0;
		tileinfomask->tileinfomask1[i].height = 0;
		tileinfomask->tileinfomask1[i].width = 0;
		tileinfomask->tileinfomask1[i].mask = 0;
		tileinfomask->tileinfomask1[i].PixelLength = 0;
	}
}
//添加纯色纹理
void ADDPurity(TileInfoMask1 &tileinfomask,
	U8 &TEXADD,
	BOOL mask,
	U8 r,
	U8 g,
	U8 b,
	U16 width,
	U16 height)
{
	tileinfomask.flag = 3;
	tileinfomask.height = height;
	tileinfomask.width = width;
	tileinfomask.PixelLength = (U64)((U8)r << 23) + (U64)((U8)g << 15) + (U64)((U8)b << 7);
	tileinfomask.mask = mask;
	TEXADD++;
}
//更新纹理对应的标记数组
void GetMatrix(U8 &matrix,
	U8 num)
{
	matrix = num;
}
//tileinfo产生函数
void TileInfoGenrate(TileInfo *&tile_info,
	MatrixMask  *&Matrixmask,
	U8 *&matrix,
	TileInfoMask *&tileinfomask,
	U8 TEXADD,
	ROMInfo *rominfo)
{
	LoadTexIndex(tile_info->TextureIndex, matrix, tileinfomask, TEXADD, rominfo);
	LoadTIndexSAddr(tile_info->TileIndex, tile_info->SourceAddr, tile_info->Matrix, Matrixmask, matrix, tileinfomask, TEXADD);
}
//调用内核
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info)
{
	my_ahmi_p->DrawFrame(tile_info, rom_info, FrameBuffer);
}


