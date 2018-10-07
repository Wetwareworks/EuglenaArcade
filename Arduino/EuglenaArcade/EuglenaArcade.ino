#include <PS2X_lib.h>                         /* PS2 Controller Library */
PS2X ps2x;                                    /* create PS2 Controller Class*/
byte Type = 0;
byte vibrate = 0;
int LX=0,LY=0;

void setup(){
  pinMode(2, OUTPUT); /* setup pins for LEDS */
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600); /* setup serial connection for debugging */
   ps2x.config_gamepad(13,11,10,12, true, true); /* setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error*/
   Type = ps2x.readType();                       /* Reading type of the PS2 Ccontroller */
   if(Type==1){                                  /* Type 1 is Duel shock controller */ 
      Serial.println("   DualShock    ");             /* display if the controller is duel shock*/
      Serial.println("Controller Found");
      delay(100);
   }
}
void loop(){

   LY = ps2x.Analog(PSS_LY);          /* Reading Left stick Y axis */
   LX = ps2x.Analog(PSS_LX);          /* Reading Left stick X axis */
   //Serial.println(LY,DEC);                 /* display left analog stick Y axis */
   //Serial.println(",");                    /* separate values using comma */
   //Serial.println(LX,DEC);   

  if(LY < 128) {
    // DOWN
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if(LY > 128) {
    // UP
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if(LX < 128) { 
    // LEFT
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if(LX > 128) {
    // RIGHT
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

   ps2x.read_gamepad(false, vibrate);   /* read controller and set large motor to spin at 'vibrate' speed */

   if(ps2x.NewButtonState()) {        /* will be TRUE if any button changes state  */
      //lcd.setCursor(0, 0);
      if(ps2x.Button(PSB_START))      /* will be TRUE as long START button is pressed */
         Serial.println("START PRESSED   ");
      if(ps2x.Button(PSB_SELECT))             /* will be TRUE as long SELECT button is pressed */
         Serial.println("SELECT PRESSED  ");
      if(ps2x.Button(PSB_PAD_UP)) {            /* will be TRUE as long as UP button is pressed */
         Serial.println("UP PRESSED      "); 
         digitalWrite(2, LOW);
         digitalWrite(3, LOW);
         digitalWrite(4, HIGH);
         digitalWrite(5, LOW); }
      if(ps2x.Button(PSB_PAD_RIGHT)) {         /* will be TRUE as long as UP button is pressed */
         Serial.println("RIGHT PRESSED   ");
         digitalWrite(2, LOW);
         digitalWrite(3, HIGH);
         digitalWrite(4, LOW);
         digitalWrite(5, LOW); }
      if(ps2x.Button(PSB_PAD_LEFT)) {          /* will be TRUE as long as LEFT button is pressed */
         Serial.println("LEFT PRESSED    "); 
         digitalWrite(2, HIGH);
         digitalWrite(3, LOW);
         digitalWrite(4, LOW);
         digitalWrite(5, LOW); }
      if(ps2x.Button(PSB_PAD_DOWN)) {           /* will be TRUE as long as DOWN button is pressed */
         Serial.println("DOWN PRESSED    ");
         digitalWrite(2, LOW);
         digitalWrite(3, LOW);
         digitalWrite(4, LOW);
         digitalWrite(5, HIGH); } 
      if(ps2x.Button(PSB_L1))                 /* will be TRUE as long as L1 button is pressed */
         Serial.println("L1 pressed      ");
      if(ps2x.Button(PSB_R1))                 /* will be TRUE as long as R1 button is pressed */
         Serial.println("R1 pressed      "); 
      if(ps2x.Button(PSB_L2))                 /* will be TRUE as long as L2 button is pressed */
         Serial.println("L2 pressed      ");
      if(ps2x.Button(PSB_R2))                 /* will be TRUE as long as R2 button is pressed */
         Serial.println("R2 pressed      ");
      if(ps2x.Button(PSB_L3))                 /* will be TRUE as long as L3 button is pressed */
         Serial.println("L3 pressed      ");
      if(ps2x.Button(PSB_R3))                 /* will be TRUE as long as R3 button is pressed */
         Serial.println("R3 pressed      ");
      if(ps2x.Button(PSB_GREEN))              /* will be TRUE as long as GREEN/Triangle button is pressed */
         Serial.println("Triangle pressed");
      if(ps2x.Button(PSB_BLUE))                /* will be TRUE as long as BLUE/CROSS/X button is pressed */
         Serial.println("X pressed       "); 
       if(ps2x.Button(PSB_RED))               /* will be TRUE as long as RED/Circle button is pressed */
         Serial.println("Circle pressed  "); 
      if(ps2x.Button(PSB_PINK))               /* will be TRUE as long as PINK/Squre button is pressed */
         Serial.println("Square pressed  "); 
      delay(50);
   }
   else {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
   }
}
