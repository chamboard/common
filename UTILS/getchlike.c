//
int kbhit(void)
{
	 int i;
	 ioctl(0, FIONREAD, &i);
	 return i; /* return a count of chars available to read (from stdin=fd/0) */
}
// getch() like test
//

void test(void)
	{
		 int i = 0;
		 int c=0;
		 system("stty raw -echo");
		 printf("enter 'q' to quit \n");
		 for (;c!='q';i++) 
		 {
			if (kbhit()) {
				c=getchar();
			   printf("\n got %c, on iteration %d",c, i);
			}
		}
		 system("stty cooked echo");
	}
// getch() like : system cook ,start
void getch_start(void)	{  system("stty raw -echo"); }
void getch_stop(void) { system("stty cooked echo"); }

unsigned char getch_try(void)
{
	int c=0;
	if (kbhit()) { c=getchar(); }
	return (unsigned char) c;		// one char from queue only
}	
