// Including necessary libraries
#include <LiquidCrystal_I2C.h>
// Declaring an instance of the LiquidCrystal_I2C class
LiquidCrystal_I2C lcd_1(32,16,2);
// Declaration of LED pins and button order arrays
const int ledPins[] = {13, 12, 11, 10, 9, 8};
const int button_order[] = {2, 3, 4, 5, 6, 7};
// Number of LEDs
const int numLeds = 6;

// Boolean variables to track button presses
bool button_pressed_one = false;
bool button_pressed_two = false;
bool button_pressed_three = false;
bool button_pressed_four = false;
bool button_pressed_five = false;
bool button_pressed_six = false;

// Array to track button presses
bool button_pressed[6];

// Function to reset button states
void reset(bool* button[], int quantity) {
  // sets the initial conditions only for the specified buttons
  for (int i = 0; i < quantity; i++) {
    *(button[i]) = false;
  }
}

// State variables
bool state = true;
bool game = false;
int rounds = 1;

// Setup function
void setup() {
  	// Initializing the LCD display
    lcd_1.init(); // lcd_begin(); to old versions
    lcd_1.setCursor(0,0);
    lcd_1.backlight();
    lcd_1.display();
  
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
void message(const char* msg, int time, int position_one=0, bool need_clear = true){
	lcd_1.setCursor(0, position_one);
    lcd_1.print(msg);
  	delay(time);
    if(need_clear){
      lcd_1.clear();
    }
}

// Main loop
void loop() {
  if(digitalRead(button_order[5]) == HIGH){
    // Clear the LCD display
    lcd_1.clear();
    message("TRY TO REMEMBER", 2000, 0);
    for(int i = 0; i<rounds;i++){
        int correct_order[rounds];
      	int selected_order[rounds];
      
      	// Generating random numbers for LED order
        correct_order[i] = random(8, 14);
      
      	// Displaying current round number on LCD
        message("ROUNDS: ", 1000, 0, false);
      	lcd_1.setCursor(0, 1);
        lcd_1.print(rounds);
        delay(1500);
        lcd_1.clear();
      
      	// Flashing LEDs in the correct order
        for (int led = 0; led < rounds; led++) {
            digitalWrite(correct_order[led],HIGH);
            delay(1000);
            digitalWrite(correct_order[led],LOW);
            delay(1000);
          }
      	// Player's turn
        int x = 0;
      	message("TRY", 1000, 0);
      
      	// Loop for handling player's input
      	do{
          delay(150);
          // Checking if buttons are pressed and handling them
          if(digitalRead(button_order[0]) == HIGH && !button_pressed_one){
            selected_order[x] = 13;
				on_led(&PORTB, 1 << PB5);
              if(selected_order[x] == correct_order[x]){
                message("GOOD JOB!", 2000, 0);
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
              	on_led(&PORTB, 1 << PB4);
            if(selected_order[x] == correct_order[x]){
                message("NICE!", 2000, 0);
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
                on_led(&PORTB, 1 << PB3);
            if(selected_order[x] == correct_order[x]){
                message("GOOD PLAY!", 2000, 0);
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
              on_led(&PORTB, 1 << PB2);
            if(selected_order[x] == correct_order[x]){
              message("VERY NICE", 2000, 0);
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
              on_led(&PORTB, 1 << PB1);
            if(selected_order[x] == correct_order[x]){
              message("NICE!", 2000, 0);
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
              on_led(&PORTB, 1 << PB0);
              message("GOOD JOB!", 2000, 0);
            if(selected_order[x] == correct_order[x]){
              bool* button[] = {&button_pressed_six};
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
            message("YOU REMEMBERED!", 1100, 0);
          	rounds++;
        }else{
          	message("YOU LOSS :<", 1000, 0);
          	message("YOU SELECTED: ", 900, 0, false);
            lcd_1.setCursor(0, 1);
            lcd_1.print(selected_order[x]);
            delay(700);
            lcd_1.clear();
          	
        	message("BUT IT WAS: ", 900, 0, false);
            lcd_1.setCursor(0, 1);
            lcd_1.print(correct_order[x]);
            delay(700);
            lcd_1.clear();     
            rounds = 1;
            // to do any treading for this situation
          bool* button[] = {&button_pressed_one, &button_pressed_two, &button_pressed_three, &button_pressed_four, &button_pressed_five, &button_pressed_six};
    
         	 reset(button, 6);
        }
    }
    
    // End of game
    Serial.println("\n----------- THE GAME IS OVER -----------");
    bool* button[] = {&button_pressed_one, &button_pressed_two, &button_pressed_three, &button_pressed_four, &button_pressed_five, &button_pressed_six};
    reset(button, 6); // This will reset only the first 6 buttons
    }
  	else{
      	// Displaying message to start the game
        message("PRESS BUTTON SIX ", 500, 0,false);
        message("TO PLAY", 1000, 1,false);
    }
}
