int EHS_mdevice_init(const char* device_string);
void EHS_mdevice_close(void);
int EHS_mdevice_get(int* dst_x,int* dst_y,unsigned char* dst_buttons);
int EHS_mdevice_get_EVENT(int32_t* dst_x,int32_t* dst_y,uint8_t* dst_buttons);
int32_t EHS_mdevice_get_EVENTS(int32_t* dst_x,int32_t* dst_y,uint8_t* dst_buttons,int32_t* dst_wheel,uint32_t max_events);	// gets up to max_events. cuts it if button changed
#include "EHS_mouse_device.c"
