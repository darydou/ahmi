#ifndef __JOGGLELAYER
#define __JOGGLELAYER
#include "ALLHeader.h"
#include "SNSDriver.h"
#include "DNSDriver.h"
#include "ahmiv2.h"
#include "MatrixGenerate.h"
#include "LoadFontlibrary.h"

extern U16 * FrameBuffer;

//����tileinfo
void TileInfoGenrate(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8 (&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 TEXADD,
	ROMInfo &rom_info);

//��ʼ��������Ϣ��¼�ṹ��
void TileInfoMaskIng(TileInfoMask &tileinfomask);

//��ȡAlpha�����*.dds����
void ReadROMinfo(char*filename, 
	ROMInfo &rom_info, 
	TileInfoMask &tileinfomask, 
	U8 &RomAddr, 
	U8 &TEXADD, 
	BOOL mask);

//���ú��Ĳ�
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info);
//���������¾���ʱ���¾����¼����
//void MatrixIng(TileInfo *&tile_info,
//	MatrixMask *&Matrixmask);

#endif
