#pragma once
#include <stdio.h>
#include "lusb0_usb.h"
#include "atlstr.h"

#define COMPASS_SWITCH_VID  0x0403
#define COMPASS_SWITCH_PID  0xc631

#define HMC5883L_ADDR	0x0A
#define HMC5883L_ID		0x1e

#define USB_CTRL_IN    (USB_TYPE_CLASS | USB_ENDPOINT_IN)
#define USB_CTRL_OUT   (USB_TYPE_CLASS)

/* commands via USB, must e.g. match command ids firmware */
#define CMD_ECHO       0
#define CMD_GET_FUNC   1
#define CMD_SET_DELAY  2
#define CMD_GET_STATUS 3
#define CMD_I2C_IO     4
#define CMD_I2C_BEGIN  1  // flag to I2C_IO
#define CMD_I2C_END    2  // flag to I2C_IO

class i2c_tiny_usb
{
public:
						i2c_tiny_usb();
						~i2c_tiny_usb();
						
	bool				init(void);
	TCHAR *				get_device_state_str(void);
	TCHAR *				get_device_data_str(void);

private:
	void				get_func(TCHAR*);
	int					read(unsigned char, char*, int, TCHAR*);


	usb_dev_handle*     handle;
	struct usb_bus      *bus;
	struct usb_device   *dev;
	TCHAR				device_state[1000];
	TCHAR				device_data[200];
};

