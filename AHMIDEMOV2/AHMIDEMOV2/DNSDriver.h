#ifndef __DNSDRIVER
#define __DNSDRIVER
#include "ALLHeader.h"
 
const U16 magnitude1 = 7;
void LoadIndexSoueAddr(TileInfo &tile_info,
	MatrixMask  &Matrixmask,
	U8(&matrix)[MatrixSize],
	TileInfoMask &tileinfomask,
	U8 &TEXADD);
void LoadTextureIndex(TileInfo &tile_info,
	             U8(&matrix)[MatrixSize],
	             TileInfoMask &tileinfomask,
				 U8 &TEXADD,
				 ROMInfo &rom_info);
#endif
