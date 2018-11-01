/* This code is for a LED bike helmet cover that is controlled with two push buttons.
Left button for left turn, right button for right turn, both 
buttons for stop. The default condion is a light show for general visibility.
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

   if (leftHit == 0 && rightHit == 0) {
   
       pulse();   
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
    pulse();
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
    pulse();
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
   pulse();
      
}

// A more exciting light show, sort of.This function runs by default when the contoller is on.
void pulse() {

   
   rightHit = 0;
   leftHit =0;
 
    while (rightHit ==0 && leftHit == 0) {
     for(int fade = 0 ; fade <= 255; fade +=10) { 
       analogWrite(LLED, fade);  
       analogWrite(RLED, fade - 40);
       analogWrite(GLED, fade - 80); 
       delay (30);
      }
    }
   digitalWrite (RLED, LOW); 
   digitalWrite (SLED, LOW);
   digitalWrite (LLED, LOW);
   digitalWrite (GLED, LOW);
    if (rightHit == 1){
    
      rightTurn();
    }
    if (leftHit == 1){
    
      leftTurn();
    }  
}                          
   
