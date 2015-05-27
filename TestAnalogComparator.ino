volatile boolean triggered;

/*
Ovo je program za testiranje unutarnjeg komparatora na AtMega2560
Interrupt signal se treba dovesti na Arduino DP5 (AIN1). 
*/


ISR (ANALOG_COMP_vect)
  {
  triggered = true;
  }

void setup ()
  {
  Serial.begin (9600);
  Serial.println ("Started.");
  ADCSRB = 0x00;           // (Disable) ACME: Analog Comparator Multiplexer Enable
  ACSR =  0b01001010;
}
void loop ()
  {
  if (triggered)
    {
    Serial.println ("Triggered!"); 
    triggered = false;
    }
  
  }  // end of loop
