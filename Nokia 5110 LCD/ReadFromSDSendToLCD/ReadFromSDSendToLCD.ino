#include <SPI.h>
#include <SD.h>

#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

#define LCD_C     LOW  //Data
#define LCD_D     HIGH  //Command

#define LCD_X     84
#define LCD_Y     48

File myFile;

char tempchar[4] = {0};
char scena[504] = {0};
unsigned char podatak1, podatak2;
byte data;

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);    //All characters blank
  }
  delay (2);
  LcdWrite(LCD_C, 0x22);  // LCD Basic Commands. (0x20 ili 0x22)
  LcdWrite(LCD_C, 0x40);    //Y address set to 0
  LcdWrite(LCD_C, 0x80);    //X address set to 0
  LcdWrite(LCD_C, 0x0D);    //Back to Normal (0x0C) or VideoInverted (0x0D) mode
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xA5 );  // Set LCD Vop (Contrast).
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x14
  LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  SPI.transfer(data);
  //  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(53, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  SPI.begin();
  LcdInitialise();
  LcdClear();
  myFile = SD.open("Scena.txt");

}
int k = 0, i=0;
byte mask=1;
void loop() {

for (k; k<500; k++){
    for (i=0; i < 504; i++) {
        mask=1;
        podatak2=0;
          for (int j = 0; j < 8; j++) {
            podatak1 = myFile.read();
            if (podatak1=='A') podatak1=0;
            else if (podatak1=='B') podatak1=1;
            podatak1=podatak1<<(0+j);  //Ovdje bit ode na svoje mjesto         
            podatak2 |=podatak1;           
    }
      LcdWrite(LCD_D, podatak2);
  }
  delay (10);
  }
  myFile.close();  
}
