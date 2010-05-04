#include "control_unit.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <util/delay.h>


unsigned char curent_ind=0;
unsigned char display_digits [DISPLAY_NAMBER];

void control_unit_init(void)
{
    DISPLAY_LED_PORT &=~(1<<DISPLAY_LED_PIN); // ��������� ���������� �����
    DISPLAY_LED_DDR &=~(1<<DISPLAY_LED_PIN); // ����� � Z - ���� ��������� �� �����

    DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); //��� LE - ����� ������
    DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN);  // LE - �����

    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //OE- ��������� ���������� �����
    DISPLAY_OE_DDR &=~(1<<DISPLAY_OE_PIN);  // OE � Z-���������. ��� ������ ��� �������� ���������

   // DISPLAY_CLK_PORT &=~(1<<DISPLAY_CLK_PIN); //���� �� ����� ��������
    DISPLAY_CLK_DDR |=(1<<DISPLAY_CLK_PIN);  // CLK - �����

    UART1_init();
    Dig_init();

}

unsigned char Dig[10];
void Dig_init(void)
{
  Dig[0] = (a+b+c+d+e+f);   // ���� ��������� � ����� ������,
  Dig[1] = (b+c);           // ����� ����� �������� ������ ��
  Dig[2] =  (a+b+g+e+d);     // 255. ���� � ����� �������, ��
  Dig[3] =  (a+b+g+c+d);     // �������� �� �����.
  Dig[4] =  (f+g+b+c);       // ����� �������� �������������
  Dig[5] =  (a+f+g+c+d);     // ������ ��������� ����������
  Dig[6] =  (a+f+g+c+d+e);
  Dig[7] =  (a+b+c);
  Dig[8] =  (a+b+c+d+e+f+g);
  Dig[9] = (a+b+c+d+f+g);
}

void UART1_init(void)
{
        // USART1 initialization
    // Communication Parameters: LSB first
    // USART1 Receiver: OFF
    // USART1 Transmitter: On
    // USART1 Mode: SPI UCPOL=0
    // USART1 Baud Rate: 9600

    UCSR1A=0x00;
    UCSR1B=0;
    UCSR1B |= (1<<UDRIE1); // �������� ����������  USART1 Data Register Empty
    UCSR1B |= (1<<TXEN1); // �������� ��������

    UCSR1C=0;
    UCSR1C|=(1<<UMSEL11); // �������� ����� SPI
    UCSR1C|=(1<<UMSEL10); // .....SPI.....

    UCSR1C|=(1<<UCSZ11); //LSB first
    //UCSR1C|=(1<<UCPHA1);

    //USART1 Baud Rate: 9600
    UBRR1H=0x00;
    UBRR1L=0x33;
}
/*
// USART1 Receiver interrupt service routine
// ����� �������������� ��� �������� ����������� ���� �
//�������� ���������� ����������� � �������
ISR(USART1_RX_vect)
{

}
*/

// USART1 Data Register Empty interrupt service routine
ISR(USART1_UDRE_vect)
{
    unsigned char data=display_digits[curent_ind];
    UDR1= data;
    curent_ind++;
    if (curent_ind>DISPLAY_NAMBER)
    {
        DISPLAY_LE_PORT |=(1<<DISPLAY_LE_PIN); //��������� ������� ������
        curent_ind=1;
        DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); //��������� LE
    }
}

inline void display_on_off(char mode)
{
    if (mode)  DISPLAY_OE_DDR |=(1<<DISPLAY_OE_PIN);  // ������
    else DISPLAY_OE_DDR &=~(1<<DISPLAY_OE_PIN);  // ��������
}

inline void display_LED_on_off(char mode)
{
    if (mode)  DISPLAY_LED_DDR &=~(1<<DISPLAY_LED_PIN);  // ������
    else DISPLAY_LED_DDR |=(1<<DISPLAY_LED_PIN);  // ��������
}