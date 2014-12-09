#include <iostream>
#include "ALLHeader.h"
namespace TOOL{
	//Ìí¼Ó´¿É«ÎÆÀí
	void ADDPurity(TileInfoMask &tileinfomask,
		U8 &TEXADD,
		BOOL mask,
		U8 r,
		U8 g,
		U8 b,
		U16 width,
		U16 height);
	void GetMatrix(U8(&matrix)[MatrixSize],
		U8 TEXADD,
		U8 num);
}
