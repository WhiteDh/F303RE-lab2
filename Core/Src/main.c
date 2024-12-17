#include "main.h"
#include "stm32f3xx_hal_exti.h"  // Додано для EXTI

TIM_HandleTypeDef htim6;  // Оголошення змінної для таймера

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Увімкнення тактування для GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Налаштування піну для кнопки (PA0)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // Підключення до переривання по сплеску
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // Підтягування піну
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Налаштування пінів для світлодіодів (PA5, PA6, PA7, PA8)
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;  // Піні PA5, PA6, PA7, PA8
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Режим виходу
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void MX_USART2_UART_Init(void) {
    UART_HandleTypeDef huart2;

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
}

void MX_TIM6_Init(void) {
    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 15999;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 999;
    htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim6.Init.RepetitionCounter = 0;

    if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
        Error_Handler();
    }
}

void MX_EXTI0_Init(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(EXTI0_IRQn);  // Включення переривання для EXTI0
}

int main(void) {
    HAL_Init();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM6_Init();
    MX_EXTI0_Init();

    if (HAL_TIM_Base_Start_IT(&htim6) != HAL_OK) {
        Error_Handler();
    }

    while (1) {
    }
}

void Error_Handler(void) {
    while (1) {
    }
}

void EXTI0_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        // Логіка, коли кнопка натиснута
    }
}
