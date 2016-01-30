//
int multitouch_init(const char* device_string)
{
	int rd;
	struct input_event ev[64];
	char name[256] = "Unknown";
	if ((multitouch_device_fd = open(device_string, O_RDONLY | O_NONBLOCK)) < 0) 	// added : NONBLOCK reads
	{
		printf("multitouch : can't open specified point {%s}",device_string);
		return -1;
	}
	ioctl(multitouch_device_fd, EVIOCGNAME(sizeof(name)), name);
	printf("Input device name: [%s] OPEN OK\n", name);
	//
	rd = read(multitouch_device_fd, ev, sizeof(struct input_event) * 64);			// wipes out datas if any
	
	return 1;
}
void multitouch_close(void)
{
	if (multitouch_device_fd!=0) { close(multitouch_device_fd); }
}
//
int multitouch_get(MTpoint_t* tmpP)
{
	MTpoint_t* loc_s;
	int rd, i;
	struct input_event ev[64];
	//MTpoint_t tmpP[10]={ [0 ... 9] = {.x=0, .y=0, .id=-1 }};												// 10 slots MAX
	int contacts_count=0;												// dev : contact counts ( num slots total)
	//
	
		rd = read(multitouch_device_fd, ev, sizeof(struct input_event) * 64);
		if (rd < (int) sizeof(struct input_event)) 
		{
			// perror("\nMultitouch_read: ERROR\n");
			return -1;
		}
		//printf("Read:%d\n",rd);
		for (i = 0; i < rd / sizeof(struct input_event); i++)
		{
			
			if (ev[i].type == EV_SYN) 									// 
			{
				
				if (SYN_MT_REPORT==ev[i].code) 
				// ******************************* for PROTOCOL A multitouch
				{ // MT_Sync : Multitouch event end
				   
				} 
				else if (SYN_REPORT==ev[i].code) 
				{ // ******************************* for PROTOCOL B multitouch (eGalax/ rpi)
					
				}
			} 
			else if (ev[i].type == EV_MSC && (ev[i].code == MSC_RAW || ev[i].code == MSC_SCAN)) 
			{
				
			} 
			else if(ev[i].type==1)
			{
				if(ev[i].code==330) 
				{
					loc_s=tmpP+multitouch_current_slot;
					loc_s->click=ev[i].value;
				}
			}
			else 
			{				
					
					//
					if (ev[i].code==ABS_MT_SLOT ) 
					{
						if(ev[i].value<10) { multitouch_current_slot = ev[i].value; }			// limit 10 points (dev) : change/set SLOT
												
					}
					if (ev[i].code==ABS_MT_TRACKING_ID ) 
					{
						loc_s=tmpP+multitouch_current_slot;
						loc_s->id = ev[i].value; // release  if -1
						
					}
					if (ev[i].code==ABS_MT_POSITION_X) 
					{  
						loc_s=tmpP+multitouch_current_slot;
						loc_s->x  = ev[i].value;
					}
					if (ev[i].code==ABS_MT_POSITION_Y)   
					{
						loc_s=tmpP+multitouch_current_slot;
						loc_s->y  = ev[i].value;
					}
			
			} 
			//printf(" ../.. \n");
		}
	//
	return 1;
}
