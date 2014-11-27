       //将字体库装换成64位的数据GB2312
#include "stdafx.h"
#include "LoadFontlibrary.h"

void  LoadChineseLibrary ( char *filenamein,char *filenameout, U8 size)
{
	ifstream  infile;
	infile.open(filenamein, std::ios::binary);
	U32 i = 0;
	U64 temp;
	char * fuck = new char[4];
	U16 rominfosize = chinesefontsize * size * size >> 6;
	U64 *rominfo = new U64[rominfosize];
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
	infile.close();
	ofstream infilecin(filenameout);
	i = 0;
	U32 temp1, temp2;
	while (i < rominfosize)
	{
		temp1 = ((U64)(*(rominfo + i) >> 32) & 0xffffffff);
		infilecin << '0';
		infilecin << 'x';
		infilecin << std::hex << temp1;
		infilecin << ',' << endl;
		temp2 = (*(rominfo + i) & 0xffffffff);
		temp = *(rominfo + i);
		infilecin << '0';
		infilecin << 'x';
		infilecin << std::hex << temp2;
		infilecin << ',' << endl;
		i++;
	}
}