#include "ALLHeader.h"
#define MSize 9
//生成矩阵模块
class MatrixGenerate
{
private:
	S1_B_4 Matrix[MSize];
	S1_B_4 MatrixTemp[MSize];
	S1_B_4 MatrixCurrent[MSize];
	void CORDIC(S16 &Radian, S16 &COS, S16 &SIN);//由角度计算cos和sin
public:
	MatrixGenerate();
	void Triscale(S1_3_4 cx, S1_3_4 cy);
	void Tritranslate(S1_B_4 tx, S1_B_4 ty);
	void Trirotate(S16 degrees);
	void Trihorizontal(S1_3_4 sv);
	void Trivertical(S1_3_4 sh);
	void MatrixING();
	void GetMatrix(struct _Matrix &tile_info_matrix,
		MatrixMask1 &Matrixmask,
		U8 &matrix,
		U8 TEXADD);
	~MatrixGenerate();
};