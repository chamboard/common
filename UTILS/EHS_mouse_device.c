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
int ehs_mouse_device_fd=0;
//
int EHS_mdevice_init(const char* device_string)
{
	if((ehs_mouse_device_fd = open(device_string, O_RDONLY | O_NONBLOCK )) == -1) 
	{
		return -1;
	}
	return 1;
}
void EHS_mdevice_close(void)
{
	if (ehs_mouse_device_fd!=0) { close(ehs_mouse_device_fd); }
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
int EHS_mdevice_get(int* dst_x,int* dst_y,unsigned char* dst_buttons)
{
	char *ptr = malloc(128);//(char*)&ie;
	if(read(ehs_mouse_device_fd, &ptr[0], sizeof(struct input_event))!=-1)
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
int EHS_mdevice_get_EVENT(int32_t* dst_x,int32_t* dst_y,uint8_t* dst_buttons)
{
	int wheel_change;
	struct input_event* ie;
	//struct input_event* ptr;
	char *ptr = malloc(128);//(char*)&ie;
	ie=(struct input_event*) &ptr[0]; // had no cast
	*dst_buttons=0;	// inits button target at 0
	wheel_change=0;
	if(read(ehs_mouse_device_fd, &ptr[0], sizeof(struct input_event))!=-1)
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
			//*dst_x=0;
			//*dst_y=0;
			if(ie->code==0)	// X
			{
				*dst_x+=(int32_t) (ie->value);
			} 
			else if(ie->code==1)	// Y
			{
				*dst_y+=(int32_t) (ie->value);
			} 
			else if(ie->code==8)	// wheel
			{
				wheel_change+=(int32_t) (ie->value);
			}
			//*dst_y=(int) 
		}
		if(ie->type==EV_KEY) 
		{ 	
			//printf("button\n");
			if(ie->code==272) // button left
			*dst_buttons|=1<<(ie->value);		// 01 ou 10 == release/press LEFT

		}
		if(ie->type==EV_KEY) 
		{ 	
			//printf("button\n");
			if(ie->code==273) // button right
			*dst_buttons|=4<<(ie->value);     // 100 ou 1000 == release/press RIGHT

		}
		//
		return 1;
	}
	// nothing available
    // keeps target x,y the same, buttons is zeroed
	return -1;
}//
//
// newer function
//
int32_t EHS_mdevice_get_EVENTS(int32_t* dst_x,int32_t* dst_y,uint8_t* dst_buttons,int32_t* dst_wheel,uint32_t max_events)
{
	//int8_t wheel_change=0;
	struct input_event* ie;
	int32_t total_events;
	//struct input_event* ptr;
	char *ptr = malloc(128);//(char*)&ie;
	ie=(struct input_event*) &ptr[0];
	*dst_buttons=0;	// inits button
	total_events=0;
	//
	//wheel_change=(*dst_buttons&0xf0)>>4;
	while(max_events--)
	{	// does multiple reads up to max_events at once .
		if(read(ehs_mouse_device_fd, &ptr[0], sizeof(struct input_event))!=-1)
		{
			//
			if(ie->type==EV_REL) 
			{ 		
				if(ie->code==0)	// X
				{
					*dst_x+=(int32_t) (ie->value);
				} else if(ie->code==1)	// Y
				{
					*dst_y+=(int32_t) (ie->value);
				} else if (ie->code==8)
				{
					*dst_wheel+=(int32_t) (ie->value);	// incs/dec wheel data pointed		
				}
				//*dst_y=(int) 
			}
			if(ie->type==EV_KEY) 
			{ 	
				//printf("button\n");
				if(ie->code==272) // button left
				*dst_buttons|=1<<(ie->value);		// 01 ou 10 == release/press LEFT
				max_events=0;						// force exit. button change hve to be managed outside
			}
			if(ie->type==EV_KEY) 
			{ 	
				//printf("button\n");
				if(ie->code==273) // button right
				*dst_buttons|=4<<(ie->value);     // 100 ou 1000 == release/press RIGHT
				max_events=0;						// force exit. button change hve to be managed outside , prior to more updates
			}
			//
			total_events++;
		}
	}
	//
	free(ptr);
	// nothing available
    // keeps target x,y the same, buttons is zeroed
	return total_events;
}//
//
