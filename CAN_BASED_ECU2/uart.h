
#ifndef UART_H
#define	UART_H
#include <xc.h>

/*To initialize the UART protocol*/
void init_uart(void);
/*To recieve the data from other device*/
unsigned char uart_recieve(void);
/*To transmit the character*/
void uart_tx_char(unsigned char ch);
/*To transmit the string*/
void uart_tx_str(unsigned char* str);
#endif	/* UART_H */

