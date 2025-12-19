**
Project1:

Please extend the base ADC project shared with you earlier today and implement the following changes:

In the existing project, Channel-0 was defined with certain properties and bound with P2.1
Go ahead and configure another channel of your choice (could be any of Channel-1 through Channel-15) for 8 bit conversion.
After the piece of code which has the Result-0 register being read for extraction of the results of the 12 bit conversion, insert code for 8 bit conversion and eventual extraction of the results.
Follow the 8 bit conversion sequence with 10 bit conversion sequence. This means you will have to configure a third channel with 10 bit conversion properties. You may retain the same sampling time as in the 12 bit case for the 8b and 12b case.
In all three cases, ensure that the LDR does not receive any light. Compare the three results.**
 Here are the two changes made to achieve the conversion:

Channel Configuration: Configured Channels 1 and 2 to use
Sub-Resolution (instead of the default Max Resolution) in their
SAR_CHAN_CONFIG registers.
Dynamic Switching: Added code in the main loop to toggle the global
SUB_RESOLUTION bit in SAR_SAMPLE_CTRL (switching between 8-bit and
10-bit) before triggering each respective conversion.

below screenshot confirms it is working perfectly!

12-bit: 1469
10-bit: 366 (x4 ≈ 1464)
8-bit: 91 (x16 ≈ 1456) All 3 results are consistent.
<img width="368" height="477" alt="ADC_p1" src="https://github.com/user-attachments/assets/d64651bf-f3bb-4b52-bfa6-ffcd28778488" />



 
**
Project2:

Take the base ADC project and modify the results alignment to Left Aligned. Share a screenshot of the result extracted after the conversion. Compare that to the Right Aligned result**
Left Alignment shifts the data to the upper bits (x16) for higher
precision processing, while Right Alignment keeps it in the lower bits
for direct value reading.

<img width="1857" height="471" alt="image" src="https://github.com/user-attachments/assets/f5509aca-82ce-4def-85ec-81610806ee24" />

<img width="1919" height="524" alt="image" src="https://github.com/user-attachments/assets/e1dfd2da-2f76-42be-b5d9-7b9d7d9981fc" />

