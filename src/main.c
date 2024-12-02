#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"
#include "delay.h"

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    
    //Inicializace LEDek a tlačítka
    GPIO_Init(LED1_PORT, LED1_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(LED2_PORT, LED2_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(LED3_PORT, LED3_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
#if defined (BTN_PORT) || defined (BTN_PIN)
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);


#endif

    init_milis();
    //init_uart1();
}


int main(void)
{   
    uint32_t time= 0;
    uint8_t btn_state= 0;
    uint8_t last_btn_state= 0;
    uint8_t led_number= 1;

    init();

    while (1) {
        
        btn_state = GPIO_ReadInputPin(BTN_PORT, BTN_PIN);

        //Sledování změny tlačítka
        if (btn_state== 0 && last_btn_state == 1) {
            delay_ms(20);
            led_number += 1;
        }

        if (led_number > 3) {
            led_number= 1;
        }

        //Nastavení LEDek  
        if (led_number == 1) {
            GPIO_WriteHigh(LED1_PORT, LED1_PIN);
            GPIO_WriteLow(LED2_PORT, LED2_PIN);
            GPIO_WriteLow(LED3_PORT, LED3_PIN);
        } else if (led_number == 2) {
            GPIO_WriteLow(LED1_PORT, LED1_PIN);
            GPIO_WriteHigh(LED2_PORT, LED2_PIN);
            GPIO_WriteLow(LED3_PORT, LED3_PIN);
        } else {
            GPIO_WriteLow(LED1_PORT, LED1_PIN);
            GPIO_WriteLow(LED2_PORT, LED2_PIN);
            GPIO_WriteHigh(LED3_PORT, LED3_PIN);
        }

        last_btn_state = btn_state;
    } 
} 

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
