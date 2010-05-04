/* 
 * File:   UART1_to_SPI.h
 * Author: ?????????????
 *
 * Created on 27 ������ 2010 �., 19:19
 */

#ifndef _CONTROL_UNIT_H
#define	_CONTROL_UNIT_H

#ifdef	__cplusplus
extern "C" {
#endif

    // ���������� ����������� LED1 �� ����� ������
#define DISPLAY_LED_DDR     DDRD
#define DISPLAY_LED_PORT    PORTD
#define DISPLAY_LED_PIN     PD7
    // ��� LATCH_EN �� ��������� ����������������
#define DISPLAY_LE_DDR      DDRD
#define DISPLAY_LE_PORT     PORTD
#define DISPLAY_LE_PIN      PD6
    // ��� OE. ��������-��������� ���������������
#define DISPLAY_OE_DDR      DDRD
#define DISPLAY_OE_PORT     PORTD
#define DISPLAY_OE_PIN      PD5

    // CLK �� UART1. �� �������� ����������������
#define DISPLAY_CLK_DDR     DDRD
#define DISPLAY_CLK_PORT    PORTD
#define DISPLAY_CLK_PIN     PD4


#define DISPLAY_NAMBER      4


#define a 2       // ��� ������� �������� �����, ��������������� ������,
#define b 1       // ����������� � �������, ������ ������ "�����" ����
#define c 64      // �����, � �������� ��������� ������� ���������� �
#define d 32      // ����������� ������� ���������. ��� ����, ����� �������
#define e 16      // �����-���� ����� �� ���������, ����� ��������� � ����
#define f 4       // ����� 255 ����� ����� ��������������� ��������� ��������.
#define g 8       // ��� ����� ��������� ������� ��������� ����������� �� �����������.
#define DP 128    // �������� ��� �����, ���� ��������� ������� ����� "��"

//unsigned char DigNumber = 0;
extern unsigned char Dig[10]; // ������, � ������� �������� �����, ������� �����
// ������� ����� ���� �� ���������, ����� �� ������� �����, ������ ������
// �������� �������. ����� ������� ������ �� ��������.

void control_unit_init(void); // ���� ��� ��� �������������������
void Dig_init(void);
void UART1_init(void);

void display_on_off(char mode);
void display_LED_on_off(char mode);


extern unsigned char display_digits [DISPLAY_NAMBER];



#ifdef	__cplusplus
}
#endif

#endif	/* _CONTROL_UNIT_H */

