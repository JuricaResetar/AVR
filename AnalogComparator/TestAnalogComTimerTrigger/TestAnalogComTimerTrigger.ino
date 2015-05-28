#include <UTFT.h>
#include <UTouch.h>
#include <avr/pgmspace.h>

volatile int triggered=0;
volatile long seconds=0;
volatile int x,y;
boolean firstTime=true;

UTFT myGLCD(ITDB32S,38,39,40,41);
UTouch  myTouch(48, 8, 4, 3, 6);  //Treba maknuti ovaj zadnji (izvaditi žicu) IRQ argument jer sam ga ja spojio na IRPin od Arduina
/*
Ovo je program za testiranje unutarnjeg komparatora na AtMega2560
Interrupt signal se treba dovesti na Arduino DP5 (AIN1). 

Prekidi se okidaju na promjenu brida. Kada se dogodi padajući brid (stisak ekrana) pokrene se brojilo T1
Zatim se prilikom drugog prekida (rastući brid) provjerava stanje brojila

Program koristi Arduino funkciju millis (time je izbjegnuta silna konfiguracija timera koje se pokrece na 
okidanje comparatora) :
Returns the number of milliseconds since the Arduino board began running the current program. 
This number will overflow (go back to zero), after approximately 50 days.

*/


ISR (ANALOG_COMP_vect){
  interruptRoutine();
  }


void interruptRoutine (){
  ACSR =  0b01010000;     
  triggered++;       
  if (triggered==1){
    seconds=millis();    
    }
  Serial.println();  
  Serial.print ("triggered: ");
  Serial.println (triggered);    
  }

void setup (){
  Serial.begin (9600);
  Serial.println ("Started.");
  ADCSRB = 0x00;           // (Disable) ACME: Analog Comparator Multiplexer Enable
  ACSR =  0b01001000;      
  myGLCD.InitLCD();
  myGLCD.clrScr();
  Serial.begin(9600);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);  
  pinMode(53, OUTPUT);  
}



void loop (){

 
  if (triggered==1){
    Serial.println ("Usao u 1");  
    if (myTouch.dataAvailable()==true && firstTime==true){
     /*
    * In this moment, TS is pressed. So, read now!
    */
      firstTime=false;
      
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      Serial.print(x);
      Serial.print ("   ");
      Serial.println(y);       
      }
      delay (50);       
  ACSR =  0b01011000;       
    }  
  else if (triggered==2){    
    Serial.println ("Turned off"); 
    Serial.print("Duration: ");
    Serial.println (millis()-seconds);
    triggered=0;
    firstTime=true;
    delay (50);
  ACSR =  0b01011000;      
    }
  else if(triggered>2){
    Serial.println ("Usao u 3!");    
    triggered=0;
    firstTime=true; 
    delay (50);
  ACSR =  0b01011000;         
    }
  }  // end of loop
