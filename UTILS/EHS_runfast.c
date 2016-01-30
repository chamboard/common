static void EHS_PI_B_PLUS_enable_runfast(void)
	{
		uint32_t fpscr;
		__asm__ __volatile__ ("vmrs %0,fpscr" : "=r" (fpscr));
		fpscr |= 0x03000000;
		__asm__ __volatile__ ("vmsr fpscr,%0" : :"ri" (fpscr));
		//
		printf("[EHS_BPLUS_enable_runfast]:ON\n");
	}