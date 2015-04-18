#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
int analogIn = A1;
int value = 0;

void setup() 
{ 
  myservo.attach(13);  // attaches the servo on pin 9 to the servo object 
} 
 

void loop(){
  value = analogRead(analogIn);//reading from pin A1
  Serial.println(value);
  if (value < 300) {
    //display_pattern(15);// calls for the display_pattern function and says that int loop = 15(if you do more loop the pattern would scroll slower).
    for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  }
}
