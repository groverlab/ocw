
#define ocwstring "\
o2\
w1000\
c2\
w2000\
"

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

// OCW code to start repeating at startup:
String ocw = String(ocwstring);

bool waiting = false;
int i = 0;
unsigned long startTime = 0;

void loop() {
  if (waiting) {
    if (millis() >= startTime) {
      waiting = false;
      i += 1;
    }
  }

  else {
    if (ocw.charAt(i) == 'o') {
      int len = 1;
      while (isDigit(ocw.charAt(i + 1 + len))) {
        len += 1;
      }
      digitalWrite(ocw.substring(i + 1, i + 1 + len).toInt(), HIGH);
    }
    if (ocw.charAt(i) == 'c') {
      int len = 1;
      while (isDigit(ocw.charAt(i + 1 + len))) {
        len += 1;
      }
      digitalWrite(ocw.substring(i + 1, i + 1 + len).toInt(), LOW);
    }
    if (ocw.charAt(i) == 'w') {
      int len = 1;
      while (isDigit(ocw.charAt(i + 1 + len))) {
        len += 1;
      }
      startTime = millis() + ocw.substring(i + 1, i + 1 + len).toInt();
      waiting = true;
    }
    i += 1;
    if (i > ocw.length()) {
      i = 0;
    }
  }
}
