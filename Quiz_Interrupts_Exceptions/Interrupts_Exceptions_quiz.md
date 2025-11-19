**1.The CPU is executing a regular thread when an interrupt occurs. The SP at the time of the interrupt contains a value of 0x2000C0B0. From the class, you know that the CPU automatically stores the context of the interrupted thread on the stack before executing the ISR. What will be the value of the SP when the program control enters ISR?**



ans: when an interrupt occurs and enters into isr the CPU Updates the Stack Pointer by deducting 32 from its old value

so, old SP = 0x2000C0B0

&nbsp;   new SP = old SP - 0x20(32 in decimal)

&nbsp;   SP(during ISR)  = 0x2000C0B0 - 0x20 = 0x2000C090

&nbsp;



**2.Suppose the ISR code utilizes R8 and R9. These were also used by the interrupted program. What will be the first obligation of the ISR? Will there be a change in SP? If so, what will the new value be? If no change, then explain why?**

ans: 

1\. SP Value upon ISR Entry: From our previous calculation, the SP value when control entered the ISR was 0x2000C090 (after the CPU deducted 32 bytes for the automatic context save).

2\. Saving R8 and R9: Two 32-bit registers (R8 and R9) must be pushed onto the stack. This requires 2×4 bytes (assuming standard word size for registers) =8 bytes (0x8 in hexadecimal) of storage.

3\. New SP Calculation: The SP is decremented by 8 bytes: 

0x2000C090-0x8=0x2000C088

The new value of the Stack Pointer after the ISR saves R8 and R9 will be 0x2000C088.

&nbsp;



**3.You have enabled IRQ-3 and IRQ-17. You have set their priority levels to 2 and 1 respectively. What will be the hexadecimal value of data contained in their IPR registers?**

ans:  
      for IRQ3(01) --> IPR0(bits 30,31) = 1000 0000 0000 0000 0000 0000 0000 0000 = 0x80000000

&nbsp;         IRQ17(10)--> IPR4(bits 14,15) = 0000 0000 0000 0000 0100 0000 0000 0000 = 0x00004000



**4.What will be the hexadecimal value of the word that you will write to SETENA register to enable the two IRQs?**

ans: SETENA = 0000 0000 0000 0010 0000 0000 0000 1000  = 0x00020008



**5.Both of the interrupts occur simultaneously. Which of the ISRs will execute first?**

ans: the interrupt having priority 1(01) has highest priority than the interrupt having priority 2(10) so the IRQ-17 will be executed first utill then IRQ-3 will be on pending state.



**6.When the CPU is executing the chosen ISR, what will the hexadecimal value contained in the 6 LSBs of IPSR register?**

ans:  -On the PSOC, there are a total of 44 interrupt entries (16 for Exceptions and 28 for interrupts)

&nbsp;     - 44 interrupts require 6 bits for encoding

&nbsp;     - So read the 6 LSBs of IPSR register

If the CPU is executing the IRQ-3 handler:

When the CPU is executing the IRQ-3 handler, the value in the 6 LSBs of the IPSR register will be 19 in decimal. 

&nbsp;   (19)10 =0x13

If the CPU is executing the IRQ-17 handler:

The sources establish a pattern where an external interrupt (IRQ-N) has an associated IPSR value of 16+N.

For IRQ-17, the calculation is: 16+17=33 (decimal).

​    (33)10=0x21

Therefore, when the CPU is executing the chosen ISR (IRQ-3 or IRQ-17), the 6 LSBs of the IPSR register will contain 0x13 or 0x21, respectively.

**7.In the project that was given to you today (15/Nov), please open the Makefile. What is the code optimization level set to?**

ans: CFLAGS = $(DFLAGS) -g -c -Wall -Wextra -std=gnu11 -O0 -DSEMIHOSTING=$(SEMIHOSTING)
     **the code optimization level set to 0.**



**8.Change the code optimization level to 2 and recompile your project from scratch \[make clean followed by make all]**

ans: CFLAGS = $(DFLAGS) -g -c -Wall -Wextra -std=gnu11 -O2 -DSEMIHOSTING=$(SEMIHOSTING)



**9.Go to Debug\\Application\_Source where main.o must exist**

&nbsp;ans: PS C:\\embedded\_systems\_ifx\\BareMetal\_Interrupt\\Debug\\Application\_Source>

**10.Run arm-none-eabi-objdump -S main.o**

&nbsp;ans: done



**11.This will output C-Assembly mixed code. What assembly instruction do you see right at the start of ioss\_interrupts\_gpio\_3\_IRQHandler?**

6:   b570            push    {r4, r5, r6, lr}

**12.Do you see a reversal of it towards the function end? If so, what is it?**

**ans:**   

 28:   bd70            pop     {r4, r5, r6, pc}

This saves the frame pointer (r7) and return address (lr) onto the stack

.

.

.

 1ba:   bd80            **pop**     {r7, pc} (at the end of ioss\_interrupts\_gpio\_3\_IRQHandler)

This restores r7 and loads the return address into pc, effectively returning from the interrupt.

This push/pop symmetry is a hallmark of ARM Cortex-M interrupt handlers. It ensures that the processor state is preserved and restored correctly across the interrupt execution.

<img width="1699" height="650" alt="image" src="https://github.com/user-attachments/assets/11ee33d9-ec41-48e4-8c8e-ed1a63c31b47" />

