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

/*
*-------------------------------------------------------------------
* $Id: sub_if.h,v 1.51 2011-01-16 03:45:10 avr32 Exp $
*-------------------------------------------------------------------
*/
#ifndef SUB_IF_H_INCLUDED
#define SUB_IF_H_INCLUDED


/*
*-----------------------------------------------------------------------------
* Types
*-----------------------------------------------------------------------------
*/

#ifndef AVR
 #pragma pack(1)
#endif
typedef struct 
{
	uint8_t		code;
		#define SUB_UNKNOWN			0xFF
		#define	SUB_GET_VERSION		0x00
		
		#define SUB_I2C_START		0x10
		#define SUB_I2C_STOP		0x11
		#define SUB_I2C_GENERIC		0x12
		#define SUB_I2C_RDWR		0x14
		#define SUB_I2C_SCAN		0x15
		#define SUB_I2C_FREQ		0x20
		#define SUB_I2C_CONFIG		0x21
		
		#define SUB_SPI_CONFIG		0x40
		#define SUB_SPI_READ		0x41
		#define SUB_SPI_WRITE		0x42
		#define SUB_SPI_RDWR		0x43
		#define SUB_SPI_SDIO_RDWR	0x44
		#define SUB_SPI_RDWR_ESS	0x45
		
		#define SUB_MDIO_XFER		0x48
		
		#define SUB_LCD_WRITE		0x50
		
		#define SUB_ADC_CONFIG		0x58
		#define SUB_ADC_READ		0x59
		
		#define SUB_GPIO_CONFIG		0x60
		#define SUB_GPIO_READ		0x61
		#define SUB_GPIO_WRITE		0x62
		#define SUB_GPIOB_CONFIG	0x63
		#define SUB_GPIOB_READ		0x64
		#define SUB_GPIOB_WRITE		0x65
		#define SUB_FAST_PWM_CONFIG	0x66
		#define SUB_FAST_PWM_SET	0x67
		#define SUB_PWM_CONFIG		0x6C
		#define SUB_PWM_SET			0x6D
		#define SUB_EDGE_CONFIG		0x6E
		#define SUB_EDGE_READ		0x6F
		
		#define SUB_RS_CONFIG		0x68
		#define SUB_RS_TIMING		0x69
		#define SUB_RS_XFER			0x6A
		
		#define SUB_FIFO_CONFIG		0x70
		
		#define SUB_BB_I2C_START	0x80
		#define SUB_BB_I2C_STOP		0x81
		#define SUB_BB_I2C_CONFIG	0x82
		#define SUB_BB_I2C_SCAN		0x83
		#define SUB_BB_I2C_RDWR		0x84
		
		#define SUB_IR_CONFIG		0x90
		#define SUB_IR_TX			0x91
        
    uint8_t		size;

	union
	{
		uint8_t		data[0];

		/* Get Version */
		struct get_version_resp_st
		{
			uint8_t		micro;
			uint8_t		minor;
			uint8_t		major;
			uint8_t		boot;
		}get_version_resp;

		/* I2C Start */
		struct i2c_start_req_st
		{
			uint8_t		restart;
		}i2c_start_req;

		struct i2c_start_resp_st
		{
			uint8_t		status;
		}i2c_start_resp;

		/* I2C Stop */
		struct i2c_stop_resp_st
		{
			uint8_t		status;
		}i2c_stop_resp;

		/* I2C Generic */
		struct i2c_generic_req_st
		{
			uint8_t 	sa;			/* Slave Address */
			uint8_t		flags;
				#define __GENF_RESTART	0x01	/* Repeated START */
				#define __GENF_NOSTOP	0x02	/* No STOP */
				#define __GENF_NOSLA	0x04	/* Do not issue SLA+R/W */
			uint8_t		sz;				 
			uint8_t		data[0];
		}i2c_generic_req;

		struct i2c_generic_resp_st
		{
			uint8_t		status;
			uint8_t		data[0];
		}i2c_generic_resp;

		/* I2C Read/Write */
		struct i2c_rdwr_req_st
		{
			uint8_t		sa;
			uint8_t		flags;		/* __GENF flags are also respected */
			uint8_t		ma_sz;		/* Memory address size */
			uint8_t		sz;			/* Data szie */
			uint8_t		ma[0];
		}i2c_rdwr_req;
#define SUB_MAX_I2C_READ  (SUB_MAX_PACK-1-offsetof(sub_tag_t,i2c_rdwr_resp.data))
#define SUB_MAX_I2C_WRITE (SUB_MAX_PACK-1-offsetof(sub_tag_t,i2c_rdwr_req.ma))

		struct i2c_rdwr_resp_st
		{
			uint8_t		status;
			uint8_t		data[0];
		}i2c_rdwr_resp;

		/* I2C Baud */
		struct i2c_baud_req_st
		{
			uint8_t		twi_TWBR;
			uint8_t		twi_TWPS;
		}i2c_baud_req;
		
		struct i2c_baud_resp_st
		{
			uint8_t		twi_TWBR;
			uint8_t		twi_TWPS;
		}i2c_baud_resp;

		/* I2C Config */
		struct i2c_config_req_st
		{
			uint8_t		sa;
			uint8_t		flags;

		}i2c_config_req;

		/* I2C Scan */
		struct i2c_scan_resp_st
		{
			uint8_t		slave_n;
			uint8_t		slave_buf[0];
		}i2c_scan_resp;
#define SUB_MAX_I2C_SCAN (SUB_MAX_PACK-1-offsetof(sub_tag_t,i2c_scan_resp.slave_buf))

		/* SPI Config */
		struct spi_config_req_st
		{
			uint8_t		spi_SPCR;
		}spi_config_req;

		struct spi_config_resp_st
		{
			uint8_t		spi_SPCR;
		}spi_config_resp;

		/* SPI Read/Write */
		struct spi_rdwr_req_st
		{
			uint8_t		SS_config;
			uint8_t		sz;
			uint8_t		data[0];
		}spi_rdwr_req;
#define SUB_MAX_SPI_RDWR 		(SUB_MAX_PACK-1-offsetof(sub_tag_t,spi_rdwr_req.data))
#define SUB_MAX_SPI_RDWR_LONG 	(SUB_MAX_PACK_LONG-1-offsetof(sub_tag_t,spi_rdwr_req.data))

		/* SPI Read/Write with Extended SS control */
		struct spi_rdwr_ess_req_st
		{
			uint8_t		SS_config_sz;
			uint8_t		sz;
			uint8_t		buf[0];
		}spi_rdwr_ess_req;
#define SUB_MAX_SPI_ESS_RDWR_LONG (SUB_MAX_PACK_LONG-1-offsetof(sub_tag_t,spi_rdwr_ess_req.buf))

		struct spi_rdwr_resp_st
		{
			uint8_t		sz;
			uint8_t		data[0];
		}spi_rdwr_resp;
		
		/* SPI SDIO rdwr */
		struct spi_sdio_rdwr_req_st
		{
			uint8_t		SS_config;
			uint8_t		out_sz;
			uint8_t		in_sz;
			uint8_t		data[0];
		}spi_sdio_rdwr_req;
#define SUB_MAX_SPI_SDIO_RDWR (SUB_MAX_PACK-1-offsetof(sub_tag_t,spi_sdio_rdwr_req.data))

		struct spi_sdio_rdwr_resp_st
		{
			uint8_t		in_sz;
			uint8_t		data[0];
		}spi_sdio_rdwr_resp;

		/* MDIO Xfer */
		struct mdio_xfer_req_st
		{
			uint8_t		n;
			struct mdio_xfer_st
			{
				uint8_t	op_prtad;	/* bit7:Clause22, bit6,5:op, bit4,0:prtad */
				uint8_t	devad;		/* bit6,5:channel */
				uint8_t	data_lo;
				uint8_t	data_hi;
			}xfer[0];
		}mdio_xfer_req;
#define SUB_MAX_MDIO_XFER ((SUB_MAX_PACK-1-offsetof(sub_tag_t,mdio_xfer_req.xfer[0]))/sizeof(struct mdio_xfer_st))

		/* GPIO */
		struct gpio_req_st
		{
			uint8_t		mask[4];
			uint8_t		val[4];
		}gpio_req;

		struct gpio_resp_st
		{
			uint8_t		val[4];
		}gpio_resp;

		/* GPIOB */
		struct gpiob_req_st
		{
			uint8_t		mask;
			uint8_t		val;
		}gpiob_req;

		struct gpiob_resp_st
		{
			uint8_t		val;
		}gpiob_resp;

		/* Edge */
		struct edge_config_st
		{
			uint8_t		_EICRA;
			uint8_t		_EICRB;
		}edge_config;

		struct edge_read_st
		{
			uint8_t		val[4];		/* GPIO */
			uint8_t		_EIFR;
			uint8_t		_PCIFR;
		}edge_read;

		/* Fast PWM */
		struct fast_pwm_config_req_st
		{
			uint8_t		TCCRA;
			uint8_t		TCCRB;
			uint8_t		TCCRC;
			uint8_t		ICRL;
			uint8_t		ICRH;
		}fast_pwm_config_req;

		struct fast_pwm_set_req_st
		{
			uint8_t		pwm_n;
			uint8_t		duty_lo;
			uint8_t		duty_hi;
		}fast_pwm_set_req;

		/* PWM */
		struct pwm_config_req_st
		{
			uint8_t		TCCRA;
			uint8_t		TCCRB;
			uint8_t		OCRA;
			uint8_t		limit;
		}pwm_config_req;

		struct pwm_set_req_st
		{
			uint8_t		pwm_n;
			uint8_t		duty;
		}pwm_set_req;

		/* ADC */
		struct adc_config_req_st
		{
			uint8_t		admux;
			uint8_t		adcsra;
		}adc_config_req;

		struct adc_read_req_st
		{
			uint8_t		reads;
#define MAX_ADC_READS 30
			uint8_t		mux[0];
		}adc_read_req;
		struct adc_read_resp_st
		{
			uint8_t		reads;
			uint8_t		adc_lh[0];
		}adc_read_resp;

		/* LCD */
		struct LCD_write_req_st
		{
        #define SUB_MAX_LCD_STR 60
			char		str[SUB_MAX_LCD_STR];
		}LCD_write_req;

		struct LCD_write_resp_st
		{
			uint8_t		status;
				#define __LCD_NOT_SUPPORTED	0xFF
		}LCD_write_resp;

		/* RS232/RS485 */
		struct RS_config_req_st
		{
			uint8_t		UCSRC;
			uint8_t		UBRRL;
			uint8_t		UBRRH;
		}RS_config_req;

		struct RS_config_resp_st
		{
			uint8_t		UCSRC;
			uint8_t		UBRRL;
			uint8_t		UBRRH;
		}RS_config_resp;

		struct RS_timing_req_st
		{
			uint8_t		flags;
			uint16_t	tx_space;		/* LSB first */
			uint16_t	rx_msg_to;
			uint16_t	rx_byte_to;
		}RS_timing_req;

		struct RS_xfer_req_st
		{
			uint8_t		rx_sz;
			uint8_t		tx_buf[0];
		}RS_xfer_req;

		struct RS_xfer_resp_st
		{
			uint8_t		rx_sz;
			uint8_t		rx_buf[0];
		}RS_xfer_resp;
#define SUB_MAX_RS_XFER	(SUB_MAX_PACK-1-offsetof(sub_tag_t,RX_xfer_req.tx_buf))

		/* FIFO */
		struct FIFO_config_req_st
		{
			uint8_t		selector;
			uint8_t		flags;
		}FIFO_config_req;

		/* BB I2C Start */
		struct bb_i2c_start_req_st
		{
			uint8_t		channel;
			uint8_t		restart;
		}bb_i2c_start_req;

		struct bb_i2c_start_resp_st
		{
			uint8_t		status;
		}bb_i2c_start_resp;

		/* BB I2C Stop */
		struct bb_i2c_stop_req_st
		{
			uint8_t		channel;
		}bb_i2c_stop_req;

		struct bb_i2c_stop_resp_st
		{
			uint8_t		status;
		}bb_i2c_stop_resp;

		/* BB I2C Read/Write */
		struct bb_i2c_rdwr_req_st
		{
			uint8_t		channel;
			uint8_t		sa;
			uint8_t		flags;		/* __GENF flags are also respected */
			uint8_t		ma_sz;		/* Memory address size */
			uint8_t		sz;			/* Data szie */
			uint8_t		ma[0];
		}bb_i2c_rdwr_req;
#define SUB_MAX_BB_I2C_READ  (SUB_MAX_PACK_LONG-1-offsetof(sub_tag_t,bb_i2c_rdwr_resp.data))
#define SUB_MAX_BB_I2C_WRITE (SUB_MAX_PACK_LONG-1-offsetof(sub_tag_t,bb_i2c_rdwr_req.ma))

		struct bb_i2c_rdwr_resp_st
		{
			uint8_t		status;
			uint8_t		data[0];
		}bb_i2c_rdwr_resp;

		/* BB I2C Config */
		struct bb_i2c_config_req_st
		{
			uint8_t		mode;
			uint8_t		stretch;
		}bb_i2c_config_req;
		
		/* BB I2C Scan */
		struct bb_i2c_scan_req_st
		{
			uint8_t		channel;
		}bb_i2c_scan_req;

		/* IR Config */
		struct ir_config_req_st
		{
			uint8_t		ICRL;	
			uint8_t		ICRH;		/* Fcarrier = 16MHz/(ICR+1) */
			uint8_t		OCRL;
			uint8_t		OCRH;       /* Carrier duty = OCR/ICR */ 
			uint8_t		mode;
			union ir_config_mode_un
			{
				struct
				{
					uint8_t	pp_bit;	/* Carrier pulses per bit */
				}uart_mode;
				struct
				{
					uint8_t	pp_bit;	/* Carrier pulses per bit */
				}row_mode;
			}ir_config_mode;
		}ir_config_req;

		/* IR Tx */
		struct ir_tx_req_st
		{
			uint8_t		sz;
			uint8_t		buf[0];
		}ir_tx_req;
#define SUB_MAX_IR_TX  (SUB_MAX_PACK_LONG-1-offsetof(sub_tag_t,ir_tx_req.buf))
		struct ir_tx_resp_st
		{
			uint8_t		status;
		}ir_tx_resp;
	};
}sub_tag_t;


/*
*-----------------------------------------------------------------------------
* Constants
*-----------------------------------------------------------------------------
*/

/* Vendor Specific Control Request wIndex */
#define SUB_VENDOR_REQUEST	0x80
 #define SUB_WINDEX_BOOT		0x00
 #define SUB_WINDEX_MODE		0x01
 #define SUB_WINDEX_VER			0x02
 #define SUB_WINDEX_CFG_VPD		0x03

/* Vendor requests in boot mode */
#define SUB_BOOT_WRITE_NVRAM	1

#define SUB_MAX_PACK		64
#define SUB_MAX_PACK_LONG	256

/*
* I2C Status
*/
#define __I2C_START     0x08  	/* A START condition transmitted			*/
#define __I2C_RESTART   0x10	/* A repeated START condition transmitted	*/
#define __I2C_SLAW_ACK  0x18	/* SLA+W transmitted; ACK received			*/
#define __I2C_SLAW_NAK  0x20	/* SLA+W transmitted; NAK received			*/
#define __I2C_DATA_ACK  0x28	/* Data byte transmitted; ACK received		*/
#define __I2C_DATA_NAK  0x30	/* Data byte transmitted; NAK received		*/
#define __I2C_SLA_ARB  	0x38	/* Arbitration lost in SLA or NAK received	*/
#define __I2C_SLAR_ACK  0x40	/* SLA+R transmitted; ACK received			*/ 
#define __I2C_SLAR_NAK	0x48	/* SLA+R transmitted; NAK received			*/
#define __I2C_READ_ACK  0x50	/* Data received; ACK has been returned		*/
#define __I2C_READ_NAK  0x58	/* Data received; NAK has been returned		*/

#define __I2C_WAIT_TO	0xE0    /* Arbitration lost							*/
#define __I2C_START_TO	0xE1    /* Arbitration lost in START				*/
#define __I2C_STOP_TO	0xE2    /* Arbitration lost in STOP					*/
#define __I2C_READ_ACK_TO 0xE3	/* Arbitration lost in read ACK				*/
#define __I2C_READ_NAK_TO 0xE4	/* Arbitration lost in read NAK				*/
#define __I2C_WRITE_TO	0xE5    /* Arbitration lost in write				*/
#define __I2C_ERROR		0xF8  	/* Unknown error							*/
#define __I2C_ILLEGAL	0xFF	/* Illegal START or STOP condition			*/

#endif /*_H_INCLUDED*/

