#include "ALLHeader.h"
#include <fstream>
#include <vector>
#include <string>




const U16 chinesefontsize = 8178;
const U16 englishfontsize = 128;



void  LoadChineseLibrary(std::string filenamein, std::string filenameout, U8 size);
void  LoadEnglishLibrary(std::string filenamein, std::string filenameout, U8 width, U8 height);