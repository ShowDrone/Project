#define TRIG 12 // TRIG 핀
#define ECHO 13 // EHCO 핀

// 라이브러리
#include <DFRobot.h>
#include <IIC1.h>
#include <SPI.h>
#include <WiFi.h>

// 변수선언
int Temp = A0;
int TempValue = 0;
float TempData;
float TempC;
int Flame = A1;
int Flame_Data = 0;
int Flame_Value = 0;
char ssid[] = "edison";  //  연결하실 와이파이 SSID
char pass[] = "92669474";   // 네트워크 보안키
int Wave_Data = 0;
int search_distance = 10;

DFrobotEdison motor;

int status = WL_IDLE_STATUS;
WiFiServer server(80);  // 80포트를 사용하는 웹서버 선언

void setup() {
  Serial.begin(115200); // 하드웨어 - PC간의 직렬 통신
  Serial.println("Hello Edison");
  if (WiFi.status() == WL_NO_SHIELD) { // 현재 아두이노에 연결된 실드를 확인
    Serial.println("WiFi shield not present"); 
    while (true);  // 와이파이 실드가 아닐 경우 계속 대기
  } 

  // 와이파이에 연결 시도
  while ( status != WL_CONNECTED) { //연결될 때까지 반복
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);  // WPA/WPA2 연결
  } 
  server.begin();
  printWifiStatus();  // 연결 성공시 연결된 네트워크 정보를 출력

  pinMode(TRIG,OUTPUT); // 초음파를 보내는 핀이니 OUTPUT
  pinMode(ECHO,INPUT); // 보낸 초음파를 받는 핀이니 INPUT
}


void loop() {
  Wave_Begin(); //노이즈 방지
  Wave_Data = pulseIn(ECHO,HIGH)/58.8; // 340*Wave_Data)/10000)/2;
  TempValue = analogRead(Temp);
  TempData = TempValue*5.0/1024.0;
  TempC = (TempData-0.5)*100.0;
   Flame_Data = analogRead(Flame);
  if(Flame_Data>=100)
  {
     Flame_Value = true;
  }
  else
  {
     Flame_Value = false;
  }
   WiFiClient client = server.available();  // 들어오는 클라이언트를 수신한다.
  if (client) {  // 클라이언트를 수신 시
    Serial.println("new client");  // 클라이언트 접속 확인 메시지 출력
    boolean currentLineIsBlank = true;

    while (client.connected ()) { 
      if (client.available()) {
        char c = client.read();
        // 문자의 끝을 입력 받으면 http 요청이 종료되고, 답신을 보낼 수 있습니다.
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 0.5"); // 0.5초당 페이지 refresh
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<meta charset=utf-8/>");
          client.print("<meta name=view content=width=device-width, ");
          client.println("initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no />");
          client.println("<html>");
          client.println("<head>");  
          client.println("<title>Sensor Test</title>");
          client.println("</head>");
          client.println("<h1><b>Sensor Test for Intel edison</b></h1>");
          client.println("<hr></hr>"); //라인
          client.println("<hr></hr>"); //라인
          client.println("<div data-role=content>");
          client.println("<table border=0pxwidth=800xheight=700px>");
          client.println("<tr>");
          client.println("<th><b><h2>Sensor&nbsp&nbsp&nbsp&nbsp&nbsp<h2><b></th>");
          client.println("<th colspan=10><b><h2>&nbsp&nbsp&nbsp&nbspData<b></h2></th>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td>&nbsp&nbspTemp</td>");
          client.print("<td colspan=10>");
          client.print("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
          client.print(TempC);
          client.println(" 'C");
          client.println("</td>");
          client.println("</tr>");
                
          client.println("<tr>");
          client.println("<td>&nbsp&nbsp&nbsp&nbsp<br/>&nbsp&nbspFlame</td>");
          client.print("<td colspan=10>");
          client.print("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
          if(Flame_Value)
          {
            client.println("Fire ON");
          }
          else
          {
            client.println("Fire OFF");
          }
          client.println("</td>");
          client.println("</tr>");
          
          client.println("</div>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') { 
          currentLineIsBlank = true;
        }

        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disonnected");
    // 클라이언트와 연결을 끊는다.
  }
  
  if(Wave_Data > search_distance) // 일정 거리안에 물체가 없으면
  { 
     Forward();
     Serial.println("Forward");
  }      
  else if(Wave_Data <= search_distance)  // 일정 거리안에 물체가 있으면
  {
     Auto_Reverse();
     delay(1100);
     Auto_TurnRight();
     delay(1200);
  }
  
}

void Wave_Begin() {
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  delayMicroseconds(10);
}

void Auto_Reverse(){
  Serial.println("Reverse");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 200);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 200);    
}

void Forward(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);   
}

void Auto_TurnRight() {
  Serial.println("Auto_Right");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);
}

void TurnLeft(){
  Serial.println("Left");
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 255);   
}


void Stop(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 0);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 0);   
}

void printWifiStatus() {  // 연결된 네트워크 정보 출력
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // 네트워크 SSID 출력

  IPAddress ip = WiFi.localIP(); 
  Serial.print("IP Address: ");
  Serial.println(ip);
  // 네트워크 ip 출력

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // 수신 강도 출력
}

