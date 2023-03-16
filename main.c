/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the RDK4 SBC Wake Up Signal
*              Application for ModusToolbox.
*
* Related Document: See README.md
*
*
*  Created on: 2023-03-14
*  Company: Rutronik Elektronische Bauelemente GmbH
*  Address: Jonavos g. 30, Kaunas 44262, Lithuania
*  Author: GDR
*
*******************************************************************************
* (c) 2019-2021, Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*
* Rutronik Elektronische Bauelemente GmbH Disclaimer: The evaluation board
* including the software is for testing purposes only and,
* because it has limited functions and limited resilience, is not suitable
* for permanent use under real conditions. If the evaluation board is
* nevertheless used under real conditions, this is done at one’s responsibility;
* any liability of Rutronik is insofar excluded
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "TLE926x.h"

/*Priority for SBC interrupts*/
#define SBC_IRQ_PRIORITY		1

/*Ignition signal bit mask for WK_LVL_STAT register*/
#define IGNITION_SIGNAL				0b00000100

/*Function prototypes*/
void sbc_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);

/*TLE9262 SBC Interrupt Data*/
cyhal_gpio_callback_data_t sbc_int_data =
{
		.callback = sbc_interrupt_handler,
		.callback_arg = NULL,
};

int main(void)
{
    cy_rslt_t result;
    SBC_ErrorCode sbc_err;
    uint16_t wake_level = 0;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /*Initialize LEDs*/
    result = cyhal_gpio_init( USER_LED_GREEN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_ON);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    result = cyhal_gpio_init( USER_LED_RED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_ON);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    result = cyhal_gpio_init( USER_LED_BLUE, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_ON);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}

    /*Enable debug output via KitProg UART*/
    result = cy_retarget_io_init( KITPROG_TX, KITPROG_RX, CY_RETARGET_IO_BAUDRATE);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    __enable_irq();
    printf("\r\n");

    /*Initialize SBC Interrupt Pin*/
    result = cyhal_gpio_init(INT_SBC, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    /*Register callback functions */
    cyhal_gpio_register_callback(INT_SBC, &sbc_int_data);
    /* Enable rising edge interrupt events */
    cyhal_gpio_enable_event(INT_SBC, CYHAL_GPIO_IRQ_RISE, SBC_IRQ_PRIORITY, true);

    /*SBC Initializations*/
    sbc_err = sbc_init();
    if(sbc_err.flippedBitsMask)
    {
    	printf("SBC initialization failure.\r\n");
    	printf("SBC might be in Sleep Mode.\r\n");
    	printf("Switch the SW4 to the LDO position and provide the power to the battery terminals.\r\n");
    	CY_ASSERT(0);
    }

    /*Check what level caused the SBC to wake up*/
    wake_level = sbc_read_reg(SBC_WK_LVL_STAT);
    if(!(wake_level & IGNITION_SIGNAL))
    {
    	printf("RDK4 is online. Ignition signal LOW detected.\r\n");
    	printf("RDK4 is shutting down.\r\n");
        /* Enter Sleep Mode */
        sbc_err = sbc_mode_sleep();
        if(sbc_err.flippedBitsMask)
        {
        	printf("Could not enter Sleep Mode.\r\n");
        	CY_ASSERT(0);
        }
    }

    /*Ignition Signal Detected*/
    printf("RDK4 is online. Ignition signal HIGH detected.\r\n");
    Cy_SysLib_Delay(5000);

    printf("RDK4 is shutting down.\r\n");
    /* Enter Sleep Mode */
    sbc_err = sbc_mode_sleep();
    if(sbc_err.flippedBitsMask)
    {
    	printf("Could not enter Sleep Mode.\r\n");
    	CY_ASSERT(0);
    }

    /*Should never reach this*/
    for (;;)
    {
    	printf("System Failure.\r\n");
    	CY_ASSERT(0);
    }
}

/* SBC Interrupt handler callback function */
void sbc_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event)
{
	CY_UNUSED_PARAMETER(handler_arg);
    CY_UNUSED_PARAMETER(event);

    SBC_ISR();
}

/* [] END OF FILE */
