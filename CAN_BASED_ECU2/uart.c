
#include "uart.h"

void init_uart(void) {
    //TRISC
    TRISC6 = 0;
    TRISC7 = 1;

    /*TXSTA - Transmit registers*/
    TX9 = 0; //Disable parity
    TXEN = 1; //Enable transmit 
    SYNC = 0; //Asynchronous mode
    BRGH = 1; //High speed - Baud rate
    /*RCSTA - Receive registers*/

    SPEN = 1; //serial port enabled
    RX9 = 0; //Disable receive parity
    CREN = 1; //Enable receiver

    /*BAUDCON - To select the baud rate*/
    BRG16 = 0; //8bit baud rate generator
    ABDEN = 0; //Disable auto baud rate
    WUE = 0; //Disable Wake up enable

    SPBRG = 129; //To achieve 9600 baud rate
}

void uart_tx_char(unsigned char ch) {
    /*TXIF - transmit flag it will be set and cleared by microcontroller*/
    /*Whenever the data 8 bits is completely transmitted the TXIF flag will be set by microcontroller*/
    while (!TXIF);
    /*Loading the data to TXREG register*/
    TXREG = ch;
}

void uart_tx_str(unsigned char *str) {
    while (*str) {
        uart_tx_char(*str);
        str++;
    }
}

unsigned char uart_recieve(void) {
    /*RCIF - Receive flag it will be set by controller when the data
     *  is completely stored inside a RCREG register*/
    while (!RCIF);
    /*To return the value from the function*/
    return RCREG;
}