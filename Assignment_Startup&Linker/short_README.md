
The `.cosmic_constellation` section contains a 5-element `uint32_t` array. It is placed at **LMA `0x00003000`** in FLASH using the `AT()` directive and relocated to **RAM at runtime**, immediately after `.bss`. This ensures the section is initialized from FLASH but accessed from RAM during execution.

---

## 🔧 Linker Symbols Used

Defined in the linker script:

```ld
.cosmic_constellation : AT(0x00003000)
{
  __cosmic_constellation_start_vma = .;
  KEEP(*(.cosmic_constellation))
  __cosmic_constellation_end_vma = . + SIZEOF(.cosmic_constellation);
} > RAM

_start_cosmic_constellation_lma = LOADADDR(.cosmic_constellation);
```

Used in `startup.c`:

```c
extern uint32_t __cosmic_constellation_start_vma[];
extern uint32_t __cosmic_constellation_end_vma[];
extern uint32_t _start_cosmic_constellation_lma[];
```

- `__cosmic_constellation_start_vma[]`: Start of section in RAM (VMA)  
- `__cosmic_constellation_end_vma[]`: End of section in RAM  
- `_start_cosmic_constellation_lma[]`: Start of section in FLASH (LMA)

---

## 🔁 Copy Loop in `Reset_handler`

```c
void relocate_cosmic_constellation(void)
{
    uint32_t *vma_start = __cosmic_constellation_start_vma;
    uint32_t *lma_start = _start_cosmic_constellation_lma;
    uint32_t *vma_end = __cosmic_constellation_end_vma;

    size_t size_bytes = (uint8_t *)vma_end - (uint8_t *)vma_start;

    if (vma_start != lma_start)
    {
        memcpy(vma_start, lma_start, size_bytes);
    }
}
```

This function is called from `Reset_handler()` to copy the section from FLASH to RAM before `main()` executes.

---

## ⚠️ Caveats

- **Alignment**: `. = ALIGN(4)` ensures word alignment before section placement.  
- **Memory sizing**: RAM must accommodate `.bss` and `.cosmic_constellation` without overlap.  
- **Retention**: `KEEP()` ensures the section is not discarded during linking.  
- **Symbol consistency**: Linker and source symbols must match exactly for relocation to succeed.  
- **Safety**: `memcpy()` is guarded by a pointer comparison to avoid redundant copies.

---

## 🖼️ Debugger Verification Screenshots

### 📌  1: RAM View at VMA (`0x2000000C`)
- Shows relocated values: `0x0000000B`, `0x00000016`, `0x00000021`, `0x0000002C`, `0x00000037`
- Confirms successful relocation of `.cosmic_constellation` to RAM

  
<img width="1742" height="159" alt="image" src="https://github.com/user-attachments/assets/c0f3b3b8-eb87-46dc-905a-53899036269f" />


- after modigication during runtime VMA


<img width="1773" height="156" alt="image" src="https://github.com/user-attachments/assets/5ceee613-3b36-4586-8c9f-92b5da6bdbc1" />



### 📌  2: Symbol and Memory Layout
- Displays linker symbols:
  - `_start_cosmic_constellation_lma`
  - `__cosmic_constellation_start_vma`
  - `__cosmic_constellation_end_vma`
- Confirms correct placement and size of the section
  <img width="1416" height="341" alt="image" src="https://github.com/user-attachments/assets/2fc8209f-940d-47db-a63f-ae04ac9d9083" />

### 📌 3: Variable Watch and Execution Flow
- Shows `stars[0]` and `stars[4]` accessed in `main()`
- Verifies modified values (`100`, `200`) after runtime changes
- Confirms execution flow and memory updates

<img width="1766" height="777" alt="image" src="https://github.com/user-attachments/assets/9f1f9165-7de6-45c6-ab81-f7ae4afead3f" />
