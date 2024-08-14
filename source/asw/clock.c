/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "clock.h"
#include "sp_common.h"
#include "stdlib.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
STATE_state_t init_state = CLOCK_C_ISDISPLAYING;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/** ---------------------------- Actions ---------------------------------- **/

static void CLOCK__Dispatch_Wrapper(EVENT_t ev, CLOCK_Active_Widget_t widget);

static void CLOCK__Dispatch_KL_Hours();

static void CLOCK__Dispatch_KL_HoursMin();

static void CLOCK__Dispatch_KR_Hours();

static void CLOCK__Dispatch_KRLP_Hours();

static void CLOCK__Dispatch_250MS_Hours();

static void CLOCK__Dispatch_KL_Min();

static void CLOCK__Dispatch_KR_Min();

static void CLOCK__Dispatch_KRLP_Min();

static void CLOCK__Dispatch_250MS_Min();

static void CLOCK__setEditFonts();

static void CLOCK__setDisplayFonts();

static void CLOCK__incrementWidget();

static void CLOCK__updateDisplay();

static void CLOCK__updateTime();

static void CLOCK__IncrementHourandDisplay();

static void CLOCK__IncrementMinuteandDisplay();


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/** ------------------------------------- Transitions Table Start ------------------------------------------- **/

/**============================== Container ================================ **/

/** ========= CLOCK_C_ISDISPLAYING ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISDISPLAYING_Transitions[] = 
{
    /*  Event               ToState                         Guard           Action                      */
    {   EV_KEYLEFT,         CLOCK_C_ISEDITINGHOURS,         0,              CLOCK__Dispatch_KL_Hours     },
    {   EV_1MIN,            CLOCK_C_ISDISPLAYING,           0,              CLOCK__updateTime            },
};

/** ========= CLOCK_C_ISEDITINGHOURS ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISEDITINGHOURS_Transitions[] = 
{
    /*  Event                       ToState                           Guard           Action                         */
    {   EV_KEYLEFT,                 CLOCK_C_ISEDITINGMINUTES,         0,              CLOCK__Dispatch_KL_HoursMin    },
    {   EV_KEYRIGHT,                CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__Dispatch_KR_Hours       },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__Dispatch_KRLP_Hours     },
    {   EV_250MS,                   CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__Dispatch_250MS_Hours    },
};

/** ========= CLOCK_C_ISEDITINGMINUTES ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISEDITINGMINUTES_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                      */
    {   EV_KEYLEFT,                 CLOCK_C_ISDISPLAYING,           0,              CLOCK__Dispatch_KL_Min       },
    {   EV_KEYRIGHT,                CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__Dispatch_KR_Min       },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__Dispatch_KRLP_Min     },
    {   EV_250MS,                   CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__Dispatch_250MS_Min    },
};

/** ===CLOCK_CONTAINER=== */
static const STATE_stateOuterTransitionTable_t CLOCK_Container_Transitions = 
{
    /*  fromState                     Pointer to table                                        Size of table [Elements]                                                                    */
    {   CLOCK_C_ISDISPLAYING,         &STATE_CLOCK_C_ISDISPLAYING_Transitions,                sizeof(STATE_CLOCK_C_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)         },
    {   CLOCK_C_ISEDITINGHOURS,       &STATE_CLOCK_C_ISEDITINGHOURS_Transitions,              sizeof(STATE_CLOCK_C_ISEDITINGHOURS_Transitions)/sizeof(STATE_stateInnerTransition_t)       },
    {   CLOCK_C_ISEDITINGMINUTES,     &STATE_CLOCK_C_ISEDITINGMINUTES_Transitions,            sizeof(STATE_CLOCK_C_ISEDITINGMINUTES_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
};
static const uint16_t CLOCK_Container_Transitions_size = sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t);

/**============================== WIDGET ================================ **/

/** ========= CLOCK_W_ISDISPLAYING =========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISDISPLAYING_Transitions[] = 
{
    /*  Event               ToState                    Guard           Action                  */
    {   EV_KEYLEFT,         CLOCK_W_ISEDITING,         0,              CLOCK__setEditFonts     },
};

/** ========= CLOCK_W_ISEDITING ============== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISEDITING_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                     */
    {   EV_KEYRIGHT,                CLOCK_W_ISEDITING,              0,              CLOCK__incrementWidget     },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_W_ISAUTOINCREMENT,        0,              0                          },
    {   EV_KEYLEFT,                 CLOCK_W_ISDISPLAYING,           0,              CLOCK__setDisplayFonts        },
};

/** ========= CLOCK_W_ISAUTOINCREMENT ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISAUTOINCREMENT_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                     */
    {   EV_KEYRIGHT,                CLOCK_W_ISEDITING,              0,              CLOCK__incrementWidget     },
    {   EV_250MS,                   CLOCK_W_ISAUTOINCREMENT,        0,              CLOCK__incrementWidget     },
};

/** ===CLOCK_WIDGET============= */
static const STATE_stateOuterTransitionTable_t CLOCK_Widget_Transitions = 
{
    /*  fromState                   Pointer to table                                Size of table [Elements]                                                                */
    {   CLOCK_W_ISDISPLAYING,       &STATE_CLOCK_W_ISDISPLAYING_Transitions,        sizeof(STATE_CLOCK_W_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
    {   CLOCK_W_ISEDITING,          &STATE_CLOCK_W_ISEDITING_Transitions,           sizeof(STATE_CLOCK_W_ISEDITING_Transitions)/sizeof(STATE_stateInnerTransition_t)        },
    {   CLOCK_W_ISAUTOINCREMENT,    &STATE_CLOCK_W_ISAUTOINCREMENT_Transitions,     sizeof(STATE_CLOCK_W_ISAUTOINCREMENT_Transitions)/sizeof(STATE_stateInnerTransition_t)  },
};
static const uint16_t CLOCK_Widget_Transitions_size = sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t);



/** ---------------------------------- Action ------------------------------------------- **/

/** ============= Container Action ============== **/
static const STATE_stateActionTable_t CLOCK_Container_Actions = 
{
    /*  fromState                   actionEntry                   actionExit          */
    {   CLOCK_C_ISDISPLAYING,       CLOCK__updateDisplay,         0                   },
};
static const uint16_t CLOCK_Container_Actions_size = sizeof(CLOCK_Container_Actions)/sizeof(STATE_stateAction_t);

/** ============= Widget Action ============== **/
static const STATE_stateActionTable_t CLOCK_Widget_Actions = 
{
    /*  fromState                   actionEntry                  actionExit          */
    {   CLOCK_W_ISDISPLAYING,       CLOCK__updateDisplay,        0                   },
    {   CLOCK_W_ISEDITING,          CLOCK__updateDisplay,        0                   },
    {   CLOCK_W_ISAUTOINCREMENT,    CLOCK__updateDisplay,        0                   },
};
static const uint16_t CLOCK_Widget_Actions_size = sizeof(CLOCK_Widget_Actions)/sizeof(STATE_stateAction_t);

/** ------------------------------------- Transitions Table End ------------------------------------------- **/

void statemachine_init()
{
    SC_CONTROL_data_t fontstyle     =   SC_CONTROL_INIT_DATA;
        
    fontstyle   =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    
    fontstyle.hour.font_type.bg_colour        =   BLACK;
    fontstyle.minute.font_type.bg_colour      =   BLACK;
    
    fontstyle.hour.font_type.widget_colour    =   WHITE;
    fontstyle.minute.font_type.widget_colour  =   WHITE;
    
    
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, fontstyle);
}

void ProcessEvent(STATE_event_t event)
{
    STATE_event_t local_event = event;
    STATE_processEvent(CLOCK_Container_Transitions, CLOCK_Container_Transitions_size, CLOCK_Container_Actions, CLOCK_Container_Actions_size, local_event, &init_state);
}

void CLOCK__Dispatch_Wrapper(EVENT_t ev, CLOCK_Active_Widget_t widget)
{
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);
    
    clock.m_ev = EV_NONE;
    
    clock.m_clock_data.m_activeWidget = widget;
    
    RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);
    
    if(widget == CLOCK_HOURWIDGET)
    {
        STATE_state_t localstate = clock.m_clock_data.m_hours.m_widgetState;        
        STATE_processEvent(CLOCK_Widget_Transitions, CLOCK_Widget_Transitions_size, CLOCK_Widget_Actions, CLOCK_Widget_Actions_size, ev, &localstate);        
        clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);       
        clock.m_clock_data.m_hours.m_widgetState = localstate;       
        RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);
    }
    else if(widget == CLOCK_MINWIDGET)
    {
        STATE_state_t localstate = clock.m_clock_data.m_minutes.m_widgetState;  
        STATE_processEvent(CLOCK_Widget_Transitions, CLOCK_Widget_Transitions_size, CLOCK_Widget_Actions, CLOCK_Widget_Actions_size, ev, &localstate);        
        clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);       
        clock.m_clock_data.m_minutes.m_widgetState = localstate;       
        RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);
    }
}

void CLOCK__updateTime()
{
    SC_CONTROL_data_t   time  =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    
    time.minute.value++;
    if(time.minute.value%60 == 0)
    {
        time.hour.value++;
        if(time.hour.value%24 == 0)
        {
            time.hour.value = 0;
        }
        time.minute.value = 0;
    }
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, time);
}



void CLOCK__Dispatch_KL_Hours()
{
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);   
    clock.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISDISPLAYING;    
    RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);    
    CLOCK__Dispatch_Wrapper(EV_KEYLEFT, CLOCK_HOURWIDGET);
}

void CLOCK__Dispatch_KR_Hours()
{   
    CLOCK__Dispatch_Wrapper(EV_KEYRIGHT, CLOCK_HOURWIDGET);
}

void CLOCK__Dispatch_KRLP_Hours()
{   
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);
    clock.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISEDITING;
    RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);  
    CLOCK__Dispatch_Wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_HOURWIDGET);
}

void CLOCK__Dispatch_250MS_Hours()
{   
    CLOCK__Dispatch_Wrapper(EV_250MS, CLOCK_HOURWIDGET);
}

void CLOCK__Dispatch_KL_HoursMin()
{   
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);
    
    clock.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISEDITING;
    clock.m_clock_data.m_minutes.m_widgetState = CLOCK_W_ISDISPLAYING;
    
    RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);
    
    CLOCK__Dispatch_Wrapper(EV_KEYLEFT, CLOCK_HOURWIDGET);
    CLOCK__Dispatch_Wrapper(EV_KEYLEFT, CLOCK_MINWIDGET);
}

void CLOCK__Dispatch_KL_Min()
{    
    CLOCK__Dispatch_Wrapper(EV_KEYLEFT, CLOCK_MINWIDGET);
}

void CLOCK__Dispatch_KR_Min()
{    
    CLOCK__Dispatch_Wrapper(EV_KEYRIGHT, CLOCK_MINWIDGET);
}

void CLOCK__Dispatch_KRLP_Min()
{   
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);   
    clock.m_clock_data.m_minutes.m_widgetState = CLOCK_W_ISEDITING;   
    RTE_SC_INPUT_set(&SO_BUTTONEVENT_signal, clock);   
    CLOCK__Dispatch_Wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_MINWIDGET);
}

void CLOCK__Dispatch_250MS_Min()
{   
    CLOCK__Dispatch_Wrapper(EV_250MS, CLOCK_MINWIDGET);
}

void CLOCK__incrementWidget()
{  
    SC_INPUT_data_t clock = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);
    
    if(clock.m_clock_data.m_activeWidget == CLOCK_HOURWIDGET)
    {
        CLOCK__IncrementHourandDisplay();
    }
    else if(clock.m_clock_data.m_activeWidget == CLOCK_MINWIDGET)
    {
        CLOCK__IncrementMinuteandDisplay();
    }   
}

void CLOCK__setDisplayFonts()
{
    
    SC_CONTROL_data_t font =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);;
    
    font.hour.font_type.bg_colour        =   BLACK;
    font.hour.font_type.widget_colour    =   WHITE;

    font.minute.font_type.bg_colour      =   BLACK;
    font.minute.font_type.widget_colour  =   WHITE;
    
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, font);
}

void CLOCK__setEditFonts()
{
    SC_CONTROL_data_t signal =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    SC_INPUT_data_t font = RTE_SC_INPUT_get(&SO_BUTTONEVENT_signal);
    
    if(font.m_clock_data.m_activeWidget == CLOCK_HOURWIDGET)
    {   
        signal.hour.font_type.bg_colour = WHITE;
        signal.hour.font_type.widget_colour  = BLACK;
        
        signal.minute.font_type.bg_colour  =   BLACK;
        signal.minute.font_type.widget_colour  =   WHITE;
    }
    else if(font.m_clock_data.m_activeWidget == CLOCK_MINWIDGET)
    {
        signal.hour.font_type.bg_colour   = BLACK;
        signal.hour.font_type.widget_colour  =  WHITE;
        
        signal.minute.font_type.bg_colour   =   WHITE;
        signal.minute.font_type.widget_colour  =   BLACK;
    }
    
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, signal);
}

void CLOCK__updateDisplay()
{
    
    SC_CONTROL_data_t clock_values  =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);  
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, clock_values);
    
}

void CLOCK__IncrementHourandDisplay()
{
    SC_CONTROL_data_t   clock_hour  =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);    
    clock_hour.hour.value++;
    
    if(clock_hour.hour.value%24 == 0)
    {
        clock_hour.hour.value = 0;
    }
    
    CLOCK__updateDisplay();    
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, clock_hour);
}

void CLOCK__IncrementMinuteandDisplay()
{
    SC_CONTROL_data_t   clock_minute  =   RTE_SC_CONTROL_get(&SO_CONTROL_signal);       
    clock_minute.minute.value++;
    
    if(clock_minute.minute.value%60 == 0)
    {
        clock_minute.minute.value = 0;
        CLOCK__IncrementHourandDisplay();
    }
    
    CLOCK__updateDisplay();   
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, clock_minute);
}
