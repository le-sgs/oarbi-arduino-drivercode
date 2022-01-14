char t;
#define ena 7
#define enb 6
#define echoPin 8 
#define trigPin 13

int numberRecvd;
String dataString = "";

//For distance sensor additional ground and +5V
#define VCC2  3 // 
#define GND2  4 //
//Trig - Grey
//Echo - Orange wire

//Bluetooth Yellow at end then Orange
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {

pinMode(VCC2,OUTPUT);//define a digital pin as output
digitalWrite(VCC2, HIGH);// set the above pin as HIGH so it acts as 5V

pinMode(GND2,OUTPUT);//define a digital pin as output
digitalWrite(GND2, LOW);// set the above pin as LOW so it acts as Ground  

pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

pinMode(9,OUTPUT);   //left motors forward
pinMode(10,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(12,OUTPUT);   //right motors reverse
pinMode(ena, OUTPUT);
pinMode(enb, OUTPUT); 
Serial.begin(9600);

}
 
void loop() {
//Obstacle avoiding code


//Obstacle avoiding code ends

  
  if(Serial.available() > 0){
    
    dataString = "";
    while (Serial.available() > 0)
    {
      dataString += char(Serial.read());
      delay(2);
    }
    numberRecvd = dataString.toInt();


switch (numberRecvd) {
    //Assisted Mind Control Driving
case 1:
      //Forward
  int f;
  f = 1;
  while(f==1)
  {    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");
if(distance > 20)
 {
 Serial.print("Reached higher");
 digitalWrite(9,HIGH);
 digitalWrite(10,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 analogWrite(ena, 255);
 analogWrite(enb, 255);
 }
 if(distance < 19)
 {
 Serial.print("Reached lesser");
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 
}
if(Serial.available() > 0)
{
f=0;
break;
}
  }
break;
        
  case 4:
      //Right by turning one set wheel forward
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 analogWrite(ena, 250);
 analogWrite(enb, 250);
 delay(1250); // Rotate for 90 degree left turn
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 
 break;
 

 /*
  *  digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 analogWrite(ena, 250);
 analogWrite(enb, 250);
 break;
  */
        
      case 3:
      //Reverse
 digitalWrite(9,LOW);
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH);
 analogWrite(ena, 250);
 analogWrite(enb, 250);
        break;

       case 2:
  //Left by turning one set wheel backwards

 digitalWrite(9,HIGH);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 analogWrite(ena, 200);
 analogWrite(enb, 200);
 delay(1300); // Rotate for 90 degree left turn
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 break;
/*Code for proper right
 * digitalWrite(9,HIGH);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 analogWrite(ena, 150);
 analogWrite(enb, 150);
        break;
 */
        case 5:
        //Stop
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
        break;

        case 6:
        //Self Drive Mode with no brain interaction
        int self;
        self = 1;
        while(self == 1)
        {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2; 
 
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");
if (distance >25)            
            {
 digitalWrite(9,HIGH);  //Move Forward
 digitalWrite(10,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 analogWrite(ena, 200);
 analogWrite(enb, 200);
 Serial.print("Moving forward");                                                  
            }

if (distance < 24)
             {
             Serial.print("Obstace avoiding process starts");
             digitalWrite(9, LOW);  //Stop                
             digitalWrite(10, LOW);
             digitalWrite(11, LOW);                                
             digitalWrite(12, LOW);
             delay(500);
             
             digitalWrite(11, LOW);      //Move Backward         
             digitalWrite(12, HIGH);
             digitalWrite(9, LOW);                                
             digitalWrite(10, HIGH);
             analogWrite(ena, 200);
             analogWrite(enb, 200); 
             delay(500);
             
             digitalWrite(9, LOW);  //Stop                
             digitalWrite(10, LOW);
             digitalWrite(11, LOW);                                
             digitalWrite(12, LOW);
             delay(2000);  
             
digitalWrite(9,HIGH);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 analogWrite(ena, 200);
 analogWrite(enb, 200);
             delay(500);
            }
            // 2 - rotate leftleft
            // 4 - rotate right
        if(Serial.available() > 0)
         { 
         self = 0;
         break;
         }
        }
        break;
        
      default:
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
        break;
    }
 
    Serial.flush();
    Serial.print("Received Brain Input: ");
    Serial.println(numberRecvd);
  }
  
  delay(20);
}

//Default backup code for motors
/*    ///start of origi
 if(t == '5'){      //STOP (all motors stop)
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  delay(3000);
}
else
{
if(t == '1'){            //move forward(all motors rotate in forward direction)
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
 analogWrite(ena, 150);
 analogWrite(enb, 150);
}
 
else if(t == '2'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
 analogWrite(ena, 150);
 analogWrite(enb, 150);
}
 
else if(t == '3'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
 analogWrite(ena, 150);
 analogWrite(enb, 150);
}
 
else if(t == '4'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
 analogWrite(ena, 150);
 analogWrite(enb, 150);
}
 
else if(t == '5'){      //STOP (all motors stop)
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}
}
delay(100);


pinMode(9,OUTPUT);   //left motors forward
pinMode(10,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(12,OUTPUT);   //right motors reverse




if (distance > 19)            
            {
  digitalWrite(9,HIGH);  //Move Forward
 digitalWrite(10,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(12,LOW);
 analogWrite(ena, 150);
 analogWrite(enb, 150);                                                     
            }

if (distance < 18)
             {
             digitalWrite(9, LOW);  //Stop                
             digitalWrite(10, LOW);
             digitalWrite(11, LOW);                                
             digitalWrite(12, LOW);
             delay(500);
             
             digitalWrite(11, LOW);      //Move Backward         
             digitalWrite(12, HIGH);
             digitalWrite(9, LOW);                                
             digitalWrite(10, HIGH);
             analogWrite(ena, 150);
             analogWrite(enb, 150); 
             delay(500);
             
             digitalWrite(9, LOW);  //Stop                
             digitalWrite(10, LOW);
             digitalWrite(11, LOW);                                
             digitalWrite(12, LOW);
             delay(100);  
             
             digitalWrite(9,LOW);
             digitalWrite(10,LOW);
             digitalWrite(11,HIGH); //Turn Right
             digitalWrite(12,LOW);
             analogWrite(ena, 150);
             analogWrite(enb, 150);
             delay(500);
            }

}*/
