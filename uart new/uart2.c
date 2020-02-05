//https://www.includehelp.com/c-programs/c-program-to-calculate-length-of-string-string-length.aspx



#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

    char str[100] = "I am learning C programming language.";
    int length;
    int stringLength(char*);
    int i;
    int flag = 0;
    char temptext[100];
    int index = 0;
    int stringLength(char* txt)
    {
        int j=0,count=0;
        while(txt[j++]!='\0'){
            count+=1;
        }
        return count;
    }


void ConfigureUART(){

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
//    GPIOPinConfigure(GPIO_PD6_U2RX);
//    GPIOPinConfigure(GPIO_PD7_U2TX);
//    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
//    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 9600,
//    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

}

int main(void) {

     ConfigureUART();
     UARTCharPut(UART0_BASE, 'E');
     UARTCharPut(UART0_BASE, 'n');
     UARTCharPut(UART0_BASE, 't');
     UARTCharPut(UART0_BASE, 'e');
     UARTCharPut(UART0_BASE, 'r');
     UARTCharPut(UART0_BASE, ' ');
     UARTCharPut(UART0_BASE, 'T');
     UARTCharPut(UART0_BASE, 'e');
     UARTCharPut(UART0_BASE, 'x');
     UARTCharPut(UART0_BASE, 't');
     UARTCharPut(UART0_BASE, ':');
     UARTCharPut(UART0_BASE, ' ');
     UARTCharPut(UART2_BASE, 'A');



     while (1)
     {

         while ((UARTCharsAvail(UART0_BASE))&&(flag == 0)){
              uint32_t recd = 0;
              recd = UARTCharGet(UART0_BASE);
              if(recd==' '){
                  flag = 1;
                  UARTCharPut(UART0_BASE, '@');
                  length = stringLength(temptext);
                  for(i=0;i<=length;i++){
                  UARTCharPut(UART0_BASE, temptext[i]);
                  }
                  flag = 0;
               }
              UARTCharPut(UART0_BASE, recd);
              temptext[index] = recd;
              index++;
             }
         if(flag==1){
          length = stringLength(str);
          for(i=0;i<=length;i++){
          UARTCharPut(UART0_BASE, str[i]);
          }
          flag = 0;
         }
         }

//         length = stringLength(str);
//         for(i=0;i<=length;i++){
//         UARTCharPut(UART0_BASE, str[i]);
//         }
      }
