/* Define PS2 controller parameters */
#include <PS2X_lib.h>                         /* Include PS2 Controller Library */
PS2X ps2x;                                    /* Create PS2 Controller Class*/
byte Vibrate = 0;                             /* Define power to be used on the Rumble motor */
int LX=0, LY=0;                               /* Define variables for Left Stick coordinates */

/* Define LED PWM pins */
byte UpPin    = 9;
byte DownPin  = 6;
byte LeftPin  = 3;
byte RightPin = 5;

/* Define memory parameters */
byte CurrDirection = 0;
byte PrevDirection = 0;    

/* Define config mode parameters */
#include <EEPROM.h>                           /* Include EEPROM Library for storing PWMvalue during power interrupt */
boolean ConfigMode = false;                   /* Define whether the device is in config mode */
byte EEPROMaddr    = 0;                       /* Define address in EEPROM that we are going to use */
int PWMvalue       = EEPROM.read(EEPROMaddr); /* Define intensity of LEDs on a scale from 0 to 255 */

/* The Setup Function gets called only once when the Arduino starts */
void setup(){
  /* Setup pins for LEDS */
  pinMode(UpPin,    OUTPUT); 
  pinMode(DownPin,  OUTPUT);
  pinMode(LeftPin,  OUTPUT);
  pinMode(RightPin,    OUTPUT);

  /* Setup serial connection for debugging */
  Serial.begin(9600);                             /* Set Baudrate to 9600 */

  /* Setup Pins and Settings for PS2 Class */  
  ps2x.config_gamepad(13,11,10,12, true, true);   /* GamePad(clock, command, attention, data, Pressures?, Rumble?). The function returns error value */ 
  if(ps2x.readType()==1){                         /* Check the type of controller. Type 1 = Duel Shock controller */ 
      Serial.println("DualShock");                /* Show if the controller is Duel Shock*/
      Serial.println("Controller Found");
      delay(100);
   }
}

/* The Loop Function gets repeated indefinitely */
void loop(){
  /* Reset CurrDirection */
  CurrDirection = 0;

  /* Red Left Stick Axis values */
  LY = ps2x.Analog(PSS_LY);                     /* Reading Left stick Y axis */
  LX = ps2x.Analog(PSS_LX);                     /* Reading Left stick X axis */

  if(LY < 128) {                                /* Up */
    CurrDirection = UpPin;
  }  
  if(LY > 128) {                                /* Down */
    CurrDirection = DownPin;
  }
  if(LX < 128) {                                /* Left */ 
    CurrDirection = LeftPin;
  }
  if(LX > 128) {                                /* Right */
    CurrDirection = RightPin;
  }

  /* Read button states */
  ps2x.read_gamepad(false, Vibrate);          /* You could set large motor to spin at 'Vibrate' speed */

  if(ps2x.NewButtonState()) {                 /* This will be TRUE if any button changes state  */
    
    if(ps2x.Button(PSB_START)) {              /* This will be TRUE as long START button is pressed */
      Serial.println("START PRESSED");
      ConfigMode = true;                      /* The device will enter configuration mode */ 
    }
    if(ps2x.Button(PSB_SELECT)) {             /* This will be TRUE as long SELECT button is pressed */
      Serial.println("SELECT PRESSED");
      EEPROM.write(EEPROMaddr, PWMvalue);     /* Store PWM value in EEPROM value */
      ConfigMode = false;                     /* The device will leave configuration mode */
    }
    if(ps2x.Button(PSB_PAD_UP)) {             /* This will be TRUE as long as UP button is pressed */
      Serial.println("UP PRESSED"); 
      CurrDirection = UpPin;
    }
    if(ps2x.Button(PSB_PAD_RIGHT)) {          /* This will be TRUE as long as UP button is pressed */
      Serial.println("RIGHT PRESSED");
      CurrDirection = RightPin; 
    }
    if(ps2x.Button(PSB_PAD_LEFT)) {           /* This will be TRUE as long as LEFT button is pressed */
      Serial.println("LEFT PRESSED"); 
      CurrDirection = LeftPin;
    }
    if(ps2x.Button(PSB_PAD_DOWN)) {           /* This will be TRUE as long as DOWN button is pressed */
      Serial.println("DOWN PRESSED");
      CurrDirection = DownPin; 
    } 
    
    /* In case you would like to add features, use the functions below */
    if(ps2x.Button(PSB_L1))                   /* This will be TRUE as long as L1 button is pressed */
       Serial.println("L1 pressed");
    if(ps2x.Button(PSB_R1))                   /* This will be TRUE as long as R1 button is pressed */
       Serial.println("R1 pressed"); 
    if(ps2x.Button(PSB_L2))                   /* This will be TRUE as long as L2 button is pressed */
       Serial.println("L2 pressed");
    if(ps2x.Button(PSB_R2))                   /* This will be TRUE as long as R2 button is pressed */
       Serial.println("R2 pressed");
    if(ps2x.Button(PSB_L3))                   /* This will be TRUE as long as L3 button is pressed */
       Serial.println("L3 pressed");
    if(ps2x.Button(PSB_R3))                   /* This will be TRUE as long as R3 button is pressed */
       Serial.println("R3 pressed");
    if(ps2x.Button(PSB_GREEN))                /* This will be TRUE as long as GREEN/Triangle button is pressed */
       Serial.println("Triangle pressed");
    if(ps2x.Button(PSB_BLUE))                 /* This will be TRUE as long as BLUE/CROSS/X button is pressed */
       Serial.println("X pressed"); 
     if(ps2x.Button(PSB_RED))                 /* This will be TRUE as long as RED/Circle button is pressed */
       Serial.println("Circle pressed"); 
    if(ps2x.Button(PSB_PINK))                 /* This will be TRUE as long as PINK/Squre button is pressed */
       Serial.println("Square pressed"); 
  }

   
  if(ConfigMode) {
    /* Allow user to set the LED intensity */
    analogWrite(UpPin, PWMvalue);
    analogWrite(DownPin, PWMvalue);
    analogWrite(LeftPin, PWMvalue);
    analogWrite(RightPin, PWMvalue);

    if(CurrDirection == UpPin && PWMvalue < 255)   /* Increase LED intensity */
      PWMvalue += 10;
    
    if(CurrDirection == DownPin && PWMvalue > 5)   /* Decrease LED intensity */
      PWMvalue -= 10;
    
  }
  else {
    /* Process changes in LED states */
    if(CurrDirection != PrevDirection) {        /* This will be TRUE as long as something changed */
      digitalWrite(PrevDirection, LOW);         /* Turn previous LED off */
      if(CurrDirection == 0) {                  /* Turn all LEDs off, just to be sure */
        digitalWrite(UpPin, LOW);
        digitalWrite(DownPin, LOW);
        digitalWrite(LeftPin, LOW);
        digitalWrite(RightPin, LOW);
      }
      else {
        analogWrite(CurrDirection, PWMvalue);     /* Turn new LED on */
      }
        
      PrevDirection = CurrDirection;           /* Remember which LED we toggled this time */
    }
  }
}
