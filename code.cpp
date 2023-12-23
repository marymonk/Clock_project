#include <TM1637Display.h>
#include <DS1302.h>


const int CLK_PIN = A2;
const int DIO_PIN = A3;
TM1637Display display(CLK_PIN, DIO_PIN);
DS1302 rtc(4, 5, 6);


void setup() {
  Serial.begin(9600);
  rtc.begin();


  if (rtc.chipPresent()) {
    Serial.println("DS1302 is present!");
  } else {
    Serial.println("Couldn't find DS1302");
    while (1);
  }


  if (rtc.haltFlag()) {
    rtc.clearHaltFlag();
    Serial.println("DS1302 was halted, cleared halt flag");
  }


  rtc.writeProtect(false); // Отключение защиты записи
  display.setBrightness(0x0a);
}


void loop() {
  Time t = rtc.time();
  int hour = t.hr;
  int minute = t.min;
  Serial.print("Time: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minute);
  display.showNumberDec(hour * 100 + minute, true);
  delay(1000);
}
