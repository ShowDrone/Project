#ifndef _INTEL_EDISON_BT_SPP_H_
#define _INTEL_EDISON_BT_SPP_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define MAX_BUF 4096

class Intel_Edison_BT_SPP {
	public:
	int open();
	int read();
	const char * getBuf();
	~Intel_Edison_BT_SPP();

	private:
	int _fd = -1;
	const char * _pipeName = "/tmp/arduino_pipe_out";
	char _buf[MAX_BUF];
};

#endif
