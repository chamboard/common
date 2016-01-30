#define _S_R	0
#define _S_G	1
#define _S_B	2
#define _S_A	3

GLubyte *                          /* O - Bitmap data */
Load_BMP(const char *filename, 		/* I - File to load */
             BITMAPINFO **info)    /* O - Bitmap information */
{
    FILE             *fp;          /* Open file pointer */
    GLubyte          *bits;        /* Bitmap pixel bits */
    GLubyte          *ptr;         /* Pointer into bitmap */
#ifdef _BITMAP_LOADER_RGB_TO_BGR
    GLubyte          tempr,tempv,tempb;         /* Temporary variable to swap red and blue */
#endif
    int              x, y;         /* X and Y position in image */
    int              length;       /* Line length */
    uint64_t              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */
#ifdef _SHOW_LOADER
	printf("Opening bitmap..\n");
#endif
    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
        return (NULL);
#ifdef _SHOW_LOADER
	printf("Reading header..\n");
#endif
    /* Read the file header and any following bitmap information... */
    header.bfType      = read_word(fp);
    header.bfSize      = read_dword(fp);
    header.bfReserved1 = read_word(fp);
    header.bfReserved2 = read_word(fp);
    header.bfOffBits   = read_dword(fp);
	//
#ifdef _SHOW_LOADER
	printf("Reading bitmapinfo part\n");
#endif
    infosize = header.bfOffBits - 18;
    if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    (*info)->bmiHeader.biSize          = read_dword(fp);
    (*info)->bmiHeader.biWidth         = read_long(fp);
    (*info)->bmiHeader.biHeight        = read_long(fp);
    (*info)->bmiHeader.biPlanes        = read_word(fp);
    (*info)->bmiHeader.biBitCount      = read_word(fp);
    (*info)->bmiHeader.biCompression   = read_dword(fp);
    (*info)->bmiHeader.biSizeImage     = read_dword(fp);
    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biClrUsed       = read_dword(fp);
    (*info)->bmiHeader.biClrImportant  = read_dword(fp);
#ifdef _SHOW_LOADER
	printf("Reading Colors (skip)\n");
#endif
    if (infosize > 40)
	if (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1)
            {
            /* Couldn't read the bitmap header - return NULL... */
            free(*info);
            fclose(fp);
            return (NULL);
            }
#ifdef _SHOW_LOADER
	printf("Allocate memory, reading pixels (skip)\n");
#endif
    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    if ((bits = malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }
#ifdef _SHOW_LOADER     
	printf("Swappin [2]<->[1] color (green/blue)\n");
#endif
    length = (((*info)->bmiHeader.biWidth * 3 + 3) & ~3);
    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
        for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth; x > 0;x --, ptr += 3)
	    {
#ifdef _BITMAP_LOADER_RGB_TO_BGR
	    tempr   = ptr[0];
	    tempv  = ptr[1];
	    tempb = ptr[2];//
	    //

	    
	    ptr[0]=tempb;
	    ptr[1]=tempv;//b;
	    ptr[2]=tempr;//v;
#endif
	    //			
	    }				// noswap
#ifdef _SHOW_LOADER	
	printf("Closing [Done]\n");
#endif   
    fclose(fp);
    return (bits);
}
//
//
GLubyte* BMP_genRGBA8888_BUFFER(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H)    /* O - Bitmap information */
{
	//GLubyte i;
	GLubyte* dst_ptr;
	GLubyte this_R,this_G,this_B,this_A;
	GLubyte* w_ptr;
	uint64_t tot_bytes;
	//uint64_t iter;
	dst_ptr=malloc(source_W*source_H*4);					// 4 components
	//if (dst_ptr==NULL) { printf("Error inside,allocating (W=%u x H=%u bytes)\n",source_W,source_H);}
	w_ptr=dst_ptr;
	unsigned long ig=0;
	//i=0;
	tot_bytes=0;
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MODIFIED , OK on x86 linux , gimp export BMP , openGL MESA GLES mode..
	//source_BMP+=1;// why ?
	// end @@@@@@@@@@@@@@@
	#ifdef _BMP_DO_REVERSE
	// new : add BITMAP REVERSE function
		w_ptr=dst_ptr+((source_H-1)*source_W)*4;						// 1 line before the end
		#ifdef _SHOW_LOADER
		printf("Reverse pointer's value (start=%lu , pointsto=%lu)",dst_ptr,w_ptr);fflush(stdout);
		#endif
	#endif
	//iter=0;
	for(ig=0;ig<(source_W*source_H);ig++)
	{	
			
			this_B=source_BMP[0];w_ptr[_S_B]=this_B;tot_bytes++;	// 2
			this_G=source_BMP[1];w_ptr[_S_G]=this_G;tot_bytes++;	// 1
			this_R=source_BMP[2];w_ptr[_S_R]=this_R;tot_bytes++;	// 0
			this_A=source_BMP[3];w_ptr[_S_A]=this_A;tot_bytes++;	// alpha
			//
			#ifdef _BMP_DO_REVERSE
				w_ptr+=4;
				iter++;
				if(iter==source_W) { iter=0; w_ptr-=(source_W*4*2);}
			#else
				w_ptr+=4;
			#endif
			source_BMP+=4;
			tot_bytes++;
	}
	printf("...Generated : %lu bytes RGBA  ",(unsigned long)tot_bytes);
	return dst_ptr;
}
// BMP read with auto ALPHA ( alpha test color as input
//
GLubyte* BMP_genALPHA(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H,unsigned char genR,unsigned char genV,unsigned char genB,unsigned int opaque_value,unsigned char transparent_value)    /* O - Bitmap information */
{
	GLubyte i;
	GLubyte* dst_ptr;
	GLubyte this_R,this_G,this_B;
	GLubyte* w_ptr;
	uint64_t tot_bytes;
	//uint64_t iter;
	dst_ptr=malloc(source_W*source_H*4);					// 4 components
	//if (dst_ptr==NULL) { printf("Error inside,allocating (W=%u x H=%u bytes)\n",source_W,source_H);}
	w_ptr=dst_ptr;
	unsigned long ig=0;
	i=0;
	tot_bytes=0;
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MODIFIED , OK on x86 linux , gimp export BMP , openGL MESA GLES mode..
	//source_BMP+=1;// why ?
	// end @@@@@@@@@@@@@@@
	#ifdef _BMP_DO_REVERSE
	// new : add BITMAP REVERSE function
		w_ptr=dst_ptr+((source_H-1)*source_W)*4;						// 1 line before the end
		#ifdef _SHOW_LOADER
		printf("Reverse pointer's value (start=%lu , pointsto=%lu)",dst_ptr,w_ptr);fflush(stdout);
		#endif
	#endif
	//iter=0;
	for(ig=0;ig<(source_W*source_H);ig++)
	{	
			
			this_B=source_BMP[0];w_ptr[_S_B]=this_B;tot_bytes++;	// 2
			this_G=source_BMP[1];w_ptr[_S_G]=this_G;tot_bytes++;	// 1
			this_R=source_BMP[2];w_ptr[_S_R]=this_R;tot_bytes++;	// 0
			//w_ptr[_S_A]=0xff;// sure
			// blending alpha, with levels of tolerance
			//
			// DEV : commented
			
			i=0;
			while(i<4)
			{
				if(opaque_value<256)
				{
					w_ptr[_S_A]=(unsigned char) opaque_value;			// 3
					if((this_R==(genR+i))&&(this_G==(genV+i))&&(this_B==(genB+i)))
					{
						w_ptr[_S_A]=(GLubyte) (transparent_value)+(i*2);							// is (RGB)+i matching ? modulates transparency
						i=100;												// exit
					}
				}
				else { w_ptr[_S_A]=0xff;}									// force full opacity
				i++;										// is at full opacity , no RVB component transformation to alpha
			}
			
			// DEV
			//w_ptr[=0xff;
			// end DEV
			#ifdef _BMP_DO_REVERSE
				w_ptr+=4;
				iter++;
				if(iter==source_W) { iter=0; w_ptr-=(source_W*4*2);}
			#else
				w_ptr+=4;
			#endif
			source_BMP+=3;
			tot_bytes++;
			//
			/*
			if(ig<16) 
			{
				printf("RGB %2x %2x %2x\n",this_R,this_G,this_B);
			}
			* */
			//if(++i>255) i=0;
	}
	printf("...Generated : %lu bytes RGBA  ",(unsigned long)tot_bytes);
	return dst_ptr;
}
//
// BMP read with ALPHA from LUMA  alpha=((r+v+b)/3.0) ,r,v,b = r,g,b
//
GLubyte* BMP_genALPHA_fromRGB_LUMA(unsigned char* source_BMP,unsigned int source_W,unsigned int source_H)    /* O - Bitmap information */
{
	//GLubyte i;
	GLubyte* dst_ptr;
	GLubyte this_R,this_G,this_B;
	GLubyte* w_ptr;
	uint64_t tot_bytes;
	//uint64_t iter;
	dst_ptr=malloc(source_W*source_H*4);					// 4 components
	//if (dst_ptr==NULL) { printf("Error inside,allocating (W=%u x H=%u bytes)\n",source_W,source_H);}
	w_ptr=dst_ptr;
	unsigned long ig=0;
	//i=0;
	tot_bytes=0;
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MODIFIED , OK on x86 linux , gimp export BMP , openGL MESA GLES mode..
	//source_BMP+=1;// why ?
	// end @@@@@@@@@@@@@@@
	#ifdef _BMP_DO_REVERSE
	// new : add BITMAP REVERSE function
		w_ptr=dst_ptr+((source_H-1)*source_W)*4;						// 1 line before the end
		#ifdef _SHOW_LOADER
		printf("Reverse pointer's value (start=%lu , pointsto=%lu)",dst_ptr,w_ptr);fflush(stdout);
		#endif
	#endif
	//iter=0;
	for(ig=0;ig<(source_W*source_H);ig++)
	{	
			/*
			this_B=source_BMP[0];w_ptr[_S_B]=this_B;tot_bytes++;	// 2
			this_G=source_BMP[1];w_ptr[_S_G]=this_G;tot_bytes++;	// 1
			this_R=source_BMP[2];w_ptr[_S_R]=this_R;tot_bytes++;	// 0
			* */
			this_B=source_BMP[0];w_ptr[_S_B]=this_B;tot_bytes++;	// 2
			this_G=source_BMP[1];w_ptr[_S_G]=this_G;tot_bytes++;	// 1
			this_R=source_BMP[2];w_ptr[_S_R]=this_R;tot_bytes++;	// 0
			w_ptr[_S_A]=(this_B+this_G+this_R)/3;
			w_ptr[_S_A]=255.0;/*tanh(w_ptr[_S_A]/300.0)*255.0;*/
			// DEV
			//w_ptr[=0xff;
			// end DEV
			#ifdef _BMP_DO_REVERSE
				w_ptr+=4;
				iter++;
				if(iter==source_W) { iter=0; w_ptr-=(source_W*4*2);}
			#else
				w_ptr+=4;
			#endif
			source_BMP+=3;
			tot_bytes++;
			//
			/*
			if(ig<16) 
			{
				printf("RGB %2x %2x %2x\n",this_R,this_G,this_B);
			}
			* */
			//if(++i>255) i=0;
	}
	printf("...Generated : %lu bytes RGBA from LUMA  ",(unsigned long)tot_bytes);
	return dst_ptr;
}





/*
 * 'read_word()' - Read a 16-bit unsigned integer.
 */

static unsigned short     /* O - 16-bit unsigned integer */
read_word(FILE *fp)       /* I - File to read from */
    {
    unsigned char b0, b1; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
    }


/*
 * 'read_dword()' - Read a 32-bit unsigned integer.
 */

static unsigned int               /* O - 32-bit unsigned integer */
read_dword(FILE *fp)              /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }


/*
 * 'read_long()' - Read a 32-bit signed integer.
 */

static int                        /* O - 32-bit signed integer */
read_long(FILE *fp)               /* I - File to read from */
    {
    unsigned char b0, b1, b2, b3; /* Bytes from file */

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
    }

// 2D (videocore) utility
// image reverse
void Reverse_BMP(GLubyte* src_buffer,GLubyte* dst_buffer,unsigned int height,unsigned int pitch)
{
		unsigned int i=0;
		unsigned int xx,yy;
		for(yy=0;yy<height;yy++)
		{
			for(xx=0;xx<(pitch);xx++) 
			{ 
				dst_buffer[i]=*(src_buffer+(height*pitch)-(pitch*yy)-(pitch-xx));
				i++;
			}
		}
}
//
// latest
// ARGB8888 loader
//
uint8_t* EHSBMP_load8888(const char *filename, BITMAPINFO **info) 
{
    FILE             *fp;          /* Open file pointer */
    GLubyte          *bits;        /* Bitmap pixel bits */
    //GLubyte          *ptr;         /* Pointer into bitmap */
    //GLubyte          tempr,tempv,tempb;         /* Temporary variable to swap red and blue */
    //int              x, y;         /* X and Y position in image */
    //int              length;       /* Line length */
    uint64_t              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */
	#ifdef _SHOW_LOADER
		printf("EHSBMP_load888\t:Opening bitmap..\n");fflush(stdout);
	#endif
    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
	{
		#ifdef _SHOW_LOADER
		printf("[EHSBMP_load8888]:Error opening file\n");fflush(stdout);
		#endif
        return (NULL);
	}
	#ifdef _SHOW_LOADER
		printf("EHSBMP_load888\t:Reading header..\n");
	#endif
    /* Read the file header and any following bitmap information... */
    header.bfType      = read_word(fp);
    header.bfSize      = read_dword(fp);
    header.bfReserved1 = read_word(fp);
    header.bfReserved2 = read_word(fp);
    header.bfOffBits   = read_dword(fp);
	//
	#ifdef _SHOW_LOADER
		printf("EHSBMP_load888\t:Reading bitmapinfo part\n");
	#endif
    infosize = header.bfOffBits - 18;
    if ((*info = (BITMAPINFO *)malloc(sizeof(BITMAPINFO))) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    (*info)->bmiHeader.biSize          = read_dword(fp);
    (*info)->bmiHeader.biWidth         = read_long(fp);
    (*info)->bmiHeader.biHeight        = read_long(fp);
    (*info)->bmiHeader.biPlanes        = read_word(fp);
    (*info)->bmiHeader.biBitCount      = read_word(fp);
    (*info)->bmiHeader.biCompression   = read_dword(fp);
    (*info)->bmiHeader.biSizeImage     = read_dword(fp);
    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biClrUsed       = read_dword(fp);
    (*info)->bmiHeader.biClrImportant  = read_dword(fp);
	#ifdef _SHOW_LOADER
		printf("EHSBMP_load888\t:Reading Colors (skip)\n");
	#endif
    if (infosize > 40)
	if (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1)
            {
            /* Couldn't read the bitmap header - return NULL... */
            free(*info);
            fclose(fp);
            return (NULL);
            }
	#ifdef _SHOW_LOADER
		printf("EHSBMP_load888\t:Allocate memory, reading pixels\n");
	#endif
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)   bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8 * abs((*info)->bmiHeader.biHeight);
	#ifdef _SHOW_LOADER
	printf("EHSBMP_load888\t:bitsize:{%8.8d}\n",bitsize);
	#endif
    if ((bits = malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

	#ifdef _SHOW_LOADER	
		printf("EHSBMP_load888\t:Closing [Done]\n");
	#endif   
    fclose(fp);
    return (bits);
}

