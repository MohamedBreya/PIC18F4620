#include"hal_timer1.h"


#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler TMR1_Interrupt_Handeler = NULL;
    
#endif

static uint16 timer1_preload =ZERO_INIT; 



static inline void Timer1_Mode_Select(const timer1_t *_timer);
//static inline void Timer1_Register_Size_Config(const timer1_t *_timer);




Std_ReturnType Timer1_Init(const timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer->prescaler_value);
        Timer1_Mode_Select(_timer);
//        Timer0_Register_Size_Config(_timer);
        TMR1H = ((_timer->timer1_preload_value)>>8);
        TMR1L = (uint8)(_timer->timer1_preload_value);
        
        timer1_preload = _timer->timer1_preload_value;
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            TIMER1_InterruptEnable();
            TIMER1_InterruptFlagClear();
            TMR1_Interrupt_Handeler = _timer->TMR1_InterruptHandler;
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_LevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    TIMER1_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _timer->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    TIMER1_LowPrioritySet();
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
        
        TIMER1_MODULE_ENABLE();

    }    
}



Std_ReturnType Timer1_DeInit(const timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TIMER1_InterruptDisable();
        #endif
    }    
}



Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (_value>>8);
        TMR1L = (uint8)(_value);
    }    
}



Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1_l = ZERO_INIT; 
    uint8 l_tmr1_h = ZERO_INIT;
    if(( NULL == _timer ) || ( NULL == _value ))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr1_l = TMR1L;
        l_tmr1_h = TMR1H;
        *_value = (uint16)((l_tmr1_h<<8)+l_tmr1_l);
    }    
}




static inline void Timer1_Mode_Select(const timer1_t *_timer)
{
    if(TIMER1_TIMER_MODE == _timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
//        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if (TIMER1_COUNTER_MODE == _timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if (TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if (TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
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

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void TMR1_ISR(void)
    {
        TIMER1_InterruptFlagClear();
        
        TMR1H = (timer1_preload>>8);
        TMR1L = (uint8)(timer1_preload);
        if (TMR1_Interrupt_Handeler)
        {
            TMR1_Interrupt_Handeler();
        }
        else
        {
            /* Nothing */
        }
    }
#endif
    
/*========================================================================*/



