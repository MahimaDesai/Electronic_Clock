/*
 * Filename: sc_display_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Signal class for display
 * name: sc_Display
 * shortname: Display
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_display_type.h"



/* USER CODE START SC_DISPLAY_INCLUDE */
#include "stdlib.h"
#include "sp_common.h"
/* USER CODE END SC_DISPLAY_INCLUDE */




/* USER CODE START SC_DISPLAY_USERDEFINITIONS */

/* USER CODE END SC_DISPLAY_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_DISPLAY signal  ****************
 *****************************************************************************************/
 
 
/**
 * Default OUT driver API
 */
inline RC_t SC_DISPLAY_driverOut(const SC_DISPLAY_data_t  *const data)
{
	/* USER CODE START driverOutSC_DISPLAY */
       
    uint16_t local_hour_value    =   data->hour.value;
            
    TFT_colors_t    bg_color_hour    =   data->hour.font_type.bg_colour;
    TFT_colors_t    txt_color_hour   =   data->hour.font_type.widget_colour; 
    TFT_setTextSize(3);
    TFT_setCursor(TFT_width()/6, TFT_height()/2);
    TFT_setColors(txt_color_hour, bg_color_hour);   
    TFT_printf( "%d%d", (local_hour_value/10), (local_hour_value%10));
    
    
    char blinker    =   ':';
    static uint8_t toggle   =   0;
    static uint16_t blinker_count    =   0;   
    if(toggle   ==  0)
    {
        blinker =   ':';
        toggle  =   1;
    }
    else
    {
        blinker =   ' ';
        toggle  =    0;
    }
    TFT_setTextSize(3);
    TFT_setCursor(TFT_width()/2,TFT_height()/2);
    TFT_setColors(WHITE, BLACK);
    TFT_printf( "%c", blinker);
    
    
    uint16_t local_minute_value  =   data->minute.value;
    
    TFT_colors_t    bg_color_min    =   data->minute.font_type.bg_colour;
    TFT_colors_t    txt_color_min   =   data->minute.font_type.widget_colour;  
    TFT_setTextSize(3);
    TFT_setCursor(2 * TFT_width()/3,TFT_height()/2);
    TFT_setColors(txt_color_min, bg_color_min);   
    TFT_printf( "%d%d",(local_minute_value/10), (local_minute_value%10));
    
    
	//Scale application data to drive format

	//Write scaled data to driver

	return RC_SUCCESS;
	/* USER CODE END driverOutSC_DISPLAY */
}



