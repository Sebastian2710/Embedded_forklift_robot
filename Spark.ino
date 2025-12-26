#include "NewPing.h"                   
#define trig 12                       
#define echo 11                        
#define maxd 250                       
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 23
#define NUM_PIXELS 8
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
//alb sus,
// DC Motor A
int enA = 9;                          
int in1 = 5;                          
int in2 = 4;                          
// DC Motor B
int enB = 6;                         
int in3 = 2;                           
int in4 = 3;                           
                     
NewPing sonar(trig, echo, maxd);       

// Joystick
int jx = A2;
int jy = A1;
int jb = 10;

int servo = 13;
Servo srv;

void showLevel(int count, uint8_t r, uint8_t g, uint8_t b) {
  pixels.clear();
  for (int i = 0; i < count; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

void setup(){                          
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(jx, INPUT_PULLUP);
  pinMode(jy, INPUT_PULLUP);
  pinMode(jb, INPUT_PULLUP);
  pixels.begin();
  pixels.clear();
  pixels.show();
  Serial.begin(9600);
} 

int forklift_move_direction = 1; // 0 == down , 1 == up  

int current_height = 90;
void loop(){                            
  delay(50);  
                         
  unsigned int d = sonar.ping_cm();   
  Serial.print("Distanta: ");           
  Serial.print(d );                  
  Serial.println("cm  ");   
  if (d == 0 || d > 20) 
    showLevel(0, 0, 0, 0);            // all off
  else if (d > 15)
    showLevel(2, 0, 255, 0);          // green
  else if (d > 10)
    showLevel(4, 255, 255, 0);        // yellow
  else if (d > 5)
    showLevel(6, 255, 100, 0);        // orange
  else
    showLevel(8, 255, 0, 0);          // red
  
  // machine works with joystick   
  int x = analogRead(jx);
  int y = analogRead(jy);
  int b = digitalRead(jb);   
  int speedA = 0;
  int speedB = 0;
  
  // Forklift control                                                                                          
  if ( x > 530 && x < 570 && y >530 && y < 570 && b==0)
  {
    srv.attach(servo); 
    Serial.println("button pressed");
    if(forklift_move_direction == 0 && current_height >= 100)
      forklift_move_direction = 1;
    else
      if(forklift_move_direction == 1 && current_height <= 10)
        forklift_move_direction = 0;
    
    if(forklift_move_direction == 0)
      // move forklift down
      current_height+=5;
    else
      // move forklift up 
      current_height-=5;
    Serial.println(current_height);
    srv.write(current_height);
    delay(100);
  }
  else
    srv.detach();
  // Car movement control
  if ( x < 50)
    if( y > 50)
      if ( y < 950)
      {
        //Serial.println("back");
        digitalWrite(in1, LOW);              
        digitalWrite(in2, HIGH);                         
        speedA=100;              
        digitalWrite(in3, LOW);             
        digitalWrite(in4, HIGH);
        speedB=100;
      }
      else
      {
        //Serial.println("back-right");
        digitalWrite(in1, LOW);              
        digitalWrite(in2, HIGH);                         
        speedA=100;              
        digitalWrite(in3, LOW);             
        digitalWrite(in4, HIGH);
        speedB=50;
      } 
    else
    {
      //Serial.println("back-left");
      digitalWrite(in1, LOW);              
      digitalWrite(in2, HIGH);                         
      speedA=50;              
      digitalWrite(in3, LOW);             
      digitalWrite(in4, HIGH);
      speedB=100;
    }
  if ( x > 950)
    if( y > 50)
      if ( y < 950)
      {
        //Serial.println("front");
        digitalWrite(in1, HIGH);              
        digitalWrite(in2, LOW);                         
        speedA=100;              
        digitalWrite(in3, HIGH);             
        digitalWrite(in4, LOW);
        speedB=100;
      }
      else
      {
        //Serial.println("front-left");
        digitalWrite(in1, HIGH);              
        digitalWrite(in2, LOW);                         
        speedA=100;              
        digitalWrite(in3, HIGH);             
        digitalWrite(in4, LOW);
        speedB=50;
      }
    else
    {
      //Serial.println("front-right");
      digitalWrite(in1, HIGH);              
      digitalWrite(in2, LOW);                         
      speedA=50;              
      digitalWrite(in3, HIGH);             
      digitalWrite(in4, LOW);
      speedB=100;
    }
  analogWrite(enA,speedA);
  analogWrite(enB,speedB);
  
}

