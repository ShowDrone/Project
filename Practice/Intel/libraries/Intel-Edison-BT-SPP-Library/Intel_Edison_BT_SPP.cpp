#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <Intel_Edison_BT_SPP.h>

using namespace std;

int Intel_Edison_BT_SPP::open() {

	if (_fd != -1)
		close(_fd);

	_fd = ::open(_pipeName, O_RDONLY);

	if (_fd == -1) {
		perror("Cannot open file\n");
		printf("errno %s\n", strerror(errno));
		Serial.print("open error "); Serial.println(strerror(errno));
		return 0;
	}

	return -1;
}

ssize_t Intel_Edison_BT_SPP::read() {

	if (_fd == -1)
		open();

	ssize_t size = ::read(_fd, _buf, MAX_BUF-1);

	if (size == -1) {
		perror("Read error\n");
		printf("errno %s\n", strerror(errno));
		Serial.print("read error "); Serial.println(strerror(errno));
	} else {
		_buf[size]=0;
	}

	return size;
}

const char * Intel_Edison_BT_SPP::getBuf() {
	return _buf;
}

Intel_Edison_BT_SPP::~Intel_Edison_BT_SPP() {
	if (_fd != -1) {
		close (_fd);
		_fd = -1;
	}
}
