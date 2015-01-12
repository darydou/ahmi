#include <malloc.h>
#include <string.h>
#include <gl/glut.h>

#include "ALLHeader.h"
#include "JoggleLayer.h"
#include "WriteChinese.h"
#include "WriteEnglish.h"
#include "DrawCircle.h"
#include "DrawPointer.h"

static GLint    ImageWidth = 1024;
static GLint    ImageHeight = 768;
static GLint    PixelLength = ImageWidth * ImageHeight * 3;
static GLubyte* PixelData;
#define FileName "Show.bmp"


#define PICNAME0   "test.dds"
#define PICNAME1   "ALPHA5.data"
#define PICNAME2   "arrow.dds"
#define PICNAME3   "gauge-back.dds"
#define PICNAME4	"1111.dds"
#define PICNAME5	"2222.dds"


U16 * FrameBuffer = new U16[ImageWidth * ImageHeight];