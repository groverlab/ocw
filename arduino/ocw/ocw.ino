void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

String ocw = String("o2wc4wo3wc2wo4wc3w");

int i = 0;
void loop() {
  if(ocw.charAt(i) == 'o') {
    digitalWrite(ocw.substring(i+1,i+2).toInt(), HIGH);
  }
  if(ocw.charAt(i) == 'c') {
    digitalWrite(ocw.substring(i+1,i+2).toInt(), LOW);
  }
  if(ocw.charAt(i) == 'w') {
    delay(100);
  }
  i += 1;
  if(i > ocw.length()) {
    i = 0;
  }
}
