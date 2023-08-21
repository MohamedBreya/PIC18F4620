    /* 
 * File:   hal_usart.h
 * Author: moham
 *
 * Created on July 1, 2023, 12:06 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Includes */

#include"hal_usart_cfg.h"
#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */
#define EUSART_MODULE_ENABLE  1
#define EUSART_MODULE_DISABLE 0


#define EUSART_SYNCHRONOUS_MODE        1
#define EUSART_ASYNCHRONOUS_MODE       0

#define EUSART_ASYNCHRONOUS_HIGH_SPEED 1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  0

#define EUSART_16BIT_BAUDRATE_GEN      1
#define EUSART_8BIT_BAUDRATE_GEN       0


#define EUSART_ASYNCHRONOUS_TX_ENABLE            1
#define EUSART_ASYNCHRONOUS_TX_DISABLE           0

#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE  1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE 0

#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE       1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE      0


#define EUSART_ASYNCHRONOUS_RX_ENABLE            1
#define EUSART_ASYNCHRONOUS_RX_DISABLE           0

#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE  1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE 0

#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE       1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE      0


#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;


typedef struct 
{
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*EUSART_TxDefaultInterruptHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg usart_tx_priority; 
        #endif
    #endif
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
}usart_tx_cfg_t;

typedef struct 
{
    #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*EUSART_RxDefaultInterruptHandler)(void);
        void (*EUSART_FramingErrorHandler)(void);
        void (*EUSART_OverrunErrorHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg usart_rx_priority; 
        #endif
    #endif    
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
}usart_rx_cfg_t;

typedef union
{
    struct 
    {
        uint8 usart_tx_reserved : 6;
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1;
    };
    uint8 status;
    
}usart_error_status_t;

typedef struct 
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
}usart_t;
  
/* Section : Functions Declarations */

Std_ReturnType EUSART_ASYN_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYN_DeInit(const usart_t *_eusart);
Std_ReturnType EUSART_ASYN_ReadByte_Blocking(const usart_t *_eusart, uint8 *_data);
Std_ReturnType EUSART_ASYN_ReadByte_NonBlocking(const usart_t *_eusart, uint8 *_data);
Std_ReturnType EUSART_ASYN_WriteByte_Blocking(const usart_t *_eusart, uint8 _data);
Std_ReturnType EUSART_ASYN_WriteString_Blocking(const usart_t *_eusart, uint8 *_data, uint16 str_len);
#endif	/* HAL_USART_H */

