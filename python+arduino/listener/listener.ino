void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

int cnt = 0;
char buffer[32];
int valve = 0;

void loop() {
  while (Serial.available())
  {
    char c = Serial.read();
    buffer[cnt++] = c;
    if (c == '\n')
    {
      buffer[cnt] = '\0';
      cnt = 0;
      Serial.print("received: ");
      Serial.print(buffer);
      if (buffer[0] == 'o') {
        valve = atoi(&buffer[1]);
        Serial.print("  opening "); Serial.println(valve);
        digitalWrite(valve, HIGH);
      }
      if (buffer[0] == 'c') {
        valve = atoi(&buffer[1]);
        Serial.print("  closing ");  Serial.println(valve);
        digitalWrite(valve, LOW);
      }
    }
  }
}
