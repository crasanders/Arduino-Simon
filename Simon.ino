#include "pitches.h" //https://github.com/arduino/Arduino/blob/master/build/shared/examples/02.Digital/toneMelody/pitches.h

#define RED_LED 5
#define YELLOW_LED 4
#define GREEN_LED 3
#define BLUE_LED 2

#define RED_BUTTON 8
#define YELLOW_BUTTON 9
#define GREEN_BUTTON 10
#define BLUE_BUTTON 11

#define BUZZER 7

#define N_COLORS 4
#define MAX_SEQUENCE 10
#define NOTE_DURATION 100
#define WRONG_NOTE NOTE_A1
#define WRONG_DURATION 250

int leds[] = {RED_LED, YELLOW_LED, GREEN_LED, BLUE_LED};
int notes[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_B5};

int sequence[MAX_SEQUENCE];
int n = 0;
int selection;
bool correct;

void light(int i, int duration){
    digitalWrite(leds[i], HIGH);
    tone(BUZZER, notes[i], NOTE_DURATION);
    delay(duration);
    digitalWrite(leds[i], LOW);
}

void buzz(){
    for (int i=0; i<N_COLORS; i++){
      digitalWrite(leds[i], HIGH);
    }
    tone(BUZZER, WRONG_NOTE, WRONG_DURATION);
    delay(500);
    for (int i=0; i<N_COLORS; i++){
      digitalWrite(leds[i], LOW);
    }
}
 
void setup() {
  pinMode(RED_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);

  pinMode(RED_BUTTON,INPUT_PULLUP);
  pinMode(YELLOW_BUTTON,INPUT_PULLUP);
  pinMode(GREEN_BUTTON,INPUT_PULLUP);
  pinMode(BLUE_BUTTON,INPUT_PULLUP);

  randomSeed(analogRead(0));

  correct = true;
}

void loop() {
  while (n < MAX_SEQUENCE && correct){
    //Get next color
    selection = random(0, 4);
    sequence[n] = selection;
    n++;

    //Light up color sequence
    for (int i=0; i<n; i++){
      light(sequence[i], 1000);
      delay(100);
    }

    //Get player input
    for (int i=0; i<n; i++){
      
      int button_press = -1;
      while (button_press < 0){
        while (digitalRead(RED_BUTTON) == LOW){
          button_press = RED_LED;
        }
        while (digitalRead(YELLOW_BUTTON) == LOW){
          button_press = YELLOW_LED;
        }
        while (digitalRead(GREEN_BUTTON) == LOW){
          button_press = GREEN_LED;
        }
        while (digitalRead(BLUE_BUTTON) == LOW){
          button_press = BLUE_LED;
        }
      }

      //If correct color is chosen, light it up and continue
      if (button_press == leds[sequence[i]]){
        light(sequence[i], 250);
      }

      //If incorrect color is chosen, give an error and end the game
      else{
        buzz();
        correct = false;
        break;
      }
    }
    delay(1000);
  }

  //If the player successfully completes the full sequence, celebrate with lights and sounds
  if (correct){
    for (int j=0; j<3; j++){
      for (int i=0; i<N_COLORS; i++){
        light(i, 100);
      }
    }
    correct = false;
  }
  
}
   
