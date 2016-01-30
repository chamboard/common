int mdevice_init(const char* device_string);
void mdevice_close(void);
int mdevice_get(int* dst_x,int* dst_y,unsigned char* dst_buttons);
int mdevice_get_EVENT(int* dst_x,int* dst_y,unsigned char* dst_buttons);
//
