// multitouch device (DEV)
#include <fcntl.h>
#include <linux/input.h>
//
int multitouch_device_fd=0;												// global multitouch FD
int multitouch_current_slot=0;											// current multitouch SLOT 
typedef struct { 
	int x; 
	int y; 
	int id;
	int click; 
} MTpoint_t;
//
int multitouch_init(const char* device_string);							// success =1 
void multitouch_close(void);
int multitouch_get(MTpoint_t* tmpP);
#include "multitouch_device.c"
