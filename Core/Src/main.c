#include "main.h"

typedef enum{ // tạo kiểu cho biến
		LED_GREEN = 12,
		LED_ORANGE = 13,
		LED_RED = 14,
		LED_BLUE = 15
}LED_t; // tên biến do mình tạo

/*#define GPIOD_BASE_ADDR 0x40020C00
void LedInit_Green() // Đèn Led là xét OUTPUT
{
	// Led Green PD12 -> chân D
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 24);
	*GPIOD_MODER |= (0b01 << 24);
}*/

#define GPIOD_BASE_ADDR 0x40020C00
void LedInit(LED_t led) // Đèn Led là xét OUTPUT
{
	// Led Green PD12 -> chân D
	// Led Orange PD13 -> chân D
	// Led Red PD14 -> chân D
	// Led Blue là PD15 -> chân D

	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << (led * 2));
	*GPIOD_MODER |= (0b01 << (led * 2));
}


#define GPIOA_BASE_ADDR 0x40020000
void ButtonInit() // Nút nhấn là xét INPUT
{
	// Button là PA0 -> chân A
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*GPIOA_MODER &= ~(0b11 << 0);

	uint32_t* GPIOA_PUPDR = (uint32_t*)(GPIOA_BASE_ADDR +  0x0C);
	*GPIOA_PUPDR &= ~(0b11 << 0); // clear
	*GPIOA_PUPDR |= (0b01 << 0); // 01 = pull-up
}

void LedCtrl(LED_t led, int on_off)
{
#if 0
	uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	if(on_off == 1)
	{
		*GPIOD_ODR |= (1 << led);
	}
	else
	{
		*GPIOD_ODR &= ~(1 << led);
	}
#else
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1 << led); // Bật Led
	}
	else
	{
		*GPIOD_BSRR |= (1 << (led + 16)); // Tắt Led
	}
#endif
}

int buttonPress() // nút nhấn là PA0
{
	uint32_t* GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
	uint32_t giaTri = *GPIOA_IDR;
	if((giaTri & (1 << 0)) == 0) // Nếu bit 0 là 0
		return 1; // Được nhấn
	else
		return 0; // Không nhấn
}

#define EXTI_BASE_ADDR 0x40013C00
#define SYSCFG_BASE_ADDR 0x40013800
void EXTOInit()
{
	__HAL_RCC_SYSCFG_CLK_ENABLE(); // Bật clock cho SYSCFG

	 // Gán PA0 → EXTI0 qua SYSCFG_EXTICR1
	uint32_t* SYSCFG_EXTICR1 = (uint32_t*)(SYSCFG_BASE_ADDR + 0x08);
	*SYSCFG_EXTICR1 &= ~(0xF << 0); // chọn Port A cho EXTI0

	//RISING
	uint32_t* EXTI_RTSR = (uint32_t*)(EXTI_BASE_ADDR + 0x08);
	*EXTI_RTSR |= (1 << 0);

	//FALLING
	uint32_t* EXTI_FTSR = (uint32_t*)(EXTI_BASE_ADDR + 0x0C);
	*EXTI_FTSR |= (1 << 0);

	//MASK (cho phép EXTI0 hoạt động)
	uint32_t* EXTI_IMR = (uint32_t*)(EXTI_BASE_ADDR + 0x00);
	*EXTI_IMR |= (1 << 0);

	//NVIC (cho phép ngắt EXTI0)
	uint32_t* NVIC_ISER0 = (uint32_t*)(0xE000E100);
	*NVIC_ISER0 |= (1 << 6);
}

int press_count = 0;
void EXTI0_IRQHandler()
{
	// Đây là nơi bạn xử lý khi có ngắt EXTI0
	press_count++;
	uint32_t* EXTI_PR = (uint32_t*)(EXTI_BASE_ADDR + 0x14);
	*EXTI_PR |= (1 << 0);
}

int main()
{
	HAL_Init();

//	LedInit(LED_BLUE);
//	ButtonInit();
//	while(1)
//	{
//		LedCtrl(LED_BLUE, 1);
//		HAL_Delay(1000);
//		LedCtrl(LED_BLUE, 0);
//		HAL_Delay(1000);
//	}

	LedInit(LED_RED);
	LedInit(LED_BLUE);
	ButtonInit();
	EXTOInit();
//	while(1)
//	{
//		LedCtrl(LED_RED, 1);
//		HAL_Delay(1000);
//		LedCtrl(LED_RED, 0);
//		HAL_Delay(1000);
//	}
	while(1)
	{
		LedCtrl(LED_RED, 1);
		if(press_count >= 2)
			LedCtrl(LED_BLUE, 1);
		HAL_Delay(1000);

		LedCtrl(LED_RED, 0);
		if(press_count >= 2)
				LedCtrl(LED_BLUE, 0);
		HAL_Delay(1000);
	}

	return 0;
}


