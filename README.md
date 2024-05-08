# RDK4 TLE9262-3BQX SBC "Ignition Signal" Wake Up

Rutronik Development Kit 4 Programmable System-on-Chip CY8C4149AZE-S598 "SBC Ignition Signal Wake Up" Code Example. 

 <img src="images/oscilogram.png" style="zoom:80%;" />

The wake threshold of the TLE9262-3BQX WK3 input is 3V. Once the voltage threshold is crossed on WK3 pin - the wake up event happens. If a TLE9262-3BQX is woken up with a rising edge of the Ignition signal, the system stays 5 seconds online before entering the Sleep Mode. If TLE9262-3BQX is woken up with a falling edge of the Ignition signal, the system goes into the Sleep Mode just right after the initialization.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v3.1
- The latest hardware release [RDK4 Rev2](https://github.com/RutronikSystemSolutions/RDK4_Hardware_Files).

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`

## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>




1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialogue.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialogue, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

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

If you successfully have imported the example, the debug configurations are already prepared to use with the KitProg3 or MiniProg4. Open the ModusToolbox™ perspective and find the Quick Panel. Click on the desired debug launch configuration and wait for the programming to complete and the debugging process to start.

<img src="images/debug_start.png" style="zoom:100%;" />

#### SBC Development Mode

A special mode, called SBC Development Mode, is available during software development or debugging of the system. The watchdog counter is stopped and does not need to be triggered. This mode can be accessed by setting the TEST [**FO3**] pin to GND during SBC Init Mode.

## Legal Disclaimer

The evaluation board including the software is for testing purposes only and, because it has limited functions and limited resilience, is not suitable for permanent use under real conditions. If the evaluation board is nevertheless used under real conditions, this is done at one’s responsibility; any liability of Rutronik is insofar excluded. 

<img src="images/rutronik_origin_kaunas.png" style="zoom:50%;" />



