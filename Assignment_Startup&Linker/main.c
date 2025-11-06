#include <stdio.h>
#include <stdint.h>
#include "./../Special_Libraries/reset.h"
#include <string.h>

extern uint32_t __cosmic_constellation_start_vma[];
extern uint32_t __cosmic_constellation_end_vma[];
extern uint32_t _start_cosmic_constellation_lma[];

uint8_t app_heap[512] __attribute__((section(".heap")));
uint8_t app_stack[1024] __attribute__((section(".stack")));

void Delay(uint32_t);
uint32_t var1 = 50u;       // initialized global var
uint32_t var2;             // un initialized global var
const uint32_t var3 = 50u; // constant
volatile uint32_t var6;    // volatile variable

uint32_t stars[5] __attribute__((section(".cosmic_constellation"))) = {11, 22, 33, 44, 55};

int main()
{
  // Local variables are on the stack and help verify execution flow
  uint32_t var4 = 0xAA;
  uint32_t var5 = 0xBB;
  // Check initial values in RAM (VMA: 0x20000000)
  // Place your first breakpoint on the next line
  volatile uint32_t star_value_0_original = stars[0]; // Should be 11
  volatile uint32_t star_value_4_original = stars[4]; // Should be 55

  // Modify the array in RAM
  stars[0] = 100;
  stars[1] = 200;

  // Place your second breakpoint here to inspect modified values
  volatile uint32_t star_value_0_modified = stars[0]; // Should be 100
  volatile uint32_t star_value_1_modified = stars[1]; // Should be 200

  Delay(60000);

  // Infinite loop to keep the program running for debugging
  for (;;)
  {
    var5 = var1 + var2 + var3 + var4;
    var6 = var5 + 50u;
    Delay(10000);
  }
  return 0; // Unreachable but good practice
}

void Delay(uint32_t delayNumber)
{
  for (uint32_t i = 0; i < delayNumber; i++)
    ;
  for (uint32_t i = 0; i < delayNumber; i++)
    ;
}
