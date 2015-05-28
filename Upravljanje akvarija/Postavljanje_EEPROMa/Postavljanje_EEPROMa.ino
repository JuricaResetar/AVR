/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
int inic=1;

void setup()
{
}




void loop(){
  
if (inic==1){

for (int i=0; i<=255; i++){  //Postavi sve EEPROMe u 0
    EEPROM.write(i, 0);
    delay (4);
}
//Ovdje treba postaviti ON/OFF eeprom lokacije u 1
      for (int i=0; i<=64; i++){
      EEPROM.write (144+i, 1);
      delay (4);
      }
//Ovdje treba postaviti prve eeprom lokacije u 1
      for (int i=1; i<=8; i++){
      EEPROM.write (i, 1);
      delay (4);
      }      
inic++;
}}
