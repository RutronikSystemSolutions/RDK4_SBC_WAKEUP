# RDK4 TLE9262-3BQX SBC "Ignition Signal" Wake Up

Rutronik Development Kit 4 Programmable System-on-Chip CY8C4149AZE-S598 "SBC Ignition Signal Wake Up" Code Example. 

 <img src="images/oscilogram.png" style="zoom:80%;" />

The wake threshold of the TLE9262-3BQX WK3 input is 3V. Once the voltage threshold is crossed on WK3 pin - the wake up event happens. If a TLE9262-3BQX is woken up with a rising edge of the Ignition signal, the system stays 5 seconds online before entering the Sleep Mode. If TLE9262-3BQX is woken up with a falling edge of the Ignition signal, the system goes into the Sleep Mode just right after the initialization.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v3.0

### Using the code example with a ModusToolbox™ IDE:

1. Import the project: **File** > **Import...** > **General** > **Existing Projects into Workspace** > **Next**.
2. Select the directory where **"RDK4_SBC_WAKEUP"** resides and click  **Finish**.
3. Update the libraries using a **"Library Manager"** tool.
4. Select and build the project **Project ** > **Build Project**.

### Operation

The firmware example uses KitProg3 UART for debugging information output. The RDK4 will print the message to the terminal if HIGH or LOW Ignition [Battery] signal has been detected. The CY8C4149AZE-S598 MCU initializes the TLE9262-3BQXV33 to detect static wake up event and puts it into Sleep Mode. During the wake up event, no matter if it is a Ignition-HIGH or Ignition-LOW signal, the MCU is powered up and prints the information as it is shown below.

<img src="images/debug_output.png" style="zoom:100%;" />

The "Ignition Input" is the input "WK3 pin-24" of the TLE9262-3BQXV33 System Basis Chip. The WK3 pin has no internal pull-up or pull-down configuration, since it has an external 10K pull-down resistor R12 connected so the pin is not left "floating". Nevertheless it has a 64μs filter enabled to avoid the false-trigger of the pin due to the electromagnetic interferences that might be present in harsh working environment. The configuration of the wake up pin WK3 resides in the "TLE926x_SPI.h" file.

```
#define CW_WK_CTRL_1 (0x0) /*decimal 0*/

#define CW_WK_CTRL_2 (0x4) /*decimal 4*/

#define CW_WK_FLT_CTRL (0x10) /*decimal 16*/

#define CW_WK_PUPD_CTRL (0x0) /*decimal 0*/
```

### Debugging

If you successfully have imported the example, the debug configurations are already prepared to use with a the KitProg3, MiniProg4, or J-link. Open the ModusToolbox™ perspective and find the Quick Panel. Click on the desired debug launch configuration and wait for the programming to complete and the debugging process to start.

<img src="images/debug_start.png" style="zoom:100%;" />

## Legal Disclaimer

The evaluation board including the software is for testing purposes only and, because it has limited functions and limited resilience, is not suitable for permanent use under real conditions. If the evaluation board is nevertheless used under real conditions, this is done at one’s responsibility; any liability of Rutronik is insofar excluded. 

<img src="images/rutronik_origin_kaunas.png" style="zoom:50%;" />



