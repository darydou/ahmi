#ifndef __JOGGLELAYER
#define __JOGGLELAYER
#include "ALLHeader.h"
#include "SNSDriver.h"
#include "DNSDriver.h"
#include "ahmiv2.h"
#include "MatrixGenerate.h"
#include "LoadFontlibrary.h"

extern U16 * FrameBuffer;

//更新tileinfo
void TileInfoGenrate(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8 (&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 TEXADD,
	ROMInfo &rom_info);

//初始化纹理信息记录结构体
void TileInfoMaskIng(TileInfoMask &tileinfomask);

//读取Alpha纹理或*.dds纹理
void ReadROMinfo(char*filename, 
	ROMInfo &rom_info, 
	TileInfoMask &tileinfomask, 
	U8 &RomAddr, 
	U8 &TEXADD, 
	BOOL mask);

//调用核心层
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info);
//当不产生新矩阵时更新矩阵记录数组
//void MatrixIng(TileInfo *&tile_info,
//	MatrixMask *&Matrixmask);

#endif
