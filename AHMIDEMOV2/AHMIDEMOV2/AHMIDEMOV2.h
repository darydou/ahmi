#include <malloc.h>
#include <string.h>
#include <gl/glut.h>

#include "ALLHeader.h"
#include "JoggleLayer.h"
#include "WriteChinese.h"
#include "WriteEnglish.h"

static GLint    ImageWidth = 1024;
static GLint    ImageHeight = 768;
static GLint    PixelLength = 1024 * 768 * 3;
static GLubyte* PixelData;
#define FileName "Show.bmp"


#define PICNAME0   "test.dds"
#define PICNAME1   "ALPHA5.data"
#define PICNAME2   "arrow.dds"




U16 * FrameBuffer = new U16[1024 * 768];