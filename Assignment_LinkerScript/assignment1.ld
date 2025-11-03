/* Assignment-1 
 * Microcontroller Memory Layout:
 * - FLASH: 4MB at 0x20000000
 * - SRAM1: 128KB at 0x30000000
 * - SRAM2: 32KB at 0x40000000
 */

MEMORY
{
    FLASH    (rx)  : ORIGIN = 0x20000000, LENGTH = 0x00400000
    SRAM1    (rw)  : ORIGIN = 0x30000000, LENGTH = 0x00020000
    SRAM2    (rw)  : ORIGIN = 0x40000000, LENGTH = 0x00008000
}

SECTIONS
{
    /* Output section: .flashsections → FLASH
     * Includes: .text and .rodata
     */
    .flashsections :
    {
        __stext = .;
        *(.text)
        *(.text.*)
        __etext = .;

        __srodata = .;
        *(.rodata)
        *(.rodata.*)
        __erodata = .;
    } > FLASH

    /* Output section: .rwdata → SRAM1
     * Includes: .data and .bss
     */
    .rwdata :
    {
        __sdata = .;
        *(.data)
        *(.data.*)
        __edata = .;

        __sbss = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        __ebss = .;
    } > SRAM1

    /* Output section: .criticaltext → SRAM2
     * Includes: .criticaltext
     */
    .criticaltext :
    {
        __scritical = .;
        KEEP(*(.criticaltext))
        __ecritical = .;
    } > SRAM2

    _end = .;
}