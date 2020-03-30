//Dhaddammm Robotics //
// 1 is front, 2 is right, 3 is left

const int buzzer = A5;
const int trigPin1 = 6;
const int echoPin1 = 7;
const int trigPin2 = 8; //13;
const int echoPin2 = 9;
const int trigPin3 = 12; //PWM enabled
const int echoPin3 = 13; // PWM enabled
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int enA = 10; // change to trigpin3
const int enB = 11; // change to echopin3
#define fullSpeed 220
#define PWM 150
#define minDistance 50
#define maxDistance 500

void setup() 
{
 //Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
 pinMode (in1, OUTPUT);
 pinMode (in2, OUTPUT);
 pinMode (in3, OUTPUT);
 pinMode (in4, OUTPUT);
 pinMode (enA, OUTPUT);
 pinMode (enB, OUTPUT); 
}


void loop(){

  forward();

 if ( FrontSensor() < minDistance && RightSensor() < minDistance && LeftSensor() < minDistance ) // obstacle infront of all 3 sides
 {
        reverse(); 
        delay(900);
        
        if ( RightSensor() > LeftSensor() ) // after reversing, RIGHT side has more space
 {
        //reverse(); 
        //delay(700);
        turn_right();
        delay(1500);
        //forward(); 
 }
        else if ( RightSensor() < LeftSensor() ) // after reversing, LEFT side has more space
 {
        turn_left();
        delay(1500);
        //forward();
 }
 
 }

 
 else if ( FrontSensor() < minDistance && RightSensor() < minDistance && LeftSensor() > minDistance ) // obstacle on RIGHT and FRONT side
 { 
 reverse();
 delay(900);
 turn_left (); // turn left side
 delay(1500);
 }

 
 else if ( FrontSensor() < minDistance && RightSensor() >minDistance && LeftSensor() < minDistance ) // obstacle on LEFT and FRONT side
 {
 reverse();
 delay(900);
 turn_right (); // turn right side
 delay(1500);
 }


 else if ( FrontSensor() < minDistance && RightSensor() > minDistance && LeftSensor() > minDistance ) // obstacle just in FRONT
 { 
 reverse (); // reverse
 delay(900);
        if ( RightSensor() > LeftSensor() ) // after reversing, RIGHT side has more space
 {
        turn_right();
        delay(1500); 
 }
        else if ( RightSensor() < LeftSensor() ) // after reversing, LEFT side has more space
 {
        turn_left();
        delay(1500); 
 }
 }


 else if ( FrontSensor() > minDistance && RightSensor() > minDistance && LeftSensor() < minDistance ) // obstacle just on the LEFT 
 {
 reverse();
 delay(900);
 turn_right (); 
 delay(1500);
 }


 else if ( FrontSensor() > minDistance && RightSensor () < minDistance && LeftSensor() > minDistance ) // obstacle just on the RIGHT
 {
 reverse();
 delay(900);
 turn_left (); 
 delay(1500);
 }

 else if ( FrontSensor() > minDistance && RightSensor () > minDistance && LeftSensor() > minDistance ) // No obstacle 
 {
 forward();
 }

///////////////////////////////////EXCEPTION CASES///////////////////////////////////////////
 else if ( (FrontSensor() < 10 || RightSensor() < 10 || LeftSensor() < 10) || (FrontSensor() > 500 || RightSensor() > 500 || LeftSensor() > 500) ) // Any obstacle that is too close 
 {
 reverse();
 delay(900);
 }



 else 
 {
 forward();
 }


}


void forward ()         
 // left wheels: in1 L, in2, H
 // right wheels: in3 H, in4 L

{
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enA, PWM); 
 analogWrite(enB, PWM);
}


void turn_left () // right wheels forward
{
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enA, fullSpeed); 
 analogWrite(enB, fullSpeed);
}


void turn_right () // left wheels forward
{
 digitalWrite(in1, LOW); 
 digitalWrite(in2, HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
 analogWrite(enA, fullSpeed);
 analogWrite(enB, fullSpeed);
}


void reverse ()
{
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 analogWrite(enA, fullSpeed);
 analogWrite(enB, fullSpeed);
}


void stop()
{
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
 analogWrite(enA, 0);
 analogWrite(enB, 0);
}

long FrontSensor ()
{
 long dur;
 long cm;
 long bestEstimate;

 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(5); // delays are required for a succesful sensor operation.
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); //this delay is required as well!
 digitalWrite(trigPin1, LOW);
 dur = pulseIn(echoPin1, HIGH);
 // CHANGED HERE TO ADD POST PROCESSING. NOT DONE
 cm = (dur/29.1);// convert the minDistancetance to centimeters.
 // post process values
 bestEstimate = cm;
 return bestEstimate;
}


long RightSensor () 
{
 long dur;
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(5); // delays are required for a succesful sensor operation.
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); //this delay is required as well!
 digitalWrite(trigPin2, LOW);
 dur = pulseIn(echoPin2, HIGH);
 return (dur/29.1);// 62, convert the minDistancetance to centimeters.
}


long LeftSensor ()    
{
 long dur;
 digitalWrite(trigPin3, LOW); 
 delayMicroseconds(5); // delays are required for a succesful sensor operation.
 digitalWrite(trigPin3, HIGH);
 delayMicroseconds(10); //this delay is required as well!
 digitalWrite(trigPin3, LOW);
 dur = pulseIn(echoPin3, HIGH);
 return (dur/29.1);// 50,convert the minDistancetance to centimeters.
}
