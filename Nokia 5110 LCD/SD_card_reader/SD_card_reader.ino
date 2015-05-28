/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

File myFile;

char tempchar[4]={0};
char scena[504]={0};
char podatak1, podatak2;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(53, OUTPUT);


  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("Scena.txt", FILE_WRITE);

 
  // re-open the file for reading:
  myFile = SD.open("Scena.txt");
  if (myFile) {
    Serial.println("Scena.txt:");

    // read from the file until there's nothing else in it:
    for (int i=0; i<=3; i++){
      Serial.write((tempchar[i]=myFile.read()));
    // close the file:
    }
    podatak1=tempchar[2];
    podatak1 =podatak1<<4;
    podatak1 &=0xF0;
    podatak2 = tempchar[3];
    podatak2 &=0x0F;
    podatak1 |= podatak2;    
    myFile.close();
    Serial.println();
    Serial.print(podatak1, BIN);
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}


