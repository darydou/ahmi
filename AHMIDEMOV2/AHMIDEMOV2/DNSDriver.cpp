#include "stdafx.h"
#include "DNSDriver.h"

void RTLTexIndex(TileInfo &tile_info,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 &TEXADD,
	ROMInfo &rom_info)
{
	U8 count = 0;
	for (U8 i = 0; i < TEXADD;i++)
	{ 
		if (tileinfomask.tileinfomask1[i].flag == 3)
		{
			tile_info.TextureIndex[i] = (((S2_8_11_11_1_24_7)tileinfomask.tileinfomask1[i].flag) << 62)
				+ (((S2_8_11_11_1_24_7)matrix[i]) << 54)
				+ (((S2_8_11_11_1_24_7)tileinfomask.tileinfomask1[i].height) << 43)
				+ (((S2_8_11_11_1_24_7)tileinfomask.tileinfomask1[i].width) << 32)
				+ (((S2_8_11_11_1_24_7)tileinfomask.tileinfomask1[i].mask) << 31)
				+ (((S2_8_11_11_1_24_7)tileinfomask.tileinfomask1[i].PixelLength));
		}
		else
		{
			int  texture_addr = (int)rom_info.tex[count].texel;
			tile_info.TextureIndex[i] = (((S2_8_11_11_1_32)tileinfomask.tileinfomask1[i].flag) << 62)
				+ (((S2_8_11_11_1_32)matrix[i]) << 54)
				+ (((S2_8_11_11_1_32)tileinfomask.tileinfomask1[i].height) << 43)
				+ (((S2_8_11_11_1_32)tileinfomask.tileinfomask1[i].width) << 32)
				+ (((S2_8_11_11_1_32)tileinfomask.tileinfomask1[i].mask) << 31)
				+ count;//移植到硬件时只需将此count改为texture_addr
			count++;
		}
			
	}
}

void RTLIndxSD(TileInfo &tile_info,
			   MatrixMask  &Matrixmask,
			   U8(&matrix)[MatrixSize],
			   TileInfoMask &tileinfomask,
			   U8 &TEXADD)
{
	int indexadd = 0;
	int sourceindexadd = 0;
	for (int tile_num = 0; tile_num < TILEINDEXSIZE; tile_num++)
	{
		tile_info.TileIndex[tile_num] = indexadd;
		for (int tex_num = 0; tex_num < TEXADD; tex_num++)
		{
			if (boxtest(tile_info, tile_num, Matrixmask, matrix, tileinfomask, tex_num))
			{
				tile_info.SourceAddr[sourceindexadd] = tex_num;
				sourceindexadd++;
				indexadd++;
			}
		}
	}
}

bool boxtest(TileInfo &tile_info,
	int &tile_num,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	int &tex_num)
{
	bool flag = false;
	//Point leftb, leftu, rightb, rightu;
	//leftb.x = (tile_num-((tile_num>>5)<<5)) * 32;
	//leftb.y = (tile_num / 32) * 32;
	//leftb.x = (leftb.x*Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[0]
	//	+ leftb.y*Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[3]
	//	+ Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[6]);
	//leftb.y = (((tile_num - ((tile_num >> 5) << 5)) * 32)
	//	*Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[1]
	//	+ leftb.y*Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[4]
	//	+ Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[7]);
	//if (leftb.x + 32 < 0 || leftb.x - 32 > tileinfomask->tileinfomask1[tex_num].width
	//	|| leftb.y + 32 < 0 || leftb.y - 32 > tileinfomask->tileinfomask1[tex_num].height)
	//	flag = false;
	//else
	//	return true;
	//
	//leftu.x = leftb.x + (int)(31.0 * Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[3]);
	//leftu.y = leftb.y + (int)(31.0 * Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[4]);
	//if (leftu.x + 32 < 0 || leftu.x - 32 > tileinfomask->tileinfomask1[tex_num].width
	//	|| leftu.y + 32 < 0 || leftu.y - 32 > tileinfomask->tileinfomask1[tex_num].height)
	//	flag = false;
	//else
	//	return true;
	//
	//rightb.x = leftb.x + (int)(31.0 * Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[0]);
	//rightb.y = leftb.y + (int)(31.0 * Matrixmask->Matrixmask1[matrix[tex_num]].Matrix[1]);
	//if (rightb.x + 32 < 0 || rightb.x - 32 > tileinfomask->tileinfomask1[tex_num].width
	//	|| rightb.y + 32 < 0 || rightb.y - 32 > tileinfomask->tileinfomask1[tex_num].height)
	//	flag = false;
	//else
	//	return true;
	//
	//rightu.x = rightb.x + leftu.x - leftb.x;
	//rightu.y = rightb.y + leftu.y - leftb.y;
	//if (rightu.x + 32 < 0 || rightu.x - 32 > tileinfomask->tileinfomask1[tex_num].width
	//	|| rightu.y + 32 < 0 || rightu.y - 32 > tileinfomask->tileinfomask1[tex_num].height)
	//	flag = false;
	//else
	//	return true;
	//return false;
	
	Point leftb;
	leftb.x = (tile_num - ((tile_num >> 5) << 5)) * 32;
	leftb.y = (tile_num >>5) * 32;
	leftb.x = (leftb.x*(S32)tile_info.matrix[matrix[tex_num]].A
		     + leftb.y*(S32)tile_info.matrix[matrix[tex_num]].C
		             + (S32)tile_info.matrix[matrix[tex_num]].E)>>4;
	leftb.y = ((tile_num - ((tile_num >> 5) << 5)) * 32 * (S32)tile_info.matrix[matrix[tex_num]].B
		+ leftb.y*(S32)tile_info.matrix[matrix[tex_num]].D
		        + (S32)tile_info.matrix[matrix[tex_num]].F) >>4;
	if (   leftb.x  <0 || leftb.x  >tileinfomask.tileinfomask1[tex_num].width
		|| leftb.y  <0 || leftb.y  >tileinfomask.tileinfomask1[tex_num].height)
		flag = false;
	else
		return true;

	Point leftu;
	leftu.x = leftb.x + ((S32)(31 * (S32)tile_info.matrix[matrix[tex_num]].C) >>4);
	leftu.y = leftb.y + ((S32)(31 * (S32)tile_info.matrix[matrix[tex_num]].D) >>4);
	if    (leftu.x <0 || leftu.x >tileinfomask.tileinfomask1[tex_num].width
		|| leftu.y <0 || leftu.y >tileinfomask.tileinfomask1[tex_num].height)
		flag = false;
	else
		return true;

	Point rightb;
	rightb.x = leftb.x + ((S32)(31 * (S32)tile_info.matrix[matrix[tex_num]].A) >>4);
	rightb.y = leftb.y + ((S32)(31 * (S32)tile_info.matrix[matrix[tex_num]].B) >>4);
	if (   rightb.x <0 || rightb.x >tileinfomask.tileinfomask1[tex_num].width
		|| rightb.y <0 || rightb.y >tileinfomask.tileinfomask1[tex_num].height)
		flag = false;
	else
		return true;

	Point rightu;
	rightu.x = rightb.x + leftu.x - leftb.x;
	rightu.y = rightb.y + leftu.y - leftb.y;
	// rightu.x = leftb.x + (int)(31 * (int)tile_info->Matrix[matrix[tex_num]].A) / 16 + (int)(31 * (int)tile_info->Matrix[matrix[tex_num]].C) / 16;
	// rightu.y = leftb.y + (int)(31 * (int)tile_info->Matrix[matrix[tex_num]].B) / 16 + (int)(31 * (int)tile_info->Matrix[matrix[tex_num]].D) / 16;

	if (   rightu.x <0 || rightu.x >tileinfomask.tileinfomask1[tex_num].width
		|| rightu.y <0 || rightu.y >tileinfomask.tileinfomask1[tex_num].height)
		flag = false;
	else
		return true;
	return flag;
}

//void RTLIndxSD2(TileInfo *&tile_info,
//	MatrixMask  *&Matrixmask,
//	unsigned char *&matrix,
//	TileInfoMask *&tileinfomask,
//	unsigned char TEXADD)
//{
//	Point leftb,leftu,rightb,rightu;
//	for (int tex_num = 0; tex_num < TEXADD; tex_num++)
//	{
//		leftb.x = (int)tile_info->Matrix[matrix[tex_num]].E;
//		leftb.y = (int)tile_info->Matrix[matrix[tex_num]].F;
//		leftu.x = (int)tileinfomask->tileinfomask1[tex_num].height
//			*(int)tile_info->Matrix[matrix[tex_num]].C
//			+ leftb.x;
//		leftu.y = (int)tileinfomask->tileinfomask1[tex_num].height
//			*(int)tile_info->Matrix[matrix[tex_num]].D
//			+ leftb.y;
//		rightb.x = (int)tileinfomask->tileinfomask1[tex_num].width
//			*(int)tile_info->Matrix[matrix[tex_num]].A
//			+ leftb.x;
//		rightb.y = (int)tileinfomask->tileinfomask1[tex_num].width
//			*(int)tile_info->Matrix[matrix[tex_num]].B
//			+ leftb.y;
//		rightu.x = (int)tileinfomask->tileinfomask1[tex_num].width
//			*(int)tile_info->Matrix[matrix[tex_num]].A
//			+ (int)tileinfomask->tileinfomask1[tex_num].height
//			*(int)tile_info->Matrix[matrix[tex_num]].C
//			+ leftb.x;
//		rightu.y = (int)tileinfomask->tileinfomask1[tex_num].width
//			*(int)tile_info->Matrix[matrix[tex_num]].B
//			+(int)tileinfomask->tileinfomask1[tex_num].height
//			*(int)tile_info->Matrix[matrix[tex_num]].D
//			+ leftb.y;
//		int minx = MIN4(leftb.x, leftu.x, rightb.x, rightu.x);
//		int maxx = MAX4(leftb.x, leftu.x, rightb.x, rightu.x);
//		int miny = MIN4(leftb.y, leftu.y, rightb.y, rightu.y);
//		int maxy = MAX4(leftb.y, leftu.y, rightb.y, rightu.y);
//		minx = MAX(minx,0);
//		maxx = MIN(maxx, SCREENWIDTH);
//		miny = MAX(miny,0);
//		maxy = MAX(maxx, SCREENHEIGHT);
//
//	}
//
//}