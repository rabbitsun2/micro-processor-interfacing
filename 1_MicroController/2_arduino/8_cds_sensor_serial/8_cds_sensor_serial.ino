const int ANALOG_CDS_PORT = A0;
const int BRIGHT_DARK = 40;
const int LED_PORT = 8;

int val = 0;

void setup() {

  Serial.begin(9600);

  pinMode(ANALOG_CDS_PORT, INPUT);
  pinMode(LED_PORT, OUTPUT);

}

void loop() {

  val = analogRead(ANALOG_CDS_PORT);  // 아날로그 값 읽기
  
  Serial.print("CDS = ");
  Serial.print(val);
  Serial.println();

  // 조도가 어두울 때
  if ( val <= BRIGHT_DARK ){
    digitalWrite(LED_PORT, HIGH);
  }
  // 조도가 밝아질 때
  else{
    digitalWrite(LED_PORT, LOW);
  }

  delay(1000);

}
