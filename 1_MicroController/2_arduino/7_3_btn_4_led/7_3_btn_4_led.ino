const int BTN_1 = 3;
const int BTN_2 = 4;
const int BTN_3 = 5;

const int LED_1 = 8;
const int LED_2 = 9;
const int LED_3 = 10;
const int LED_4 = 11;

const int led_arr[4] = {LED_1, LED_2, LED_3, LED_4};

const int LAST_LOOP_NUM = 3;


const int DIRECTION_FORWARD = 0;
const int DIRECTION_REVERSE = 1;

int choose = 0;

void led_init();
void print_led(int choose);
void print_serial_monitor(int number);

void setup() {
  
  Serial.begin(9600);

  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

}


void loop() {

  led_init();   // 전체 LED 초기화

  print_serial_monitor(1);
  
  choose = 0;
  
  if ( digitalRead(BTN_1) == HIGH &&
       digitalRead(BTN_2) == LOW && 
       digitalRead(BTN_3) == LOW){
    choose = 1;
  }
  else if ( digitalRead(BTN_1) == LOW &&
       digitalRead(BTN_2) == HIGH && 
       digitalRead(BTN_3) == LOW){
    choose = 2;
  }
  else if ( digitalRead(BTN_1) == LOW &&
       digitalRead(BTN_2) == LOW && 
       digitalRead(BTN_3) == HIGH){
    choose = 3;
  }
  else if ( digitalRead(BTN_1) == LOW &&
       digitalRead(BTN_2) == LOW && 
       digitalRead(BTN_3) == LOW){
    choose = 0;
  }

  print_serial_monitor(2);

  Serial.print("choose:");
  Serial.println(choose);
  print_led(choose);

  delay(2000);
  
}

void led_init(){

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
    
}

void print_led(int choose){

  
  switch(choose)
  {

    case 0:
      break;
    
    case 1:

      
      for ( int i = 0; i < 2; i++){

        // 정 방향
        if ( i == DIRECTION_FORWARD  ){

          for ( int x = 0; x < 4; x++ ){

            digitalWrite( led_arr[ x ], HIGH);

            if ( x > 0 ){
              digitalWrite( led_arr[ x-1 ], LOW);
            }
            
            delay(500);
          }
           
        }
        // 역 방향
        else if ( i == DIRECTION_REVERSE ) {

          
          for ( int x = 4; x > 0; x-- ){

            digitalWrite( led_arr[ x - 1 ], HIGH);

            
            if ( x != 4 ){
              digitalWrite( led_arr[ x ], LOW);
            }
            
            delay(500);
          }
          
        }
        
      }
    
      break;

    case 2:

      for( int i = 1; i <= LAST_LOOP_NUM; i++ ){

        if ( i % 2 == 0 ){
          digitalWrite(LED_1, HIGH);
          digitalWrite(LED_2, LOW);
          digitalWrite(LED_3, HIGH);
          digitalWrite(LED_4, LOW);
        }else{
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, HIGH);
          digitalWrite(LED_3, LOW);
          digitalWrite(LED_4, HIGH);
        }

        delay(300);
        
      }

      break;

    case 3:

      for (int i = 1; i <= LAST_LOOP_NUM; i++ ){
      
        digitalWrite(LED_1, HIGH);
        delay(100);
        digitalWrite(LED_2, HIGH);
        delay(100);
        digitalWrite(LED_3, HIGH);
        delay(100);
        digitalWrite(LED_4, HIGH);
        delay(100);
  
        led_init();     // 전체 초기화
 
      }

      break;

    default:

      break;
    
  }
  
}

void print_serial_monitor(int number){
  
  Serial.print("Serial");
  Serial.print("(");
  Serial.print(number);
  Serial.print("):");
  Serial.print(digitalRead(BTN_1));
  Serial.print("/");
  Serial.print(digitalRead(BTN_2));
  Serial.print("/");
  Serial.print(digitalRead(BTN_3));
  Serial.println("");
  
}
