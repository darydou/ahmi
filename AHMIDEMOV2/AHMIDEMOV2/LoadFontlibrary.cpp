       //将字体库装换成64位的数据GB2312
#include "stdafx.h"
#include "LoadFontlibrary.h"

void  LoadChineseLibrary(std::string  filenamein, std::string filenameout, U8 size)
{
	ifstream  infile;
	infile.open(filenamein, std::ios::binary);
	U32 i = 0;
	U64 temp;
	char * buffer = new char[4];
	U16 rominfosize = chinesefontsize * size * size >> 6;
	U64 *rominfo = new U64[rominfosize];
	
	while (!infile.eof())// && i<Pixellength)
	{
		infile.read(buffer, 4 * sizeof(char));
		temp = ((U64)((U8)buffer[0]) << 56)
			+ ((U64)((U8)buffer[1]) << 48)
			+ ((U64)((U8)buffer[2]) << 40)
			+ ((U64)((U8)buffer[3]) << 32);
		infile.read(buffer, 4 * sizeof(char));
		temp = temp + ((U64)((U8)buffer[0]) << 24)
			+ ((U64)((U8)buffer[1]) << 16)
			+ ((U64)((U8)buffer[2]) << 8)
			+ ((U64)((U8)buffer[3]) << 0); 
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
	infilecin.close();
}

void  LoadEnglishLibrary(std::string filenamein, std::string filenameout, U8 width, U8 height)
{
	ifstream infile;
	infile.open(filenamein, std::ios::binary);
	U32 i = 0;
	char buffer[4];
	U16  rominfosize = englishfontsize*width*height >> 5;
	U32 *rominfobuffer = new U32[rominfosize];
	while (!infile.eof())
	{
		infile.read(buffer, sizeof(char) * 4);
		*(rominfobuffer + i) = static_cast<U32>(static_cast<U8>(buffer[0])) << 24 | 
			static_cast<U32>(static_cast<U8>(buffer[1])) << 16 | 
			static_cast<U32>(static_cast<U8>(buffer[2])) << 8  | 
			static_cast<U32>(static_cast<U8>(buffer[3]));
		i++;
	}
	infile.close();
	ofstream outfile(filenameout);
	i = 0;
	while (i < rominfosize)
	{
		outfile << '0' << 'x' << std::hex << *(rominfobuffer + i) <<','<< endl;
		i++;
	}
	outfile.close();
}