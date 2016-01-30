/*
#include <stdio.h>
#include <stdlib.h>
*/
#include <fcntl.h>
#include <linux/input.h>

//#define MOUSEFILE "/dev/input/event4\0" //"/dev/input/mouse0\0"
#define _MD_BUTTON_LEFT		0x01
#define _MD_BUTTON_RIGHT	0x02
#define _MD_BUTTON_MIDDLE	0x04

//
int mouse_device_fd=0;
//
int mdevice_init(const char* device_string)
{
	if((mouse_device_fd = open(device_string, O_RDONLY | O_NONBLOCK )) == -1) 
	{
		return -1;
	}
	return 1;
}
void mdevice_close(void)
{
	if (mouse_device_fd!=0) { close(mouse_device_fd); }
}
// rem (nota from web
//
/*
struct input_event ev[2];


ev[0].type = EV_ABS;
ev[0].code = ABS_X;
ev[0].value = 1023;
ev[1].type = EV_ABS;
ev[1].code = ABS_Y;
ev[1].value = 767;
*/
int mdevice_get(int* dst_x,int* dst_y,unsigned char* dst_buttons)
{
	char *ptr = malloc(128);//(char*)&ie;
	if(read(mouse_device_fd, &ptr[0], sizeof(struct input_event))!=-1)
	{
		*dst_buttons=(unsigned char) ptr[0];
		*dst_x=(int) ptr[1];
		*dst_y=(int) ptr[2];
		//
		//int ii;
		//printf("\n");
		//for(ii=8;ii<14;ii++) { printf("[%02x] ",(unsigned char) ptr[ii]&128);fflush(stdout);}
		//printf("\n{%d}\n",(char) ptr[8]);
		//
		return 1;
	}
	// nothing available
	*dst_buttons=0;
	*dst_x=0;
	*dst_y=0;
	return -1;
}//
//
int mdevice_get_EVENT(int* dst_x,int* dst_y,unsigned char* dst_buttons)
{
	struct input_event* ie;
	//struct input_event* ptr;
	char *ptr = malloc(128);//(char*)&ie;
	ie=&ptr[0];
	if(read(mouse_device_fd, &ptr[0], sizeof(struct input_event))!=-1)
	{
		//*dst_buttons=(unsigned char) ptr[0];
		//*dst_x=(int) ptr[1];
		//*dst_y=(int) ptr[2];
		//
		//printf("\n#####################\n");
		//int ii;
		//for(ii=0;ii<sizeof(struct input_event);ii++) { printf("%3.3d ",ptr[ii]);fflush(stdout);}
		// printf("\n###### END ########## (%d)(sizeof=%d) , %d\n",ie->type&EV_REL,sizeof(struct input_event),ie->type);
		//printf("EV->type=%04x\n",(unsigned char) ie->type);
		if(ie->type==EV_REL) 
		{ 		
			//printf("val-->%3.3d code{%3.3d}",ie->value,ie->code);
			*dst_x=0;
			*dst_y=0;
			if(ie->code==0)	// X
			{
				*dst_x=ie->value;
			} 
			if(ie->code==1)	// X
			{
				*dst_y=-(ie->value);
			} 
			//
			return 1;
			//*dst_y=(int) 
		}
		//fflush(stdout);
		return -1;
	}
	// nothing available
	*dst_buttons=0;
	*dst_x=0;
	*dst_y=0;
	return -1;
}//
//
