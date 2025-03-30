#include "main.h"

#define GPIOD_BASE_ADDR 0x40020C00
void LedInit_Green()
{
	// Led Green PD12 -> output
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 24);
	*GPIOD_MODER |= (0b01 << 24);
}

void LedInit_Orange()
{
	// Led Orange PD13 -> output
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 26);
	*GPIOD_MODER |= (0b01 << 26);
}

void LedInit_Red()
{
	// Led Red PD14 -> output
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 28);
	*GPIOD_MODER |= (0b01 << 28);
}

void LedInit_Blue()
{
	// Led Blue PD15 -> output
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 30);
	*GPIOD_MODER |= (0b01 << 30);
}

#define GPIOA_BASE_ADDR 0x40020000
void ButtonInit()
{
	//Cài đặt Input trên thanh ghi MODER (Blue Button) - PA0
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*GPIOA_MODER &= ~(0b11 << 0);
}

void LedCtrl_Green(int on_off)
{
	// Điều khiển sáng tắt của Led - Dùng thanh ghi BSRR
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1 << 12); // bật led
	}
	else
	{
		*GPIOD_BSRR |= (1 << 28); // tắt led 12+16
	}
}

void LedCtrl_Orange(int on_off)
{
	// Điều khiển sáng tắt của Led - Dùng thanh ghi BSRR
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1 << 13); // bật led
	}
	else
	{
		*GPIOD_BSRR |= (1 << 29); // tắt led 13+16
	}
}

void LedCtrl_Red(int on_off)
{
	// Điều khiển sáng tắt của Led - Dùng thanh ghi BSRR
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1 << 14); // bật led
	}
	else
	{
		*GPIOD_BSRR |= (1 << 30); // tắt led 14+16
	}
}

void LedCtrl_Blue(int on_off)
{
	// Điều khiển sáng tắt của Led - Dùng thanh ghi BSRR
	uint32_t* GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off == 1)
	{
		*GPIOD_BSRR |= (1 << 15); // bật led
	}
	else
	{
		*GPIOD_BSRR |= (1 << 31); // tắt led 15+16
	}
}

int main()
{
	HAL_Init();

	LedInit_Green();
	LedInit_Orange();
	LedInit_Red();
	LedInit_Blue();

	ButtonInit();
	while(1)
	{
		/*// LED GREEN
		LedCtrl_Green(1);
		HAL_Delay(1000);
		LedCtrl_Green(0);
		HAL_Delay(1000);*/

		// LED ORANGE
		LedCtrl_Orange(1);
		HAL_Delay(1000);
		LedCtrl_Orange(0);
		HAL_Delay(1000);

		/*// LED RED
		LedCtrl_Red(1);
		HAL_Delay(1000);
		LedCtrl_Red(0);
		HAL_Delay(1000);*/

		// LED BLUE
		LedCtrl_Blue(1);
		HAL_Delay(1000);
		LedCtrl_Blue(0);
		HAL_Delay(1000);
	}

	return 0;
}
