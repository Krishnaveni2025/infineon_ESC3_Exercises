#include <stdio.h>
#include <stdint.h>
#include "./../Special_Libraries/cmsis_gcc.h"
#include "./../Special_Libraries/reset.h"
#include "./../Device_Drivers/GPIO/gpio.h"

uint8_t app_heap[512] __attribute__((section(".heap")));
uint8_t app_stack[4096] __attribute__((section(".stack")));

/* LED Port/Pin Definitions */
#define LED13_PORT_DR ((volatile uint32_t *)0x40040500) // P5.7
#define LED13_PORT_PC ((volatile uint32_t *)0x40040508)
#define LED13_PIN 7

#define LED12_PORT_DR ((volatile uint32_t *)0x40040500) // P5.5
#define LED12_PORT_PC ((volatile uint32_t *)0x40040508)
#define LED12_PIN 5

#define LED11_PORT_DR ((volatile uint32_t *)0x40040500) // P5.2
#define LED11_PORT_PC ((volatile uint32_t *)0x40040508)
#define LED11_PIN 2

#define LED10_PORT_DR ((volatile uint32_t *)0x40040200) // P2.2
#define LED10_PORT_PC ((volatile uint32_t *)0x40040208)
#define LED10_PIN 2

#define LED09_PORT_DR ((volatile uint32_t *)0x40040200) // P2.0
#define LED09_PORT_PC ((volatile uint32_t *)0x40040208)
#define LED09_PIN 0

#define LED08_PORT_DR ((volatile uint32_t *)0x40040100) // P1.6
#define LED08_PORT_PC ((volatile uint32_t *)0x40040108)
#define LED08_PIN 6

#define LED07_PORT_DR ((volatile uint32_t *)0x40040100) // P1.4
#define LED07_PORT_PC ((volatile uint32_t *)0x40040108)
#define LED07_PIN 4

#define LED06_PORT_DR ((volatile uint32_t *)0x40040100) // P1.2
#define LED06_PORT_PC ((volatile uint32_t *)0x40040108)
#define LED06_PIN 2

#define LED05_PORT_DR ((volatile uint32_t *)0x40040100) // P1.0
#define LED05_PORT_PC ((volatile uint32_t *)0x40040108)
#define LED05_PIN 0

/* Button Definitions */
#define BUTTON_PORT_DR ((volatile uint32_t *)0x40040300) // P3.7
#define BUTTON_PORT_PC ((volatile uint32_t *)0x40040308)
#define BUTTON_PORT_INTR_CFG ((volatile uint32_t *)0x4004030C)
#define BUTTON_PORT_INTR ((volatile uint32_t *)0x40040310)
#define BUTTON_PORT_PS ((volatile uint32_t *)0x40040304)
#define BUTTON_PIN 7

/* Global Variables */
volatile uint8_t keyPressDetected = 0;
volatile uint8_t currentSequence = 0; // 0: Idle, 1: Seq1, 2: Seq2

typedef struct
{
    volatile uint32_t *port_dr;
    uint32_t pin;
} LedConfig;

LedConfig sequence1[] = {
    {LED10_PORT_DR, LED10_PIN},
    {LED09_PORT_DR, LED09_PIN},
    {LED08_PORT_DR, LED08_PIN},
    {LED07_PORT_DR, LED07_PIN},
    {LED06_PORT_DR, LED06_PIN},
    {LED05_PORT_DR, LED05_PIN},
    {LED11_PORT_DR, LED11_PIN},
    {LED12_PORT_DR, LED12_PIN},
    {LED13_PORT_DR, LED13_PIN}};

LedConfig sequence2[] = {
    {LED13_PORT_DR, LED13_PIN},
    {LED12_PORT_DR, LED12_PIN},
    {LED11_PORT_DR, LED11_PIN},
    {LED05_PORT_DR, LED05_PIN},
    {LED06_PORT_DR, LED06_PIN},
    {LED07_PORT_DR, LED07_PIN},
    {LED08_PORT_DR, LED08_PIN},
    {LED09_PORT_DR, LED09_PIN},
    {LED10_PORT_DR, LED10_PIN}};

void DelayWithCheck(uint32_t delayNumber);
void TurnOffAllLeds(void);
void InitLeds(void);

int main()
{
    /* Enable Interrupts at CPU level */
    enable_irq();

    /* Initialize LEDs */
    InitLeds();
    TurnOffAllLeds();

    /* Initialize Button */
    *BUTTON_PORT_PC = (*BUTTON_PORT_PC) | (2 << (BUTTON_PIN * 3)); // Digital Input resistive pull up
    *BUTTON_PORT_DR = (1 << BUTTON_PIN);                           // Default output value 1
    *BUTTON_PORT_INTR_CFG = (2 << (BUTTON_PIN * 2));               // Falling edge interrupt

    /* Set priority level of the P3.7 user button (CM0P_IPRx) */
    *((uint32_t *)0xE000E400) = (3 << 30);

    /* Clearing and enabling the GPIO interrupt in NVIC for IRQ3 */
    *((uint32_t *)0xE000E280) = 0xFFFFFFFF; // (CM0P_ICPR)
    *((uint32_t *)0xE000E100) = (1 << 3);   // (CM0P_ISER)

    for (;;)
    {
        if (currentSequence == 0)
        {
            // Idle state, do nothing, wait for interrupt
            TurnOffAllLeds();
        }
        else if (currentSequence == 1)
        {
            for (int i = 0; i < 9; i++)
            {
                if (keyPressDetected)
                    break;

                TurnOffAllLeds();
                *(sequence1[i].port_dr) &= ~(1 << sequence1[i].pin); // Turn ON (Active Low: 0)
                DelayWithCheck(500000);                              // Adjust delay as needed

                if (keyPressDetected)
                    break;
            }
        }
        else if (currentSequence == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                if (keyPressDetected)
                    break;

                TurnOffAllLeds();
                *(sequence2[i].port_dr) &= ~(1 << sequence2[i].pin); // Turn ON (Active Low: 0)
                DelayWithCheck(500000);                              // Adjust delay as needed

                if (keyPressDetected)
                    break;
            }
        }

        if (keyPressDetected)
        {
            keyPressDetected = 0;
            // State transition logic is handled in ISR or here?
            // Requirement: "Seq1, Seq1... KP -> Seq2"
            // If we are here, it means keyPressDetected was set.
            // The ISR updates the state.
        }
    }

    return 0;
}

void InitLeds(void)
{
    // Configure all LED pins as Digital Output Push Pull (Drive Mode 6)
    // Note: This overwrites PC register for pins in same port if not careful.
    // Ideally Read-Modify-Write, but for this simple bare metal, direct assignment to specific bits is safer if we know the layout.
    // However, since multiple LEDs are on same port, we MUST use Read-Modify-Write for PC register or set them carefully.

    // Port 1: 0, 2, 4, 6
    *LED05_PORT_PC &= ~(7 << (LED05_PIN * 3));
    *LED05_PORT_PC |= (6 << (LED05_PIN * 3));
    *LED06_PORT_PC &= ~(7 << (LED06_PIN * 3));
    *LED06_PORT_PC |= (6 << (LED06_PIN * 3));
    *LED07_PORT_PC &= ~(7 << (LED07_PIN * 3));
    *LED07_PORT_PC |= (6 << (LED07_PIN * 3));
    *LED08_PORT_PC &= ~(7 << (LED08_PIN * 3));
    *LED08_PORT_PC |= (6 << (LED08_PIN * 3));

    // Port 2: 0, 2
    *LED09_PORT_PC &= ~(7 << (LED09_PIN * 3));
    *LED09_PORT_PC |= (6 << (LED09_PIN * 3));
    *LED10_PORT_PC &= ~(7 << (LED10_PIN * 3));
    *LED10_PORT_PC |= (6 << (LED10_PIN * 3));

    // Port 5: 2, 5, 7
    *LED11_PORT_PC &= ~(7 << (LED11_PIN * 3));
    *LED11_PORT_PC |= (6 << (LED11_PIN * 3));
    *LED12_PORT_PC &= ~(7 << (LED12_PIN * 3));
    *LED12_PORT_PC |= (6 << (LED12_PIN * 3));
    *LED13_PORT_PC &= ~(7 << (LED13_PIN * 3));
    *LED13_PORT_PC |= (6 << (LED13_PIN * 3));
}

void TurnOffAllLeds(void)
{
    // Turn OFF all LEDs (Active Low: Set to 1)
    *LED05_PORT_DR |= (1 << LED05_PIN);
    *LED06_PORT_DR |= (1 << LED06_PIN);
    *LED07_PORT_DR |= (1 << LED07_PIN);
    *LED08_PORT_DR |= (1 << LED08_PIN);
    *LED09_PORT_DR |= (1 << LED09_PIN);
    *LED10_PORT_DR |= (1 << LED10_PIN);
    *LED11_PORT_DR |= (1 << LED11_PIN);
    *LED12_PORT_DR |= (1 << LED12_PIN);
    *LED13_PORT_DR |= (1 << LED13_PIN);
}

void DelayWithCheck(uint32_t delayNumber)
{
    for (uint32_t i = 0; i < delayNumber; i++)
    {
        if (keyPressDetected)
            return;
    }
}

/* Interrupt handler for the button */
void ioss_interrupts_gpio_3_IRQHandler(void)
{
    uint32_t readVal;

    /* Clear the interrupt status */
    *BUTTON_PORT_INTR = (1 << BUTTON_PIN);

    readVal = *BUTTON_PORT_PS;
    // Check if button is pressed (Active Low usually, so 0)
    if (((readVal >> BUTTON_PIN) & 1) == 0u)
    {
        // Simple Debounce (blocking in ISR is bad, but for this simple logic...)
        // Better: just set flag and let main loop handle it.
        // But we need to toggle state here to ensure we capture the event.

        // Wait, if I hold the button, this might trigger multiple times if not careful?
        // Edge detection is configured.

        keyPressDetected = 1;

        if (currentSequence == 0)
        {
            currentSequence = 1;
        }
        else if (currentSequence == 1)
        {
            currentSequence = 2;
        }
        else if (currentSequence == 2)
        {
            currentSequence = 1;
        }
    }
}
