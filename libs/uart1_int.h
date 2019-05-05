
#ifndef __UART1_INT_H_
#define __UART1_INT_H_

#define UART1_TX_INT 17
#define UART1_RX_INT 18

//TODO: Will be removed...
//extern __IO uint8_t rcv_char;
//extern __IO uint8_t chr_received;

void UART1_TX_IRQHandler(void) __interrupt(UART1_TX_INT);
void UART1_RX_IRQHandler(void) __interrupt(UART1_RX_INT);

void UART1_Config(void);

#define RCVBUFLEN 20  //Receive buffer characterlength.

extern __IO uint8_t rcv_buf[RCVBUFLEN];

extern __IO uint8_t rcvbuf_wr;
extern __IO uint8_t rcvbuf_rd;

void putchar (char c);
char getchar (void);
char getchar_nb (void);
void putstr (char* c);

void SendBufHex(char *buf, uint8_t bufsize);



#endif
