#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_1(32,16,2);

const int ledPins[] = {13, 12, 11, 10, 9, 8};
const int button_order[] = {2, 3, 4, 5, 6, 7};
const int numLeds = 6;

void setup() {
    lcd_1.init();
    lcd_1.setCursor(0,0);
    lcd_1.backlight();
    lcd_1.display();
    Serial.begin(9600);
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(button_order[i], INPUT); // Enables the internal pull-up resistor on the button pins
    }
}


bool button_pressed_one = false; // Variable to track whether button 2 has been pressed
bool button_pressed_two = false;
bool button_pressed_three = false;
bool button_pressed_four = false;
bool button_pressed_five = false;
bool button_pressed_six = false;
bool button_pressed[6];
void reset(bool* button[], int quantity) {
  // sets the initial conditions only for the specified buttons
  for (int i = 0; i < quantity; i++) {
    *(button[i]) = false;
  }
}
bool state = true;
int rounds = 1;
void loop() {
    Serial.print("\n START GAME \n");
    for(int i = 0; i<rounds;i++){
        int correct_order[rounds];
      	int selected_order[rounds];
        correct_order[i] = random(8, 14);
        lcd_1.setCursor(0, 0);
        lcd_1.print("rounds: ");
        lcd_1.setCursor(0, 1);
        lcd_1.print(rounds);
        delay(1000);
        lcd_1.clear();
        Serial.print("\n\n variable rounds: ");
        Serial.print(rounds);
        for (int led = 0; led < rounds; led++) {
            Serial.print("\n\n variable led (indice): ");
            Serial.print(led);
            Serial.print("\n pin: ");
            Serial.print(correct_order[led]);
            digitalWrite(correct_order[led],HIGH);
            delay(1000);
            digitalWrite(correct_order[led],LOW);
            delay(1000);
          }
        int x = 0;
      	
      	do{
          delay(150);
          if(digitalRead(button_order[0]) == HIGH && !button_pressed_one){
            selected_order[x] = 13;
              if(selected_order[x] == correct_order[x]){
                Serial.print("\n selected_order[x]: ");
                Serial.print(selected_order[x]);
                Serial.print("\n correct_order[x]: ");
                Serial.print(correct_order[x]);    
                Serial.print("\n valor do x: ");
                Serial.print(x);
                digitalWrite(selected_order[x], HIGH);
                delay(1000);
                digitalWrite(selected_order[x], LOW);
                delay(200);
                bool* button[] = {&button_pressed_one};
  				reset(button, 1);
                x++;
              }
              else{
                  state = false; // to do The game over
                  break;
        	    }
          }
          if(digitalRead(button_order[1]) == HIGH && !button_pressed_two){
            selected_order[x] = 12;
            if(selected_order[x] == correct_order[x]){
              Serial.print("\n selected_order[x]: ");
              Serial.print(selected_order[x]);
              Serial.print("\n correct_order[x]: ");
              Serial.print(correct_order[x]);    
              Serial.print("\n valor do x: ");
              Serial.print(x);
              digitalWrite(selected_order[x], HIGH);
                delay(1000);
                digitalWrite(selected_order[x], LOW);
                delay(200);
                bool* button[] = {&button_pressed_two};
  				      reset(button, 1);
                x++;
            }else{
                state = false; // to do The game over
                break;
            }
          }
          if(digitalRead(button_order[2]) == HIGH && !button_pressed_three){
            selected_order[x] = 11;
            if(selected_order[x] == correct_order[x]){
                Serial.print("\n selected_order[x]: ");
                Serial.print(selected_order[x]);
                Serial.print("\n correct_order[x]: ");
                Serial.print(correct_order[x]);    
                Serial.print("\n valor do x: ");
                Serial.print(x);
              digitalWrite(selected_order[x], HIGH);
                delay(1000);
                digitalWrite(selected_order[x], LOW);
                delay(200);
                bool* button[] = {&button_pressed_three};
                reset(button, 1);
                x++;
            }else{
              state = false; // to do The game over
              break;
            }
          }
          if(digitalRead(button_order[3]) == HIGH && !button_pressed_four){
            selected_order[x] = 10;
            if(selected_order[x] == correct_order[x]){
              Serial.print("\n selected_order[x]: ");
              Serial.print(selected_order[x]);
              Serial.print("\n correct_order[x]: ");
              Serial.print(correct_order[x]);    
              Serial.print("\n valor do x: ");
              Serial.print(x);
              digitalWrite(selected_order[x], HIGH);
                delay(1000);
                digitalWrite(selected_order[x], LOW);
                delay(200);
              bool* button[] = {&button_pressed_four};
  			      reset(button, 1);
              x++;
            }else{
              state = false; // to do The game over
              break;
            }
          }
          if(digitalRead(button_order[4]) == HIGH && !button_pressed_five){
            selected_order[x] = 9;
            if(selected_order[x] == correct_order[x]){
              Serial.print("\n selected_order[x]: ");
              Serial.print(selected_order[x]);
              Serial.print("\n correct_order[x]: ");
              Serial.print(correct_order[x]);    
              Serial.print("\n valor do x: ");
              Serial.print(x);
              digitalWrite(selected_order[x], HIGH);
                delay(1000);
                digitalWrite(selected_order[x], LOW);
                delay(200);
              bool* button[] = {&button_pressed_five};
              reset(button, 1);
              x++;
            }else{
              state = false; // to do The game over
              break;
            }
          }
          if(digitalRead(button_order[5]) == HIGH && !button_pressed_six){
            selected_order[x] = 8;
            
            if(selected_order[x] == correct_order[x]){
              
              digitalWrite(selected_order[x], HIGH);
              delay(1000);
              digitalWrite(selected_order[x], LOW);
              delay(200);
              bool* button[] = {&button_pressed_six};
  			  reset(button, 1);
              x++;
            }else{
              state = false; // to do The game over
              break;
            }
          }
        }while(x<rounds);
      if(rounds==3){
        Serial.print("\n");
      	Serial.print(selected_order[0]);
        Serial.print("\n");
        Serial.print(selected_order[1]);
        Serial.print("\n");
        Serial.print(selected_order[2]);
      }
        if(state == true){
          	lcd_1.setCursor(0, 0);
            lcd_1.print("YOU SELECTED: "+(String)selected_order[x]);
            delay(1400);
            lcd_1.setCursor(0, 1);
            lcd_1.print("BUT IT WAS: " + String(correct_order[x]));
            delay(1400);
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("CONGRATULATIONS!");
            delay(1000);
            lcd_1.clear();
          	rounds++;

        }else{
            lcd_1.setCursor(0, 0);
            lcd_1.print("YOU LOSS :<");
          	lcd_1.setCursor(0, 1);
            lcd_1.print("YOU SELECTED: "+(String)selected_order[x]);
            delay(2000);
          	lcd_1.clear();
        	lcd_1.setCursor(0, 0);
          	lcd_1.print("BUT IT WAS: " + String(correct_order[x]));
          	delay(2000);
         	lcd_1.clear();
            rounds = 1;
            // to do any treading for this situation
        }
    }
    Serial.println("\n ------- THE GAME IS OVER -----------");
  // correct_order - selected_order 
  // pin (led)     - pin (button)   +  cts(normalizacao)
  // 13            - 2              +  11     = 13
  // 12            - 3              +   9     = 12
  // 11            - 4              +   7     = 11
  // 10            - 5              +   5     = 10
  //  9            - 6              +   3     =  9

  bool* button[] = {&button_pressed_one, &button_pressed_two, &button_pressed_three, &button_pressed_four, &button_pressed_five, &button_pressed_six};
  reset(button, 6); // This will reset only the first 6 buttons
}
