**01.What name would you give a Silicon imprinted with circuits? Bare \_\_\_\_**



Answer: Bare Die (or Bare Chip).

**02. Google up and find out what kind of transistors are used to fabricate the circuits**



Answer: MOSFETs (Metal-Oxide-Semiconductor Field-Effect Transistors). specifically, most modern ICs use CMOS (Complementary Metal-Oxide-Semiconductor) technology, which uses both N-channel (NMOS) and P-channel (PMOS) MOSFETs. While BJTs are used for specialized high-speed or analog applications. 

**03. Google up and find out the two basic layers that you are likely to find on a silicon with circuits**



Answer: The Silicon Substrate (the base wafer material) and the Interconnect Layers (consisting of Metal wiring and Oxide insulation).

Alternative interpretation: It could also refer to the N-type and P-type doped semiconductor layers. 

**04. Is the silicon directly soldered on to the PCB? If not, what is the arrangement?**



Answer: No, the bare silicon die is rarely soldered directly to the PCB (except in specific Chip-on-Board applications).

Arrangement: The silicon die is typically mounted inside a Package. The die is connected to the package pins via Wire Bonding or Flip-Chip bumps, and the Package is what gets soldered to the PCB.

**05. Can you name at-least two packages? As an example, DIP is one such package. Name another two.**



Answer: QFP (Quad Flat Package), BGA (Ball Grid Array), SOIC (Small Outline Integrated Circuit), QFN (Quad Flat No-leads).

**06. What do you call those I/O gateways on the silicon?**



Answer: Pads (or Bond Pads).

**07. What do you call those I/O gateways on the package?**



Answer: Pins (or Leads, Balls, Lands).

**08. What is a typical relationship between a pad and a pin? Is it 2:1, Many-Many, 1: Many or something else?**



Answer: Typically 1:1 (One Pad connected to One Pin).

Note: Sometimes multiple pads connect to a single pin (e.g., for Power/Ground distribution), making it Many:1.

**09. What material is used to connect a silicon pad to a package pin? And why?**



Answer: Gold (Au) or Aluminum (Al) wire.

Why: Gold is chosen for its excellent electrical conductivity, corrosion resistance, and ductility (ease of drawing into fine wires and bonding). Copper is also increasingly used for lower cost and better conductivity.

**10. Can a pad receive I/O signals from multiple peripherals?**



Answer: Yes, through Multiplexing. The internal circuitry can route the pad to different peripheral controllers inside the chip.

**11. When a pad is directly controlled by software, what mode is that?**



Answer: GPIO (General Purpose Input/Output) mode, often referred to as Bit-Banging when toggling pins manually in software.

**12. Can a pad receive both Input and Output signals?**



Answer: Yes, most pads are Bidirectional (can be configured as Input or Output).

**13. Suppose a pad has been configured as an input to receive a signal from an external sensor. The sensor sends a ‘0’ to signal an event and at all other times, its out is a ‘1’. The line between the sensor and the microcontroller pad is noisy. What measure will you take now?**



Answer: Enable a Pull-up Resistor (internal or external).

Reasoning: Since the idle state is '1' (High), a pull-up resistor ensures the line stays firmly at '1' when the sensor is not driving it low, preventing noise from falsely triggering a '0'. A capacitor to ground (for filtering) or software debouncing can also help.

**14. Swap ‘0’ and ‘1’ in the above question. What measure will you take?**



Answer: Enable a Pull-down Resistor.

Reasoning: If the idle state is '0' (Low) and the event is '1', a pull-down resistor ensures the line stays at '0' when not driven high.

**15. When a semiconductor transistor is fully ON, what is the typical resistance between its terminals (e.g. R\_CE, R\_DS) ?**



Answer: Very Low. Typically in the range of milli-ohms  to a few Ohms , depending on the power rating. Ideally, it acts as a short circuit.

**16. A 5V supply is connected to ground via a 1 k-ohm resistor. What is the current which will have to be sourced by the power supply?**



Answer: 5 mA.

Calculation: I = V/R = 5V/1000 = 0.005A = 5mA.

**17. What is meant by High Load and Low Load? Which one of them requires lower current than the other?**



Answer:

High Load: Draws a large amount of current (implies Low Resistance).

Low Load: Draws a small amount of current (implies High Resistance).

Which requires lower current? Low Load.

**18. If you are given two choices (1 KOhm Resistor, semiconductor transistor) to connect a load to a power supply through one of the two options, what will you choose? And Why?**



Answer: Semiconductor Transistor.

Why: A transistor acts as an efficient switch. It can turn the load fully ON or OFF with minimal power loss (low voltage drop). A resistor would constantly limit current and dissipate power as heat (I^2\*R), and wouldn't allow you to toggle the load effectively.



**19. Suppose you see a Power Supply connected to a semiconductor transistor which in turn is connected to a load. What happens to the load if that transistor is turned OFF?**



Answer: The load is disconnected from the power supply (open circuit), so no current flows through it, and it turns off.

**20. In the above question, how much of a current can the load sink if that transistor were turned ON?**



Answer: The current is determined by the Load Resistance and the Supply Voltage (I = (V\_supply/R\_load)), assuming the transistor can handle that current and has negligible resistance.



**21. In an extreme case, what can parasitic capacitances and inductances of a PCB trace do to a signal exchanged between the microcontroller and a sensor?**



Answer: They can cause Signal Integrity issues such as:

Ringing (oscillations)

Overshoot / Undershoot (voltage spikes)

Crosstalk (interference from neighboring lines)

Propagation Delay (timing errors)

Signal Distortion (rounding of digital edges)

