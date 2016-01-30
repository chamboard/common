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