//Include libraries

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/pwm.h"
#include "driverlib/ssi.h"
#include "driverlib/systick.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include <string.h>

//configure clock and UART
void InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, 115200, 16000000);
}

//program starts from here
int main(void)
{
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    uint32_t ui32SysClock;
#endif

    uint32_t pui32ADC0Value[3];

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_480), 20000000);
#else
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
#endif

//       call the configuration function
    InitConsole();

    //! - UART0 peripheral
    //! - GPIO Port A peripheral (for UART0 pins)
    //! - UART0RX - PA0
    //! - UART0TX - PA1
//    Print on Terminal through COM port
    UARTprintf("ADC ->\n");
    UARTprintf("  Type: Single Ended\n");
    UARTprintf("  Samples: One\n");
    UARTprintf("  Update Rate: 250ms\n");
    UARTprintf("  Input Pin: AIN0/PE3\n\n");


    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

//    mention pins that you are going to use as ADC

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);

//    ADC BASE, Sample Sequencer, Trigger method, Priority
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);

//    configure pins for each ADC_BASE, SEQUENCE_NUMER, STEP, CHANNEL TO STOR EACH ADC
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0 | ADC_CTL_IE |ADC_CTL_END);

//    sequence enable for ADC0_BASE
    ADCSequenceEnable(ADC0_BASE, 1);


//    create variables to store multiple analog read
   int test = 0;
   int test1 = 0;
   int test2 = 0;

           //clear adc
           ADCIntClear(ADC0_BASE, 1);

    while(1)
    {

        //trigger it
        ADCProcessorTrigger(ADC0_BASE, 1);

        // if(not conversion completed) run this
        while(!ADCIntStatus(ADC0_BASE, 1, false))
        {
        }

        ADCIntClear(ADC0_BASE, 1);

        // read adc of all the adc and save it in pui32ADC0Value variable
        ADCSequenceDataGet(ADC0_BASE, 1, pui32ADC0Value);

   //   ADC PIN PE1
   test =  pui32ADC0Value[0];

   //   ADC PIN PE2
   test1 = pui32ADC0Value[1];

   //   ADC PIN PE3
   test2 = pui32ADC0Value[2];


//   print ADC values

UARTprintf("ADC:%d\t\t",test);
UARTprintf("ADC1:%d\t",test1);
UARTprintf("ADC2:%d\n",test2);

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(ui32SysClock / 12);
#else
    SysCtlDelay(SysCtlClockGet() / 12);
#endif
    }
}
