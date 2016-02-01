void setup() {
  Serial.begin(19200);
}

int buf[4] = {0x25,0x62,0x3F,0x52};

void loop() {
  Serial.println(CheckSum((unsigned char*)buf, 4));
}

/*unsigned char CheckSum(unsigned char *data, int len) {
  int sum;
  int total=0;
  sum = 0xFF;
  
  for(int x=0;x<len;x++,data++) {
    sum ^= *data; // 모든 바이트 값 저장
  }
  total = sum;
  
  return ~total; // 반환
}*/


unsigned char CheckSum(unsigned char *msg_ptr, unsigned char len) {
	unsigned char x;
	unsigned char xorResult;

	xorResult = 0;

	for (x = 0; x < len; x++, msg_ptr++)
		xorResult = xorResult ^ *msg_ptr;

	xorResult = xorResult & 0xFF;
	return (xorResult);
}

