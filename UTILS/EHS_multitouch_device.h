// multitouch device (DEV)
// functions
int multitouch_init(const char* device_string);							// success =1 
void multitouch_close(void);
int multitouch_get(MTpoint_t* tmpP);
#include "multitouch_device.c"
