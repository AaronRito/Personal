/* This code is for a LED bike helmet cover that is controlled with two push buttons, and an accelerometer.
Left button for left turn, right button for right turn, both 
buttons for stop. Tilt head right or left for tunring, tilt back for stop.
The default condion is a light show for general visibility.
It will work on the Arduino and Lilypad USB microcontollers, make
sure to select the correct contorller (under Tools/Board/ Your controller)
Date : 11/7/2014
Author :Aaron Rito
*/

int GLED= 11;
int LLED = 9;
int RLED = 10;
int SLED = A5;
int leftHit =0;
int rightHit =0;
int Xaxis = 0;         // fresh data from accelerometer
int Yaxis = 0;
int Zaxis = 0;
int XX = 40; // sensitivity data
int YY = 40; 
int ZZ = 40; 
int Xcal = 18;        // calibration data, 
int YcalLOW = 19;
int YcalHIGH = 22;
int Zcal = 500;
int key = -1;
int i =0;

void setup () {

  pinMode (GLED, OUTPUT);
  pinMode (LLED, OUTPUT);
  pinMode (RLED, OUTPUT);
  pinMode (SLED, OUTPUT);
  attachInterrupt(0, leftButt, FALLING);   // this activates pin 2 on the Arduino using one of the two interrupts.
  attachInterrupt(1, rightButt, FALLING);  // this activates pin 3 as the other interrupt.
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
}

void loop () {
  
/*The Serial prints can be placed at the start and end of each function so 
you can watch on the monitor to see what's happening with the flags. 
I left them here for easy copy/paste..

     Serial.print(leftHit);
     Serial.print(" LOOP   " );
     Serial.println(rightHit);*/
     
    rightHit = 0;
    leftHit =0;
    Xaxis = analogRead(A2); 
    Xaxis = map(Xaxis,0,1023,0,XX);
    Xaxis = constrain(Xaxis, 0, XX);
    Zaxis = analogRead(A4);  
    Yaxis= analogRead(A3);
    Yaxis = map(Yaxis,0,1023,0,YY);
    Yaxis = constrain(Yaxis, 0, YY);  

   while (rightHit ==0 && leftHit == 0 ){
 
         if (Xaxis<Xcal && Yaxis<YcalHIGH && Yaxis>YcalLOW){
  
            for(int fade = 0 ; fade <= 255; fade +=10) { 
 
             analogWrite(LLED, fade);  
             analogWrite(RLED, fade - 40);
             analogWrite(GLED, fade - 80); 
             delay (30);
             Xaxis = analogRead(A2); 
             Xaxis = map(Xaxis,0,1023,0,XX);
             Xaxis = constrain(Xaxis, 0, XX);
             Yaxis= analogRead(A3);
             Yaxis = map(Yaxis,0,1023,0,YY);
             Yaxis = constrain(Yaxis, 0, YY); 
             Serial.print (Xaxis);
             Serial.print ("  "); 
             Serial.print (Yaxis);
             Serial.println ("  ");    
             digitalWrite (RLED, LOW); 
             digitalWrite (LLED, LOW);
             digitalWrite (GLED, LOW);
           }
         }

         else if (Xaxis>=Xcal){
  
           for(int fade1 = 0 ; fade1 <= 255; fade1 +=50) { 
 
             analogWrite(SLED, fade1);  
             delay (30);
             Xaxis = analogRead(A2); 
             Xaxis = map(Xaxis,0,1023,0,XX);
             Xaxis = constrain(Xaxis, 0, XX);
             Serial.println (Xaxis); 
             digitalWrite (SLED, LOW); 
            }
          }
         
         else if (Yaxis>=YcalHIGH){
  
           for(int fade1 = 0 ; fade1 <= 255; fade1 +=50) { 
 
             analogWrite(RLED, fade1);  
             delay (30);
             Yaxis = analogRead(A3); 
             Yaxis = map(Yaxis,0,1023,0,YY);
             Yaxis = constrain(Yaxis, 0, YY);
             Serial.println (Yaxis); 
             digitalWrite (RLED, LOW);
            }
         }
         
         else if (Yaxis<=YcalLOW){
  
           for(int fade1 = 0 ; fade1 <= 255; fade1 +=50) { 
 
             analogWrite(LLED, fade1);  
             delay (30);
             Yaxis = analogRead(A3); 
             Yaxis = map(Yaxis,0,1023,0,YY);
             Yaxis = constrain(Yaxis, 0, YY);
             Serial.println (Yaxis); 
             digitalWrite (LLED, LOW);
            }
         }
       }
       
    if (rightHit ==1) {
   
     rightTurn();
    } 
    
    else if (leftHit ==1) {
   
     leftTurn();
    } 
}

// the interrupt flags are set here....

void leftButt() {
  
  leftHit = 1;
}

void rightButt() {
  
  rightHit = 1;
}

void leftTurn() { // left turn function...
  
   delay(300);
   leftHit =0;

        while (rightHit == 0 && leftHit ==0) {
          
         for(int fade = 0 ; fade <= 255; fade +=10) { 
         analogWrite(LLED, fade); 
         delay(10); 
         }    
        }
   
   digitalWrite (LLED, LOW);
   
   if (rightHit ==1) {
   
     stopNow();
   }   
   if (leftHit == 1) {
  
    delay(500);
    return;
   } 
}

void rightTurn() { // right turn func..
  
   delay(300);
   rightHit =0;
   
        while (rightHit == 0 && leftHit ==0) {
          
         for(int fade = 0 ; fade <= 255; fade +=10) { 
         analogWrite(RLED, fade); 
         delay(10); 
         }    
        }
   digitalWrite (RLED, LOW);
   
   if (leftHit ==1) {
   
     stopNow();
   }   
   if (rightHit == 1) {
  
    delay (500);
    return;
   }    
}

void stopNow() { // Stop function. 
   
  delay(500);
  rightHit = 0;
  leftHit =0;
   
       while (rightHit == 0 && leftHit ==0) {
                  
         digitalWrite(SLED, HIGH); 
         delay(100); 
         digitalWrite(SLED, LOW); 
         delay(100); 
      }
   digitalWrite (SLED, LOW);
   delay (500);
   rightHit = 0;
   leftHit =0;
   return;
      
}

                        

