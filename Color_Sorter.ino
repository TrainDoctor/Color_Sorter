#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

//Servo 
int servoPinOne = 12;
int servoPinTwo = 11;
int servoPinThree = 10;
int servoPinFour = 9;
int servoPinFive = 8;
 
Servo servo1; 
Servo servo2;  
Servo servo3;  
Servo servo4;  
Servo servo5;  
 
int servoAngle = 0;   // servo position in degrees

//Color Sensor Declerations 
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

unsigned long averageColorStartRed, averageColorStartBlue, averageColorStartGreen;
unsigned long averageColorFinishedRed,averageColorFinishedBlue, averageColorFinishedGreen;
unsigned long averageColorElapsedRed, averageColorElapsedBlue, averageColorElapsedGreen;
unsigned long start, finished, elapsed;

// set to false if using a common cathode LED
#define commonAnode false

// our RGB -> eye-recognized gamma color
byte gammatable[256];

//
bool colorRed;
bool colorBlue; 
bool colorGreen;  

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
   
void setup()
{
  //Servo
  Serial.begin(9600);
  Serial.println("RGB Sensor Online, running version; 2.0.2");  
  servo5.attach(servoPinFive);
  servo4.attach(servoPinFour);
  servo3.attach(servoPinThree);
  servo2.attach(servoPinTwo);
  servo1.attach(servoPinOne);

  //Color Sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
   // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
}

void loop() {
  uint16_t clear, red, green, blue;

//  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
    
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

//    averageColorStartRed = int(red);
//    averageColorStartBlue = int(blue);
//    averageColorStartGreen = int(green);
//    averageColorFinishedRed = int(red);
//    averageColorFinishedBlue = int(blue);
//    averageColorFinishedGreen = int(green);
//    averageColorElapsedRed=averageColorFinishedRed-averageColorStartRed;
//    averageColorElapsedBlue=averageColorFinishedBlue-averageColorStartBlue;
//    averageColorElapsedGreen=averageColorFinishedGreen-averageColorStartGreen;
//    Serial.print(averageColorElapsedRed + " ");
//    Serial.print(averageColorElapsedBlue + " ");
//    Serial.print(averageColorElapsedGreen + " ");

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

  analogWrite(redpin, gammatable[(int)r]);
  analogWrite(greenpin, gammatable[(int)g]);                                                                                                                                                                       
  analogWrite(bluepin, gammatable[(int)b]);     

    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
    
   if ((red > 3800 && red < 4250) && (green > 2700 && green < 3600) && (blue > 2600 && blue < 3075)){ 
    Serial.print("\n RED RED RED RED RED RED RED ");
    servo5.write(70);
    servo1.write(40);
    delay(1000);
    servo5.write(70);
    servo1.write(40);
    delay(500);
//Reset Section
   servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
  if ((red > 1500 && red < 2800) && (green > 4600 && green < 5100) && (blue > 4500 && blue < 7200)){
    Serial.print("BLUE BLUE BLUE BLUE BLUE BLUE BLUE ");
    servo4.write(135);
    servo3.write(40);
    delay(1500);
    servo4.write(135);
    servo3.write(40);
    delay(500);
    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
  //IT FINALLY WORKS \0/
  if ((red > 3100 && red < 3600) && (green > 6000 && green < 7800) && (blue > 3600 && blue < 4300)){
    Serial.print("GREEN GREEN GREEN GREEN GREEN GREEN GREEN ");
    servo2.write(110);
    delay(1000);
    servo2.write(110);
    delay(500);
    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
  if ((red > 5300 && red < 9800) && (green > 3300 && green < 4450) && (blue > 2700 && blue < 4500)){
    Serial.print("ORANGE ORANGE ORANGE ORANGE ORANGE ORANGE ORANGE ");
    servo1.write(115);
    servo5.write(70);
    delay(1000);
    servo5.write(70);
    servo1.write(115);
    delay(500);
    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
  if ((red > 6000 && red < 11500) && (green > 6500 && green < 11000) && (blue > 3900 && blue < 7500)){
    Serial.print("YELLOW YELLOW YELLOW YELLOW YELLOW YELLOW YELLOW ");
    servo2.write(40);
    delay(1000);
    servo2.write(40);
    delay(500);
    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
   if ((red > 2000 && red < 2500) && (green > 2300 && green < 2700) && (blue > 2300 && blue < 2700)){
    Serial.print("BROWN BROWN BROWN BROWN BROWN BROWN BROWN ");
    servo4.write(135);
    servo3.write(110);
    delay(1000);
    servo4.write(135);
    servo3.write(110);
    delay(500);
    servo5.write(84);
    servo4.write(90);
    servo3.write(90);
    servo2.write(90);
    servo1.write(90);
    return;
  }
}
//end control the servo's direction and the position of the motor 

//Control the servo's speed  
//if you change the delay value (from example change 50 to 10), the speed of the servo changes
//  for(servoAngle = 0; servoAngle < 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
//  {                                  
//    servo.write(servoAngle);              
//    delay(50);                  
//  }
// 
//  for(servoAngle = 180; servoAngle > 0; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
//  {                                
//    servo.write(servoAngle);          
//    delay(10);      
//  }
//  //end control the servo's speed  
//}
