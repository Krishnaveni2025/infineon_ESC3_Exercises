# Optimization Analysis Notes

## Optimization Level 0 (O0)

### Delay Function
```asm
0000015c <Delay>:
 15c:	b580      	push	{r7, lr}
 15e:	b084      	sub	sp, #16
 160:	af00      	add	r7, sp, #0
 162:	6078      	str	r0, [r7, #4]
 164:	2300      	movs	r3, #0
 166:	60fb      	str	r3, [r7, #12]
 168:	e002      	b.n	170 <Delay+0x14>
 16a:	68fb      	ldr	r3, [r7, #12]
 16c:	3301      	adds	r3, #1
 16e:	60fb      	str	r3, [r7, #12]
 170:	68fa      	ldr	r2, [r7, #12]
 172:	687b      	ldr	r3, [r7, #4]
 174:	429a      	cmp	r2, r3
 176:	dbf8      	blt.n	16a <Delay+0xe>
 178:	2300      	movs	r3, #0
 17a:	60bb      	str	r3, [r7, #8]
 17c:	e002      	b.n	184 <Delay+0x28>
 17e:	68bb      	ldr	r3, [r7, #8]
 180:	3301      	adds	r3, #1
 182:	60bb      	str	r3, [r7, #8]
 184:	68ba      	ldr	r2, [r7, #8]
 186:	687b      	ldr	r3, [r7, #4]
 188:	429a      	cmp	r2, r3
 18a:	dbf8      	blt.n	17e <Delay+0x22>
 18c:	46c0      	nop			@ (mov r8, r8)
 18e:	46c0      	nop			@ (mov r8, r8)
 190:	46bd      	mov	sp, r7
 192:	b004      	add	sp, #16
 194:	bd80      	pop	{r7, pc}
```

### Observations (O0)
- **Stack Usage:** The function sets up a stack frame (`push {r7, lr}`, `sub sp, #16`).
- **Variables:** Local variables (loop counters `i`) and arguments (`delayNumber`) are stored on the stack.
- **Register-Stack Relationship:** There is a constant cycle of loading from stack to register, performing an operation (increment, compare), and storing back to stack.
    - `ldr r3, [r7, #12]` (Load `i`)
    - `adds r3, #1` (Increment)
    - `str r3, [r7, #12]` (Store `i`)
- **Efficiency:** This is inefficient because memory access (even stack) is slower than register access, and there are many redundant instructions.

## Optimization Level 2 (O2)
## Optimization Level 2 (O2)

### Delay Function
```asm
000000c0 <Delay>:
  c0:	4770      	bx	lr
  c2:	46c0      	nop			@ (mov r8, r8)
```

### Observations (O2)
- **Delay Function:** The compiler detected that the loop body was empty and had no side effects (since `i` is a local variable and not volatile). It completely removed the loop, reducing the function to a single return instruction (`bx lr`).
- **IRQ Handler:**
    - **Stack Usage:** Significantly reduced. Only `push {r4, r5, r6, lr}` is used to save callee-saved registers. No stack space is allocated for local variables (`sub sp` is gone).
    - **Dead Code Elimination:** The variables `Varint_1` through `Varint_7` were incremented but never used. The compiler removed all instructions related to them.
    - **Register Usage:** Operations are performed directly in registers. There are no redundant load/store operations to the stack.

## Comparison and Conclusion

| Feature | Optimization Level 0 (O0) | Optimization Level 2 (O2) |
| :--- | :--- | :--- |
| **Code Size** | Larger (Delay: ~60 bytes, IRQ: ~230 bytes) | Smaller (Delay: 2 bytes, IRQ: ~60 bytes) |
| **Stack Usage** | Heavy. Local variables on stack. | Minimal. Only for context saving. |
| **Register Usage** | Load-Modify-Store cycle with stack. | Direct register manipulation. |
| **Execution Speed** | Slow. Many memory accesses. | Fast. Optimized instructions, dead code removed. |

**Conclusion:**
Optimization Level 2 (O2) generated code that executed significantly faster.
- The `Delay` function became instantaneous (0 cycles vs thousands).
- The interrupt handler became much shorter and faster by removing unused calculations and minimizing memory access.

QUIZ_TIMERS:

1.You have been asked to write a device driver for a 12 bit timer. The timer clock frequency is 32 KHz. What is the highest count the timer can attain and how long will it take to get there?
Ans: clock period = 31.25u sec
        time = (2^12)*31.25u = 0.128 sec
2.A 12 bit timer is clocked at 1 MHz. Can it generate a 8 ms timeout? Justify your answer.
Ans: No, the 12-bit timer clocked at 1 MHz cannot generate an 8 ms timeout with a single overflow configuration. The maximum timeout period achievable by this configuration is 4.096 ms, which is less than the required 8 ms. The number of required cycles for an 8 ms timeout would be 𝟖𝟎𝟎𝟎, but the 12-bit timer can only count up to 𝟒𝟎𝟗𝟔 cycles.