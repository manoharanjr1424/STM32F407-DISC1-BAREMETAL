

#include <stdint.h>
#include <mcu.h>
#include <timer.h>
#include <gpio.h>
#include <i2c.h>
#include <uart.h>

uint8_t gpio_init(void);
uint8_t data = 0;
uint8_t uart_data = 0;


#include <stdio.h>

//void Check_APB2_Timer_Clock(void) {
//    uint32_t sysclk, hclk, pclk2, timer_clock;
//
//    // Read system clock source
//    uint32_t clk_source = (RCC->CFGR >> 2) & 0x3;
//
//    // Determine SYSCLK
//    if (clk_source == 0) {
//        sysclk = 16000000; // HSI = 16 MHz
//    } else if (clk_source == 1) {
//        sysclk = 8000000;  // HSE = 8 MHz (if external crystal is used)
//    } else if (clk_source == 2) {
//        sysclk = 168000000; // PLL = 168 MHz (common case)
//    } else {
//        sysclk = 0; // Undefined
//    }
//
//    // Read AHB Prescaler (HCLK)
//    uint32_t ahb_prescaler = (RCC->CFGR >> 4) & 0xF;
//    uint32_t ahb_div[] = {1, 1, 2, 4, 8, 16, 64, 128, 256, 512};
//    hclk = sysclk / ahb_div[ahb_prescaler];
//
//    // Read APB2 Prescaler
//    uint32_t apb2_prescaler = (RCC->CFGR >> 13) & 0x7;
//    uint32_t apb2_div[] = {1, 1, 2, 4, 8, 16};
//    pclk2 = hclk / apb2_div[apb2_prescaler];
//
//    // Calculate Timer Clock
//    if (apb2_prescaler >= 2) {
//        timer_clock = pclk2 * 2;
//    } else {
//        timer_clock = pclk2;
//    }
//
//    // Print values
//    printf("SYSCLK: %lu Hz\n", sysclk);
//    printf("HCLK: %lu Hz\n", hclk);
//    printf("PCLK2: %lu Hz\n", pclk2);
//    printf("Timer Clock (APB2 Timers): %lu Hz\n", timer_clock);
//}
//




void uartPinInit(void);
void UART4_IRQHandler(void);

int main(void) {


	ENABLE_FPU();
	gpio_init();
	TimerInit(TIMER9);
	GetSystemClockFrequency(0);
	uartPinInit();

//	i2c_handler_t i2c;
	usartHandle_t uart;

//	i2c.I2C_Base = I2C1;
//	i2c.I2C_Mode =I2C_SM_MODE;
//	i2c.APB_PripheralFreq = 16;
//	i2c.I2C_CCRValue = 0x50;
//	i2c.I2C_TRISEValue = 17;

//	I2C_Init(i2c);

	uart.baudRate = 9600;
	uart.usartBase = UART4;
	uart.overSampling = OVERSAMPLING_16;
	uart.parityBit = 0;
	uart.stopBit = STOP_BIT_0;
	uart.wordLength = 0;



	uartInit(&uart);
	NvicEnableInt(UART4_IRQn);
	if ( uartInterruptEnable(UART4,RX_INTERRUPT) == USART_RX_INTERRUPT_NOT_ENABLED) {
		printf("uart Interrupt was Not Enable\n");
	}






//	uartCalculateBaurdRate(9600,1);

	while (1) {

				data ^= 1;
				GpioPinWrite(GPIOD, 12, data);
				uartSendChar(UART4,'A');
				MilliSecondsDelay(1000);

//		if(GpioPinRead(GPIOA,0) == 0)
//		{
//		data ^= 1;
//		GpioPinWrite(GPIOD, 12, data);
//		delay_ms(1000000);
//		}

	}
}

uint8_t gpio_init(void) {

	gpio_handler_t led_pin;

	led_pin.mode = SET_PIN_OUTPUT;
	led_pin.pin = 12;
	led_pin.port = GPIOD;
	led_pin.pull_up_down = 0;
	led_pin.output_type = 0;
	led_pin.ouput_speed = 0;



	GpioPinSet(led_pin);
//	GpioPinSet(switch_pin);
//	GpioIntEnable(GPIOA,0,FALLINGEDGE);

	return SUCCESS;
}

void delay_ms(uint32_t delay_ms) {
	while (delay_ms--);
}


void uartPinInit(void) {


	gpio_handler_t rx,tx;

	tx.mode = SET_PIN_ALTERNATIVE;
	rx.mode = SET_PIN_ALTERNATIVE;

	tx.pin = 10;
	rx.pin = 11;

	tx.Afmode = SET_PIN_AF8;
	rx.Afmode = SET_PIN_AF8;

	tx.port = GPIOC;
	rx.port = GPIOC;

	tx.pull_up_down = SET_PIN_NOPUPD;
	rx.pull_up_down = SET_PIN_NOPUPD;

	tx.output_type = 0;
	rx.output_type = 0;

	tx.ouput_speed = 0;
	rx.ouput_speed = 0;

	GpioPinSet(tx);
	GpioPinSet(rx);
}

void UART4_IRQHandler(void) {

	uartInterruptDisable(UART4,RX_INTERRUPT);
	while(! ( (UART4->SR) & (1 << 5)) );
	uart_data = UART4->DR;
	uartInterruptEnable(UART4,RX_INTERRUPT);
	uart_data = 0;

}
