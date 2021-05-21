
#include <NintendoSwitchControlLibrary.h>
#include <Psx.h>

const int DataPin = 8;
const int CmndPin = 9;
const int ClockPin = 10;
const int AttPin = 11;

const int StickXPin = 0;
const int StickYPin = 1;
const int StickSwPin = 20;

Psx Psx;
unsigned int PsRead = 0;  

bool Mode103 = false;

typedef struct {
  int brake[8];
  int brake205[8];
  int brake103[4];
  int neutral;
  int power[5];
  int power103[4];
} notch;

const notch MasconStickVals{
  {100,80,70,60,40,35,20,0},
  {160,175,185,195,215,225,235,255},
  {163,185,230,255},
  128,
  {163,179,204,230,255},
  {80,60,30,0}
}; 

void setup(){
  SwitchControlLibrary();
  
  SwitchControlLibrary().pressButton(Button::R);
  SwitchControlLibrary().sendReport();
  delay(50);
  SwitchControlLibrary().releaseButton(Button::R);
  SwitchControlLibrary().sendReport();
  delay(500);
  SwitchControlLibrary().pressButton(Button::L);
  SwitchControlLibrary().sendReport();
  delay(50);
  SwitchControlLibrary().releaseButton(Button::L);
  SwitchControlLibrary().sendReport();
  delay(500);
  SwitchControlLibrary().pressButton(Button::R);
  SwitchControlLibrary().sendReport();
  delay(50);
  SwitchControlLibrary().releaseButton(Button::R);
  SwitchControlLibrary().sendReport();
  delay(500);
    
  Psx.setupPins(DataPin, CmndPin, AttPin, ClockPin, 10);  
  pinMode(StickSwPin,INPUT_PULLUP);
}

void loop(){ 
  PsRead = Psx.read();
  
  static bool btnAPressed = false;

  if(PsRead & psxO){
    if(!btnAPressed){
      SwitchControlLibrary().pressButton(Button::A);
      SwitchControlLibrary().sendReport();
      btnAPressed = true;
    }
  }else{
    if(btnAPressed){
      SwitchControlLibrary().releaseButton(Button::A);
      SwitchControlLibrary().sendReport();
      btnAPressed = false;
    }
  }

  static bool btnBPressed = false;
  
  if(PsRead & psxX){
    if(!btnBPressed){
      SwitchControlLibrary().pressButton(Button::B);
      SwitchControlLibrary().sendReport();
      btnBPressed = true;
    }
  }else{
    if(btnBPressed){
      SwitchControlLibrary().releaseButton(Button::B);
      SwitchControlLibrary().sendReport();
      btnBPressed = false;
    }
  }
 
  static bool btnXPressed = false;
  
  if(PsRead & psxSlct){
    if(!btnXPressed){
      SwitchControlLibrary().pressButton(Button::X);
      SwitchControlLibrary().sendReport();
      btnXPressed = true;
    }
  }else{
    if(btnXPressed){
      SwitchControlLibrary().releaseButton(Button::X);
      SwitchControlLibrary().sendReport();
      btnXPressed = false;
    }
  }
 
  static bool btnYPressed = false;
  
  if(PsRead & psxSqu){
    if(!btnYPressed){
      SwitchControlLibrary().pressButton(Button::Y);
      SwitchControlLibrary().sendReport();
      btnYPressed = true;
    }
  }else{
    if(btnYPressed){
      SwitchControlLibrary().releaseButton(Button::Y);
      SwitchControlLibrary().sendReport();
      btnYPressed = false;
    }
  }
  
  static bool btnCapturePressed = false;
  static uint32_t btnJoyPressedAt = 0;
  int btnJoyPressCount = 0;
   
  while(digitalRead(StickSwPin) == LOW){
    btnJoyPressCount++;

    if(btnJoyPressCount > 100){
      if(btnJoyPressedAt == 0){
        btnJoyPressedAt = millis();
      }else{
        if(!btnCapturePressed && millis() - btnJoyPressedAt >= 1000){
          SwitchControlLibrary().pressButton(Button::CAPTURE);
          SwitchControlLibrary().sendReport();
          delay(100);
          SwitchControlLibrary().releaseButton(Button::CAPTURE);
          SwitchControlLibrary().sendReport();
          btnCapturePressed = true;
        }
      }
      break;
    }
  }
  
  if(digitalRead(StickSwPin) == HIGH){
    if(!btnCapturePressed && btnJoyPressedAt != 0 && millis() - btnJoyPressedAt < 1000){
      SwitchControlLibrary().pressButton(Button::HOME);
      SwitchControlLibrary().sendReport();
      delay(100);
      SwitchControlLibrary().releaseButton(Button::HOME);
      SwitchControlLibrary().sendReport();
    }
    btnJoyPressedAt = 0;
    btnCapturePressed = false;
  }

  static bool btnPlusPressed = false;
  
  if(PsRead & psxStrt){
    if(!btnPlusPressed){
      SwitchControlLibrary().pressButton(Button::PLUS);
      SwitchControlLibrary().sendReport();
      btnPlusPressed = true;
    }
  }else{
    if(btnPlusPressed){
      SwitchControlLibrary().releaseButton(Button::PLUS);
      SwitchControlLibrary().sendReport();
      btnPlusPressed = false;
    }
  }

  int readStickX = analogRead(StickXPin);
  int readStickY = analogRead(StickYPin);
  static bool btnRPressed = false;
  static bool btnLPressed = false;
  
  if(PsRead & psxSqu){
    
    if(readStickX < 100 ){
      if(!btnRPressed){
        SwitchControlLibrary().pressButton(Button::R); 
        SwitchControlLibrary().sendReport(); 
        btnRPressed = true;
      }
    }else{
      if(btnRPressed){
        SwitchControlLibrary().releaseButton(Button::R);
        SwitchControlLibrary().sendReport(); 
        btnRPressed = false;
      }
    }
    
    if(readStickX > 924){
      if(!btnLPressed){
        SwitchControlLibrary().pressButton(Button::L); 
        SwitchControlLibrary().sendReport(); 
        btnLPressed = true;
      }
    }else{
      if(btnLPressed){
        SwitchControlLibrary().releaseButton(Button::L);
        SwitchControlLibrary().sendReport(); 
        btnLPressed = false;
      }
    }
  }else{
    if(btnRPressed){
      SwitchControlLibrary().releaseButton(Button::R);
      SwitchControlLibrary().sendReport(); 
      btnRPressed = false;
    }
    
    if(btnLPressed){
      SwitchControlLibrary().releaseButton(Button::L);
      SwitchControlLibrary().sendReport(); 
      btnLPressed = false;
    } 
 
    static bool btnRightPressed = false;
  
    if(readStickX < 100 ){
      if(!btnRightPressed){
        SwitchControlLibrary().pressHatButton(Hat::RIGHT);
        SwitchControlLibrary().sendReport(); 
        btnRightPressed = true;
      }
    }else{
      if(btnRightPressed){
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport(); 
        btnRightPressed = false;
      }
    }

    static bool btnLeftPressed = false; 
    
    if(readStickX > 924 ){
      if(!btnLeftPressed){
        SwitchControlLibrary().pressHatButton(Hat::LEFT);
        SwitchControlLibrary().sendReport(); 
        btnLeftPressed = true;
      }
    }else{
      if(btnLeftPressed){
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport(); 
        btnLeftPressed = false;
      }
    }

    static bool btnUpPressed = false;

  
    if(readStickY < 100 ){
      if(!btnUpPressed){
        SwitchControlLibrary().pressHatButton(Hat::UP);
        SwitchControlLibrary().sendReport(); 
        btnUpPressed = true;
      }
    }else{
      if(btnUpPressed){
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport(); 
        btnUpPressed = false;
      }
    }

    static bool btnDownPressed = false;
    
    if(readStickY > 924 ){
      if(!btnDownPressed){
        SwitchControlLibrary().pressHatButton(Hat::DOWN);
        SwitchControlLibrary().sendReport(); 
        btnDownPressed = true;
      }
    }else{
      if(btnDownPressed){
        SwitchControlLibrary().releaseHatButton();
        SwitchControlLibrary().sendReport(); 
        btnDownPressed = false;
      }
    }

  }
  
  int lStickX;
  int lStickY;
  int rStickX;
  const int rStickY = MasconStickVals.neutral;
 
  int masconPower = getPower();
  int masconBrake = getBrake();

  if(masconBrake == 9){  
    SwitchControlLibrary().pressButton(Button::ZL);
    SwitchControlLibrary().sendReport(); 

    lStickX = MasconStickVals.neutral;
    
    if(Mode103){
      lStickY = MasconStickVals.neutral;
    }else{
      lStickY = MasconStickVals.brake[7];
    }
    rStickX = MasconStickVals.brake205[7];  
  }else if(masconBrake > 0){
    SwitchControlLibrary().releaseButton(Button::ZL);
    SwitchControlLibrary().sendReport();
    
    lStickX = MasconStickVals.neutral; 
    
    if(Mode103){
      if(masconBrake > 4){
        masconBrake = 4;
      }
      
      lStickY = MasconStickVals.neutral;
      rStickX = MasconStickVals.brake103[masconBrake - 1];
    }else{
      lStickY = MasconStickVals.brake[masconBrake - 1];
      rStickX = MasconStickVals.brake205[masconBrake - 1];   
    }
  }else if(masconPower == 0){
    SwitchControlLibrary().releaseButton(Button::ZL);
    SwitchControlLibrary().sendReport();
    rStickX = MasconStickVals.neutral;
    lStickX = MasconStickVals.neutral;
    lStickY = MasconStickVals.neutral; 
  }else{
    SwitchControlLibrary().releaseButton(Button::ZL);
    SwitchControlLibrary().sendReport();
    rStickX = MasconStickVals.neutral;
    
    if(Mode103){
      if(masconPower > 4){
        masconPower = 4;
      }
      lStickX = MasconStickVals.power103[masconPower - 1];
      lStickY = MasconStickVals.neutral;
      
    }else{
      lStickX = MasconStickVals.neutral;
      lStickY = MasconStickVals.power[masconPower - 1];
    }
  }
  
  SwitchControlLibrary().moveLeftStick(lStickX, lStickY);
  SwitchControlLibrary().sendReport(); 

  SwitchControlLibrary().moveRightStick(rStickX, rStickY);
  SwitchControlLibrary().sendReport(); 

  unsigned int readStart = PsRead & psxStrt; 
  unsigned int readSelect = PsRead & psxSlct; 
  
  if(readStart && readSelect){
    if(masconBrake == 9){
      Mode103 = true;
    }else{
      Mode103 = false;
    }
  }
} 

int getPower(){
  static int powerPosition;

  unsigned int readRight = PsRead & psxRight;
  unsigned int readLeft = PsRead & psxLeft;
  unsigned int readTri = PsRead & psxTri; 
   
  if(readRight && readLeft && !readTri){
    powerPosition = 0;
  }else if(readRight && !readLeft && readTri){
    powerPosition = 1;
  }else if(readRight && !readLeft && !readTri){
    powerPosition = 2;
  }else if(!readRight && readLeft && readTri){
    powerPosition = 3;
  }else if(!readRight && readLeft && !readTri){
    powerPosition = 4;
  }else if(!readRight && !readLeft && readTri){
    powerPosition = 5;
  } 

  return powerPosition;
}

int getBrake(){
  static int brakePosition; 
  unsigned int readR1= PsRead & psxR1;
  unsigned int readR2 = PsRead & psxR2;
  unsigned int readL1 = PsRead & psxL1;
  unsigned int readL2 = PsRead & psxL2; 
  
  if(!readL1 && readL2 && readR1 && readR2){
    brakePosition = 0;
  }else if(readL1 && !readL2 && readR1 && readR2){
    brakePosition = 1;
  }else if(!readL1 && !readL2 && readR1 && readR2){
    brakePosition = 2;
  }else if(readL1 && readL2 && !readR1 && readR2){
    brakePosition = 3;
  }else if(!readL1 && readL2 && !readR1 && readR2){
    brakePosition = 4;
  }else if(readL1 && !readL2 && !readR1 && readR2){
    brakePosition = 5;
  }else if(!readL1 && !readL2 && !readR1 && readR2){
    brakePosition = 6;
  }else if(readL1 && readL2 && readR1 && !readR2){
    brakePosition = 7;
  }else if(!readL1 && readL2 && readR1 && !readR2){
    brakePosition = 8;
  }else if(!readL1 && !readL2 && !readR1 && !readR2){
    brakePosition = 9;
  }
  
  return brakePosition;
}
