## Exercise 01: LED Blink with Switch-Controlled Timing

- LED on GPIO2 blinks continuously
- Switch on GPIO5 changes blink rate:
  - Pressed → 4 ms period
  - Not pressed → 2 ms period
- Uses direct register access (no libraries, no timers, no interrupts)
- Tested on ESP32-WROOM board
