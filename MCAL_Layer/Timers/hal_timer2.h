/* 
 * File:   hal_timer2.h
 * Author: moham
 *
 * Created on June 26, 2023, 1:07 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Includes */

#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */

//#define TIMER1_COUNTER_MODE 1
//#define TIMER1_TIMER_MODE   0
//
//#define TIMER1_ASYNC_COUNTER_MODE 1
//#define TIMER1_SYNC_COUNTER_MODE  0
//
//#define TIMER1_OSCILLATOR_ENABLE  1
//#define TIMER1_OSCILLATOR_DISABLE 0
//
//
//#define TIMER0_PRESCALER_ENABLE_CFG  1
//#define TIMER0_PRESCALER_DISABLE_CFG 0
//
//#define TIMER0_RISING_EDGE_CFG  1
//#define TIMER0_FALLING_EDGE_CFG 0
//
//
//
//#define TIMER1_8BIT_REGISTER_MODE   0
//#define TIMER1_16BIT_REGISTER_MODE  1

/* Section : Macro Functions Declarations */

#define TIMER2_MODULE_ENABLE()               (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()              (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_PRESCALER_)   (T2CONbits.T2CKPS = _PRESCALER_)
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)

//#define TIMER1_TIMER_MODE_ENABLE()           (T1CONbits.TMR1CS = 0)
//#define TIMER1_COUNTER_MODE_ENABLE()         (T1CONbits.TMR1CS = 1)
//
//#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 1)
//#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0)
//
//#define TIMER1_OSC_ENABLE()                  (T1CONbits.T1OSCEN = 1)
//#define TIMER1_OSC_DISABLE()                 (T1CONbits.T1OSCEN = 0)
//

//
//#define TIMER1_SYSTEM_CLK_STATUS()           (T1CONbits.T1RUN)
//
//#define TIMER1_8BIT_REGISTER_MODE_ENABLE()   (T1CONbits.RD16 = 0)
//#define TIMER1_16BIT_REGISTER_MODE_ENABLE()  (T1CONbits.RD16 = 1)


//#define TIMER0_RISING_EDGE_ENABLE()  (T0CONbits.T0SE = 0)
//#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE = 1)







/* Section : Data Type Declarations */
typedef enum
{
    TIMER2_POSTSCALER_DIV_BY_1 = 0,
    TIMER2_POSTSCALER_DIV_BY_2,
    TIMER2_POSTSCALER_DIV_BY_3,
    TIMER2_POSTSCALER_DIV_BY_4,
    TIMER2_POSTSCALER_DIV_BY_5,
    TIMER2_POSTSCALER_DIV_BY_6,
    TIMER2_POSTSCALER_DIV_BY_7,
    TIMER2_POSTSCALER_DIV_BY_8,
    TIMER2_POSTSCALER_DIV_BY_9,
    TIMER2_POSTSCALER_DIV_BY_10,
    TIMER2_POSTSCALER_DIV_BY_11,
    TIMER2_POSTSCALER_DIV_BY_12,
    TIMER2_POSTSCALER_DIV_BY_13,
    TIMER2_POSTSCALER_DIV_BY_14,
    TIMER2_POSTSCALER_DIV_BY_15,
    TIMER2_POSTSCALER_DIV_BY_16
            
}timer2_postscaler_select_t;


typedef enum
{
    TIMER2_PRESCALER_DIV_BY_1 = 0,
    TIMER2_PRESCALER_DIV_BY_4,
    TIMER2_PRESCALER_DIV_BY_16
            
}timer2_prescaler_select_t;

typedef struct 
{
    #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*TMR2_InterruptHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg priority; 
        #endif
    #endif

    timer2_prescaler_select_t prescaler_value;
    timer2_postscaler_select_t postscaler_value;
    uint8 timer2_preload_value;

}timer2_t;

/* Section : Functions Declarations */
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);


#endif	/* HAL_TIMER2_H */

