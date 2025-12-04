
Understand Figure-9.1 of Chapter-9. There are 3 clock sources which can be pressed into service for supplying clock to the rest of the chip. They are EXTCLK, IMO and the PLL sub-system.

<img width="1404" height="836" alt="image" src="https://github.com/user-attachments/assets/3c3b9cdf-1f84-40ca-9687-c489944aa686" />

 
<img width="1406" height="789" alt="image" src="https://github.com/user-attachments/assets/5364c6ce-2690-4814-895b-8c47bbe87199" />

<img width="1010" height="786" alt="image" src="https://github.com/user-attachments/assets/6e4c7138-1146-423c-b653-7ca314f8f5c6" />
<img width="578" height="712" alt="image" src="https://github.com/user-attachments/assets/0fefa411-dcb4-47f7-b2db-a1a50dd7f56a" />

**1. IMO generates by default 24 MHz. Choosing IM as the clock source, what should be the programming sequence to deliver 12 MHz to the HFCLK net?**
Ans: 
     The 24 MHz should be divided by 2 to get 12MHz at HFCLK, so we should select the HFCLK predivider value.
     To set the HFCLK predivider to 2, write the binary value 01 to bits [3:2] of the CLK_SELECT register at address 0x40030028.

**2. Assume EXTCLK to be 48 MHz. Choosing EXTCLK as the clock source, What should be the programming sequence to deliver 12 MHz to the HFCLK net?**
Ans: <img width="920" height="636" alt="image" src="https://github.com/user-attachments/assets/2e73e837-6ba1-41ed-9c8a-4e162ad295f1" />
     <img width="948" height="616" alt="image" src="https://github.com/user-attachments/assets/9d80fbbf-235e-4d57-b759-5d9c2ea38766" />
     <img width="1211" height="252" alt="image" src="https://github.com/user-attachments/assets/57fa5152-4071-4429-8f67-38b9ab082bd2" />
     <img width="980" height="627" alt="image" src="https://github.com/user-attachments/assets/bb67f264-86c7-4515-8aba-2232a07393fd" />
     <img width="987" height="829" alt="image" src="https://github.com/user-attachments/assets/d2154482-9272-4bae-b1bd-b9eb29a27c03" />





**3. Assume that the PLL sub-system has been configured to generate 200 MHz. How will you route this clock to HFCLK net?**
Ans:



**4. IMO generates by default 24 MHz. Choosing IM as the clock source, what should be the programming sequence to deliver 24 MHz to the ADC peripheral?**
Ans:
