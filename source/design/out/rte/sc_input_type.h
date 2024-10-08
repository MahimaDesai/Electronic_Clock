
/*
 * Filename: sc_input_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Signal class for clock input
 */

#ifndef _H_DEFINE_SC_INPUT_TYPE
#define _H_DEFINE_SC_INPUT_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_INPUT_INCLUDES */

/* USER CODE END SC_INPUT_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_INPUT signal    
 **********************************************************************/

/* USER CODE START SC_INPUT_USERDEFINITIONS */

/* USER CODE END SC_INPUT_USERDEFINITIONS */

typedef 
/* USER CODE START SC_INPUT_SIGNALDATADEFINITION */
struct
{
	#error "Provide your data structure"
} 
/* USER CODE END SC_INPUT_SIGNALDATADEFINITION */
SC_INPUT_data_t;

/* USER CODE START InitSC_INPUT */
#error "Provide a sensible init value"
#define SC_INPUT_INIT_DATA ((SC_INPUT_data_t){})
/* USER CODE END InitSC_INPUT */


/**
 * Default IN driver API
 * \param SC_INPUT_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_INPUT_driverIn(SC_INPUT_data_t *const data);




/* USER CODE START SC_INPUT_USERFUNCTIONS */

/* USER CODE END SC_INPUT_USERFUNCTIONS */


#endif