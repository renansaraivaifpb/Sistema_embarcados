// Including necessary libraries
//#include <LiquidCrystal_I2C.h>
// Declaring an instance of the LiquidCrystal_I2C class
//LiquidCrystal_I2C lcd_1(32,16,2);
// Declaration of LED pins and button order arrays
const int ledPins[] = {12, 11, 10, 9, 8};
const int button_order[] = {2, 3, 4, 5, 6};
// Number of LEDs
const int numLeds = 5;
// Boolean variables to track button presses
bool button_pressed_one = false;
bool button_pressed_two = false;
bool button_pressed_three = false;
bool button_pressed_four = false;
bool button_pressed_five = false;

// Array to track button presses
bool button_pressed[5];

// State variables
bool state = true;
// Function to reset button states
void reset(bool* button[], int quantity) {
  // sets the initial conditions only for the specified buttons
  for (int i = 0; i < quantity; i++) {
    *(button[i]) = false;
  }
}
void feedback(){
  PORTB = 0xFF; // Define os pinos 11, 12 e 13 como HIGH
  delay(1500);
  //PORTB |= 0xA9; // Define os pinos 9 a 13 como HIGH
  //delay(2000);
  PORTB = ~0xFF;
  delay(1000);  
}
// State variables
bool game = false;
int rounds = 1;

// Setup function
void setup() {
  	// Initializing the LCD display
    //lcd_1.begin(); // lcd_begin(); to old versions
    //lcd_1.setCursor(0,0);
    //lcd_1.backlight();
    //lcd_1.display();
  
  	// Initializing Serial communication
    Serial.begin(9600);
  	// Configuring the ports
  	DDRD |= (B11111100); // Configures pins PD2-PD7 pin 2 to 7 as outputs
  	DDRB &= ~(B00111111); // Configures pins PB0-PB5 pin 8 to 13 as outputs

}

// Function to control LED states
void on_led(volatile uint8_t *port, uint8_t bitMask) {
    // Configures the pin as an output
    volatile uint8_t *reg = port - 1; // Get the port direction recorder
    *reg |= bitMask;
    // Turn on the LED
    *port |= bitMask;
    // Wait 1 second
    delay(1000);
    // Turn off the LED
    *port &= ~bitMask;
    // Wait 200 milliseconds
    delay(650);
}

// Function to display message on LCD
//void message(const char* msg, int time, int position_one=0, bool need_clear = true){
	//  lcd_1.setCursor(0, position_one);
  //  lcd_1.print(msg);
  //	delay(time);
  //  if(need_clear){
  //    lcd_1.clear();
  //  }
//}

// Main loop
void loop() {
  if(digitalRead(button_order[4]) == HIGH){
    // Clear the LCD display
    //lcd_1.clear();
    //message("TRY TO REMEMBER", 2000, 0);
    delay(4000);
    Serial.print("\n Try to Remember \n");
    
    for(int i = 0; i<rounds;i++){
    int correct_order[rounds];
    int selected_order[rounds];    
      	// Generating random numbers for LED order
        correct_order[i] = random(9, 14);
        Serial.print(correct_order[i]);
      	// Displaying current round number on LCD
        Serial.print("Rounds: ");
        Serial.print(rounds);
        //message("ROUNDS: ", 1000, 0, false);
      	//lcd_1.setCursor(0, 1);
        //lcd_1.print(rounds);
        //delay(1500);
        //lcd_1.clear();
      
      	// Flashing LEDs in the correct order
        for (int led = 0; led < rounds; led++) {
            Serial.print("\n contador: " +(String)led +"\n ");
            Serial.print("\n rounds: " +(String)rounds+ "\n ");
            Serial.print("\npin led :" +(String)correct_order[led]);
            digitalWrite(correct_order[led], HIGH);
            delay(1500);
            digitalWrite(correct_order[led], LOW);
            delay(1000);
        }
      	// Player's turn
        
      	//message("TRY", 1000, 0);
        Serial.print("\n TRY \n");
      	int x = 0;
        // Loop for handling player's input
      	do{
          delay(150);
          // Checking if buttons are pressed and handling them
          if(digitalRead(button_order[0]) == HIGH && !button_pressed_one){
              selected_order[x] = 13;
              Serial.print(selected_order[x]);
				      on_led(&PORTB, 1 << PB5);
              //on_led_normal(13);
              if(selected_order[x] == correct_order[x]){
                //message("GOOD JOB!", 2000, 0);
                Serial.print("\n Acertou \n");
                bool* button[] = {&button_pressed_one};
  				      reset(button, 1);
                x++;
              }
              else{
                  state = false; // to do The game over
                  break;
        	    }
          }
          
          // Similar code for other buttons...
          if(digitalRead(button_order[1]) == HIGH && !button_pressed_two){
            selected_order[x] = 12;
            Serial.print(selected_order[x]);
              	on_led(&PORTB, 1 << PB4);
                //on_led_normal(12);
            if(selected_order[x] == correct_order[x]){
                Serial.print("\n Acertou \n");
                //message("NICE!", 2000, 0);
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
                Serial.print(selected_order[x]);
                on_led(&PORTB, 1 << PB3);
                //on_led_normal(11);
            if(selected_order[x] == correct_order[x]){
                //message("GOOD PLAY!", 2000, 0);
                Serial.print("\n Acertou \n");
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
              Serial.print(selected_order[x]);
              on_led(&PORTB, 1 << PB2);
              //on_led_normal(10);
            if(selected_order[x] == correct_order[x]){
              //message("VERY NICE", 2000, 0);
              Serial.print("\n Acertou \n");
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
              Serial.print(selected_order[x]);
              on_led(&PORTB, 1 << PB1);
              //on_led_normal(9);
            if(selected_order[x] == correct_order[x]){
              Serial.print("\n Acertou \n");
              // message("NICE!", 2000, 0);
              bool* button[] = {&button_pressed_five};
              reset(button, 1);
              x++;
            }else{
              state = false; // to do The game over
              break;
            }
          }
          
        }while(x<rounds);
      
      	// Displaying result
        if(state == true){
            Serial.print("\n YOU REMEMBERED! \n");
            //feedback();
            //message("YOU REMEMBERED!", 1100, 0);
            feedback();
          	rounds++;
        }else{
            Serial.print("\n YOU LOSS :< \n");
            Serial.print("\n YOU SELECTED: \n");
            Serial.print(selected_order[x]);
          	//message("YOU LOSS :<", 1000, 0);
          	//message("YOU SELECTED: ", 900, 0, false);
            //lcd_1.setCursor(0, 1);
            //lcd_1.print(selected_order[x]);
            //delay(700);
            //lcd_1.clear();
          	Serial.print("\n BUT IT WAS: \n");
        	  //message("BUT IT WAS: ", 900, 0, false);
            //lcd_1.setCursor(0, 1);
            //lcd_1.print(correct_order[x]);
            Serial.print(correct_order[x]);
            Serial.print("\n value of x: " +(String)x);
            Serial.print("\n rounds of x: " +(String)rounds);
            
            //delay(700);
            //lcd_1.clear();  
            
            //feedback();
            //feedback();
            int x = 0;
            rounds = 1;
            feedback();
            feedback();
            state = true;
            // to do any treading for this situation
            bool* button[] = {&button_pressed_one, &button_pressed_two, &button_pressed_three, &button_pressed_four, &button_pressed_five};
         	  reset(button, 6);
        }
    }
    
    // End of game
    Serial.println("\n----------- THE GAME IS OVER -----------");
    bool* button[] = {&button_pressed_one, &button_pressed_two, &button_pressed_three, &button_pressed_four, &button_pressed_five};
    reset(button, 6); // This will reset only the first 6 buttons
    }
  	else{
      	// Displaying message to start the game
        Serial.print("PRESS BUTTON FIVE TO PLAY");
        //message("PRESS BUTTON SIX ", 500, 0,false);
        //message("TO PLAY", 1000, 1,false);
    }
}
