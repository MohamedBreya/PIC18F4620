#include"hal_adc.h"




#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

    static InterruptHandeler ADC_Interrupt_Handeler = NULL;
    
#endif



/*==============================================================================================================*/


static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t * _adc);
static inline void configure_voltage_reference(const adc_config_t * _adc);


/*==============================================================================================================*/



/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_Init(const adc_config_t * _adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT = _adc->acquisition_time; 
        ADCON2bits.ADCS = _adc->conversion_clock;
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        
        #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

            ADC_InterruptEnable();
            ADC_InterruptFlagClear();
            
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

                INTERRUPT_Priority_LevelsEnable();
                
                if (INTERRUPT_HIGH_PRIORITY == _adc->priority)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                    ADC_HighPrioritySet();
                }
                else if (INTERRUPT_LOW_PRIORITY == _adc->priority)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                    ADC_LowPrioritySet();
                }
                else
                {
                    /* Nothing */
                }
            #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
            #endif
            ADC_Interrupt_Handeler = _adc->ADC_InterruptHandler;
        #endif

        select_result_format(_adc);
        configure_voltage_reference(_adc);

        ADC_CONVERTER_ENABLE();

    }

    return ret;    
}



/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_DeInit(const adc_config_t * _adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
       ADC_CONVERTER_DISABLE(); 
       
       #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
           ADC_InterruptDisable();
       #endif

    }

    return ret;     
}


/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_SelectChannel(const adc_config_t * _adc,adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }

    return ret;     
}


/**
 * 
 * @param _adc
 * @return 
 */
Std_ReturnType ADC_StartConversion(const adc_config_t * _adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }

    return ret;     
}


/**
 * 
 * @param _adc
 * @param conversion_status
 * @return 
 */
Std_ReturnType ADC_IsConversionDone(const adc_config_t * _adc, uint8 *conversion_status)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {

        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }

    return ret;     
}

/**
 * 
 * @param _adc
 * @param conversion_Result
 * @return 
 */
Std_ReturnType ADC_GetConversionResult(const adc_config_t * _adc , adc_result_t *conversion_Result)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == _adc) || (NULL == conversion_Result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if( ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_Result = (adc_result_t)((ADRESH <<8)+ADRESL);
        }
        else if (ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_Result = (adc_result_t)(((ADRESH <<8)+ADRESL)>>6);
        }
        else
        {
            *conversion_Result = (adc_result_t)((ADRESH <<8)+ADRESL);
        }

    }

    return ret;     
}


/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_Result
 * @return 
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t * _adc,adc_channel_select_t channel,
                                 adc_result_t *conversion_Result)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL == _adc) || (NULL == conversion_Result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= ADC_SelectChannel(_adc, channel);
        ret &= ADC_StartConversion(_adc);
        while(ADCON0bits.GO_nDONE);
        ret &= ADC_GetConversionResult(_adc, conversion_Result);
    }

    return ret;     
}


Std_ReturnType ADC_Conversion_Interrupt(const adc_config_t * _adc,adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= ADC_SelectChannel(_adc, channel);
        ret &= ADC_StartConversion(_adc);
        
    }

    return ret;    
}


static inline void adc_input_channel_port_configure(adc_channel_select_t channel)
{
    switch (channel)
    {
        case ADC_CHANNEL_AN0 :
            SET_BIT(TRISA,_TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1 :
            SET_BIT(TRISA,_TRISA_RA1_POSN);                
            break;
        case ADC_CHANNEL_AN2 :
            SET_BIT(TRISA,_TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3 :
            SET_BIT(TRISA,_TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4 :
            SET_BIT(TRISA,_TRISA_RA5_POSN);
            break;                
        case ADC_CHANNEL_AN5 :
            SET_BIT(TRISE,_TRISE_RE0_POSN);
            break;                
        case ADC_CHANNEL_AN6 :
            SET_BIT(TRISE,_TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7 :
            SET_BIT(TRISE,_TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8 :
            SET_BIT(TRISB,_TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9 :
            SET_BIT(TRISB,_TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10 :
            SET_BIT(TRISB,_TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11 :
            SET_BIT(TRISB,_TRISB_RB4_POSN);
            break;                
        case ADC_CHANNEL_AN12 :
            SET_BIT(TRISB,_TRISB_RB0_POSN);
            break;                
        default : /*Nothing*/;

    }
}


static inline void select_result_format(const adc_config_t * _adc)
{
    if ( ADC_RESULT_RIGHT == _adc->result_format)
    {
       ADC_RESULT_RIGHT_FORMAT(); 
    }
    else if (ADC_RESULT_LEFT == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}


static inline void configure_voltage_reference(const adc_config_t * _adc)
{
    if (ADC_VOLTAGE_REFERENCE_ENABLE == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if (ADC_VOLTAGE_REFERENCE_DISABLE == _adc->voltage_reference)
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

/*======================================================================*/


/*============================== ADC_ISR ==============================*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void ADC_ISR(void)
    {
        ADC_InterruptFlagClear();

        if (ADC_Interrupt_Handeler)
        {
            ADC_Interrupt_Handeler();
        }
        else
        {
            /* Nothing */
        }
    }
#endif
/*======================================================================*/