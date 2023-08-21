#include"hal_i2c.h"



static inline void MSSP_I2C_Mode_GPIO_CFG(void);
static inline void I2C_Master_Mode_Clock_CFG(const mssp_i2c_t *i2c_obj);



#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler I2C_Report_Write_Collision = NULL;
    static InterruptHandeler I2C_DefaultInterruptHandler = NULL;
    static InterruptHandeler I2C_Report_Receive_Overflow = NULL;
    
#endif



/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        MSSP_MODULE_DISABLE_CFG();
        
        if(MSSP_I2C_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode)
        {
            I2C_Master_Mode_Clock_CFG(i2c_obj);
        }
        else if(MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode)
        {
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
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
        
        MSSP_I2C_Mode_GPIO_CFG();
        
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else
        {
            /* Nothing */
        } 
        
        
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBus_DISABLE_CFG();
        }
        else
        {
            /* Nothing */
        } 
        
        #if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            
            MSSP_I2C_InterruptEnable();
            MSSP_I2C_BUS_COL_InterruptEnable();
            MSSP_I2C_InterruptFlagClear();
            MSSP_I2C_BUS_COL_InterruptFlagClear();
            
            I2C_Report_Write_Collision = i2c_obj->I2C_Report_Write_Collision;
            I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;
            I2C_Report_Receive_Overflow = i2c_obj->I2C_Report_Receive_Overflow;
            
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

                INTERRUPT_Priority_LevelsEnable();
                
                if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    MSSP_I2C_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    MSSP_I2C_LowPrioritySet();
                }
                else
                {
                    /* Nothing */
                }


                if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    MSSP_I2C_BUS_COL_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_cfg.mssp_i2c_bc_priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    MSSP_I2C_BUS_COL_LowPrioritySet();
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

        MSSP_MODULE_ENABLE_CFG();
    }

    return ret;    
}




/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        MSSP_MODULE_DISABLE_CFG() ;
        
        #if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            MSSP_I2C_InterruptDisable();
            MSSP_I2C_BUS_COL_InterruptDisable();
            
        #endif
        
    }

    return ret;      
}





/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        SSPCON2bits.SEN = 1;
        
        while(SSPCON2bits.SEN);
        
        PIR1bits.SSPIF = 0;
        
        if (START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
        }
    }

    return ret;      
}





/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        SSPCON2bits.RSEN = 1;
        
        while(SSPCON2bits.RSEN);
        
        PIR1bits.SSPIF = 0;

    }

    return ret;      
}





/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        SSPCON2bits.PEN = 1;
        
        while(SSPCON2bits.PEN);
        
        PIR1bits.SSPIF = 0;
        
        if (START_BIT_DETECTED == SSPSTATbits.P)
        {
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
        }

    }

    return ret;      
}





/**
 * 
 * @param i2c_obj
 * @param i2c_data
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Write(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == i2c_obj) || (NULL == _ack))
    {
        ret = E_NOT_OK;
    }
    else
    {
        SSPBUF = i2c_data;
        while(!(PIR1bits.SSPIF));
        
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *_ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else
        {
            *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
    }

    return ret;      
}






/**
 * 
 * @param i2c_obj
 * @param ack
 * @param i2c_data
 * @return 
 */
Std_ReturnType MSSP_I2C_Read(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == i2c_obj) || (NULL == i2c_data))
    {
        ret = E_NOT_OK;
    }
    else
    {
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        
        while(!(SSPSTATbits.BF));
        
        *i2c_data = SSPBUF;
        
        if(I2C_MASTER_SEND_ACK == ack)
        {
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;
        }
        else if(I2C_MASTER_SEND_NOT_ACK == ack)
        {
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;
        }
        else
        {
            /* Nothing */
        }
        
    }

    return ret;      
}


static inline void MSSP_I2C_Mode_GPIO_CFG(void)
{
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}


static inline void I2C_Master_Mode_Clock_CFG(const mssp_i2c_t *i2c_obj)
{
    SSPCON1bits.SSPM = I2C_MASTER_MODE_DEFINED_CLOCK;
    
    SSPADD = (uint8) (((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock ) -1 );
}

void MSSP_I2C_ISR(void)
{
    MSSP_I2C_InterruptFlagClear();
    if(I2C_DefaultInterruptHandler)
    {
        I2C_DefaultInterruptHandler();
    }
    else
    {
        /* Nothing */
    }
}

void MSSP_I2C_BC_ISR(void)
{
    MSSP_I2C_BUS_COL_InterruptFlagClear();
        if(I2C_Report_Write_Collision)
    {
        I2C_Report_Write_Collision();
    }
    else
    {
        /* Nothing */
    }
}
