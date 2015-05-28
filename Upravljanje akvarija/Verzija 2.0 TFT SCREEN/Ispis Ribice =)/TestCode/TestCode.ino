#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <avr/pgmspace.h>


// Declare which fonts we will be using
extern uint8_t BigFont[];
//extern unsigned int Riba[0x1C84];
extern unsigned int Riba [0x1C84];
UTFT myGLCD(ITDB32S,38,39,40,41);
File myFile;

void setup() {
  myGLCD.InitLCD();


  Serial.begin(9600);
  pinMode(53, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  SPI.begin();
  myFile = SD.open("Scena.txt");
}

  String naziv="Mirkec";
  char *znakic;
  
void loop() {
  myGLCD.setFont(BigFont);
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 399, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, 399, 239);
  myGLCD.setColor(255, 255, 255);
  //myGLCD.setBackColor(255, 0, 0);
  /*
  for (int i=0; i<4; i++){
    //naziv = myFile.read();
    *znakic = 'b';
    Serial.println("Slijedi znak");
    Serial.print(znakic);
    myGLCD.printNumI(myFile.read(), CENTER, (i*50));
    }
    */
   myGLCD.drawBitmap (55, 55, 100, 73, Riba);
  while (1){
  };

}
