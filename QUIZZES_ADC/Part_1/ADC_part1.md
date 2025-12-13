From the SAR ADC specifications chapter of the datasheet, find out the values of the resistance and capacitance of the S&H circuit.
Ans: Resistance and Capacitance of the S&H Circuit: According to the
"SAR ADC specifications" in the Datasheet (Table 14):
    Input Resistance (A_INRES): 2.2 kΩ (Max)
    Input Capacitance (A_INCAP): 10 pF (Max)
<img width="1228" height="630" alt="image" src="https://github.com/user-attachments/assets/39897b92-9328-48bf-ae6b-fb346ded994d" />

From the datasheet, find out the the name of the power supply rail supplying the ADC reference to the SAR converter.
Ans: Power Supply Rail Supplying ADC Reference: The power supply rail
providing the ADC reference is VDDA. (The datasheet indicates the
internal reference is derived from VDDA, and the block diagram shows
VDDA/2 or VREF).
<img width="1221" height="639" alt="image" src="https://github.com/user-attachments/assets/7353bedf-11bf-4e54-a022-dfad640864d0" />

From the schematic, trace the origin of this power supply rail. Where does it come from, what is its name and what is the voltage supplied?
Ans: Name: VDDA (Analog Supply), which is connected to VDDD (Digital
Supply) and the VTARG rail on the schematic.
Origin: The rail originates from the USB VBUS (Pin 1 of connector J8)
on the KitProg2 section of the board.
Voltage: 5V (Standard USB Voltage). As per the schematic, VBUS from
the USB connector supplies power to the board (VTARG), passes through
a diode (D1), and powers the PSoC 4 device.
VDDA---->VDDD----->VTARG---->VBUS(Pin 1 of USB microconnector J8)
<img width="619" height="144" alt="image" src="https://github.com/user-attachments/assets/e3a0a93c-8d9c-4672-99cb-f099dc2508fd" />
<img width="573" height="331" alt="image" src="https://github.com/user-attachments/assets/16494d60-6022-4c21-b3f4-e35509d32522" />
