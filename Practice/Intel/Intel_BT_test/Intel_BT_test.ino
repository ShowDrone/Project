#include <Wire.h>
#include <Intel_Edison_BT_SPP.h>
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

String BT_Value = "";
void setup() {
  // 하드웨어 - Pc간의 직렬 통신
	Serial.begin(115200); // 시리얼 통신 속도 115200bps
	Serial.println("Intel Edison BT SPP test!");
	spp.open(); // 가상 시리얼 환경 오픈
}

void loop() {
	ssize_t size = spp.read(); // ssize_t == signed int
	if (size != -1)
	{
    BT_Value = spp.getBuf(); //spp.getBuf() == const char*
    Serial.print("BT_Value = "); //개행없는 출력
    Serial.println(BT_Value); //개행있는 출력
	} 
	else 
	{
		delay(500);
	}
}
