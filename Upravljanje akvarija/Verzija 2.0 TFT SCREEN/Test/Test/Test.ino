#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <UTouch.h>
#include <avr/pgmspace.h>


// Declare which fonts we will be using
extern uint8_t BigFont[];
//extern unsigned int Smajlek[0x1000];
//extern unsigned int Button[0x258];
UTFT myGLCD(ITDB32S,38,39,40,41);
UTouch  myTouch(6, 5, 7, 3, 8);
File myFile;

int bCFR [2] = {120, 170};  //buttonCordinatesFirstRow    yStart, yEnd
int bCSR [2] = {180, 230}; //yStart, yEnd
int distanceBButtons [2] = {20,10};  //Distance Beetween Buttons: (xDistace, yDistance)
int buttonSize = 50; //buttonSize
int zoneStatus [8] = {0,0,0,0,0,0,0,0};
int colomns=4, rows = 4;
int interruptCounter =0;  //I'll count interrupts to avoid bouncing


void changeColor (int x, int y){
  /*
  * This function will change state (color) of button on cordinates (x,y)
  * First we need to find out which button is pressed
  */
 
 /*
  if (interruptCounter != 0){
  interruptCounter ++;
  if (interruptCounter>250) interruptCounter=0;
  return;
  }
  */
  /*
  while (1){
      myTouch.read();
      int tempX=myTouch.getX();
      if (tempX > (x+buttonSize/2) && tempX < (x+buttonSize/2)) return;    //If I still push the same button
    }
  */
  int pressed=-1;
  if (y>bCFR[0] && y<bCFR[1]){
  for (int i=0; i<colomns; i++){
        if (x>(distanceBButtons[0]+(i*(distanceBButtons[0]+ buttonSize))) && x < (distanceBButtons[0]+ buttonSize+ (i*(distanceBButtons[0]+ buttonSize)))){
          pressed = i;
          break;
          }
     }
    }
   else if (y>bCSR[0] && y<bCSR[1]){
       for (int i=0; i<colomns; i++){
        if (x>(distanceBButtons[0]+(i*(distanceBButtons[0]+ buttonSize))) && x < (distanceBButtons[0]+ buttonSize+ (i*(distanceBButtons[0]+ buttonSize)))){
          pressed = i+colomns;
          break;
          }
     }
   }  
   Serial.println(pressed);
   Serial.print (x);
   Serial.print ("   ");
   Serial.println(y);      
    
    if (pressed != -1){
      if (readStatus(pressed)){   //If turned ON
        myGLCD.setColor(255, 0, 0);
        saveStatus(pressed, 0);
      }
      else {  //If turned OFF
        myGLCD.setColor(0, 255, 0);
        saveStatus(pressed, 1);      
        }
      if (y>bCFR[0] && y<bCFR[1]){
        myGLCD.fillRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+ buttonSize+ (pressed*(distanceBButtons[0]+ buttonSize)), bCFR[1]);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCFR[1]);
        }
      else if (y>bCSR[0] && y<bCSR[1]){
        myGLCD.fillRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+ buttonSize+ ((pressed-colomns)*(distanceBButtons[0]+ buttonSize)), bCSR[1]);
        myGLCD.setColor(255, 255, 255);      
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCSR[1]);
        }
    }
  }

int readStatus (int zone){
  /*
  * This function will return status od zone "zone"
  */
  return zoneStatus[zone];
  }
  
int saveStatus (int zone, int state){
  /*
  * This function will update status of zone "zone" 
  */
 zoneStatus[zone] = state;
}  
void drawButtons(int colomns, int rows){
  
// Draw the upper row of buttons
  for (int x=0; x<colomns; x++)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRoundRect (distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+ buttonSize+ (x*(distanceBButtons[0]+ buttonSize)), bCFR[1]);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCFR[1]);
  //  myGLCD.printNumI(x+1, 27+(x*60), 135);
  }
// Draw the center row of buttons
  for (int y=0; y<rows; y++)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRoundRect (distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+ buttonSize+ (y*(distanceBButtons[0]+ buttonSize)), bCSR[1]);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCSR[1]);
    //myGLCD.printNumI(y+1, 27+(y*60), 135);
//    if (x<4)      myGLCD.printNumI(y+6, 27+(x*60), 200);
  }
 
}

void interruptRoutine(){
      myTouch.read();
      int x=myTouch.getX();
      int y=myTouch.getY();
      Serial.print (x);
      Serial.print ("   ");
      Serial.println (y);
  if (x>200 && y<60) drawButtons(colomns,rows);
  else{
   changeColor (x,y);
    }
  }

void setup() {
  attachInterrupt(0, interruptRoutine, LOW);    //Najbolje staviti da se okida na LOW
  myGLCD.InitLCD();
  myGLCD.clrScr();
  Serial.begin(9600);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);  
    myGLCD.setFont(BigFont);
  pinMode(53, OUTPUT);
  //if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    //return;
  //}
  //Serial.println("initialization done.");

  //SPI.begin();
  //myFile = SD.open("Scena.txt");
  //drawButtons();
}


  
void loop() {
int x,y;
//drawButtons(colomns,rows);
while (1){
  }
       
}

