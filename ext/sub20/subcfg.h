/*
 * Internal libsub header file
 * Copyright (C) 2008-2009 Alex Kholodenko <sub20@xdimax.net>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


#ifndef __SUBCFG_H__
#define __SUBCFG_H__
#ifndef ASSEMBLER
#include <stddef.h>
#endif

/*
* I/O Pinout
*/	

/* SPI Level Convertor */
#define DIR_PORT	PORTA
#define DIR_DDR		DDRA
#define DIR			PORTA4

#ifndef USBKEY

/* Leds */
#define LED_PORT	PORTA
#define LED_DDR		DDRA
#define RLED		PORTA0
#define YLED		PORTA1
#define LED_OFF(  LEDN )	LED_PORT |= _BV( LEDN )
#define LED_ON( LEDN )		LED_PORT &=~_BV( LEDN )
#define IS_LED_ON(LEDN)		(!(LED_PORT & _BV(LEDN)))
#define LED_TGL( LEDN )		LED_PORT ^= _BV(LEDN)

/* SW1,2 */
#define SW_PORT		PORTA
#define SW_PIN		PINA
#define SW1			PINA2
#define	SW2			PINA3

/* RS485 */
#define DE_PORT		PORTA
#define DE_DDR		DDRA
#define DE_PIN		PORTA7
#define RE_PORT		PORTA
#define RE_DDR		DDRA
#define RE_PIN		PORTA6

#else	/* USBKEY */

#define SW1_PIN				PINE
#define SW1_BIT				PORTE2
#define LED_ON()			(LED_PORT |= BIT(LED_BIT))
#define LED_OFF()			(LED_PORT &= ~BIT(LED_BIT))
#define IS_LED_ON()		(LED_PORT & BIT(LED_BIT))

#endif	/* USBKEY */

/* GPIO */
#define GPIO_PIN0	PINC
#define GPIO_DDR0   DDRC
#define GPIO_PORT0  PORTC
#define GPIO_PIN1   PIND
#define GPIO_DDR1   DDRD
#define GPIO_PORT1  PORTD
#define GPIO_PIN2   PINF
#define GPIO_DDR2   DDRF
#define GPIO_PORT2  PORTF
#define GPIO_PIN3   PINE
#define GPIO_DDR3   DDRE
#define GPIO_PORT3  PORTE

/* GPIOB */
#define GPIOB_PIN0	PINB
#define GPIOB_DDR0	DDRB
#define GPIOB_PORT0	PORTC

/* MDIO */
#define MDIO0_PORT	PORTD
#define MDIO0_DDR	DDRD
#define MDIO0_PINS	PIND
#define MDC0_PIN	PORTD6
#define MDIO0_PIN	PORTD7

#define MDIO1_PORT	PORTB
#define MDIO1_DDR	DDRB
#define MDIO1_PINS	PINB
#define MDC1_PIN	PORTB2
#define MDIO1_PIN	PORTB1

/* LCD */   
#define LCD_RS_PORT PORTC
#define LCD_RS_DDR  DDRC
#define LCD_RS_PIN  PORTC7

#define LCD_E_PORT  PORTC
#define LCD_E_DDR   DDRC
#define LCD_E_PIN   PORTC6

#define LCD_WDTH 4		/* LCD_DATA 4 or 8 bits */
#define LCD_PORT 0		/* LCD_PORT 0-Separate Pins, else-Single Port */
#define LCD_D4_PORT    PORTC       
#define LCD_D4_DDR     DDRC        
#define LCD_D4_PIN     PORTC3         
#define LCD_D5_PORT    PORTC       
#define LCD_D5_DDR     DDRC        
#define LCD_D5_PIN     PORTC2         
#define LCD_D6_PORT    PORTC       
#define LCD_D6_DDR     DDRC        
#define LCD_D6_PIN     PORTC1         
#define LCD_D7_PORT    PORTC       
#define LCD_D7_DDR     DDRC        
#define LCD_D7_PIN     PORTC0         

#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR  DDRC

#ifndef ASSEMBLER

#define MAX_STR_DESCR       4
typedef struct
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t data[10];
}sub_string_descr_t;

#if defined(_MSC_VER) && (_MSC_VER > 800)
#pragma pack(push, 1)
#endif	/*_MSC_VER*/

typedef struct
{
    uint8_t lcd_w;      /* LCD With (0-no LCD, 8, 16) */
    uint8_t lcd_h;      /* LCD Lines 1,2,... */
    uint8_t serial;     /* 2-RS232, 4-RS485 */
    uint8_t buttons;    /* 0,1,2 */
    uint16_t ir_car;    /* 0-no IR, IR carrier frequency Hz */
}sub_vpd_t;

#if defined(_MSC_VER) && (_MSC_VER > 800)
#pragma pack(pop)
#endif	/*_MSC_VER*/

typedef struct
{
    uint8_t st_ver;                         /* structure version */
    uint8_t bl_ver;                         /* boot loader version */
    uint8_t dev_descr[18];                  /* device descriptor */
    sub_string_descr_t string_descr[MAX_STR_DESCR];     /* string descriptors */
    sub_vpd_t vpd;
}sub_cfg_t /* __attribute__((packed)) */ ;

#endif	/*ASSEMBLER*/


#ifdef AVR

#define SUBCFG_ADDR ((uint32_t)(FLASHEND+1-256))
#define SUBCFG_OFFSET(MEMBER) offsetof(sub_cfg_t, MEMBER)

#endif /*AVR*/

#endif	/*__SUBCFG_H__*/

