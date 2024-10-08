/*
 * Filename: swc_input.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Software component for input
 * name: swc_Input
 * shortname: Input
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_input.h"



/* USER CODE START SWC_INPUT_INCLUDE */

/* USER CODE END SWC_INPUT_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_INPUT_USERDEFINITIONS */
#include "clock.h"
/* USER CODE END SWC_INPUT_USERDEFINITIONS */



/*
 * component: swc_Input
 * cycletime: 50
 * description: Runnable for input to clock
 * events: 
 * name: INPUT_Clock_input_run
 * shortname: Clock_input
 * signalIN: 
 * signalOUT: so_ButtonEvent
 * task: tsk_io
 */
void INPUT_Clock_input_run(RTE_event ev){
	
	/* USER CODE START INPUT_Clock_input_run */
    
    RC_t result = RTE_SC_INPUT_pullPort(&SO_BUTTONEVENT_signal);
    
    if (result != RC_SUCCESS)
    {      
        UART_LOG_PutString("Invalid input data"); 
    }
    
    /* USER CODE END INPUT_Clock_input_run */
}

/* USER CODE START SWC_INPUT_FUNCTIONS */

/* USER CODE END SWC_INPUT_FUNCTIONS */

