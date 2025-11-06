/***************************************************************************//**
* Linker file for the GNU C compiler.
********************************************************************************/
/*--------------------- Flash Configuration ---------------------------------*/
__FLASH_START = 0x00000000;
__FLASH_SIZE =  0x00020000;

/*--------------------- Embedded RAM Configuration ----------------------------*/
__RAM_START = 0x20000000;
__RAM_SIZE =  0x00004000; /* 16KB */

/* Define the explicit LMA address for the custom section */
__COSMIC_LMA_ADDR = 0X00003000;

/*--------------------- Stack Configuration ---------------------------------*/
__STACK_SIZE = 0x00001000; /* 4KB */
__HEAP_SIZE = 0x00000200; /* 512B */

/* Added semicolons to the end of all assignments */
__STACK_START = __RAM_START + __RAM_SIZE;
__STACK_END = __STACK_START - __STACK_SIZE;

__HEAP_START = __STACK_END - __HEAP_SIZE;
__HEAP_END = __STACK_END; /* Corrected assignment */


ENTRY(Reset_handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = __FLASH_START, LENGTH = __FLASH_SIZE
  RAM   (rwx) : ORIGIN = __RAM_START,   LENGTH = __RAM_SIZE
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.init*)
        *(.fini*)
		. = ALIGN(4);
		*(.rodata .rodata.*)  
        . = ALIGN(4);
        __etext = .; /* End of text in FLASH */
    } > FLASH 

    /* Standard .data section, define LMA after the section block */
    .data :
    {
        __data_start = .;
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > RAM AT > FLASH
    _la_data = LOADADDR(.data);


    .bss :
    {
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .; /* End of BSS in RAM */
        end = .;
        __end__ = .;
    } > RAM

    /* 
     * *** THE CRITICAL SECTION DEFINITION (Universally Compatible Syntax) ***
     * We define the VMA location first, then use AT for the LMA location.
     */
    .cosmic_constellation : AT(0x00003000)
  {
    __cosmic_constellation_start_vma = .;
    __cosmic_constellation_end_vma = . + SIZEOF(.cosmic_constellation);
  } > RAM

  _start_cosmic_constellation_lma = LOADADDR(.cosmic_constellation);

    .heap (NOLOAD) :
    {
        . = ABSOLUTE (__HEAP_START);
		*(.heap)
		. = ALIGN(4);
    } > RAM 
	
    .stack (NOLOAD) :
    {
        . = ABSOLUTE (__STACK_END);
		*(.stack)
    } > RAM   
}
/* EOF */

