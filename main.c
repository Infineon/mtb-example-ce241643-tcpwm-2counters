/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the TCPWM Application Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
********************************************************************************
* (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/


/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cy_pdl.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
/*******************************************************************************
* Macros
*******************************************************************************/


/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Debug UART context */
cy_stc_scb_uart_context_t  DEBUG_UART_context;
/* Debug UART HAL object */
mtb_hal_uart_t DEBUG_UART_hal_obj;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/


/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CPU. It configures TCPWM 2 counters to
* generate square PWM to drive 2 leds with different period and duty
*    1.The frequency and duty-cycle of one is 2HZ and 50%
*    2.The frequency and duty-cycle of another one is 1HZ and 50%
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize the debug UART */
    result = Cy_SCB_UART_Init(DEBUG_UART_HW, &DEBUG_UART_config, &DEBUG_UART_context);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
    Cy_SCB_UART_Enable(DEBUG_UART_HW);
    /* Initialize HAL UART */
    result = mtb_hal_uart_setup(&DEBUG_UART_hal_obj, &DEBUG_UART_hal_config, &DEBUG_UART_context, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(&DEBUG_UART_hal_obj);
    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("************************************************************\r\n");
    printf("PSOC Control C3M/P8: Two TCPWM counters\r\n");
    printf("************************************************************\r\n\n");

    Cy_PPCA_CNFG_Init(CNFG_PPCA_INOUT_HW, &CNFG_PPCA_INOUT_config);
    Cy_PPCA_Enable(CNFG_PPCA_INOUT_HW);
    Cy_PPCA_CNFG_PPCA_Output_Selector(CNFG_PPCA_INOUTCNFG_HW, &CNFG_PPCA_INOUT_ppcaOutConfig);

    /*Init and start PWM1: 2HZ and 50% duty-cycle*/
    if (CY_TCPWM_SUCCESS != Cy_TCPWM_PWM_Init((TCPWM_Type*)PWM1_HW, PWM1_NUM, &PWM1_config))
    {
        CY_ASSERT(0);
    }

    /* Enable the initialized PWM1 */
    Cy_TCPWM_PWM_Enable((TCPWM_Type*)PWM1_HW, PWM1_NUM);

    /* Then start the PWM1 */
    Cy_TCPWM_TriggerStart_Single((TCPWM_Type*)PWM1_HW, PWM1_NUM);

    /*Init and start PWM2: 1HZ and 50% duty-cycle*/
    if (CY_TCPWM_SUCCESS != Cy_TCPWM_PWM_Init((TCPWM_Type*)PWM2_HW, PWM2_NUM, &PWM2_config))
    {
        CY_ASSERT(0);
    }

    /* Enable the initialized PWM2 */
    Cy_TCPWM_PWM_Enable((TCPWM_Type*)PWM2_HW, PWM2_NUM);

    /* Then start the PWM2 */
    Cy_TCPWM_TriggerStart_Single((TCPWM_Type*)PWM2_HW, PWM2_NUM);

    for (;;)
    {
    }
}

/* [] END OF FILE */
