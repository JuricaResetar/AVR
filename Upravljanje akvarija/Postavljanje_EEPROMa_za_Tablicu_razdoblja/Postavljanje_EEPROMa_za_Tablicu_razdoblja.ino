#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
int inic=1;
int zona=1, razdoblje=1;
void setup()
{
  zona=1;
  razdoblje=1;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 00);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 00);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 40);   //Gasenje minuta  
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);  
  zona=1;
  razdoblje=4;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 23);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);  
  zona=2;
  razdoblje=2;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 23);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);  
  zona=2;
  razdoblje=3;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 9);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 15);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);    
  zona=3;
  razdoblje=1;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 23);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 0);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 2);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta   
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);

  zona=3;
  razdoblje=3;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 22);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);  
  zona=4;
  razdoblje=4;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 05);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 21);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=5;
  razdoblje=1;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 14);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 14);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 30);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=5;
  razdoblje=2;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 15);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 15);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 30);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=5;
  razdoblje=4;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 0);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 15);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=6;
  razdoblje=2;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 20);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 00);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 19);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=7;
  razdoblje=1;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 15);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 23);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 20);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=7;
  razdoblje=3;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 7);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 20);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 16);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=8;
  razdoblje=2;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 21);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 35);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 23);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 40);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  zona=8;
  razdoblje=4;
  EEPROM.write ((16*zona + (razdoblje-1)*4), 7);   //Paljenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+1), 20);   //Paljenje minuta   
  EEPROM.write ((16*zona + (razdoblje-1)*4+2), 7);   //Gasenje sat 
  EEPROM.write ((16*zona + (razdoblje-1)*4+3), 00);   //Gasenje minuta    
  EEPROM.write ((144 + (zona-1)*8 + (razdoblje-1)),0);
  
}  

void loop(){
}
