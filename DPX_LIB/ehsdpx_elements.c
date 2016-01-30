//
// new : mouse cursor , create/ update /delete
//
int EHS_genDPXcursor(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t layer)
{
    int ret;
    VC_RECT_T	dst_rect;
	VC_RECT_T	src_rect;
	//
    uint32_t dummy;
	int cursor_pitch = ALIGN_UP((32) *4, 32);// first 32 is width for pitch
	//int aligned_height = ALIGN_UP(height, 16);
    //
    vars->resource = vc_dispmanx_resource_create( VC_IMAGE_ARGB8888, 32, 32, &dummy );
	assert( vars->resource );
    vc_dispmanx_rect_set( &dst_rect, 0, 0, 32, 32);//x,y,w,h
    ret = vc_dispmanx_resource_write_data( vars->resource, VC_IMAGE_ARGB8888, cursor_pitch /* width*4bytes*/, vars->image, &dst_rect );
	assert( ret == 0 );
    vars->update = vc_dispmanx_update_start( 10 );						// priority ..(not clear) , return a handler (used to remove bitmap ressource)
    assert( vars->update );
	// set src rect
    vc_dispmanx_rect_set( &src_rect, 0, 0, 32 | (32 << 16), 32|(32 << 16) );	// sets SRC with pitch modifier
	// set dst rect
    vc_dispmanx_rect_set( &dst_rect, x, y, 32, 32 );  // dest RECT : computes position
	vars->layer=layer;			// records layer
    vars->element = vc_dispmanx_element_add(		vars->update,
                                                vars->display,
                                                vars->layer,               // layer
                                                &dst_rect,
                                                vars->resource,
                                                &src_rect,
                                                DISPMANX_PROTECTION_NONE,
                                                0/*&alpha*/,
                                                NULL,             // clamp
                                                VC_IMAGE_ROT0 );
    // vc_dispmanx_element_update();
    //
#ifdef _DPX_LIB_DEBUG_ON
    printf("genDPXcursor\t:Generated cursor  :\tVC_RECT T %d %d %d %d\n",dst_rect.x,dst_rect.y,dst_rect.width,dst_rect.height);
#endif
    // submit changes
    ret = vc_dispmanx_update_submit_sync( vars->update );				// updates the display (started with update_start)
	assert( ret == 0 );
	return 1;		// returns element handle
}
//
//
int EHS_setDPXcursor(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h)
{
	//RECT_VARS_T vars=svars;
	int ret;
	VC_RECT_T	src_rect,dst_rect;
	//
	
	vars->update = vc_dispmanx_update_start( 10 );
	//ret = vc_dispmanx_element_remove( vars->update, vars->element );	// removes the bitmap rect vars->element
	// change X x
	 vc_dispmanx_rect_set( &src_rect, 0, 0, 32 | (32 << 16), 32|(32 << 16) );	
	 //
	dst_rect.x=x;
	dst_rect.y=y;
	dst_rect.width=w;
	dst_rect.height=h;
	//
    vc_dispmanx_element_change_attributes( vars->update,vars->element,0,vars->layer,120,&dst_rect,&src_rect,0,VC_IMAGE_ROT0);
	//ret = vc_dispmanx_update_submit_sync( vars->update );			// looks like beeing sync'd														// 100ms .. to check
	ret = vc_dispmanx_update_submit( vars->update,0,0);
	return 1;
}
//
int EHS_initDPXcontext(RECT_VARS_T* vars,uint32_t need_bcm_host_init)
{
	int ret;
	int screen=0;
	if(need_bcm_host_init) 
	{ 
		bcm_host_init();
		#ifdef _DPX_LIB_DEBUG_ON
		printf("initBCMHOST\n");
		#endif
	}
	#ifdef _DPX_LIB_DEBUG_ON
	printf("initDPXcontext\t:Open display[%i]...\n", screen );
	#endif
    vars->display = vc_dispmanx_display_open( screen );
    ret = vc_dispmanx_display_get_info( vars->display, &vars->info);
    assert(ret == 0);
	#ifdef _DPX_LIB_DEBUG_ON
    printf( "initDPXcontext\t:Display is %d x %d\n", vars->info.width, vars->info.height );
	#endif
	return 1;
}
int EHS_closeDPXcontext(RECT_VARS_T* vars)
{
	int ret;
	vars->update = vc_dispmanx_update_start( 10 );
    assert( vars->update );
    ret = vc_dispmanx_element_remove( vars->update, vars->element );	// removes the bitmap rect vars->element
    assert( ret == 0 );
    ret = vc_dispmanx_update_submit_sync( vars->update );
    assert( ret == 0 );
	if(vars->resource!=0) { ret = vc_dispmanx_resource_delete( vars->resource ); }// deletes if was created
    assert( ret == 0 );
    ret = vc_dispmanx_display_close( vars->display );
    assert( ret == 0 );
	return 1;
}
int EHS_destroyDPXelement(RECT_VARS_T* vars)
{
	int ret;
	//vars->update = vc_dispmanx_update_start( 10 );
    //assert( vars->update );
    if(vars->element!=0) 
	{
		ret = vc_dispmanx_element_remove( vars->update, vars->element );	// removes the bitmap rect vars->element
		assert( ret == 0 );
		printf("{element}");
	}	
	return 1;
}
int EHS_destroyDPXresource(RECT_VARS_T* vars)
{
	int ret;
	if(vars->resource!=0) 
	{ 
		ret = vc_dispmanx_resource_delete( vars->resource ); 
		printf("{resource}");
	}// deletes if was created
    return ret;
}
int EHS_closeDISPLAY(RECT_VARS_T* vars)
{
	int ret;
	ret = vc_dispmanx_display_close( vars->display );
	printf("CLose display()\n");
    assert( ret == 0 );
	return 1;
}
//
// general
//
int EHS_genDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h,uint32_t layer)
{
	int ret;
    VC_RECT_T	dst_rect;
	VC_RECT_T	src_rect;
	//
    uint32_t dummy;
	int cursor_pitch = ALIGN_UP((w) * 4, 32);// first 32 is width for pitch
	//
	vars->created_pitch=cursor_pitch;				// stores for future updates
	vars->created_w=w;
	vars->created_h=h;
	//int aligned_height = ALIGN_UP(height, 16);
    //
    vars->resource = vc_dispmanx_resource_create( VC_IMAGE_ARGB8888, w, h, &dummy );
	assert( vars->resource );
    vc_dispmanx_rect_set( &dst_rect, 0, 0, w, h);//x,y,w,h
    ret = vc_dispmanx_resource_write_data( vars->resource, VC_IMAGE_ARGB8888, cursor_pitch /* width*4bytes*/, vars->image, &dst_rect );
	assert( ret == 0 );
    vars->update = vc_dispmanx_update_start( 10 );						// priority ..(not clear) , return a handler (used to remove bitmap ressource)
    assert( vars->update );
	// set src rect
    vc_dispmanx_rect_set( &src_rect, 0, 0, w | (w << 16), h|(h << 16) );	// sets SRC with pitch modifier
	// set dst rect
    vc_dispmanx_rect_set( &dst_rect, x, y, w, h );  // dest RECT : computes position
	vars->layer=layer;			// records layer
    vars->element = vc_dispmanx_element_add(		vars->update,
                                                vars->display,
                                                vars->layer,               // layer
                                                &dst_rect,
                                                vars->resource,
                                                &src_rect,
                                                DISPMANX_PROTECTION_NONE,
                                                0/*&alpha*/,
                                                NULL,             // clamp
                                                VC_IMAGE_ROT0 );
    // vc_dispmanx_element_update();
    //
#ifdef _DPX_LIB_DEBUG_ON
    printf("genDPXelement\t:Generated element  :\tVC_RECT T %d %d %d %d\n",dst_rect.x,dst_rect.y,dst_rect.width,dst_rect.height);
#endif
    // submit changes
    ret = vc_dispmanx_update_submit_sync( vars->update );				// updates the display (started with update_start)
	assert( ret == 0 );
	return 1;		// returns element handle
}
int EHS_setDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h)
{
	int ret;
	VC_RECT_T	src_rect,dst_rect;
	vars->update = vc_dispmanx_update_start( 10 );
	 vc_dispmanx_rect_set( &src_rect, 0, 0, w |(w << 16), h|(h << 16) );	
	 //
	dst_rect.x=x;
	dst_rect.y=y;
	dst_rect.width=w;
	dst_rect.height=h;
	//
    vc_dispmanx_element_change_attributes( vars->update,vars->element,0,vars->layer,120,&dst_rect,&src_rect,0,VC_IMAGE_ROT0);
	ret = vc_dispmanx_update_submit( vars->update,0,0); // not sync'd
	return 1;
}
//
// group actions
//
void EHS_startUPDATE(RECT_VARS_T* vars)
{
	vars->update = vc_dispmanx_update_start( 10 );
}
int EHS_submitUPDATE(RECT_VARS_T* vars,uint32_t mode)
{
	if(mode==0)
	{
		return  vc_dispmanx_update_submit( vars->update,0,0);	// not sync'd
	}
	return vc_dispmanx_update_submit_sync( vars->update );		// sync to vrefresh
}
int EHS_updateDPXelement(RECT_VARS_T* vars,uint32_t x,uint32_t y,uint32_t w,uint32_t h)  // x,y changed
{
	int ret;
	VC_RECT_T	src_rect,dst_rect;
	// uses @ creation sizes for source
	vc_dispmanx_rect_set( &src_rect, 0, 0, vars->created_w |(vars->created_w << 16), vars->created_h|(vars->created_h << 16) );	
	 //
	dst_rect.x=x;
	dst_rect.y=y;
	dst_rect.width=w;	// uses set sources
	dst_rect.height=h;
	// (bit 0 layer, bit 1 opacity, [bit 2 dest rect], bit 3 src rect, bit 4 mask, bit 5 transform
    return vc_dispmanx_element_change_attributes( vars->update,vars->element, 4 ,vars->layer,120,&dst_rect,&src_rect,0,VC_IMAGE_ROT0);
	//
}
// reszet layer
int EHS_relayerDPXelement(RECT_VARS_T* vars,int32_t layer)
{
	return vc_dispmanx_element_change_layer (vars->update,vars->element,layer );
}
// rewrite data to already created element (update VC memory datas)
int EHS_rewriteDPXelement(RECT_VARS_T* vars)
{
	int ret;
    VC_RECT_T	dst_rect;
	//	
	assert( vars->resource );
    vc_dispmanx_rect_set( &dst_rect, 0, 0, vars->created_w, vars->created_h);//x,y,w,h
    return vc_dispmanx_resource_write_data( vars->resource, VC_IMAGE_ARGB8888, vars->created_pitch , vars->image, &dst_rect );
}