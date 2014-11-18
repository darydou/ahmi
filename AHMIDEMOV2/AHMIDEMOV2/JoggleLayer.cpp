#include "stdafx.h"
#include "SNSDriver.h"
#include "DNSDriver.h"
#include "JoggleLayer.h"
//����rominfo��Ϣ
void LoadROMinfo(char *filename, ROMInfo *&rom_info, TileInfoMask1 &tileinfomask, U8 &RomAddr, U8 &TEXADD, BOOL mask)
{
	//��ַ��ȡ�ļ�
	tileinfomask.mask = mask;
	READTEX readtex(filename);
	readtex.GetTexSize(tileinfomask, TEXADD);
	(*rom_info).tex[RomAddr].texel = new U64[tileinfomask.PixelLength];
	readtex.GetTexPixel((*rom_info).tex[RomAddr].texel);//��ȡʱ����������Բ�ȡ���л��ƣ����ٶ�ȡ��ʱ��
	RomAddr++;
}
//tileinfo��ǽṹ���ʼ��
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
//��Ӵ�ɫ����
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
//���������Ӧ�ı������
void GetMatrix(U8 &matrix,
	U8 num)
{
	matrix = num;
}
//tileinfo��������
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
//�����ں�
void Flush(ahmi *my_ahmi_p, TileInfo *tile_info, ROMInfo *rom_info)
{
	my_ahmi_p->DrawFrame(tile_info, rom_info, FrameBuffer);
}


