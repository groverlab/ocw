#include <IRremote.h>
#include <LiquidCrystal.h>

const int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  irrecv.enableIRIn();
  irrecv.blink13(false);
  lcd.begin(16, 2);
  lcd.print(" UCR Bee Brain");
}

// OCW code to start repeating at startup:
String ocw = String("c2 c3 c4 w100");

bool waiting = false;
int i = 0;
unsigned long startTime = 0;

void loop() {
  if (irrecv.decode(&results)) {
      if (results.value == 0XFFFFFFFF) {
        results.value = key_value;
      }
    switch(results.value) {

      case 0xFFA25D:  // POWER
      break;

      case 0xFF629D:  // VOL+
      break;

      case 0xFFE21D:  // FUNC/STOP
      break;

      case 0xFF22DD:  // |<<
      lcd.setCursor(0, 0);
      lcd.print("Pumping backward");
      ocw = "o2 w200 c4 w200 o3 w200 c2 w200 o4 w200 c3 w200";
      i=-1;
      break;

      case 0xFF02FD:  // >||
      lcd.setCursor(0, 0);
      lcd.print("Standby         ");
      ocw = "c2 c3 c4 w100";
      i=-1;
      break;  

      case 0xFFC23D:  // >>|
      lcd.setCursor(0, 0);
      lcd.print("Pumping forward ");
      ocw = "o4 w200 c2 w200 o3 w200 c4 w200 o2 w200 c3 w200";
      i=0-1;
      break;

      case 0xFFE01F:  // v
      break;

      case 0xFFA857:  // VOL-
      break; 

      case 0xFF906F:  // ^
      break; 

      case 0xFF6897:  // 0
      break;

      case 0xFF9867:  // EQ
      break;

      case 0xFFB04F:  // ST/REPT
      break;

      case 0xFF30CF:  // 1
      break;

      case 0xFF18E7:  // 2
      break;

      case 0xFF7A85:  // 3
      break;

      case 0xFF10EF:  // 4
      break;

      case 0xFF38C7:  // 5
      break;

      case 0xFF5AA5:  // 6
      break;

      case 0xFF42BD:  // 7
      break;

      case 0xFF4AB5:  // 8
      break;

      case 0xFF52AD:  // 9
      break;   

    }
    key_value = results.value;
    irrecv.resume();
  }
  
  if(waiting) {
    if(millis() >= startTime) {
      waiting = false;
      i += 1;
    }
  }
  
  else {
    if(ocw.charAt(i) == 'o') {
      int len = 1;
      while(isDigit(ocw.charAt(i+1+len))) {
        len += 1;
      }
      digitalWrite(ocw.substring(i+1,i+1+len).toInt(), HIGH);
    }
    if(ocw.charAt(i) == 'c') {
      int len = 1;
      while(isDigit(ocw.charAt(i+1+len))) {
        len += 1;
      }
      digitalWrite(ocw.substring(i+1,i+1+len).toInt(), LOW);
    }
    if(ocw.charAt(i) == 'w') {
      int len = 1;
      while(isDigit(ocw.charAt(i+1+len))) {
        len += 1;
      }
      startTime = millis()+ocw.substring(i+1,i+1+len).toInt();
      waiting = true;
    }
    i += 1;
    if(i > ocw.length()) {
      i = 0;
    }
  }

lcd.setCursor(0, 1);
lcd.print(millis()/1000.0);
}
