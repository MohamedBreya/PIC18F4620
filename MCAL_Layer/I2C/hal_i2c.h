/* 
 * File:   hal_i2c.h
 * Author: moham
 *
 * Created on July 5, 2023, 3:29 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes */

#include"../GPIO/hal_gpio.h"
#include"../Interrupt/mcal_intenal_interrupt.h"

/* Section : Macro Declarations */

#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE  0



#define I2C_SMBus_ENABLE  1
#define I2C_SMBus_DISABLE 0


#define I2C_LAST_BYTE_DATA    1
#define I2C_LAST_BYTE_ADDRESS 0


#define START_BIT_DETECTED     1
#define START_BIT_NOT_DETECTED 0


#define STOP_BIT_DETECTED     1
#define STOP_BIT_NOT_DETECTED 0



#define MSSP_I2C_MASTER_MODE 1
#define MSSP_I2C_SLAVE_MODE  0


#define I2C_SLAVE_MODE_7BIT_ADDRESS                0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS               0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE  0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE 0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK              0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED        0x0BU


#define I2C_GENERAL_CALL_ENABLE  1
#define I2C_GENERAL_CALL_DISABLE 0



#define I2C_MASTER_RECEIVE_ENABLE  1
#define I2C_MASTER_RECEIVE_DISABLE 0


#define I2C_ACK_RECEIVED_FROM_SLAVE     0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 1

#define I2C_MASTER_SEND_ACK      0
#define I2C_MASTER_SEND_NOT_ACK 1


/* Section : Macro Functions Declarations */


#define I2C_SLEW_RATE_ENABLE_CFG()      (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_DISABLE_CFG()     (SSPSTATbits.SMP = 1)



#define I2C_SMBus_ENABLE_CFG()           (SSPSTATbits.CKE = 1)
#define I2C_SMBus_DISABLE_CFG()          (SSPSTATbits.CKE = 0)


#define I2C_GENERAL_CALL_ENABLE_CFG()    (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG()   (SSPCON2bits.GCEN = 0)



#define I2C_MASTER_RECEIVE_ENABLE_CFG()  (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECEIVE_DISABLE_CFG() (SSPCON2bits.RCEN = 0)



#define MSSP_MODULE_ENABLE_CFG()         (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()        (SSPCON1bits.SSPEN = 0)

/* Section : Data Type Declarations */

typedef struct
{
    #if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_cfg mssp_i2c_priority;
            interrupt_priority_cfg mssp_i2c_bc_priority;
        #endif
    #endif
    uint8 i2c_mode_cfg;
    uint8 i2c_mode : 1;
    uint8 i2c_slew_rate : 1;
    uint8 i2c_SMBus_control : 1;
    uint8 i2c_general_call : 1;
    uint8 i2c_master_rec_mode : 1;
    uint8 i2c_reserved : 3;
}i2c_configs_t;


typedef struct
{
    uint32 i2c_clock;
    #if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*I2C_Report_Write_Collision)(void);
        void (*I2C_DefaultInterruptHandler)(void);
        void (*I2C_Report_Receive_Overflow)(void);
    #endif
    
    i2c_configs_t i2c_cfg;
}mssp_i2c_t;

/* Section : Functions Declarations */


Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Write(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_Read(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);


#endif	/* HAL_I2C_H */

