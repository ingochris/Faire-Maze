// 10*8 LED matrix with 4017 IC
// LED maze commented 

#include <Servo.h> 

int clock = 9;// goes to the clock pin on the 4017 IC
int reset = 8;//goes to the reset pin on the 4017 IC
int analogIn = A1;
int value = 0;

#define maze {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move1 {B11111111,B10000001,B11111001,B10001100,B10100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move2 {B11111111,B10000001,B11111001,B10001100,B01100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move3 {B11111111,B10000001,B11111001,B11001100,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move4 {B11111111,B10000001,B11111001,B10101100,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move5 {B11111111,B10000001,B11111001,B10011100,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move6 {B11111111,B10000001,B11111001,B10001100,B00110101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move7 {B11111111,B10000001,B11111001,B10001100,B00101101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move8 {B11111111,B10000001,B11111001,B10001100,B00100101,B11111101,B10010101,B10110101,B10000001,B11111111}
#define move9 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10011101,B10110101,B10000001,B11111111}
#define move10 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10111101,B10000001,B11111111}
#define move11 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10110101,B10001001,B11111111}
#define move12 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10110101,B10000101,B11111111}
#define move13 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10110101,B10000011,B11111111}
#define move14 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010101,B10110111,B10000001,B11111111}
#define move15 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110101,B10010111,B10110101,B10000001,B11111111}
#define move16 {B11111111,B10000001,B11111001,B10001100,B00100101,B11110111,B10010101,B10110101,B10000001,B11111111}
#define move17 {B11111111,B10000001,B11111001,B10001100,B00100111,B11110101,B10010101,B10110101,B10000001,B11111111}
#define move18 {B11111111,B10000001,B11111001,B10001110,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define finish {B11111111,B10000001,B11111001,B10001101,B00100101,B11110101,B10010101,B10110101,B10000001,B11111111}
#define times {B00000000,B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000,B00000000}

const int numPatterns = 20;//this is the number of patterns you want to display
byte patterns[numPatterns][10]={maze, move1, move2, move3, move4, move5, move6, move7, move8, move9, move10, 
                                move11, move12, move13, move14, move15, move16, move17, move18, finish};// the patterns order
int x;
int y;

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards 
int pos = 0;    // variable to store the servo position 

void setup(){
    Serial.begin(9600);
    DDRD=B11111111;// this is a commed that makes pins 0-7 outputs(see more on the arduino site)
    //simple stuff here
    pinMode(clock,OUTPUT);
    pinMode(reset,OUTPUT);
    //reseting the 4017 IC, you have to do this
    digitalWrite(reset,HIGH);
    delayMicroseconds(5);
    digitalWrite(reset,LOW);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void display_pattern(int loops)//(int loop) acts like a delay, it take 8 mSecands to scan all of the rows so int loops = 15 is a good time for it
{ 
    for(x = 0; x < numPatterns-1; x++){ // loop over the patterns
        for (int z = 0; z < 8; z++){ //scrolls one bite at a time 
            for(int t = 0; t < loops; t++){// the delay we get with loops
                for(y = 0; y < 10; y++){// loops over the array of bytes
                    PORTD = patterns[x][y];//writes digital outputs
                    delayMicroseconds(800);// the time every row is one
                    PORTD = B00000000;// all pins are low, fixes the ghosting effect
                    // telles the 4017 IC to go to the next row
                    digitalWrite(clock,HIGH);
                    delayMicroseconds(5);
                    digitalWrite(clock,LOW);
                }
            }
        }
    }
}


void loop(){
  value = analogRead(analogIn);//reading from pin A1
  Serial.println(value);
  if (value > 300) {
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

