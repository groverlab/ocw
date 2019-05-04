void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

String ocw = String("o11 c13 w200 o12 c11 w200 o13 c12 w200");

bool waiting = false;
int i = 0;
unsigned long startTime = 0;

void loop() {
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
}
