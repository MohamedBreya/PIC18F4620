/* 
 * File:   hal_timer1.h
 * Author: moham
 *
 * Created on June 24, 2023, 6:31 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : Includes */

#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */

#define TIMER1_COUNTER_MODE 1
#define TIMER1_TIMER_MODE   0

#define TIMER1_ASYNC_COUNTER_MODE 1
#define TIMER1_SYNC_COUNTER_MODE  0

#define TIMER1_OSCILLATOR_ENABLE  1
#define TIMER1_OSCILLATOR_DISABLE 0


#define TIMER1_8BIT_REGISTER_MODE   0
#define TIMER1_16BIT_REGISTER_MODE  1

/* Section : Macro Functions Declarations */

#define TIMER1_MODULE_ENABLE()               (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()              (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()           (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()         (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_ENABLE()                  (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_DISABLE()                 (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()           (T1CONbits.T1RUN)

#define TIMER1_8BIT_REGISTER_MODE_ENABLE()   (T1CONbits.RD16 = 0)
#define TIMER1_16BIT_REGISTER_MODE_ENABLE()  (T1CONbits.RD16 = 1)


//#define TIMER0_RISING_EDGE_ENABLE()  (T0CONbits.T0SE = 0)
//#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE = 1)







/* Section : Data Type Declarations */
typedef enum
{
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8 
            
}timer1_prescaler_select_t;

typedef struct 
{
    #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*TMR1_InterruptHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg priority; 
        #endif
    #endif

    timer1_prescaler_select_t prescaler_value;
    uint16 timer1_preload_value;
    uint8 timer1_register_size : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_mode : 1;
    uint8 timer1_reserved : 4;

}timer1_t;

/* Section : Functions Declarations */
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER1_H */

