#include"hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler TMR2_Interrupt_Handeler = NULL;
    
#endif

static uint8 timer2_preload =ZERO_INIT;



/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
        
        TIMER2_PRESCALER_SELECT(_timer->prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->postscaler_value);

        TMR2 = _timer->timer2_preload_value;
        
        timer2_preload = _timer->timer2_preload_value;
        
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            TIMER2_InterruptEnable();
            TIMER2_InterruptFlagClear();
            
            TMR2_Interrupt_Handeler = _timer->TMR2_InterruptHandler;
            
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_LevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    TIMER2_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    TIMER2_LowPrioritySet();
                }
                else
                {
                    /* Nothing */
                }
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif
        #endif
        
        TIMER2_MODULE_ENABLE();

    }    
}

/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer2_DeInit(const timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
        
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TIMER2_InterruptDisable();
        #endif
    }    
}


/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2 = _value;
    }    
}


/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value)
{
    Std_ReturnType ret = E_OK;

    if(( NULL == _timer ) || ( NULL == _value ))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *_value = TMR2;
    }    
}







/*============================== TIMER2_ISR ==============================*/

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void TMR2_ISR(void)
    {
        TIMER2_InterruptFlagClear();
        
        TMR2 = timer2_preload;
        
        if (TMR2_Interrupt_Handeler)
        {
            TMR2_Interrupt_Handeler();
        }
        else
        {
            /* Nothing */
        }
    }
#endif
    
/*========================================================================*/
