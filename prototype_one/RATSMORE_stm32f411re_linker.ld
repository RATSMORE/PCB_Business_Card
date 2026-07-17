/*
STM32 primarily uses two address locations; read-only flash memory and read-write sram. The origin and length of each
can likely be found in the memory map section of the microcontroller datasheet
*/

ENTRY(Reset_Handler) /* First code to run after power on */

MEMORY /* Different memory regions. Starting addresses and sizes can be found in the datasheet */
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/*
SECTIONS defines where certain memory (text, bss, etc) is placed within the memory sections we defined
*/
SECTIONS /* How we split up the memory regions defined in the last snippet */
{
    .text : 
    {
        *(.isr_vector)  /* Vector table handles all exceptions and interrupts, and starts with the stack pointer and reset handler*/
        *(.text)    /* Contains the executable code. Merges the contents of the .text for each file (main and startup)*/
        *(.rodata)  /* Contains constant values (const, strings, etc) */
        . = ALIGN(4); /* We should align our addresses to multiples of 4*/
        _etext = .; /* Store the value of the location counter into the end of text */
    } > FLASH


    /*
    data section contains variables whose values can change. Is stored in flash so it can exist on startup, but is immediately
    moved to SRAM
    */
    .data : 
    {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH



    .bss : /* Zero-initialized data*/
    {
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM
}