/* 
 * File:   application.c
 * Author: moham
 *
 * Created on May 21, 2023, 5:59 PM
 */




#include"application.h"
//#include "ECU_Layer/BUTTON/ecu_button.h"

/*
 * 
 */


//pin_config_t led_1 ={
//    .port=PORTC_INDEX,
//    .pin=GPIO_PIN0,
//    .direction=GPIO_DIRECTION_OUTPUT,
//    .logic=GPIO_LOW
//};
//pin_config_t btn_1 ={
//    .port=PORTD_INDEX,
//    .pin=GPIO_PIN0,
//    .direction=GPIO_DIRECTION_INPUT,
//    .logic=GPIO_LOW
//};
//gpio_pin_raed_logic



/*typedef struct {
    uint8 port_name : 3;
    uint8 pin : 3;
    uint8 button_state : 1;
    uint8 button_connection : 1;
}button_t;
 */


chr_lcd_4bit_t lcd_1 = {
  .lcd_rs.port= PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_en.port= PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOW,
  .lcd_data[0].port= PORTC_INDEX,
  .lcd_data[0].pin = GPIO_PIN2,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port= PORTC_INDEX,
  .lcd_data[1].pin = GPIO_PIN3,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port= PORTC_INDEX,
  .lcd_data[2].pin = GPIO_PIN4,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port= PORTC_INDEX,
  .lcd_data[3].pin = GPIO_PIN5,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW, 
};



chr_lcd_8bit_t lcd_2 = {
  .lcd_rs.port= PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN6,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_en.port= PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN7,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOW,
  .lcd_data[0].port= PORTD_INDEX,
  .lcd_data[0].pin = GPIO_PIN0,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port= PORTD_INDEX,
  .lcd_data[1].pin = GPIO_PIN1,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port= PORTD_INDEX,
  .lcd_data[2].pin = GPIO_PIN2,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port= PORTD_INDEX,
  .lcd_data[3].pin = GPIO_PIN3,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW, 
  .lcd_data[4].port= PORTD_INDEX,
  .lcd_data[4].pin = GPIO_PIN4,
  .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[4].logic = GPIO_LOW,
  .lcd_data[5].port= PORTD_INDEX,
  .lcd_data[5].pin = GPIO_PIN5,
  .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[5].logic = GPIO_LOW,
  .lcd_data[6].port= PORTD_INDEX,
  .lcd_data[6].pin = GPIO_PIN6,
  .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[6].logic = GPIO_LOW,
  .lcd_data[7].port= PORTD_INDEX,
  .lcd_data[7].pin = GPIO_PIN7,
  .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[7].logic = GPIO_LOW
};


















button_t btn_high ={
  .port_name = PORTD_INDEX,
  .pin = GPIO_PIN0,
  .button_connection = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};


button_t btn_low ={
  .port_name = PORTD_INDEX,
  .pin = GPIO_PIN1,
  .button_connection = BUTTON_ACTIVE_LOW,
  .button_state = BUTTON_RELEASED
};

led_t led_1={
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

led_t led_2={
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_HIGH
};


adc_config_t adc_1 = 
{
//    .ADC_InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .conversion_clock =   ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .adc_channel = ADC_CHANNEL_AN0,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference  = ADC_VOLTAGE_REFERENCE_DISABLE
    
};


relay_t relay_1={
    .port_name = PORTD_INDEX,
    .pin = GPIO_PIN4,
    .relay_status = GPIO_LOW
};

Std_ReturnType ret = E_NOT_OK;
button_state_t btn_high_state = BUTTON_RELEASED;
button_state_t btn_low_state = BUTTON_RELEASED;
uint8 flag=0;


adc_result_t conversion_Result_AN0,conversion_Result_AN1,conversion_Result_AN2,conversion_Result_AN3;
int main() {
//    uint8 x;
//    Data_EEPROM_WriteByte(0x0240,6);
//    Data_EEPROM_ReadByte(0x0240,&x);
    ret &= ADC_Init(&adc_1);
    
    while(1)
    {
        ret &= ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&conversion_Result_AN0);
        ret &= ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN1,&conversion_Result_AN1);
        ret &= ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN2,&conversion_Result_AN2);
        ret &= ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN3,&conversion_Result_AN3);
        flag = ret;
    }

    
    
    
    
//    char s[4];
//    ret &= convert_uint8_to_string(44,s);
//    ret = lcd_4bit_initialize(&lcd_1);
//    ret &= lcd_4bit_send_string(&lcd_1,s);
//    ret &= lcd_4bit_send_string_pos(&lcd_1,2,2,"mohamed");
//    ret &= lcd_4bit_send_char_data_pos(&lcd_1,1,1,s);
//    ret &= lcd_4bit_send_char_data_pos(&lcd_1,2,1,'E');
//    ret &= lcd_4bit_send_char_data_pos(&lcd_1,3,1,'N');
//    ret &= lcd_4bit_send_char_data_pos(&lcd_1,4,1,'A');
//    ret = lcd_8bit_initialize(&lcd_2);
//    ret &= lcd_8bit_send_string_pos(&lcd_2,1,1,"MENNA");
//    ret &= lcd_8bit_send_string_pos(&lcd_2,2,1,"MOHAMMED");
//    ret &= lcd_8bit_send_char_data_pos(&lcd_2,3,1,'N');
////    ret &= lcd_8bit_send_char_data_pos(&lcd_2,4,1'N');
//    ret &= lcd_8bit_send_char_data_pos(&lcd_2,4,1,'A');   
//    ret &= lcd_8bit_send_string(&lcd_2,"MENNA");
    
    
////    ret = gpio_pin_direction_inializtion(&led_1);
////    ret = gpio_pin_direction_inializtion(&btn_1);
////    ret = gpio_pin_write_logic(&led_1,GPIO_HIGH);
////    logic_t btn_logic ;
//    
//    led_initialize(&led_1);
//    relay_initialize(&relay_1);
////    led_initialize(&led_2);
//    button_initialize(&btn_high);
//    button_initialize(&btn_low);
//    
//    while(1)
//    {
////        ret = gpio_pin_raed_logic(&btn_1,&btn_logic);
////        if(GPIO_HIGH == btn_logic)
////        {
////            ret = gpio_pin_write_logic(&led_1,GPIO_HIGH);
//////            __delay_ms(1000);
////            
////        }
////        else
////        {
////            ret = gpio_pin_write_logic(&led_1,GPIO_LOW);
////        }
//        button_read_state(&btn_high,&btn_high_state);
//        button_read_state(&btn_low,&btn_low_state);
//        relay_turn_on(&relay_1); 
//        if(BUTTON_PRESSED == btn_high_state && flag==0 )
//        {
//           led_turn_toggle(&led_1); 
//           relay_turn_toggle(&relay_1); 
//           flag==1;
//        }
//        else if(BUTTON_RELEASED == btn_high_state && flag==1 )
//        {
//            led_turn_off(&led_1);
//            relay_turn_off(&relay_1); 
//            flag==0;
//        }
//        
////        if(BUTTON_PRESSED == btn_low_state )
////        {
////           led_turn_on(&led_2); 
////        }
////        else
////        {
////            led_turn_off(&led_2);
////        }
//        
////        __delay_ms(1000);
////        led_turn_toggle(&led_1);
////        led_turn_toggle(&led_2); 
////        __delay_ms(1000);
////        
//    }
    return (EXIT_SUCCESS);
}

