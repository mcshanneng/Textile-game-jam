#include <Adafruit_CircuitPlayground.h>\
/*
Neopixel rainbow code adapted from "Rainbow Chaser"by Carter Nelson
https://learn.adafruit.com/circuit-playground-bike-light/the-rainbow-chaser
*/
//Rainbow cycle for when puzzle is complete
#define ROTATION_RATE   100    // lower is faster
 
// Define 10 colors here.
// Must be 10 entries.
uint32_t colors[] = {
  0xFF0000,   
  0xFF5500,
  0xFFFF00,
  0x00FF00,
  0x00FF55,
  0x00FFFF,
  0x0000FF,
  0x5500FF,
  0xFF00FF,
  0xFFFFFF
};
 
int colorIndex;
int startIndex;


//Puzzle 1
int totalState; // Final state of first puzzle
int buttonPinA = 1; // The physical pin that e-textile material is connected to 
int stateA;
int buttonPinB =0;
int stateB;
int buttonPinC= 2;
int stateC;

// Puzzle 2
int analogMin = 0;
int analogMax = 1023;
//AnalogA
int analogPinA = 11; 
int analogValueA;// variable to store the value coming from the sensor
int colour;     // value for R colour value that changes based on incoming analog data
int mapValA;
//AnalogB
int analogPinB = 9;
int analogValueB;
int colourB; //value for B colour value
int mapValB;

//Completion check
int checkerPin = 19; //used to check the result of Puzzle 2
int p1Done= 0; //checks if Puzzle 1 is done
int checkerState;// checks if checker pin (PIN 19/ on board button) is pressed
int complete=0; //checks if entire puzzle is done

void setup() {
 startIndex = 0;
  Serial.begin(9600); // Starting the serial monitor
  CircuitPlayground.begin(); // Initiating the Circuit Playground
  CircuitPlayground.setBrightness(5);
  //Declare buttons
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinC, INPUT_PULLUP);
  pinMode(checkerPin, INPUT_PULLUP);

}

void loop() {
  Serial.print("Completion State=");
  Serial.println(complete);
  if (complete==1){ //if the puzzle is complete run the rainbow chaser sequence
  // Loop through and set pixels
  colorIndex = startIndex;
  for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
  }
 
  // Increment start index into color array
  startIndex++;
 
  // Check value and reset if necessary
  if (startIndex > 9) startIndex = 0;
 
  // Wait a little bit so we don't spin too fast
  delay(ROTATION_RATE);
  }
  
  else{ // if the puzzle isn't complete read the inputs
  stateA = digitalRead(buttonPinA); // Reading the current value of the pin
  stateB = digitalRead(buttonPinB);
  stateC = digitalRead(buttonPinC);
  checkerState = digitalRead(checkerPin);

 if (checkerState==LOW){
  if (stateA == LOW&& stateB == LOW && stateC ==LOW) { // All of the switches have to be pressed 
   p1Done= 1;
     //Puzzle 2 Variable Declarations
  analogValueA = analogRead(analogPinA); // Read the Analog Sensor
  colour =  map(analogValueA, analogMin, analogMax, 0, 250); // Map the incoming value for colour.
  mapValA= map(analogValueA, analogMin, analogMax,0,10); //Map the incoming value from 1-10 for puzzle puroposes
  
  analogValueB = analogRead(analogPinB);
  colourB=  map(analogValueB, analogMin, analogMax, 0, 250);
  mapValB= map(analogValueB, analogMin, analogMax,0,10);

  //Seial Prints to console to check values (for troubleshooting)
  Serial.print("Val A=");
  Serial.println(mapValA);
  Serial.print("Val B=");
  Serial.println(mapValB);


 for (int i = 0 ; i < 10; i++) { // loop through all of the LED lights on the Circuit Playground and light them up.
      CircuitPlayground.setPixelColor(i,colour,60, colourB);
    }
   }else{ // if the digital switch is not activated, turn the LED lights off. 

    CircuitPlayground.clearPixels();
  }
  }else {
   Serial.println("Button Pressed");
  if (p1Done== HIGH){
    if ((mapValA>4&& mapValA<8)&& mapValB>5){
     mapValA=5;
     mapValB=7;
     Serial.println("Green");
       for (int i = 0 ; i < 10; i++) { // loop through all of the LED lights on the Circuit Playground and light them up.
      CircuitPlayground.setPixelColor(i,20, 250, 30);
      complete=1;
    }
      } else {
       // CircuitPlayground.clearPixels();
            Serial.println("Red");
         for (int i = 0 ; i < 10; i++) { // loop through all of the LED lights on the Circuit Playground and light them up.
      CircuitPlayground.setPixelColor(i,250, 0, 0);}// Colour Red
    }
     //*/ 
    }
}

}
}
