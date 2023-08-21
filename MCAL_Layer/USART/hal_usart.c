#include"hal_usart.h"



static void EUSART_Boud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYN_TX_Init(const usart_t *_eusart);
static void EUSART_ASYN_RX_Init(const usart_t *_eusart);

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler EUSART_TX_Interrupt_Handeler = NULL;
    
#endif

#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler EUSART_RX_Interrupt_Handeler = NULL;
    static InterruptHandeler EUSART_FramingErrorHandler = NULL;
    static InterruptHandeler EUSART_OverrunErrorHandler = NULL;
    
#endif
    
    


/**
 * 
 * @param _eusart
 * @return 
 */
Std_ReturnType EUSART_ASYN_Init(const usart_t *_eusart)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        EUSART_Boud_Rate_Calculation(_eusart);
        
        SET_BIT(TRISC,RC7);
        SET_BIT(TRISC,RC6);
        
        EUSART_ASYN_TX_Init(_eusart);
        EUSART_ASYN_RX_Init(_eusart);        
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }

    return ret;    
}



/**
 * 
 * @param _eusart
 * @return 
 */
Std_ReturnType EUSART_ASYN_DeInit(const usart_t *_eusart)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
    }

    return ret;    
}



/**
 * 
 * @param _eusart
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYN_ReadByte_Blocking(const usart_t *_eusart, uint8 *_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == _eusart) ||(NULL == _data))
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(!(PIR1bits.RCIF));
        *_data = RCREG;
    }

    return ret;    
}


/**
 * 
 * @param _eusart
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYN_ReadByte_NonBlocking(const usart_t *_eusart, uint8 *_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == _eusart) ||(NULL == _data))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (1 == PIR1bits.RCIF)
        {
            *_data = RCREG;
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
 * @param _eusart
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYN_WriteByte_Blocking(const usart_t *_eusart, uint8 _data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(!(TXSTAbits.TRMT));
        
        #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
        #endif

        TXREG = _data;
    }

    return ret;    
}


/**
 * 
 * @param _eusart
 * @param _data
 * @param str_len
 * @return 
 */
Std_ReturnType EUSART_ASYN_WriteString_Blocking(const usart_t *_eusart, uint8 *_data, uint16 str_len)
{
    Std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    if((NULL == _eusart) || (_data == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(char_counter = ZERO_INIT ;char_counter < str_len; ++char_counter )
        {
            ret &= EUSART_ASYN_WriteByte_Blocking(_eusart,_data[char_counter]);
        }
    }

    return ret;    
}


static void EUSART_Boud_Rate_Calculation(const usart_t *_eusart)
{
    float Baud_Rate_Temp = 0 ;
    switch (_eusart->baudrate_gen_config)
    {
        case BAUDRATE_ASYN_8BIT_LOW_SPEED:
            
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/64)-1;
            break;
            
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/16)-1;            
            break;
            
        case BAUDRATE_ASYN_16BIT_LOW_SPEED:
            
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/16)-1;            
            break;
            
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;            
            break;
            
        case BAUDRATE_SYN_8BIT:
            
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;            
            break;
            
        case BAUDRATE_SYN_16BIT:
            
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;            
            break;
            
        default:;
    }
    
    SPBRG = (uint8) ((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8);
}

static void EUSART_ASYN_TX_Init(const usart_t *_eusart)
{
    if (EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable)
    {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        
        if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
        #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            EUSART_TX_InterruptEnable();
            EUSART_TX_Interrupt_Handeler = _eusart->usart_tx_cfg.EUSART_TxDefaultInterruptHandler;
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_LevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    EUSART_TX_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    EUSART_TX_LowPrioritySet();
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
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else
        {
            /* Nothing */
        }


        if (EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;

        }
        else if (EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable)
        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
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

static void EUSART_ASYN_RX_Init(const usart_t *_eusart)
{
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable)
    {
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        
        if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
        #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            EUSART_RX_InterruptEnable();
            EUSART_RX_Interrupt_Handeler = _eusart->usart_rx_cfg.EUSART_RxDefaultInterruptHandler;
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_LevelsEnable();
                if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    EUSART_RX_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    EUSART_RX_LowPrioritySet();
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
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else
        {
            /* Nothing */
        }  
        
        
        if (EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable)
        {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;

        }
        else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable)
        {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
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





void EUSART_TX_ISR(void)
{
   EUSART_TX_InterruptDisable();
   if (EUSART_TX_Interrupt_Handeler)
   {
       EUSART_TX_Interrupt_Handeler();
   }
   else
   {
       /* Nothing */
   }
}

void EUSART_RX_ISR(void)
{
   if (EUSART_RX_Interrupt_Handeler)
   {
       EUSART_RX_Interrupt_Handeler();
   }
   else
   {
       /* Nothing */
   }
   
   if (EUSART_FramingErrorHandler)
   {
       EUSART_FramingErrorHandler();
   }
   else
   {
       /* Nothing */
   }

   
   if (EUSART_OverrunErrorHandler)
   {
       EUSART_OverrunErrorHandler();
   }
   else
   {
       /* Nothing */
   }
   
}