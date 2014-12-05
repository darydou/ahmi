#include "stdafx.h"
#include "MatrixGenerate.h"
//构造函数
MatrixGenerate::MatrixGenerate()
{
	//Matrix[0]~Matrix[5]为1.1.6定点数
	//Matrix[6]~Matrix[7]为1.11.4定点数
	Matrix[0] = 1 << magnitude;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	Matrix[4] = 1 << magnitude;
	Matrix[5] = 0;
	Matrix[6] = 0;
	Matrix[7] = 0;
	Matrix[8] = 1 << magnitude;

	for (S32 i = 0; i < MSize; i++)
	{
		MatrixTemp[i] = Matrix[i];
		MatrixCurrent[i] = Matrix[i];
	}
}
//析构函数
MatrixGenerate::~MatrixGenerate()
{

}

//由角度转换成正弦值和余弦值
void MatrixGenerate::CORDIC(S16 &Radian, S16 &COS, S16 &SIN)
{
	S16 Angle[14] = { 5760, 3400, 1797, 912, 458, 229, 115, 57, 29, 14, 7, 4, 2, 1 };             //将上述角度扩大128倍
	S16 cosine[14] = { 181, 162, 157, 156, 156, 155, 155, 155, 155, 155, 155, 155, 155, 155 };    //cos@的结果乘以256
	S16 x, y;
	x = COS;
	y = SIN;
	x = x * 1024; 
	y = y * 1024;
	S32 count_i;
	S32 coeff1 = 0, coeff2 = 0;
	while (Radian >= 360)
		Radian = Radian - 360;
	while (Radian < 0)
		Radian = Radian + 360;
	if (Radian == 0 || Radian == 180)
	{

		if (Radian == 0)
		{
			COS = x;
			SIN = y;
		}
		else //(Radian == 180)
		{
			COS = -x;
			SIN = y;
		}
	}
	else if (Radian == 90 || Radian == 270)
	{

		if (Radian == 90)
		{
			COS = y;
			SIN = x;
		}
		else //(Radian == 270)
		{
			COS = y;
			SIN = -x;
		}
	}
	else
	{
		if (Radian > 0 && Radian < 90)
		{
			coeff1 = 1, coeff2 = 1;
		}
		else if (Radian >= 90 && Radian < 180)
		{
			Radian = Radian - 90;
			Radian = 90 - Radian;
			coeff1 = -1, coeff2 = 1;
		}
		else if (Radian > 180 && Radian < 270)
		{
			Radian = Radian - 180;
			coeff1 = -1, coeff2 = -1;
		}
		else if (Radian >= 270 && Radian < 360)
		{
			Radian = Radian - 270;
			Radian = 90 - Radian;
			coeff1 = 1, coeff2 = -1;
		}
		Radian = Radian * 128;
		for (count_i = 0; count_i <= 13; count_i++)
		{
			if (Radian>0)      //大于0表示，在角度30下面，要继续逆时针旋转，小于0表示在角度30度上面，要回转
			{
				Radian = Radian - Angle[count_i];
				COS = (x - (y >> count_i));
				SIN = (y + (x >> count_i));
				x = COS;
				y = SIN;
			}
			else if (Radian < 0)
			{
				Radian = Radian + Angle[count_i];
				COS = (x + (y >> count_i));
				SIN = (y - (x >> count_i));
				x = COS;
				y = SIN;
			}
			if (Radian == 0)
			{
				COS = coeff1*COS*cosine[count_i] >> 8;
				SIN = coeff2*SIN*cosine[count_i] >> 8;
				break;
			}
		}
	}
}

////正矩阵AMX=x;逆矩阵X=M'A'x;A为当前矩阵，M已产生的矩阵，初始M为单位矩阵
////add by darydou 12.4 to replace the old one
//void MatrixGenerate::Triscale(S1_1_6 cx, S1_1_6 cy)
//{
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = Matrix[i];
//	//ation:use >> means dec is not good solution,if the num is less than zero,the answer will be add one;
//	Matrix[0] = static_cast<S16>(static_cast<S32>(cx)*static_cast<S32>(MatrixCurrent[0]) >> 4);
//	Matrix[1] = static_cast<S16>(static_cast<S32>(cx)*static_cast<S32>(MatrixCurrent[1]) >> 4);
//	Matrix[2] = static_cast<S16>(static_cast<S32>(cx)*static_cast<S32>(MatrixCurrent[2]) >> 4);
//	Matrix[3] = static_cast<S16>(static_cast<S32>(cy)*static_cast<S32>(MatrixCurrent[3]) >> 4);
//	Matrix[4] = static_cast<S16>(static_cast<S32>(cy)*static_cast<S32>(MatrixCurrent[4]) >> 4);
//	Matrix[5] = static_cast<S16>(static_cast<S32>(cy)*static_cast<S32>(MatrixCurrent[5]) >> 4);
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = MatrixTemp[i];
//	MatrixTemp[0] = static_cast<S16>((static_cast<S32>(MatrixCurrent[0]) << 4) / static_cast<S32>(cy));
//	MatrixTemp[1] = static_cast<S16>((static_cast<S32>(MatrixCurrent[1]) << 4) / static_cast<S32>(cx));
//	MatrixTemp[2] = static_cast<S16>((static_cast<S32>(MatrixCurrent[2]) << 8) / static_cast<S32>(cx*cy));
//	MatrixTemp[3] = static_cast<S16>((static_cast<S32>(MatrixCurrent[3]) << 4) / static_cast<S32>(cy));
//	MatrixTemp[4] = static_cast<S16>((static_cast<S32>(MatrixCurrent[4]) << 4) / static_cast<S32>(cx));
//	MatrixTemp[5] = static_cast<S16>((static_cast<S32>(MatrixCurrent[5]) << 8) / static_cast<S32>(cx*cy));
//	MatrixTemp[6] = static_cast<S16>((static_cast<S32>(MatrixCurrent[6]) << 4) / static_cast<S32>(cy));
//	MatrixTemp[7] = static_cast<S16>((static_cast<S32>(MatrixCurrent[7]) << 4) / static_cast<S32>(cx));
//	MatrixTemp[8] = static_cast<S16>((static_cast<S32>(MatrixCurrent[8]) << 8) / static_cast<S32>(cx*cy));
//}
////正矩阵AMX=x;逆矩阵X=M'A'x;A为当前矩阵，M已产生的矩阵，初始M为单位矩阵
////add by darydou 12.4 to replace the old one
//void MatrixGenerate::Trirotate(S16 degrees)
//{
//	S16 COS = 1, SIN = 0;
//	CORDIC(degrees, COS, SIN);
//	//ation:use >> means dec is not good solution,if the num is less than zero,the answer will be add one;
//	S1_B_4 cos = COS >> (10 - 4);
//	S1_B_4 sin = SIN >> (10 - 4);
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = Matrix[i];
//	Matrix[0] = static_cast<S16>(static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[0])
//		+ static_cast<S32>(sin)*static_cast<S32>(MatrixCurrent[3]) >> 4);
//	Matrix[1] = static_cast<S16>(static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[1])
//		+ static_cast<S32>(sin)*static_cast<S32>(MatrixCurrent[4]) >> 4);
//	Matrix[2] = static_cast<S16>(static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[2])
//		+ static_cast<S32>(sin)*static_cast<S32>(MatrixCurrent[5]) << 4);
//	Matrix[3] = static_cast<S16>(static_cast<S32>(-sin)*static_cast<S32>(MatrixCurrent[0])
//		+ static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[3]) >> 4);
//	Matrix[4] = static_cast<S16>(static_cast<S32>(-sin)*static_cast<S32>(MatrixCurrent[1])
//		+ static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[4]) >> 4);
//	Matrix[5] = static_cast<S16>(static_cast<S32>(-sin)*static_cast<S32>(MatrixCurrent[2])
//		+ static_cast<S32>(cos)*static_cast<S32>(MatrixCurrent[5]) << 4);
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = MatrixTemp[i];
//	MatrixTemp[0] = static_cast<S16>(static_cast<S32>(MatrixCurrent[0])*static_cast<S32>(cos)
//		+static_cast<S32>(MatrixCurrent[1])* static_cast<S32>(sin) >> 4);
//	MatrixTemp[1] = static_cast<S16>(static_cast<S32>(MatrixCurrent[0])*static_cast<S32>(-sin)
//		+ static_cast<S32>(MatrixCurrent[1])*static_cast<S32>(cos) >> 4);
//	MatrixTemp[3] = static_cast<S16>(static_cast<S32>(MatrixCurrent[3])*static_cast<S32>(cos)
//		+static_cast<S32>(MatrixCurrent[4])* static_cast<S32>(sin) >> 4);
//	MatrixTemp[4] = static_cast<S16>(static_cast<S32>(MatrixCurrent[3])*static_cast<S32>(-sin)
//		+ static_cast<S32>(MatrixCurrent[4])*static_cast<S32>(cos) >> 4);
//	MatrixTemp[6] = static_cast<S16>(static_cast<S32>(MatrixCurrent[6])*static_cast<S32>(cos)
//		+static_cast<S32>(MatrixCurrent[7])* static_cast<S32>(sin) >> 4);
//	MatrixTemp[7] = static_cast<S16>(static_cast<S32>(MatrixCurrent[6])*static_cast<S32>(-sin)
//		+ static_cast<S32>(MatrixCurrent[7])*static_cast<S32>(cos) >> 4);
//}
////正矩阵AMX=x;逆矩阵X=M'A'x;A为当前矩阵，M已产生的矩阵，初始M为单位矩阵
////add by darydou 12.4 to replace the old one
//void MatrixGenerate::Tritranslate(S1_B_4 tx, S1_B_4 ty)
//{
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = Matrix[i];
//	Matrix[6] = static_cast<S16>(static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[0]) + static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[3]) >> 4)
//		+ MatrixCurrent[6];
//	Matrix[7] = static_cast<S16>(static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[1]) + static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[4]) >> 4)
//		+ MatrixCurrent[7];
//	Matrix[8] = static_cast<S16>(static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[2]) + static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[5]) >> 4)
//		+ MatrixCurrent[8];
//	for (U8 i = 0; i < MSize; i++)
//		MatrixCurrent[i] = MatrixTemp[i];
//	MatrixTemp[0] = MatrixCurrent[0] + static_cast<S16>(static_cast<S32>(MatrixCurrent[2])*static_cast<S32>(-tx) << 4);
//	MatrixTemp[1] = MatrixCurrent[1] + static_cast<S16>(static_cast<S32>(MatrixCurrent[2])*static_cast<S32>(-ty) << 4);
//	MatrixTemp[3] = MatrixCurrent[3] + static_cast<S16>(static_cast<S32>(MatrixCurrent[5])*static_cast<S32>(-tx) << 4);
//	MatrixTemp[4] = MatrixCurrent[4] + static_cast<S16>(static_cast<S32>(MatrixCurrent[5])*static_cast<S32>(-ty) << 4);
//	MatrixTemp[6] = MatrixCurrent[6] + static_cast<S16>(static_cast<S32>(MatrixCurrent[8])*static_cast<S32>(-tx) << 4);
//	MatrixTemp[7] = MatrixCurrent[7] + static_cast<S16>(static_cast<S32>(MatrixCurrent[8])*static_cast<S32>(-ty) << 4);
//}

//尺度变换
//仅能放大
void MatrixGenerate::Triscale(S16 cx, S16 cy)
{
	cx = cx << magnitude;
	cy = cy << magnitude;
	//修改，使之符合人性化输入
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	Matrix[0] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[0]) * static_cast<S32>((S16)cx)) >> magnitude);//1.9.6*1.1.6=24.12>>6
	Matrix[1] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[1]) * static_cast<S32>((S16)cy)) >> magnitude);//1.9.6*1.1.6=24.12>>6
	Matrix[3] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[3]) * static_cast<S32>((S16)cx)) >> magnitude);//1.9.6*1.1.6=24.12>>6 
	Matrix[4] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[4]) * static_cast<S32>((S16)cy)) >> magnitude);//1.9.6*1.1.6=24.12>>6
	Matrix[6] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[6]) * static_cast<S32>((S16)cx)) >> magnitude);//1.11.4*1.1.6=24.10>>6
	Matrix[7] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[7]) * static_cast<S32>((S16)cy)) >> magnitude);//1.11.4*1.1.6=24.10>>6
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[0] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[0]) << magnitude ) / static_cast<S32>((S16)cx));//1.9.6/1.1.6=1<<6
	MatrixTemp[1] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[1]) << magnitude ) / static_cast<S32>((S16)cx));//1.9.6/1.1.6=1<<6
	MatrixTemp[2] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[2]) << magnitude ) / static_cast<S32>((S16)cx));//1.9.6/1.1.6=1<<6
	MatrixTemp[3] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[3]) << magnitude ) / static_cast<S32>((S16)cy));//1.9.6/1.1.6=1<<6 
	MatrixTemp[4] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[4]) << magnitude ) / static_cast<S32>((S16)cy));//1.9.6/1.1.6=1<<6
	MatrixTemp[5] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[5]) << magnitude ) / static_cast<S32>((S16)cy));//1.9.6/1.1.6=1<<6
	MatrixTemp[6] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[6]) << (magnitude*3-4)) / static_cast<S32>(static_cast<S16>((S16)cx)*static_cast<S16>((S16)cy)));//1.11.4/(1.1.6*1.1.6)=1.-8<<8+6=14
	MatrixTemp[7] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[7]) << (magnitude*3-4)) / static_cast<S32>(static_cast<S16>((S16)cx)*static_cast<S16>((S16)cy)));//1.11.4/(1.1.6*1.1.6)=1.-8<<8+6=14
	MatrixTemp[8] = static_cast<S16>((static_cast<S32>((S16)MatrixCurrent[8]) << (magnitude*2)) / static_cast<S32>(static_cast<S16>((S16)cx)*static_cast<S16>((S16)cy)));//1.9.6/(1.1.6*1.1.6)=1.-6<<6+6=12
}

//旋转功能
void MatrixGenerate::Trirotate(S16 degrees)
{
	S16 COS = 1, SIN = 0; 
	CORDIC(degrees, COS,SIN);
	//cos求出的值为扩大1024倍的值，计算时只需要1.1.6定点数故缩小16倍
	S16 cos = COS >>(10-magnitude);
	S16 sin = SIN >>(10-magnitude);
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	//.6*.6=.12<<6为.6
	Matrix[0] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[0])*static_cast<S32>((S16)cos) - static_cast<S32>((S16)MatrixCurrent[1])*static_cast<S32>((S16)sin) >> magnitude);
	Matrix[1] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[0])*static_cast<S32>((S16)sin) + static_cast<S32>((S16)MatrixCurrent[1])*static_cast<S32>((S16)cos) >> magnitude);
	Matrix[3] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[3])*static_cast<S32>((S16)cos) - static_cast<S32>((S16)MatrixCurrent[4])*static_cast<S32>((S16)sin) >> magnitude);
	Matrix[4] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[3])*static_cast<S32>((S16)sin) + static_cast<S32>((S16)MatrixCurrent[4])*static_cast<S32>((S16)cos) >> magnitude);
	Matrix[6] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[6])*static_cast<S32>((S16)cos) - static_cast<S32>((S16)MatrixCurrent[7])*static_cast<S32>((S16)sin) >> magnitude);
	Matrix[7] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[6])*static_cast<S32>((S16)sin) + static_cast<S32>((S16)MatrixCurrent[7])*static_cast<S32>((S16)cos) >> magnitude);
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[0] = static_cast<S16>(static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[0]) - static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[3]) >> magnitude);
	MatrixTemp[1] = static_cast<S16>(static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[1]) - static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[4]) >> magnitude);
	MatrixTemp[2] = static_cast<S16>(static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[2]) - static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[5]) >> magnitude);
	MatrixTemp[3] = static_cast<S16>(static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[0]) + static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[3]) >> magnitude);
	MatrixTemp[4] = static_cast<S16>(static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[1]) + static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[4]) >> magnitude);
	MatrixTemp[5] = static_cast<S16>(static_cast<S32>((S16)sin)*static_cast<S32>((S16)MatrixCurrent[2]) + static_cast<S32>((S16)cos)*static_cast<S32>((S16)MatrixCurrent[5]) >> magnitude);
}

//平移功能
void MatrixGenerate::Tritranslate(S1_B_4 tx, S1_B_4 ty)
{
	tx = tx << 4;
	ty = ty << 4;
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	//MatrixCurrent[0]~MatrixCurrent[4]为.6的定点数，tx为.4的定点数
	Matrix[0] = static_cast<S16>(MatrixCurrent[0]) + ((static_cast<S32>((S16)MatrixCurrent[2])* static_cast<S32>((S16)tx)) >> 4);
	Matrix[1] = static_cast<S16>(MatrixCurrent[1]) + ((static_cast<S32>((S16)MatrixCurrent[2])* static_cast<S32>((S16)ty)) >> 4);
	Matrix[3] = static_cast<S16>(MatrixCurrent[3]) + ((static_cast<S32>((S16)MatrixCurrent[5])* static_cast<S32>((S16)tx)) >> 4);
	Matrix[4] = static_cast<S16>(MatrixCurrent[4]) + ((static_cast<S32>((S16)MatrixCurrent[5])* static_cast<S32>((S16)ty)) >> 4);
	Matrix[6] = MatrixCurrent[6] + static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[8]) * static_cast<S32>((S16)tx) >> magnitude);
	Matrix[7] = MatrixCurrent[7] + static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[8]) * static_cast<S32>((S16)ty) >> magnitude);
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	MatrixTemp[6] = static_cast<S16>(-static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[0]) - static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[3]) >>magnitude) + MatrixCurrent[6];
	MatrixTemp[7] = static_cast<S16>(-static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[1]) - static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[4]) >>magnitude) + MatrixCurrent[7];
	MatrixTemp[8] = static_cast<S16>(-static_cast<S32>(tx)*static_cast<S32>(MatrixCurrent[2]) - static_cast<S32>(ty)*static_cast<S32>(MatrixCurrent[5]) >> 4) + MatrixCurrent[8];
}
//水平偏移
void MatrixGenerate::Trivertical(S1_1_6 sv)
{
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	//1.1.6
	Matrix[0] = MatrixCurrent[0] + static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[1]) * static_cast<S32>((S16)sv) >> magnitude);
	Matrix[3] = MatrixCurrent[3] + static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[4]) * static_cast<S32>((S16)sv) >> magnitude);
	//12.4
	Matrix[6] = MatrixCurrent[6] + ((static_cast<S32>((S16)MatrixCurrent[7]) * static_cast<S32>((S16)sv)) >> 6);
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	//1.1.6
	MatrixTemp[3] = static_cast<S16>(static_cast<S32>((S16)-sv)*static_cast<S32>(MatrixCurrent[0]) >> magnitude) + MatrixCurrent[3];
	MatrixTemp[4] = static_cast<S16>(static_cast<S32>((S16)-sv)*static_cast<S32>(MatrixCurrent[1]) >> magnitude) + MatrixCurrent[4];
	MatrixTemp[5] = static_cast<S16>(static_cast<S32>((S16)-sv)*static_cast<S32>(MatrixCurrent[2]) >> magnitude) + MatrixCurrent[5];
}
//垂直偏移
void MatrixGenerate::Trihorizontal(S1_1_6 sh)
{
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = Matrix[i];
	//1.1.6
	Matrix[1] = static_cast<S16>(static_cast<S32>(MatrixCurrent[0]) * static_cast<S32>((S16)sh) >> magnitude) + MatrixCurrent[1];
	Matrix[4] = static_cast<S16>(static_cast<S32>(MatrixCurrent[3]) * static_cast<S32>((S16)sh) >> magnitude) + MatrixCurrent[4];
	//12.4
	Matrix[7] = static_cast<S16>(static_cast<S32>((S16)MatrixCurrent[6]) * static_cast<S32>((S16)sh) >> magnitude) + MatrixCurrent[7];
	for (U8 i = 0; i < MSize; i++)
		MatrixCurrent[i] = MatrixTemp[i];
	//1.1.6
	MatrixTemp[0] = MatrixCurrent[0] - (static_cast<S32>((S16)sh)*static_cast<S32>((S16)MatrixCurrent[3]) >> magnitude);
	MatrixTemp[1] = MatrixCurrent[1] - (static_cast<S32>((S16)sh)*static_cast<S32>((S16)MatrixCurrent[4]) >> magnitude);
	MatrixTemp[2] = MatrixCurrent[2] - (static_cast<S32>((S16)sh)*static_cast<S32>((S16)MatrixCurrent[5]) >> magnitude);
}
//传递变换矩阵
//modfied by darydou 14/12/03
void MatrixGenerate::GetMatrix(TileInfo &tile_info,
	                          MatrixMask &Matrixmask,
	                          U8 (&matrix)[MatrixSize],
	                          U8 TEXADD)
{
	//for (int i = 0; i < MSize; i++)
	//	Matrixmask->Matrixmask1[TEXADD - 1].Matrix[i] = Matrix[i];
	//int FloatValue, Exp, MantissaPart, FloatPath, bfloat;
	//char a[4] = {0,0,0,0};
	//int count = 0;
	//unsigned char flag = 0;
	//for (int i = 0; i < MSize - 3; i++)
	//{
	//	if (i % 3 < 2)
	//	{
	//		FloatValue = *reinterpret_cast<int*>(&Matrix[i]); //MatrixTemp[i]
	//		if (FloatValue == 0||FloatValue==0x80000000)//等于正零或者负零时直接赋零
	//			a[count] = 0;
	//		else
	//		{
	//			flag = 0;
	//			if (FloatValue & 0x80000000)
	//				flag = 1;
	//			Exp = (FloatValue >> 23) & 0xff;
	//			MantissaPart = (FloatValue & 0x7fffff) | 0x800000;//尾数字段，23位加一个默认位，共24位。
	//			if ((MantissaPart >> (150 - Exp)) >8)//150=127+23编译原理
	//			{
	//				cout << "The num is out of the size!\n" << endl;
	//				system("pause");
	//				exit(0);
	//			}
	//			else
	//			{
	//				//整数部分1.3.4
	//				char zs = ((MantissaPart >> (150 - Exp)) * 16);
	//				//小数部分1.3.4
	//				FloatPath = MantissaPart&(0xffffff >>((Exp - 126)>0?(Exp-126):0));//取得小数部分
	//				char xs = ((FloatPath / float(1 << (150 - Exp))) * 16);
	//				if (flag== 1)
	//				{
	//					a[count] = -(zs | xs);
	//				}
	//				else
	//					a[count] = zs | xs;
	//			}
	//		}
	//		count++; 
	//	}
	//}
	//short b[2] = {0,0};
	//count = 0;
	//for (int i = MSize - 3; i < MSize-1; i++)
	//{
	//	FloatValue = *reinterpret_cast<int*>(&Matrix[i]);//(&MatrixTemp[i])
	//	if (FloatValue == 0||FloatValue==0x80000000)
	//		b[count] = 0;
	//	else
	//	{
	//		flag = 0;
	//		if (FloatValue & 0x80000000)
	//			flag=1;
	//		Exp = (FloatValue >> 23) & 0xff;
	//		MantissaPart = (FloatValue & 0x7fffff) | 0x800000;//尾数字段，23位加一个默认位，共24位。
	//		if ((MantissaPart >> (150 - Exp)) >2048)
	//		{
	//			cout << "The num is out of the size!\n" << endl;
	//			system("pause");
	//			exit(0);
	//		}
	//		else
	//		{
	//			//整数部分1.3.4
	//			short zs = ((MantissaPart >> (150 - Exp)) * 16);
	//			//小数部分1.3.4
	//			FloatPath = MantissaPart&(0xffffff >> ((Exp - 126)>0?(Exp-126):0));//取得小数部分
	//			short xs = ((FloatPath / float(1 << (150 - Exp))) * 16);
	//			if (flag == 1)
	//			{
	//				b[count] = -(zs | xs);
	//			}
	//			else
	//				b[count] = zs | xs;
	//		}
	//	}
	//	count++;
	//} 
	
	tile_info.matrix[TEXADD - 1].A = (S1_1_6)MatrixTemp [0];
	tile_info.matrix[TEXADD - 1].B = (S1_1_6)MatrixTemp [1];
	tile_info.matrix[TEXADD - 1].C = (S1_1_6)MatrixTemp [3];
	tile_info.matrix[TEXADD - 1].D = (S1_1_6)MatrixTemp [4];
	tile_info.matrix[TEXADD - 1].E = MatrixTemp [6];
	tile_info.matrix[TEXADD - 1].F = MatrixTemp [7];
	
	Matrixmask.Matrixmask1[TEXADD - 1].matrix = ((U64)Matrix[0] & 0xffff) << 48 |
		((U64)Matrix[1] & 0xffff) << 32 |
		((U64)Matrix[3] & 0xffff) << 16 |
		((U64)Matrix[4] & 0xffff);
	Matrixmask.Matrixmask1[TEXADD - 1].matrixEF = ((U32)Matrix[6] & 0xffff) << 16 |
		((U32)Matrix[7] & 0xffff);
	matrix[TEXADD - 1] = TEXADD - 1;
}

