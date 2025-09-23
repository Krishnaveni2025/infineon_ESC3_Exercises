// Simple LED blink program for ESP32 using direct register access (no libraries)
// - LED on GPIO2 toggles continuously.
// - Switch on GPIO5 changes blink period:
//     pressed -> blink period 4 ms (ON 4 ms / OFF 4 ms)
//     not pressed -> blink period 2 ms (ON 2 ms / OFF 2 ms)

// It uses direct GPIO register access. The switch should be wired so the
// input is in a defined state (e.g. use an external pull-up or pull-down).

// GPIO registers (ESP32 legacy addresses)
volatile unsigned int *GPIO_OUT_W1TS = (volatile unsigned int *)(0x3FF44008);
volatile unsigned int *GPIO_OUT_W1TC = (volatile unsigned int *)(0x3FF4400C);
volatile unsigned int *GPIO_ENABLE_W1TS = (volatile unsigned int *)(0x3FF44024);
volatile unsigned int *GPIO_ENABLE_W1TC = (volatile unsigned int *)(0x3FF44028);
volatile unsigned int *GPIO_IN_REG = (volatile unsigned int *)(0x3FF4403C);

const int BLINK_GPIO = 2;
const int SWITCH_GPIO = 5;

static void delay_ms(int ms)
{
    volatile int count = 0;
    for (int i = 0; i < ms * 16000; i++)//- It gives a delay that feels close to 1 ms per unit on real hardware

    {
        count++;
    }
}

void app_main(void)
{
    // Configure BLINK_GPIO as output
    *GPIO_ENABLE_W1TS = (1 << BLINK_GPIO);

    // Configure SWITCH_GPIO as input: clear its enable bit
    *GPIO_ENABLE_W1TC = (1 << SWITCH_GPIO);

    while (1)
    {
        // Read switch level from GPIO_IN register
        unsigned int in = *GPIO_IN_REG;
        int switch_level = (in & (1 << SWITCH_GPIO)) ? 1 : 0;

        // Assume active-low switch: pressed -> 0
        int period_ms = (switch_level == 0) ? 4 : 2;

        // LED ON
        *GPIO_OUT_W1TS = (1 << BLINK_GPIO);
        delay_ms(period_ms);

        // LED OFF
        *GPIO_OUT_W1TC = (1 << BLINK_GPIO);
        delay_ms(period_ms);
    }
}