/*
This file contains the startup script for the microcontroller, and runs before the main code starts

We assign vectors in the vector table

*/

#include <stdint.h>
/* We define the start, end, and size of SRAM as we need to load our interrupts */
#define SRAM_START (0x20000000U)
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)


#define STACK_START (SRAM_END)


extern int main(void);

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); /* These aliases to default handler has it so addr of that*/
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVCall_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Debug_Monitor_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSv_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Systick_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI16_PVD_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI21_TAMP_STAMP_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI22_RTC_WAKEUP_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI17_RTC_Alarm_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI18_OTG_FS_WKUP_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));


void Default_Handler(void);

/* We represent the vector table as an array of handler addresses */
/* We have to specify the section, otherwise it would end up going to data */
uint32_t vector_table[] __attribute__((section (".isr_vector"))) =
{

    (uint32_t)STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0, /*Reserved spaces*/
    0,
    0,
    0,
    (uint32_t)&SVCall_Handler,
    (uint32_t)&Debug_Monitor_Handler,
    0,
    (uint32_t)&PendSv_Handler,
    (uint32_t)&Systick_Handler,

    (uint32_t)&WWDG_Handler,
    (uint32_t)&EXTI16_PVD_Handler,
    (uint32_t)&EXTI21_TAMP_STAMP_Handler,
    (uint32_t)&EXTI22_RTC_WAKEUP_Handler,
    (uint32_t)&FLASH_Handler,
    (uint32_t)&RCC_Handler,
    (uint32_t)&EXTI0_Handler,
    (uint32_t)&EXTI1_Handler,
    (uint32_t)&EXTI2_Handler,
    (uint32_t)&EXTI3_Handler,
    (uint32_t)&EXTI4_Handler,
    (uint32_t)&DMA1_Stream0_Handler,
    (uint32_t)&DMA1_Stream1_Handler,
    (uint32_t)&DMA1_Stream2_Handler,
    (uint32_t)&DMA1_Stream3_Handler,
    (uint32_t)&DMA1_Stream4_Handler,
    (uint32_t)&DMA1_Stream5_Handler,
    (uint32_t)&DMA1_Stream6_Handler,
    (uint32_t)&ADC_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&EXTI9_5_Handler,
    (uint32_t)&TIM1_BRK_TIM9_Handler,
    (uint32_t)&TIM1_UP_TIM10_Handler,
    (uint32_t)&TIM1_TRG_COM_TIM11_Handler,
    (uint32_t)&TIM1_CC_Handler,
    (uint32_t)&TIM2_Handler,
    (uint32_t)&TIM3_Handler,
    (uint32_t)&TIM4_Handler,
    (uint32_t)&I2C1_EV_Handler,
    (uint32_t)&I2C1_ER_Handler,
    (uint32_t)&I2C2_EV_Handler,
    (uint32_t)&I2C2_ER_Handler,
    (uint32_t)&SPI1_Handler,
    (uint32_t)&SPI2_Handler,
    (uint32_t)&USART1_Handler,
    (uint32_t)&USART2_Handler, 
    0,
    (uint32_t)&EXTI15_10_Handler,
    (uint32_t)&EXTI17_RTC_Alarm_Handler,
    (uint32_t)&EXTI18_OTG_FS_WKUP_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&DMA1_Stream7_Handler,
    (uint32_t)&SDIO_Handler,
    (uint32_t)&TIM5_Handler,
    (uint32_t)&SPI3_Handler,
    (uint32_t)&DMA2_Stream0_Handler,
    (uint32_t)&DMA2_Stream1_Handler,
    (uint32_t)&DMA2_Stream2_Handler,
    (uint32_t)&DMA2_Stream3_Handler,
    (uint32_t)&DMA2_Stream4_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&OTG_FS_Handler,
    (uint32_t)&DMA2_Stream5_Handler,
    (uint32_t)&DMA2_Stream6_Handler,
    (uint32_t)&DMA2_Stream7_Handler,
    (uint32_t)&USART6_Handler,
    (uint32_t)&I2C3_EV_Handler,
    (uint32_t)&I2C3_ER_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&FPU_Handler,
    0,
    0,
    (uint32_t)&SPI4_Handler,
    (uint32_t)&SPI5_Handler
};



void Reset_Handler(void) /* Gets called first. Here we need to initialize the RAM data (data and bss). Lastly call main*/
{
    /* Copying the data contents from flash to SRAM */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata; /* The size of data we want to copy .data to sram*/
    uint8_t* pDest = (uint8_t*)_sdata; /* SRAM */
    uint8_t* pSrc = (uint8_t*)_etext; /* Flash */
    for(uint32_t i = 0; i < size; i++)
    {
        *pDest++ = *pSrc++; /* Write the value from the source in flash to the destination in SRAM*/
    }

    /* Initializing the data in bss to zero */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDest = (uint8_t*)_sbss;
    for(uint32_t i = 0; i < size; i++)
    {
        *pDest++ = 0;
    }

    /* Finally call main() */
    main();
}

void Default_Handler(void) /*Infinite loop. Interrupts aliased to this should be rewritten when needed*/
{
    while(1);
}