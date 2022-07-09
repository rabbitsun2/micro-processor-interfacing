const int LED_PIN = 3;
const int ON = 1;
const int OFF = 0;

Servo servo;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
}

void loop() {
  
  for (int i = 0; i < 256; i++){
    analogWrite(LED_PIN, i);
    delay(10);
  }
  for (int i = 255; i > 0; i--){
    analogWrite(LED_PIN, i);
    delay(10);
  }
  
}
