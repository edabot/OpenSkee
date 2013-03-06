// this constant won't change:
const int  holePin[] = {22,23,24,25,26,27,28};    // the pins that the switches are attached to 
const int  holeValue[] = {10,20,30,40,50,100,100};
const int  startPin = 30;
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int ballCount=0;                             //balls left to play
int score=0;                                 //game score
int streak=1;                                //number of times current hole has been hit in a row
int lastHole=0;                              //last hole hit
int buttonState[] = {0,0,0,0,0,0,0};         // current states of the buttons   
int startState = 0;
int lastButtonState[] = {0,0,0,0,0,0,0};     // previous states of the buttons  
int lastStartState = 0;

#include <LiquidCrystal.h>
#include <DFR_Key.h>
//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
//---------------------------------------------

DFR_Key keypad;

int localKey = 0;
String keyString = "";
                 
void setup() {
  // initialize the button pin as a input:
   for (int i=0; i<7; i++){
     pinMode(holePin[i], INPUT);
   }
  pinMode(startPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OpenSkee");
  
}

void loop() {
  // read the pushbutton input pin:
     for (int i=0; i<7; i++){
     buttonState[i] = digitalRead(holePin[i]);
   }
  
  startState = digitalRead(startPin);

  //Start Button function for starting game if ballCount=0
 // compare the buttonState to its previous state
  if (startState != lastStartState) {
    // if the state has changed, increment the counter
    if (startState == LOW && ballCount==0) {
      // if the current state is HIGH then the button
       // went from off to on:
      score=0;
      streak=1;
      lastHole=0;
      ballCount=9;
      Serial.println("Game on!");
      Serial.print("score: ");
      Serial.println(score);
      Serial.print("balls left: ");
      Serial.println(ballCount);
         lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game on!");
    lcd.setCursor(0, 1);
    lcd.print("balls left: ");
    lcd.print(ballCount);
      delay(500);
    }
    else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println();
    }
  }
 
for (int i=0; i<7; i++){
 if (buttonState[i] != lastButtonState[i]) {
    // if the state has changed, increment the counter
    if (buttonState[i] == LOW && ballCount>0) {
        Serial.print("You hit the ");
        Serial.println(holeValue[i]);
      // add up new score and reduce ballCount for each hit
      score=score+holeValue[i];
      ballCount--;
      
      //add more points for a streak
       if (lastHole==holeValue[i] && lastHole!=10) {
        score = score + holeValue[i]*streak/2;
        streak++;

        Serial.print("streak: ");
        Serial.println(streak);
      }
      else {
        streak=1;
        lastHole=holeValue[i];
      }
      Serial.print("score: ");
      Serial.println(score);
      Serial.print("balls left: ");
      Serial.println(ballCount);
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("score:");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("balls left: ");
    lcd.print(ballCount);
    
    /*  for (int i=0; i<streak;i++){
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);               // wait for a second
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(200);               // wait for a second
      }*/
      delay(300);
    } 
    else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println();
    }
  }
}
   
  // save the current state as the last state,
  //for next time through the loop
   for (int i=0; i<7; i++){
  lastButtonState[i] = buttonState[i];
   }
  lastStartState = startState;
}
