//
#define _EHS_BITMAP_UTILS_ALPHA_FROM_COLOR 		0
#define _EHS_BITMAP_UTILS_ALPHA_FROM_RGB_LUMA	1
//
typedef struct {
	unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;	
} BITMAPFILEHEADER;
//
typedef struct {
	unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
    
} BITMAPHEADER;
//
typedef struct {
	BITMAPHEADER  bmiHeader;
	unsigned char bmiColors[256];										// dev	
} BITMAPINFO;

//
static unsigned short read_word(FILE *fp);
static unsigned int   read_dword(FILE *fp);
static int            read_long(FILE *fp);
//
#ifndef GLubyte
	typedef uint8_t GLubyte;
#endif
//
// Load_BMP : export options (gimp) : RGB 24 bits, no alpha. Do not write colorspace information ! ( 1 byte offset if ommited )
GLubyte * Load_BMP(const char *filename,BITMAPINFO **info);				// loads a bitmap
uint8_t* EHSBMP_load8888(const char *filename,BITMAPINFO **info);				// loads a bitmap 32 bits (alpha)
GLubyte* BMP_genALPHA(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H,unsigned char genR,unsigned char genV,unsigned char genB,unsigned int opaque_value,unsigned char transparent_value);    /* O - Bitmap information */
// generates a uint32_t buffer from rgb data , using rgb luma for alpha generation
GLubyte* BMP_genALPHA_fromRGB_LUMA(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H);
// image reverse / videocore utility
void Reverse_BMP(GLubyte* src_buffer,GLubyte* dst_buffer,unsigned int height,unsigned int pitch);	// upside down (windows bitmap for correct display) pitch=width*( "bpp bytes" ). RGB888 = 3 , width=128 :: pitch=>384
//
// last addition, gen a buffer for RGBA8888 bitmap loaded (copy temp ptr to dst created buffer
GLubyte* BMP_genRGBA8888_BUFFER(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H);

//
//#include "bitmap_utils.c"
