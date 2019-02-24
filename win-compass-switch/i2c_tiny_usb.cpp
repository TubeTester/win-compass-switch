#include "stdafx.h"
#include "i2c_tiny_usb.h"

i2c_tiny_usb::i2c_tiny_usb()
{

}

i2c_tiny_usb::~i2c_tiny_usb()
{

}

TCHAR* i2c_tiny_usb::get_device_state_str(void)
{
	return device_state;
}

TCHAR* i2c_tiny_usb::get_device_data_str(void)
{
	return device_data;
}

bool i2c_tiny_usb::init(void)
{
	USES_CONVERSION;
	usb_init();

	usb_find_busses();
	usb_find_devices();

	for (bus = usb_get_busses(); bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) {
			if ((dev->descriptor.idVendor == COMPASS_SWITCH_VID) &&
				(dev->descriptor.idProduct == COMPASS_SWITCH_PID)) {

				wsprintf(device_state, L"Found i2c_tiny_usb device on bus %s device %s.\n", A2T(bus->dirname), A2T(dev->filename));

				/* open device */
				if (!(handle = usb_open(dev))) {
					wsprintf(device_state, L"Error: Cannot open the device: %s\n", A2T(usb_strerror()));
					return -1;
				}

				break;
			}
		}
	}

	if (!handle) {
		wsprintf(device_state, L"Error: Could not find i2c_tiny_usb device\n");
		return -1;
	}

	get_func(device_data);

	return 0;
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
	nBytes = usb_control_msg(handle, USB_CTRL_IN, cmd, 0, 0, data, len, 1000);

	if (nBytes < 0) {
		wsprintf(device_data, L"USB error: %s\n", usb_strerror());
		return nBytes;
	}

	return 0;
}