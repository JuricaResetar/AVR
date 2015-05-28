#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <UTouch.h>
#include <avr/pgmspace.h>

volatile int triggered=0;
volatile long seconds=0;
volatile boolean pressed = false;
volatile int x,y;
boolean firstTime = true;

//BachGround color: 102,178,255
// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern unsigned int UpArrow[0x9C4];
//extern unsigned int Smajlek[0x1000];
//extern unsigned int Button[0x258];
UTFT myGLCD(ITDB32S,38,39,40,41);
UTouch  myTouch(48, 8, 4, 3, 6);  //Treba maknuti ovaj zadnji (izvaditi žicu) IRQ argument jer sam ga ja spojio na IRPin od Arduina
//myTouch(DCLK,CS,IN,OUT,IRQ)
File myFile;

boolean isTurnedOn [8] = {false, false, false, false, false, false, false, false};
boolean isActive [8][4] = {true, false, false, false, true, false, false, false, true, false, false, false, true, false, false, false, true, false, false, false, true, false, false, false,
true, false, false, false, true, false, false, false};
unsigned short podaciPaljenja [8][16]={10,22,33,44};
int interruptCounter [8] = {0};
int buttonCoordinates [32]={};
int bCFR [2] = {120, 172};  //buttonCordinatesFirstRow    yStart, yEnd
int bCSR [2] = {180, 232}; //yStart, yEnd
int distanceBButtons [2] = {20,10};  //Distance Beetween Buttons: (xDistace, yDistance)
int buttonSize = 52; //buttonSize
int colomns=4, rows = 4;
int time [6] = {8,5,2016,2,3,2}; //Time variable (month, day, year,hours,minutes, seconds)
int timeX=20, timeY=20;
int sensorTemp[2] = {27,29}; 
String tempMeni = "none";
int circleX=210, circleY=13, circleRadius=7;

boolean readStatus (int zone){
  /*
  * This function will return status from zone "zone"
  */
  return isTurnedOn[zone];
  }
  
int saveStatus (int zone, boolean state){
  /*
  * This function will update status of zone "zone" 
  */
 isTurnedOn[zone] = state;
}  




ISR(ANALOG_COMP_vect){
  interruptRoutine();     
}

void interruptRoutine (){
  noInterrupts();
  triggered++;
  if (triggered>2) return;
  if (triggered==1){       
    pressed=true;      
    interrupts();  
    seconds=millis();
    }
  else if (triggered==2){
    pressed=true;
    noInterrupts();  //Prekidi ce se omoguciti kada se obavi gasenje
    }
  }

void setup() {

  ADCSRB = 0x00;           // (Disable) ACME: Analog Comparator Multiplexer Enable
  ACSR =  0b01001000;
  
  myGLCD.InitLCD();
  myGLCD.clrScr();
  Serial.begin(9600);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);  
  myGLCD.setFont(BigFont);
  pinMode(53, OUTPUT);
  
  /*
  Code below (just few lines) is for analog comparator initialization 
  */
  //if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    //return;
  //}
  //Serial.println("initialization done.");

  //SPI.begin();
  //myFile = SD.open("Scena.txt");
  myGLCD.fillScr(102,178,255); 
}


  
void loop() {
int x,y,i=0, pressDuration;
int tempZone;

while (1){
  if (triggered==1){

    Serial.println("I'm reading");
    if (myTouch.dataAvailable()==true && firstTime==true){
     /*
    * In this moment, TS is pressed. So, read now but ONLY ONCE (using firstTime flag)!
    */
      firstTime=false;
      
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      Serial.print(x);
      Serial.print ("   ");
      Serial.println(y);      
      }        
      delay (300);    //Software debbouncing
    }
  else if (triggered>=2){
    
      pressDuration=((millis()-seconds));
      Serial.print("Duration: ");
      Serial.println (pressDuration);     
     
      if (tempMeni == "none"){
        drawButtons(colomns,rows);
        tempMeni = "normalMode";
        drawTime(100, 30, -1);
      }
      else if (tempMeni == "normalMode"){
        if (zonePressed(x,y)!=-1){
          if (pressDuration<500){    //Enter zone meni
           zoneMenu (zonePressed(x,y));
           tempZone = zonePressed(x,y);
           changeColorDigit (zonePressed(x,y), 'Y');   
           updateColorRec (zonePressed(x,y));            
           drawReturnButton();
           drawDurationButton();   
           drawDots(tempZone);           
           tempMeni= "zone";
          }
          else if (pressDuration>=500){
           changeColorRec (zonePressed(x,y));
            }
        }
      }
    else if (tempMeni == "zone"){
           if (x>280 && x<320 && y>0 && y<40){
             changeColorDigit (tempZone, 'B');   
             updateColorRec (tempZone);
             drawTime(100,30,-1);
             tempMeni="normalMode";  //Ako je kliknuto na "return" button
            }
           else {
             incRazdoblja (tempZone, digitPressed (x,y));
             //Odvje dolje im predajem bzvz koordinate! Treba imati varijablu temp Zona koja pamti koja se zona odabrala u "zone" meniju
             //zoneMenu (tempZone);  
             //Trebalo bi promjeniti boju tek kada se klikne na neku oznakicu sa strane za spremanje postavki                     changeColorDigit (tempZone);             
             tempMeni = "zone";
           }
     }
    
    firstTime=true; 
    triggered=0;
    pressed=false;
    delay (300);    //Software debbouncing    
    interrupts();    
  }
 }      
}

