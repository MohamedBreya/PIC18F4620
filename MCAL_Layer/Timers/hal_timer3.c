#include"hal_timer3.h"


#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler TMR3_Interrupt_Handeler = NULL;
    
#endif

static uint16 timer3_preload =ZERO_INIT; 



static inline void Timer3_Mode_Select(const timer3_t *_timer);
//static inline void Timer1_Register_Size_Config(const timer1_t *_timer);




Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->prescaler_value);
        Timer3_Mode_Select(_timer);
//        Timer0_Register_Size_Config(_timer);
        TMR3H = ((_timer->timer3_preload_value)>>8);
        TMR3L = (uint8)(_timer->timer3_preload_value);
        
        timer3_preload = _timer->timer3_preload_value;
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            TIMER3_InterruptEnable();
            TIMER3_InterruptFlagClear();
            TMR3_Interrupt_Handeler = _timer->TMR3_InterruptHandler;
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_LevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    TIMER3_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    TIMER3_LowPrioritySet();
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
        
        TIMER3_MODULE_ENABLE();

    }    
}



Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TIMER3_InterruptDisable();
        #endif
    }    
}



Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (_value>>8);
        TMR3L = (uint8)(_value);
    }    
}



Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3_l = ZERO_INIT; 
    uint8 l_tmr3_h = ZERO_INIT;
    if(( NULL == _timer ) || ( NULL == _value ))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr3_l = TMR3L;
        l_tmr3_h = TMR3H;
        *_value = (uint16)((l_tmr3_h<<8)+l_tmr3_l);
    }    
}




static inline void Timer3_Mode_Select(const timer3_t *_timer)
{
    if(TIMER3_TIMER_MODE == _timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
//        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if (TIMER3_COUNTER_MODE == _timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if (TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if (TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else
        {
           /* Nothing */ 
        }
    }
    else
    {
        /* Nothing */
    }
}




/*============================== TIMER0_ISR ==============================*/

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void TMR3_ISR(void)
    {
        TIMER3_InterruptFlagClear();
        
        TMR3H = (timer3_preload>>8);
        TMR3L = (uint8)(timer3_preload);
        if (TMR3_Interrupt_Handeler)
        {
            TMR3_Interrupt_Handeler();
        }
        else
        {
            /* Nothing */
        }
    }
#endif
    
/*========================================================================*/
