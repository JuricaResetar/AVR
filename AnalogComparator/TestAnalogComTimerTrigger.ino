volatile int triggered=0;

/*
Ovo je program za testiranje unutarnjeg komparatora na AtMega2560
Interrupt signal se treba dovesti na Arduino DP5 (AIN1). 

Prekidi se okidaju na promjenu brida. Kada se dogodi padajući brid (stisak ekrana) pokrene se brojilo T1
Zatim se prilikom drugog prekida (rastući brid) provjerava stanje brojila
*/


ISR (ANALOG_COMP_vect){
  interruptRoutine();
  }


void interruptRoutine (){
  noInterrupts();
  triggered++;
  Serial.println ("Triggered iznosi: ");
  Serial.println (triggered);
  if (triggered==1) interrupts();  
  else if (triggered==1) noInterrupts();  //Prekidi ce se omoguciti kada se obavi gasenje
  }

void setup (){
  Serial.begin (9600);
  Serial.println ("Started.");
  ADCSRB = 0x00;           // (Disable) ACME: Analog Comparator Multiplexer Enable
  ACSR =  0b01001000;
}

void loop (){
  
  if (triggered==1){
    Serial.println ("Turned on"); 
    delay (300);
    }
  else if (triggered>=2){
    Serial.println ("Turned off"); 
    triggered=0;
    /*
    Check timer 
    */
    
    delay (300);
    interrupts();   
    }
  
  }  // end of loop
