#include <Wire.h>
#define DS1307_I2C_ADDRESS 0x68
#include <LiquidCrystal.h> 
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);  //Inicijalizacija LCDa

/*
Izgleda EEPROM memorije:
 Adresa                                Podatak
 EEPROM lokacije počinju na 1, tamo spremam stanja izlaza
 (16*zona + (razdoblje-1)*4 +i         Sadrzi: PaljenjeSat, PaljenjeMinuta, GasenjeSat; GasenjeMinuta
 144 + (zona-1)*8 + (razdoblje-1)      ==1 ako je razdoblje =OFF ili ==0 ako je to razdoblje ON, tj. aktivno
 180+zona                                Stanje brojaca potrosnje
 
 
 SVE SE ZONE PALI U NEGATIVNOJ LOGICI!
 
 
 
 
 
 LCD zona ---> Arduino zona:
 1-GND
 2-VCC
 3-10k potenciometar
 4 (RS)-DP (12)
 5 (RW)-GND
 6 (E)- DP (11)
 D7 (14)- DP(5)
 D6 (13)-DP(4)
 D5 (12)-DP(3)
 D4 (11)-DP(2)
 Wanna backlight??
 Spoji:
 15-5V
 16-GND!
 
 SCL:analog 5    
 SDA:analog 4  
 |->I2C bus za Duemilanove
 */
/*
 Upute za koristenje RTCa:
 Deklarirati varijable javno: 
 byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
 
 Ako neka funcija treba podatke od RTCa, pozvati ih ovako:
 getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
 
 Funckija getDateDs1307 i potrebne funkcije za rad s RTC:
 
 -> byte decToBcd(byte val){
 return ( (val/10*16) + (val%10) );
 }
 
 -> byte bcdToDec(byte val){
 return ( (val/16*10) + (val%16) );
 }
 
 */

/*
 -> void setDateDs1307(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
 Wire.beginTransmission(DS1307_I2C_ADDRESS);
 Wire.write(0);
 Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
 Wire.write(decToBcd(minute));
 Wire.write(decToBcd(hour));
 Wire.write(decToBcd(dayOfWeek));
 Wire.write(decToBcd(dayOfMonth));
 Wire.write(decToBcd(month));
 Wire.write(decToBcd(year));
 Wire.write(0x10); // sends 0x10 (hex) 00010000 (binary) to control register - turns on square wave
 Wire.endTransmission();
 }
 
 ->Dunkcija za dobivanje podataka od RTCa:
 
 void getDateDs1307(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month,byte *year){
 // Reset the register pointer
 Wire.beginTransmission(DS1307_I2C_ADDRESS);
 Wire.write(0);
 Wire.endTransmission();
 Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 // A few of these need masks because certain bits are control bits
 *second = bcdToDec(Wire.read() & 0x7f);
 *minute = bcdToDec(Wire.read());
 *hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
 *dayOfWeek = bcdToDec(Wire.read());
 *dayOfMonth = bcdToDec(Wire.read());
 *month = bcdToDec(Wire.read());
 *year = bcdToDec(Wire.read());
 }
 
 */

//Deklaracija globalnih varijabli:

short zona[9]={                      //Polje podataka koje predstavlja digitalne pinove
  0,0,1,6,7,8,9,10,13 
};
int temp[9]={
  0};
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte stupanj[8] = {
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000
};
byte prazno[8] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111
};
byte puno[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte donja[8] = {
  B00000,
  B00000,  
  B00100,
  B01010,
  B11111,
  B00100,
  B00100,
  B00100
};

byte gornja[8] = {
  B00100,
  B00100,
  B00100,
  B11111,
  B01010,
  B00100,
  B00000,
  B00000  
};



byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

void setDateDs1307(byte second, byte minute,byte hour, byte dayOfWeek, byte dayOfMonth,byte month,byte year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(0x10); // sends 0x10 (hex) 00010000 (binary) to control register - turns on square wave
  Wire.endTransmission();
}
// Gets the date and time from the ds1307
void getDateDs1307(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  // A few of these need masks because certain bits are control bits
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}



void setup(){
  pinMode (zona[1],OUTPUT);
  pinMode (zona[2],OUTPUT);
  pinMode (zona[3],OUTPUT);
  pinMode (zona[4],OUTPUT);
  pinMode (zona[5],OUTPUT);
  pinMode (zona[6],OUTPUT);
  pinMode (zona[7],OUTPUT);
  pinMode (zona[8],OUTPUT);
  lcd.createChar(2, prazno);  
  lcd.createChar(3, puno);
  lcd.createChar(4, stupanj);  
  lcd.createChar(5, donja);  
  lcd.createChar(6, gornja);    
  lcd.begin(16, 2);  
  Wire.begin();
}

void statusscreen (){

  /* Prikazuje stanje pojedinih zona.
   Prikaze broj zone koja je upaljena, odnosno space ukoliko je zona ugasena
   */
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  lcd.clear(); // clear LCD screen
  lcd.setCursor(0,0);
  if (hour<10)  lcd.print("0");  
  lcd.print(hour, DEC);
  lcd.print(":");
  if (minute<10)  lcd.print("0");

  lcd.print(minute, DEC);
  lcd.print(" ");

  switch(dayOfWeek){
  case 1:
    lcd.print("Pon");
    break;
  case 2:
    lcd.print("Uto");
    break;
  case 3:
    lcd.print("Sri");
    break;
  case 4:
    lcd.print("Cet");
    break;
  case 5:
    lcd.print("Pet");
    break;
  case 6:
    lcd.print("Sub");
    break;
  case 7:
    lcd.print("Ned");
    break;
  }
  lcd.print(" ");
  if (dayOfMonth<10)  lcd.print("0"); 
  lcd.print(dayOfMonth, DEC);
  lcd.print(".");
  if (month<10)  lcd.print("0");   
  lcd.print(month, DEC);
  lcd.print(".");

  lcd.setCursor(0,1);
  for (int i=1; i<=8; i++){
    if (digitalRead(zona[i])==LOW) lcd.print (i); 
    else lcd.write(" "); 
    lcd.print(" ");
  }
}


int IspitajUlaz(){
  /*Ispituje stanja analognih ulaza te u ovisnosti o kombijaciji vraca vrijednosti:
   0- nista nije stisnuto
   1- aktivan je AnalogInput (1)
   2- aktivan je AnalogInput (2)
   3- aktivan je AnalogInput (3)
   */
  delay (1000);
  if (analogRead(1)>100 && analogRead(3)<100) return 1;         //Desni button (analogRead(1)
  if (analogRead(1)<100 && analogRead(3)>100) return 2;    //Lijevi button (analogRead(3)
  if (analogRead(1)>100 && analogRead(3)>100) return 3;


}

void NamjestanjeSata(){
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  int inic=1, brojac=1, time=0, konst=30000;

  while (inic){
    inic=0;
    lcd.clear(); // clear LCD screen
    lcd.setCursor(4,0);

    if (hour<10)  lcd.print("0");
    lcd.print(hour, DEC);
    lcd.print("<");

    if (minute<10)  lcd.print("0");
    lcd.print(minute, DEC);

    lcd.setCursor(11,0);
    switch(dayOfWeek){
    case 1:
      lcd.print("Pon");
      break;
    case 2:
      lcd.print("Uto");
      break;
    case 3:
      lcd.print("Sri");
      break;
    case 4:
      lcd.print("Cet");
      break;
    case 5:
      lcd.print("Pet");
      break;
    case 6:
      lcd.print("Sub");
      break;
    case 7:
      lcd.print("Ned");
      break;
    }

    lcd.setCursor(4,1);

    if (dayOfMonth<10)  lcd.print("0");
    lcd.print(dayOfMonth, DEC);
    lcd.print(".");
    if (month<10)  lcd.print("0");
    lcd.print(month, DEC);
    lcd.print(".'");
    if (year<10)  lcd.print("0");
    lcd.print(year,DEC);
    lcd.print(".");
  }

  delay (500);
  //Najmještanje sata počinje ovdje:
  while (1){
    if (time>konst) return;
    time++;     
    if (analogRead(1)>50){
      while (analogRead(1)>50){
        if (analogRead(3)>50){
          setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year); 
          return;
        }
      }
      time=0;
      brojac++;
      if (brojac>=7) brojac=1;

      switch (brojac){
      case 1:  
        {
          lcd.setCursor(13,1);
          lcd.print(".");          
          lcd.setCursor(6,0);
          lcd.print("<");
          break;
        }
      case 2:  
        {
          lcd.setCursor(6,0);
          lcd.print(":");
          lcd.setCursor(9,0);
          lcd.print("<");
          break;
        }
      case 3:  
        {
          lcd.setCursor(9,0);
          lcd.print(" ");
          lcd.setCursor(14,0);
          lcd.print("<");
          break;
        }
      case 4:  
        {
          lcd.setCursor(14,0);
          lcd.print(" ");
          lcd.setCursor(6,1);
          lcd.print("<");
          break;
        }
      case 5:  
        {
          lcd.setCursor(6,1);
          lcd.print(".");
          lcd.setCursor(9,1);
          lcd.print("<");
          break;
        }
      case 6:  
        {
          lcd.setCursor(9,1);
          lcd.print(".");          
          lcd.setCursor(13,1);
          lcd.print("<");
          break;
        }

      }
    }

    if (analogRead(3)>50){
      while (analogRead(3)>50){
      }
      time=0;

      switch (brojac){
      case 0:      //Slučaj kada se uđe odmah u switch!
        {
          hour++;    
          if (hour>23) hour =0;
          lcd.setCursor(4,0);
          if (hour<10)  lcd.print("0");
          lcd.print(hour, DEC);
          break;
        }
      case 1:      //Slučaj kada se uđe odmah u switch!
        {
          hour++;    
          if (hour>23) hour =0;
          lcd.setCursor(4,0);
          if (hour<10)  lcd.print("0");
          lcd.print(hour, DEC);
          break;
        }
      case 2:  
        {
          minute++;
          if (minute > 59) minute=0;    
          lcd.setCursor(7,0);
          if (minute<10)  lcd.print("0");
          lcd.print(minute, DEC);
          break;
        }
      case 3:  
        {

          dayOfWeek++;  
          if (dayOfWeek>7) dayOfWeek=1;
          lcd.setCursor(11,0);
          switch(dayOfWeek){
          case 1:
            lcd.print("Pon");
            break;
          case 2:
            lcd.print("Uto");
            break;
          case 3:
            lcd.print("Sri");
            break;
          case 4:
            lcd.print("Cet");
            break;
          case 5:
            lcd.print("Pet");
            break;
          case 6:
            lcd.print("Sub");
            break;
          case 7:
            lcd.print("Ned");
            break;
          }
          break;
        }
      case 4:  
        {
          dayOfMonth++; 
          if (dayOfMonth>31) dayOfMonth=1;    
          lcd.setCursor(4,1);
          if (dayOfMonth<10)  lcd.print("0");
          lcd.print(dayOfMonth, DEC);
          break;
        }
      case 5:  
        {
          month++; 
          if (month>12) month=1;   
          lcd.setCursor(7,1);
          if (month<10)  lcd.print("0");
          lcd.print(month, DEC);
          break;
        }
      case 6:  
        {
          year++;    
          if (year>25) year=13;
          lcd.setCursor(11,1);
          lcd.print(year, DEC);
          break;
        }
      }

    }
  }

}
void Programiranje (){        //POGLEDATI KAKO JE OVDJE RJEŠENA FUNKCIJA- NE TREBA INICIJALIZACIJA->ISPRAVITI OSTALE FCE
  /*Programiranje() se poziva iz funkcije Izbornik()
   Pokrece meni s:
   Razdoblja()
   NamjestanjeSata()    
   ResetBrojaca()   -reset brojaca koji mjeri aktivnost pojedine zone
   
   !Svaka gore navedena funkcija moja prije prvo pozvati RYSure()!
   
   */
  int time=0, konst=30000;
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Programiranje");
  lcd.setCursor(7,1);
  lcd.print("...");
  delay (1000);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Unos");
  lcd.setCursor(4,1);
  lcd.print("razdoblja");
  int brojac= 1;


  while (1){
    if (time>konst) return;
    time++; 
    if (analogRead(1)>100){
      while (analogRead(1)>100){
        if (analogRead(3)>100) return;
      }
      time=0;
      brojac++;
      if (brojac>2) brojac=1;


      switch (brojac){
      case 1: 
        {
          lcd.clear();
          lcd.setCursor(6,0);
          lcd.print("Unos");
          lcd.setCursor(4,1);
          lcd.print("razdoblja");
          break;
        }
      case 2: 
        {
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("Namjestanje");
          lcd.setCursor(6,1);
          lcd.print("sata");
          break;
        }
      }
    }
    if (analogRead(3)>100){
      while (analogRead(3)>100){
      }
      time=0;

      switch (brojac){
      case 1: 
        {
          lcd.clear();
          Unos();
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("Spremanje");
          lcd.setCursor(7,1);
          lcd.print("...");
          delay (500);
          lcd.clear();
          lcd.setCursor(6,0);
          lcd.print("Unos");
          lcd.setCursor(4,1);
          lcd.print("razdoblja");
          break;
        }
      case 2: 
        {
          /*      Uključiti ovaj kod ukoliko treba sigurnosno pitanje
           lcd.clear();
           lcd.print("Jesi Z?");
           lcd.setCursor(0,1);
           lcd.print("YES     NO");
           while (analogRead(1)<100 || analogRead(3)<100){
           if (analogRead(3)>100){  
           NamjestanjeSata();
           lcd.clear();
           lcd.print("Spremanje...");
           delay (2000);
           lcd.clear();
           lcd.print("Namjesteno");
           delay (2000);
           }
           if (analogRead(1)>100) break;
           }
           break;
           */
          NamjestanjeSata();
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("Spremanje");
          lcd.setCursor(7,1);
          lcd.print("...");
          break;
        }
      }
    }

  }
}



void Unos(){
  //Funkcija koristi OdabirZone() & OdabirRazdoblja() za odabiranje željenih razdoblja i zona
  int zona=OdabirZone();
  int razdoblje=OdabirRazdoblja(zona);
  int brojac=1,   temp=EEPROM.read(EEPROM.read(144 + (zona-1)*8 + (razdoblje-1)));      //Čita zbog prikaza je li Rn/Zn ON/OFF
  int time=0, konst=30000;


  int podaci[4]={
    0                                                                    };    //(16*zona + (razdoblje-1)*4 +i Sadrzi: PaljenjeSat, PaljenjeMinuta, GasenjeSat; GasenjeMinuta
  for (int i=0; i<=3; i++) podaci[i]=EEPROM.read(16*zona + (razdoblje-1)*4 +i);  //Dobivanje podataka 


  lcd.clear();
  lcd.print("Z");
  lcd.print(zona);
  lcd.print(" P:");
  lcd.setCursor(6,0);
  if(podaci[0]<10) lcd.print("0");
  lcd.print(podaci[0]);
  lcd.print("<");
  lcd.setCursor(9,0);
  if(podaci[1]<10) lcd.print("0");
  lcd.print(podaci[1]);


  lcd.setCursor(0,1);
  lcd.print("R");
  lcd.print(razdoblje);
  lcd.print(" G:");
  lcd.setCursor(6,1);
  if(podaci[2]<10) lcd.print("0");
  lcd.print(podaci[2]);
  lcd.print(":");
  lcd.setCursor(9,1);
  if(podaci[3]<10) lcd.print("0");
  lcd.print(podaci[3]);
  lcd.setCursor(13,0);
  if (EEPROM.read(144 + (zona-1)*8 + (razdoblje-1))==1) lcd.print("OFF");
  else lcd.print("ON");
  delay (500);

  while (1){
    if (time>konst) return;
    time++; 

    if (analogRead(3)>100){      //Button za inkrementaciju
      while (analogRead(3)>100){
      }
      time=0;
      switch (brojac){

      case 1:
        {
          podaci[brojac-1]++;
          if (podaci[brojac-1]>23) podaci[brojac-1]=0;
          lcd.setCursor (6,0);
          if(podaci[brojac-1]<10 && podaci[brojac-1]>=0) lcd.print("0");
          lcd.print(podaci[brojac-1]);
          break;
        }
      case 2:
        {
          podaci[brojac-1]+=5;
          if (podaci[brojac-1]>55) podaci[brojac-1]=0;
          lcd.setCursor (9,0);
          if(podaci[brojac-1]<10 && podaci[brojac-1]>=0) lcd.print("0");
          lcd.print(podaci[brojac-1]);
          break;
        }
      case 3:
        {
          podaci[brojac-1]++;
          if (podaci[brojac-1]>23) podaci[brojac-1]=0;
          lcd.setCursor (6,1);
          if(podaci[brojac-1]<10 && podaci[brojac-1]>=0) lcd.print("0");
          lcd.print(podaci[brojac-1]);
          break;
        }
      case 4:
        {
          podaci[brojac-1]+=5;
          if (podaci[brojac-1]>55) podaci[brojac-1]=0;
          lcd.setCursor (9,1);
          if(podaci[brojac-1]<10 && podaci[brojac-1]>=0) lcd.print("0");
          lcd.print(podaci[brojac-1]);
          break;
        }
      case 5:
        {

          if (temp && 1){
            lcd.setCursor(13,0);
            lcd.print("ON");
            lcd.setCursor(15,0);
            lcd.print(" ");
            temp=0;
            EEPROM.write(144 + (zona-1)*8 + (razdoblje-1), temp);
          }
          else{ 
            lcd.setCursor(13,0);
            lcd.print("OFF");
            temp=1;
            EEPROM.write(144 + (zona-1)*8 + (razdoblje-1), temp);
          }
          break;
        }
      }
    }

    if (analogRead(1)>100){      //Izlazak iz izbornika i spremanje podataka u EEPROM
      while (analogRead(1)>100) if (analogRead(3)>100){
        //Zapisivanje u EEPROM
        time=0;
        for (int i=0; i<=3; i++) EEPROM.write(16*zona + (razdoblje-1)*4 +i,  podaci[i]);  
        //EEPROM.write(zona-1, temp);        //Na zona-1 lokaciju upisuje je li neka zona ON/OFF                                      Je li ovo potrebno????? Zakomenturano u v8_0
        return;
      }

      brojac++;
      if (brojac>5) brojac=1;

      switch (brojac){      //Ovo se brine za pomak "^" pokazivača
      case 1:
        {
          lcd.setCursor (14,1);
          lcd.print(" ");
          lcd.setCursor (8,0);
          lcd.print("<");
          break; 
        }
      case 2:
        {
          lcd.setCursor (8,0);
          lcd.print(":");
          lcd.setCursor (11,0);
          lcd.print("<");
          break; 
        }

      case 3:
        {
          lcd.setCursor (8,1);
          lcd.print("<");
          lcd.setCursor (11,0);
          lcd.print(" ");
          break; 
        }

      case 4:
        {
          lcd.setCursor (8,1);
          lcd.print(":");
          lcd.setCursor (11,1);
          lcd.print("<");
          break; 
        }

      case 5:
        {
          lcd.setCursor (11,1);
          lcd.print(" ");
          lcd.setCursor(14,1);
          lcd.print("^");
          break; 
        }

      }


    }

  }


}

int OdabirZone(){      //Funkcija vraca odabranu zonu (int brojac) kada se stisne DESNO+LIJEVO
  delay (200);
  int brojac=1, time=0, konst=30000;    //brojac broji zone
  lcd.clear();

  lcd.setCursor(5,0);
  lcd.print("Zona:");
  lcd.setCursor(7,1);
  lcd.print ("1");

  while (1){        //Petlja se vrti dok se ne stisne kombinacija DESNO + LIJEVO
    if (time>konst) return 0;
    time++; 
    short SatP=-1, MinP=-1, SatG=-1, MinG=-1;



    if (analogRead(1)>100){
      while (analogRead(1)>100){
      }
      time=0;
      brojac++;
      if (brojac>8) brojac=1;
      switch (brojac){
      case 1:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 2:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 3:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 4:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 5:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 6:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 7:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }
      case 8:
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("Zona:");
          lcd.setCursor(7,1);
          lcd.print(brojac);
          break;
        }

      }
    }
    if (analogRead(3)>100) return brojac;
  }
}
int OdabirRazdoblja(int Zona){
  delay (250);
  //Odabir zone
  int brojac=1, time=0, konst=30000;
  int zona= Zona;

  lcd.clear();       
  lcd.setCursor(3,0);
  lcd.print("Razdoblje:");
  lcd.setCursor(7,1);
  lcd.print(brojac);

  while (1){
    if (time>konst) return 0;
    time++;     
    if(analogRead(3)>100) return brojac ;

    if (analogRead(1)>100){      //Ako se dogodi inc zone
      while (analogRead(1)>100){
      }
      time=0;
      lcd.clear();

      brojac++;
      if(brojac>4) brojac=1;
      lcd.clear();         
      lcd.setCursor(3,0);
      lcd.print("Razdoblje: ");
      lcd.setCursor(7,1);
      lcd.print(brojac);
    }
  }
}

void RucnoUpravljanje (){

  /* Izlazak iz RucnoUpravljanje() se odvija tako da se
   prvi pritisne desna tipka i dok je ona stisnuta, pritisne se lijeva
   */
  delay (250);
  int temp=1, init=1, brojac=1, time=0, konst=30000;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("1 2 3 4 5 6 7 8");
  lcd.setCursor(0,1);

  for (int i=1; i<=8; i++){
    if (digitalRead(zona[i])==LOW) lcd.write (3); // Puna kucica
    else lcd.write(2); 
    lcd.print(" ");
  }
  lcd.setCursor(temp,1);
  lcd.print ("<");

  temp=1;

  while (1){
    if (time>konst) return;
    time++;    
    if (init) temp+=2;
    init=0;
    if (analogRead(1)>50){
      while (analogRead(1)>50){
        time=0;
        if (analogRead(3)>50) return;
      }

      if (temp==1){                        //Ako je Temp==1; kod prvog ulaza u petlju i kod overfloata brojaca
        lcd.setCursor(temp,1);
        lcd.setCursor(15,1);
        lcd.print (" ");
      }
      else {
        lcd.setCursor(temp-2,1);
        lcd.print (" ");
      }
      lcd.setCursor(temp,1);
      lcd.print ("<");

      temp+=2;
      if (temp>15) temp=1;
      brojac++;
      if (brojac>8) brojac=1;
    }

    if (analogRead(3)>50){
      while (analogRead(3)>50){
      }
      time=0;
      digitalWrite(zona[brojac], !digitalRead(zona[brojac]));    //Invertira stanje na izlazu
      EEPROM.write(brojac, digitalRead(zona[brojac]));    //EEPROM lokacije počinju na 1, tamo spremam stanja izlaza
      if (temp==1) lcd.setCursor (14,1);                  
      else lcd.setCursor (temp-3,1);
      if (digitalRead(zona[brojac])==LOW) lcd.write(3);
      else lcd.write(2);    //prazna kucica
    }

  }
}

void ResetBrojaca(int zona){
  int time=0, konst=30000;
  delay(100);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print ("Nastaviti?");
  lcd.setCursor(0,1);
  lcd.print ("Da            Ne");
  delay (250);
  while (analogRead(1)<100 || analogRead(3)<100){
    if (time>konst) return;
    time++;   
    if (analogRead(3)>100){  
      EEPROM.write(180+zona, 0);
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Izbrisano!");
      delay (1000);
      return;
    }
    if (analogRead(1)>100) return;
  }
}

void Potrosnja(){
  int temp=1, time=0, konst=30000;
  delay (100);
  int zona = OdabirZone();
  delay (200);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Zona: ");
  lcd.print(zona);
  if (EEPROM.read((180+zona)/60) < 10)
    lcd.setCursor(6,1);
  if (EEPROM.read((180+zona)/60) < 100 && EEPROM.read((180+zona)/60) >= 10)
    lcd.setCursor(5,1);  
  if (EEPROM.read((180+zona)/60) < 1000 && EEPROM.read((180+zona)/60) >= 100)
    lcd.setCursor(4,1);  
  if (EEPROM.read((180+zona)/60) < 10000 && EEPROM.read((180+zona)/60) >= 1000)
    lcd.setCursor(3,1);
  if (EEPROM.read((180+zona)/60) < 100000 && EEPROM.read((180+zona)/60) >= 10000)
    lcd.setCursor(2,1);        
  /*
  lcd.print(EEPROM.read(180+zona)/3600);
   lcd.print("d ");
   */
  lcd.setCursor(7,1);
  lcd.print(EEPROM.read(180+zona)/60);                                                        //Staviti   lcd.print(EEPROM.read(180+zona)/60); da se prikazuje u satima!
  lcd.print("h ");
  /*  
   lcd.print(EEPROM.read(180+zona));
   lcd.print("min");
   */
  lcd.setCursor (10,0);
  lcd.print("Reset<");
  lcd.setCursor (10,1);
  lcd.print("Izlaz ");

  while (1){
    if (time>konst) return;
    time++;
    if (analogRead(1)>65){
      while (analogRead(1)>65){
      }
      time=0;
      temp++;
      if (temp>1) temp=0;

      switch (temp){
      case 0:
        {
          lcd.setCursor(15,0);
          lcd.print(" ");
          lcd.setCursor(15,1);
          lcd.print("<");  
          break;      
        }
      case 1:
        {
          lcd.setCursor(15,0);
          lcd.print("<");
          lcd.setCursor(15,1);
          lcd.print(" "); 
          break;       
        }
      }      
    }

    if (analogRead(3)>65){
      time=0;
      while (analogRead(3)>65){
      }
      if (!temp) return;
      else if (temp) {
        ResetBrojaca (zona);
        return;
      }
    }
  }
  delay (100);
  return;
}

void Izbornik (){
  //U Izbornik() se ulazi kada je IspitajUlaz()==3
  /*U Izbornik() imam samo:
   Pregled.Razdoblja()
   Rucno.Upravljanje()
   Programiranje()
   therm()
   */
  int temp=1;
  int time=0;
  int konst=30000;

  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print ("Izbornik");
  lcd.setCursor(6,1);
  lcd.print ("...");

  delay (1000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print ("Rucno");
  lcd.setCursor(2,1);
  lcd.print ("upravljanje");



  while (analogRead(3)<100){     //    Sve dok ne odaberem nekai 
    if (time>konst) return;
    time++;
    if (analogRead(1)>100){
      while (analogRead(1)>100){
      }
      temp++;
      if (temp>4) temp=1;
      switch (temp){

      case 1: 
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print ("Rucno");
          lcd.setCursor(2,1);
          lcd.print ("upravljanje");
          break;
        }
      case 2: 
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print ("Programiranje");
          break;
        }
      case 3: 
        {
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print ("Potrosnja");
          break;
        }
      case 4:
        {
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print ("Temperatura");
          break;
        }      
      }
    }
  }

  delay (100);      //Da se ima vremena otpustit button


  switch (temp){    

  case 1: 
    {
      RucnoUpravljanje();
      break;
    }
  case 2: 
    {
      Programiranje();
      break;
    }
  case 3: 
    {
      Potrosnja();
      break;
    }
  case 4: 
    {
      Therm();
      break;
    }
  
  }
}


void Podudaranje (){
  /*
  Funkcija čita vrijednosti iz EEPROMA koje odgovaraju PaliM i GasiM (manje iteracija).
   Ako se podudaraju s podacima iz RTCa tada pali/gasi određenu zonu.
   
   */

  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  /*
  for (int i=1; i<=8; i++){    //ide po zonama
   for(int j=0; j<=3; j++){    //mora ic od nula zbog zbrajanja, ide po razdobljima
   
   if(EEPROM.read(i*8+j*4 +1) == minute) {    //Ako se podudaraju minuteP
   if(EEPROM.read(i*8+j*4) == hour)    digitalWrite(zona[i],LOW);    //Ako se podudraju i sati- pali zonu
   }
   
   
   if(EEPROM.read(i*8+j*4 +3) == minute) {    //Ako se podudaraju minuteP
   if(EEPROM.read(i*8+j*4+2) == hour)    digitalWrite(zona[i],HIGH);    //Ako se podudraju i sati- pali zonu
   }
   */
  for (int i=1; i<=8; i++){    //ide po zonama
    for (int j=0; j<=3; j++){
      if ((EEPROM.read(i*16 + j*4 +1)==minute) && (EEPROM.read(i*16 + j*4)==hour && EEPROM.read(144 + (i-1)*8 + j)==0 && second<15)){
        digitalWrite(zona[i], LOW);

        EEPROM.write(1, digitalRead(zona[1]));
        EEPROM.write(2, digitalRead(zona[2]));
        EEPROM.write(3, digitalRead(zona[3]));
        EEPROM.write(4, digitalRead(zona[4]));
        EEPROM.write(5, digitalRead(zona[5]));
        EEPROM.write(6, digitalRead(zona[6]));
        EEPROM.write(7, digitalRead(zona[7]));
        EEPROM.write(8, digitalRead(zona[8]));
      }
      if ((EEPROM.read(i*16 + j*4 +3)==minute) && (EEPROM.read(i*16 + j*4 +2)==hour  && EEPROM.read(144 + (i-1)*8 + j)==0 && second<15)){    
        digitalWrite(zona[i], HIGH);    

        EEPROM.write(1, digitalRead(zona[1]));
        EEPROM.write(2, digitalRead(zona[2]));
        EEPROM.write(3, digitalRead(zona[3]));
        EEPROM.write(4, digitalRead(zona[4]));
        EEPROM.write(5, digitalRead(zona[5]));
        EEPROM.write(6, digitalRead(zona[6]));
        EEPROM.write(7, digitalRead(zona[7]));
        EEPROM.write(8, digitalRead(zona[8]));
      }
    }
  }


}

void Trosenje (){
  delay(250);
  for (int i=1; i<=8; i++) if (!digitalRead(zona[i])) EEPROM.write(180+i, EEPROM.read(180+i)+2);
}

int stanka= 20;
int inic=1;


void ProvjeraInic(int i){ 
  int time=0; 
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  int razdoblje=1;    //Razdoblje=0 jer podaci pocinju od EEPROM[16]
  int P1,P2,P3, P4, P5, P6, P7;            //Parametri
  int old1, old2;

  for (razdoblje; razdoblje<=4; razdoblje++){
    P1= EEPROM.read(16*i + (razdoblje-1)*4);  //Paljenje sat
    P2= EEPROM.read(16*i + (razdoblje-1)*4 +2);  //Gasenje sata   
    P3= EEPROM.read(16*i + (razdoblje-1)*4+1);  //Paljenje minuta
    P4= EEPROM.read(16*i + (razdoblje-1)*4+3);  //Gasenje minuta  
    P5= EEPROM.read(144 + (i-1)*8 + (razdoblje-1));      //Podatak o ON (0)/OFF (1) stanju 
    P6= hour;
    P7= minute;

    if (P5==0){            
        while (1){
          if (P1==P2 && P3==P4){    //Prosao se cijelo razdoblje upaljenosti i nije se naislo na trenutno vrijeme
            EEPROM.write (i, 1);
            break;
          }
          else if (P1==P6 && P3==P7){
            EEPROM.write (i, 0);
            return;
          }
          P3++;
          if (P3>=60){
            P3=0;
            P1++;
            if (P1>=24) P1=0;
          }
        }
    }
  }
}

void Therm(){
  /**
  Termometri su smjesteni na AnalogIn 0 i 2
  Ova funkcija treba imati meni za trenutna "Trenutna temperatura sondi" i za
  "Postavljanje sonde"
  **/
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print ("Trenutna");
  lcd.setCursor(2,1);
  lcd.print ("temperatura");

  delay (500);
  int temp=1;
  int time=0;
  int konst=30000;
  while (analogRead(3)<100){     //    Sve dok ne odaberem nekai 
  /*
    if (time>konst) return;
    time++;
    */
    if (analogRead(1)>100){
      while (analogRead(1)>100){
      }
      temp++;
      if (temp>2) temp=1;
      switch (temp){

      case 1: 
        {
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print ("Trenutna");
          lcd.setCursor(3,1);
          lcd.print ("temperatura");
          break;
        }
      case 2: 
         {
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print ("Postavke");
          lcd.setCursor(5,1);
          lcd.print ("sonde");
          break;
        }
        }}}
        
  switch (temp){
    case 1:
    {
          int therm;   
          therm=analogRead(2)-238;
          lcd.clear();
          lcd.print ("T1:");
          float thermF=therm/10.;
          lcd.print(thermF);
          lcd.write(4);
          lcd.print("C");
          delay(5000);  
          break;
      }
    case 2:
    {
      delay (120);
        temp=OdabirZone();    
      while (analogRead(1)<100){
      lcd.clear();    
        lcd.clear();
        lcd.print("S1");
        lcd.setCursor(0,1);
        lcd.print("Z");
        lcd.print(temp);
        lcd.setCursor (10,0);
        lcd.print("30.0");
        lcd.write(4);
        lcd.print("C");  
        lcd.setCursor (15,0);
        lcd.write (6);
        lcd.setCursor (10,1);
        lcd.print("25.4");
        lcd.write(4);
        lcd.print("C");         
        lcd.setCursor (15,1);
        lcd.write (5);
        delay (3000);
}
    return;
      }
          
      }
      

}

int tempmin=minute;


void loop(){


  for (inic; inic<=8; inic++){
   ProvjeraInic(inic);  //Provjeravaj treba li zona biti upaljena
  digitalWrite(zona[inic], EEPROM.read(inic));      
  }



  if (IspitajUlaz()==3) Izbornik();
  statusscreen();
  Podudaranje();
  /*
  Poziva funkciju trošenje ako je !(minute%2) i ako vec nije ispitivao tu minutu.
   
   */
  if (!(minute%2) && (minute!=tempmin)){
    Trosenje();
    tempmin=minute;
  }

}





