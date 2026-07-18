/*
    This prototype will focus on simply toggling LED output based on the rising edge interrupt of
    a push-button. To implement this, a NUCLEO-F411RE board's user LED and push-button will be used.
*/

#include <stdint.h>
/* definitions related to the LED pin*/
#define RCC_BASE            (0x40023800U)
#define RCC_AHB1ENR         *((volatile unsigned int*) (RCC_BASE + 0x30U))
#define GPIOAEN             (1U)
#define GPIOA_BASE          (0x40020000U)
#define GPIOA_MODER         *((volatile unsigned int*) (GPIOA_BASE))
#define LED_PIN_MODER       (10U)
#define GPIOA_ODR           *((volatile unsigned int*) (GPIOA_BASE + 0x14U))
#define LED_PIN_ODR         (1U << 5U)

/* Definition related to the push-button setup */
#define GPIOCEN             (1U << 2U)
#define GPIOC_BASE          (0x40020800U)
#define GPIOC_MODER         *((volatile unsigned int*) (GPIOC_BASE))
#define BUTTON_PIN_MODER    (26U)
#define GPIOC_PUPDR         *((volatile unsigned int*) (GPIOC_BASE + 0x0CU))
#define BUTTON_PIN_PUPDR    (26U)

/* Definitions related to the push-button interrupt */
#define EXTI_BASE           (0x40013C00U)
#define EXTI_IMR            *((volatile unsigned int*) (EXTI_BASE))
#define BUTTON_INT_IMR      (1U << 13U)
#define EXTI_FTSR           *((volatile unsigned int*) (EXTI_BASE + 0x0CU))
#define BUTTON_INT_FTSR     (1U << 13U)
#define NVIC_BASE           (0xE000E100U)
#define NVIC_ISER1          *((volatile unsigned int*) (NVIC_BASE + 0x04U))
#define EXTI13_IQR_POS      (8U)
#define SYSCFG_BASE         (0x40013800U)
#define SYSCFG_EXTICR4      *((volatile unsigned int*) (SYSCFG_BASE + 0x14U))
#define BUTTON_PIN_CR4      (0b10U << 4U)
#define RCC_APB2ENR         *((volatile unsigned int*) (RCC_BASE + 0x44U))
#define APB2ENR_SYSCFG      (1U << 14U)
#define EXTI_PR             *((volatile unsigned int*) (EXTI_BASE + 0x14U))



#define GPIOC_IDR           *((volatile unsigned int*) (GPIOC_BASE + 0x10))

void configure_LED_pin(void);
void configure_button_pin(void);
void configure_button_interrupt(void);
void EXTI15_10_Handler(void);

int main()
{
    configure_LED_pin();
    configure_button_pin();
    configure_button_interrupt();
    
   /* while(1)
    {
        if (GPIOC_IDR & (1U << 13U)) //check if the button is not pressed
        {
            GPIOA_ODR |= (1U << 5U); //turn on the led
        } else {
            GPIOA_ODR &= ~(1U << 5U);
        }
    }*/
   while(1);
}


void configure_LED_pin(void) // Just set PA5 to output mode
{
    RCC_AHB1ENR |= GPIOAEN;
    GPIOA_MODER &= ~(0b11 << LED_PIN_MODER); // Clearing bits before setting to output
    GPIOA_MODER |= (0b01 << LED_PIN_MODER);
}

void configure_button_pin(void) // Set PC13 to input and pulldown
{
    RCC_AHB1ENR |= GPIOCEN;
    GPIOC_MODER &= ~(0b11 << BUTTON_PIN_MODER); // Clearing before setting input type
    GPIOC_PUPDR &= ~(0b11 << BUTTON_PIN_PUPDR);
    GPIOC_PUPDR |= (0b01 << BUTTON_PIN_PUPDR); // must be 01 on nucleo because it has external wiring to pullup
}

void configure_button_interrupt(void) /* Set it so pushing the button results in an interrupt */
{
    RCC_APB2ENR |= APB2ENR_SYSCFG; // enable syscfg clock
    //SYSCFG_EXTICR4 &= ~(0b1111U << BUTTON_PIN_CR4);
    SYSCFG_EXTICR4 |= BUTTON_PIN_CR4; // Set it for port C pin 13

    
    EXTI_FTSR |= BUTTON_INT_FTSR; // Set it to falling edge interrupt
    EXTI_IMR |= BUTTON_INT_IMR; // Unmask EXTI13 interrupt
    NVIC_ISER1 = (1U << 8U); // interrupt enable
    //EXTI_PR = (1U << 13U);       // Clear pending flag by writing a 1 back to the register

}

void EXTI15_10_Handler(void)
{
    
    if (EXTI_PR & (1U << 13U)) 
    {
        EXTI_PR = (1U << 13U);       // Clear pending flag by writing a 1 back to the register
        GPIOA_ODR ^= LED_PIN_ODR;    // Toggle PA5 User LED
        
    }
}