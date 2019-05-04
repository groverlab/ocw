void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

String ocw = String("o2 c4 w500 o3 c2 w500 o4 c3 w500");

int i = 0;
void loop() {
  if(ocw.charAt(i) == 'o') {
    digitalWrite(ocw.substring(i+1,i+2).toInt(), HIGH);
  }
  if(ocw.charAt(i) == 'c') {
    digitalWrite(ocw.substring(i+1,i+2).toInt(), LOW);
  }
  if(ocw.charAt(i) == 'w') {
    int len = 1;
    while(isDigit(ocw.charAt(i+1+len))) {
      len += 1;
    }
    delay(ocw.substring(i+1,i+1+len).toInt());
  }
  i += 1;
  if(i > ocw.length()) {
    i = 0;
  }
}
