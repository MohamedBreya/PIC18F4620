/* 
 * File:   hal_timer3.h
 * Author: moham
 *
 * Created on June 26, 2023, 4:52 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes */

#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */

#define TIMER3_COUNTER_MODE 1
#define TIMER3_TIMER_MODE   0

#define TIMER3_ASYNC_COUNTER_MODE 1
#define TIMER3_SYNC_COUNTER_MODE  0


#define TIMER3_8BIT_REGISTER_MODE   0
#define TIMER3_16BIT_REGISTER_MODE  1

/* Section : Macro Functions Declarations */

#define TIMER3_MODULE_ENABLE()               (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()              (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()           (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()         (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()    (T3CONbits.T3SYNC = 0)


#define TIMER3_PRESCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)


#define TIMER1_8BIT_REGISTER_MODE_ENABLE()   (T3CONbits.RD16 = 0)
#define TIMER1_16BIT_REGISTER_MODE_ENABLE()  (T3CONbits.RD16 = 1)


/* Section : Data Type Declarations */
typedef enum
{
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8 
            
}timer3_prescaler_select_t;

typedef struct 
{
    #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*TMR3_InterruptHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg priority; 
        #endif
    #endif

    timer3_prescaler_select_t prescaler_value;
    uint16 timer3_preload_value;
    uint8 timer3_register_size : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_mode : 1;
    uint8 timer3_reserved : 5;

}timer3_t;

/* Section : Functions Declarations */
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER3_H */

