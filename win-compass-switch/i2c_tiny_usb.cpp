#include "stdafx.h"
#include "i2c_tiny_usb.h"




i2c_tiny_usb::i2c_tiny_usb()
{

}


i2c_tiny_usb::~i2c_tiny_usb()
{
}

void i2c_tiny_usb::set_handle(usb_dev_handle* handle)
{
	_handle = handle;
}

usb_dev_handle* i2c_tiny_usb::get_handle(void)
{
	return _handle;
}

/* get i2c usb interface firmware version */
void i2c_tiny_usb::get_func(TCHAR* device_data) {
	char func;

	if (read(CMD_GET_FUNC, &func, sizeof(func), device_data) == 0) {
		wsprintf(device_data, L"Functionality = %lx\n", func);
	}
}

/* read a set of bytes from the i2c_tiny_usb device */
int i2c_tiny_usb::read(unsigned char cmd, char *data, int len, TCHAR* device_data) {
	int nBytes;

	/* send control request and accept return value */
	nBytes = usb_control_msg(_handle, USB_CTRL_IN, cmd, 0, 0, data, len, 1000);

	if (nBytes < 0) {
		wsprintf(device_data, L"USB error: %s\n", usb_strerror());
		return nBytes;
	}

	return 0;
}