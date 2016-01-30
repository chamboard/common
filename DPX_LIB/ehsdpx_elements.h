//
// VC dispmanX utility
//
//#define _DPX_LIB_DEBUG_ON << debug messages, on/off . default off, setup at compile time
//
// init, create,set position, destroy+close functions
//
//
#include "bcm_host.h"
#include "assert.h"
//
// A simple demo using dispmanx to display an overlay
//#define _EHS_ELEMENTS_INIT_BCM_HOST
//
#ifndef ALIGN_UP
	#define ALIGN_UP(x,y)  ((x + (y)-1) & ~((y)-1))
#endif
//
//
//
typedef struct
{
    DISPMANX_DISPLAY_HANDLE_T   display;
    DISPMANX_MODEINFO_T         info;
    void                       *image;
    DISPMANX_UPDATE_HANDLE_T    update;
    DISPMANX_RESOURCE_HANDLE_T  resource;
    DISPMANX_ELEMENT_HANDLE_T   element;
    uint32_t                    vc_image_ptr;
	uint32_t					layer;
	// new
	int32_t created_pitch;
	int32_t created_w;
	int32_t created_h;

} RECT_VARS_T;
//
// global dpx context data : 
//
RECT_VARS_T	 gDPX_DESCR[64];	// up to 64 dispmanx resources. dispamnx resource 0 holds display's handle
//
int EHS_initDPXcontext(RECT_VARS_T* vars,uint32_t need_bcm_host_init);
int EHS_closeDPXcontext(RECT_VARS_T* vars);
int EHS_genDPXcursor(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t layer);
int EHS_setDPXcursor(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h);
// general dpx functions
int EHS_genDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h,uint32_t layer);
int EHS_setDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h);// any param == -1 : keep unchanged
//
// update : start, stop
//
void EHS_startUPDATE(RECT_VARS_T* vars);
//
// inbetween, element change
int EHS_updateDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h);//  updates x,y,w,h , inside startUPDATE/submitUPDATE (group update)
int EHS_relayerDPXelement(RECT_VARS_T* vars,int32_t layer);
int EHS_rewriteDPXelement(RECT_VARS_T* vars);
//
int EHS_destroyDPXelement(RECT_VARS_T* vars);	// called before destroy resource
int EHS_destroyDPXresource(RECT_VARS_T* vars);	// called after destroy element, and before close display
//
// update end : mode= : not synced, else : sync'd
//
int EHS_submitUPDATE(RECT_VARS_T* vars,uint32_t mode);
//
//
//
int EHS_closeDISPLAY(RECT_VARS_T* vars);
