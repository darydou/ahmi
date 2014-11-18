#include "stdafx.h"
#include "SNSDriver.h"

//构造函数
READTEX::READTEX(char *Filename)
{
	filename = Filename;
	infile.open(filename, std::ios::binary);
	Determine();
}
//析构函数
READTEX::~READTEX()
{
	infile.close();
}
//获取纹理的大小为之分配空间
void READTEX::GetTexSize(TileInfoMask1 &tileinfomask, unsigned char &TEXADD)
{
	if (flag == 0)
	{
		char *ch = new char[4];
		infile.seekg(12);
		infile.read(ch, 4 * sizeof(char));
		height = (U8)ch[0]
			+ (((U8)ch[1] << 8) & 0xFF00)
			+ (((U8)ch[2] << 16) & 0xFF0000)
			+ (((U8)ch[3] << 24) & 0xFF000000);
		infile.seekg(16);
		infile.read(ch, 4 * sizeof(char));
		width = (U8)ch[0]
			+ (((U8)ch[1] << 8) & 0xFF00)
			+ (((U8)ch[2] << 16) & 0xFF0000)
			+ (((U8)ch[3] << 24) & 0xFF000000);
		infile.seekg(84);
		infile.read(ch, 4 * sizeof(char));
		if (ch[0] == 'D'&&ch[1] == 'X'&&ch[2] == 'T')
		{
			if (ch[3] == '1')
			{
				flag = 0;
				PixelLength = width*height / 16;
			}
			else if (ch[3] == '3')
			{
				flag = 1;
				PixelLength = width*height / 8;
			}
			else if (ch[3] == '5')
			{
				cout << "DXT5 is not Sloution!\n" << endl;
				system("pause");
				exit(0);
			}
			else
			{
				cout << "*.dds is not DXT1 DXT3 OR DXT5!\n" << endl;
				system("pause");
				exit(0);
			}
			delete[] ch;
		}
		else
		{
			cout << "*.dds is not DXT1 DXT3 OR DXT5!\n" << endl;
			system("pause");
			exit(0);
		}

	}
	else if (flag == 2)
	{
		width = 1024;
		height = 768;
		PixelLength = 1024 * 768;
	}
	PixelLength = 1024 * 768;
	tileinfomask.flag = flag;
	tileinfomask.height = height;
	tileinfomask.width = width;
	tileinfomask.PixelLength = PixelLength;
	TEXADD++;
}
//将纹理读入到roninfo中
void READTEX::GetTexPixel(U64 *&rominfo)
{
	int i = 0;
	U64 temp1, temp2, temp;
	char fuck[4];
	if (flag == 2)
	{
		infile.seekg(0);
		while (!infile.eof())// && i<Pixellength)
		{

			infile >> std::hex >> temp1;
			infile >> std::hex >> temp2;
			temp = (temp1 << 32) + temp2;
			//infile.read(ciao, 20 * sizeof(char));
			//for (int num = 0; num < 20; num++)
			//{
			//	if (ciao[num] >= '0'&&ciao[num] <= '9')
			//		ciao[num] = ciao[num] - 48;
			//	else if (ciao[num] >= 'a'&&ciao[num] <= 'f')
			//		ciao[num] = ciao[num] - 87;
			//	else if (ciao[num] >= 'A'&&ciao[num] <= 'F')
			//		ciao[num] = ciao[num] - 55;
			//}
			//temp = ((U64)((U8)ciao[0] & 0xf) << 60)
			//	+ ((U64)((U8)ciao[1] & 0xf) << 56)
			//	+ ((U64)((U8)ciao[2] & 0xf) << 52)
			//	+ ((U64)((U8)ciao[3] & 0xf) << 48)
			//	+ ((U64)((U8)ciao[4] & 0xf) << 44)
			//	+ ((U64)((U8)ciao[5] & 0xf) << 40)
			//	+ ((U64)((U8)ciao[6] & 0xf) << 36)
			//	+ ((U64)((U8)ciao[7] & 0xf) << 32)
			//	+ ((U64)((U8)ciao[10] & 0xf) << 28)
			//	+ ((U64)((U8)ciao[11] & 0xf) << 24)
			//	+ ((U64)((U8)ciao[12] & 0xf) << 20)
			//	+ ((U64)((U8)ciao[13] & 0xf) << 16)
			//	+ ((U64)((U8)ciao[14] & 0xf) << 12)
			//	+ ((U64)((U8)ciao[15] & 0xf) << 8)
			//	+ ((U64)((U8)ciao[16] & 0xf) << 4)
			//	+ ((U64)((U8)ciao[17] & 0xf) << 0);
			//*(rominfo + i) = temp;
			//i++;

			*(rominfo + i) = temp;
			i++;
		}
	}
	else
	{
		infile.seekg(0x80);
		while (!infile.eof())// && i<Pixellength)
		{
			infile.read(fuck, 4 * sizeof(char));
			temp = ((U64)((U8)fuck[0]) << 56)
				+ ((U64)((U8)fuck[1]) << 48)
				+ ((U64)((U8)fuck[2]) << 40)
				+ ((U64)((U8)fuck[3]) << 32);
			infile.read(fuck, 4 * sizeof(char));
			temp = temp + ((U64)((U8)fuck[0]) << 24)
				+ ((U64)((U8)fuck[1]) << 16)
				+ ((U64)((U8)fuck[2]) << 8)
				+ ((U64)((U8)fuck[3]) << 0);
			*(rominfo + i) = temp;
			i++;
		}
	}
}
//判断纹理的格式
void READTEX::Determine()
{//ALPHA
	if ((*filename) == 'A'
		&& (*(filename + 1)) == 'L'
		&& (*(filename + 2)) == 'P'
		&& (*(filename + 3)) == 'H'
		&& (*(filename + 4)) == 'A'
		)
		flag = 2;
	else if ((*(filename + strlen(filename) - 3)) == 'd'
		&& (*(filename + strlen(filename) - 2)) == 'd'
		&& (*(filename + strlen(filename) - 1)) == 's'
		)
		flag = 0;
	else
	{
		cout << "The Tex is not Aphla or *.dds\n" << endl;
		system("pause");
		exit(0);
	}
}