#ifndef __JOGGLELAYER
#define __JOGGLELAYER
#include "ALLHeader.h"
#include "SNSDriver.h"
#include "DNSDriver.h"
#include "ahmiv2.h"
#include "MatrixGenerate.h"

extern U16 * FrameBuffer;


//更新tileinfo
void TileInfoGenrate(TileInfo &tile_info,
	MatrixMask  *&Matrixmask,
	U8 *&matrix,
	TileInfoMask *&tileinfomask,
	U8 TEXADD,
	ROMInfo &rom_info);
//初始化纹理信息记录结构体
void TileInfoMaskIng(TileInfoMask &tileinfomask);
//读取Alpha纹理或*.dds纹理
void ReadROMinfo(char*filename, 
	ROMInfo &rom_info, 
	TileInfoMask *&tileinfomask, 
	U8 &RomAddr, 
	U8 &TEXADD, 
	BOOL mask);
//添加纯色纹理
void ADDPurity(TileInfoMask &tileinfomask,
	U8 &TEXADD,
	BOOL mask,
	U8 r,
	U8 g,
	U8 b,
	U16 width,
	U16 height);
//调用核心层
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info);
//当不产生新矩阵时更新矩阵记录数组
//void MatrixIng(TileInfo *&tile_info,
//	MatrixMask *&Matrixmask);
void GetMatrix(U8 &matrix,
	U8 TEXADD,
	U8 num);
#endif
