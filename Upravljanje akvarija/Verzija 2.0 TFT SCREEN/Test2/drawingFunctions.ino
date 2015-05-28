void drawTime (int x, int y, int segment){    
  /*
  *draw time started on coordinates (x,y)
  *  Time variable (month, day, year,hours,minutes, seconds)
  *  Character size: 16x16 pixels
  *  variable segment will decide which segment (hours, minutes...) will be refreshed
  */

  //Clear your space:
  myGLCD.setColor (102, 178, 255);  //Svijetla
  myGLCD.fillRoundRect (0, 0, 300, 115);
  myGLCD.setColor(51,51,255);  //Tamna
  myGLCD.setBackColor (102,178,255);  
  
  myGLCD.setFont(BigFont); 
  if (segment==-1){
    //myGLCD.setColor(0, 9, 255);
    myGLCD.printNumI (time[3],x,y,2);  //Hours
    if (time[3]<10) myGLCD.print ("0", x,y,2);
    myGLCD.print (":", x+32, y);
    myGLCD.printNumI (time[4],x+(16*3),y,2);  //minutes
    if (time[4]<10) myGLCD.print ("0", x+(16*3),y,2);  
    myGLCD.print (":", x+(16*5), y);
    myGLCD.printNumI (time[5],x + (16*6),y,2);     //Seconds
    if (time[5]<10) myGLCD.printNumI (0, x + (16*6),y);    
    /*
    myGLCD.printNumI (time[0],x,y+18,2);
    if (time[0]<10) myGLCD.print ("0", x ,y+18,2);      
    myGLCD.print (":", x+32, y+18);  
    myGLCD.printNumI (time[1],x+(16*3),y+18,2);
    if (time[1]<10) myGLCD.print ("0", x+(16*3) ,y+18,2);        
    myGLCD.print (":", x+(16*5), y+18);  
    myGLCD.printNumI (time[2],x+(16*6),y+18,2);
    if (time[2]<10) myGLCD.print ("0", x+(16*6) ,y+18,2);  
*/    
    }
  else if (segment==0){
      myGLCD.printNumI (time[0],x,y+18,2);
      if (time[0]<10) myGLCD.print ("0", x ,y+18,2);     
    }  
  else if (segment==1){
      myGLCD.printNumI (time[1],x+(16*3),y+18,2);
      if (time[1]<10) myGLCD.printNumI (0, x+(16*3) ,y+18,2);   
  }  
  else if (segment==2){
      myGLCD.printNumI (time[2],x+(16*6),y+18,2);
      if (time[2]<10) myGLCD.printNumI (0, x+(16*6) ,y+18,2);     
  }
  else if (segment==3){
      myGLCD.printNumI (time[3],x,y,2);  //Hours
      if (time[3]<10) myGLCD.printNumI (0, x,y,2);  
    }
  else if (segment==4){
      myGLCD.printNumI (time[4],x+(16*3),y,2);  //minutes
      if (time[4]<10) myGLCD.printNumI (0, x+(16*3),y,2);  
  }  
  else if (segment==5){
      myGLCD.printNumI (time[5],x + (16*6),y,2);     //Seconds
      if (time[5]<10) myGLCD.printNumI (0, x + (16*6),y,2); 
  }
  return;
  }
  
  
  
  
  
  void drawTemperature (){
      
 }
 
 
 
 
 void drawButtons(int colomns, int rows){

   myGLCD.setFont(SevenSegNumFont);   
// Draw the upper row of buttons
  for (int x=0; x<colomns; x++)
  {
    myGLCD.setColor(51,51,255);
    myGLCD.fillRoundRect (distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+ buttonSize+ (x*(distanceBButtons[0]+ buttonSize)), bCFR[1]);
    /*
    Serial.println(x);    
    Serial.println((distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize))));
    Serial.println(bCFR[0]);
    Serial.println((distanceBButtons[0]+ buttonSize+ (x*(distanceBButtons[0]+ buttonSize))));
    Serial.println(bCFR[1]);
    */
    buttonCoordinates [x*4]=distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize));
    buttonCoordinates [x*4+1]=bCFR[0];
    buttonCoordinates [x*4+2]= distanceBButtons[0]+(x*(distanceBButtons[0]+ buttonSize)) + buttonSize;
    buttonCoordinates [x*4+3]= bCFR[1];    
    myGLCD.setBackColor(51,51,255);  
    myGLCD.setColor(255, 255, 255);        
    myGLCD.printNumI(x+1, 28+(x*72), 121);   
    updateColorRec (x);    
  }
// Draw the center row of buttons
  for (int y=0; y<rows; y++)
  {
    myGLCD.setColor(51,51,255);
    myGLCD.fillRoundRect (distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+ buttonSize+ (y*(distanceBButtons[0]+ buttonSize)), bCSR[1]);
    if (isTurnedOn[y+4]) myGLCD.setColor(0, 255, 0);
    else myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCSR[1]); 
    myGLCD.setBackColor(51,51,255);   
    buttonCoordinates [y*4+16]=distanceBButtons[0]+(y*(distanceBButtons[0]+ buttonSize));
    buttonCoordinates [y*4+1+16]=bCSR[0];
    buttonCoordinates [y*4+2+16]= distanceBButtons[0]+ buttonSize+ (y*(distanceBButtons[0]+ buttonSize));
    buttonCoordinates [y*4+3+16]= bCSR[1];
    myGLCD.setColor(255, 255, 255);    
    myGLCD.printNumI(y+5, 28+(y*72), 181);
    updateColorRec (y+4);    
//    if (x<4)      myGLCD.printNumI(y+6, 27+(x*60), 200);
  }
 
 
   
}





void changeColorDigit (int x, char boja){
  
  if (boja=='Y'){ //Yellow
    myGLCD.setBackColor(51,51,255);         
    myGLCD.setColor(0, 0, 0);
    } 
 else if (boja=='B'){
    myGLCD.setBackColor(51,51,255);         
    myGLCD.setColor(225, 255, 255);
  }   
    myGLCD.setFont(SevenSegNumFont);
    if (x<4) myGLCD.printNumI(x+1, 28+(x*72), 121);
    else  myGLCD.printNumI(x+1, 28+((x-4)*72), 181);
  
  }

void updateColorRec (int pressed){
    if (pressed != -1){
      if (readStatus(pressed)){   //If turned ON
        myGLCD.setColor(0, 255, 0);
        saveStatus(pressed, 1);
      }
      else {  //If turned OFF
        myGLCD.setColor(255, 0, 0);
        saveStatus(pressed, 0);      
        }
      if (pressed<4){ //Just draw outline
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCFR[1]);
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize))+1, bCFR [0]+1, distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize-1, bCFR[1]-1);
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize))+2, bCFR [0]+2, distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize-2, bCFR[1]-2);        
        }
      else if (pressed>=4){  
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCSR[1]);
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize))+1, bCSR [0]+1, distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize-1, bCSR[1]-1);        
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize))+2, bCSR [0]+2, distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize-2, bCSR[1]-2);                
        }
    }

}  
void changeColorRec (int pressed){
  /*
  * This function will change (toogle) state (color) of button on cordinates (x,y)
  * First we need to find out which button is pressed
  */
 
  
  //int pressed=-1;
  
  /*
  //Komentirani dio koda je kod za detekciju koji se je button stisnuo, ali to ne trebam jer imam funkciju zonePressed (int x, int y)- ovo sam ostavio da vidis kako je hard codirano
  
  myGLCD.setBackColor(51,51,255);      
  if (y>bCFR[0] && y<bCFR[1]){
  for (int i=0; i<colomns; i++){
        if (x>(distanceBButtons[0]+(i*(distanceBButtons[0]+ buttonSize))) && x < (distanceBButtons[0]+ buttonSize+ (i*(distanceBButtons[0]+ buttonSize)))){
          pressed = i;
          break;
          }
     }
    }
   else if (y>bCSR[0] && y<bCSR[1]){
       for (int i=0; i<colomns; i++){
        if (x>(distanceBButtons[0]+(i*(distanceBButtons[0]+ buttonSize))) && x < (distanceBButtons[0]+ buttonSize+ (i*(distanceBButtons[0]+ buttonSize)))){
          pressed = i+colomns;
          break;
          }
     }
   }  
*/

    if (pressed != -1){
      if (readStatus(pressed)){   //If turned ON
        myGLCD.setColor(255, 0, 0);
        saveStatus(pressed, 0);
      }
      else {  //If turned OFF
        myGLCD.setColor(0, 255, 0);
        saveStatus(pressed, 1);      
        }
      if (pressed<4){ //Just draw outline
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)), bCFR [0], distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCFR[1]);
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize))+1, bCFR [0]+1, distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize-1, bCFR[1]-1);
        myGLCD.drawRoundRect (distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize))+2, bCFR [0]+2, distanceBButtons[0]+(pressed*(distanceBButtons[0]+ buttonSize)) + buttonSize-2, bCFR[1]-2);        
        }
      else if (pressed>=4){  
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)), bCSR [0], distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize, bCSR[1]);
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize))+1, bCSR [0]+1, distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize-1, bCSR[1]-1);        
        myGLCD.drawRoundRect (distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize))+2, bCSR [0]+2, distanceBButtons[0]+((pressed-colomns)*(distanceBButtons[0]+ buttonSize)) + buttonSize-2, bCSR[1]-2);                
        }
    }
  }
 
 void drawDots (int zone){
   /*
   * This function will draw dots on every razdoblje of zone "zone"
   * Red if it's non active and green if it's active
   */
   for (int i=0; i<4; i++){
     if (isActive[zone][i]) myGLCD.setColor (0,255,0);
     else myGLCD.setColor (255,0,0);
     myGLCD.fillRoundRect (circleX, circleY+24*i,circleX+20, circleY+24*i+20);
     }
   }
 
 void zoneMenu (int zone){
   int x=25, y=17;  
   unsigned short temp;
   myGLCD.setFont(BigFont);  
   myGLCD.setBackColor(51,51,255);   
   myGLCD.setColor (51,51,255);  
   myGLCD.fillRoundRect (x-5,y-10, x+260, y+95);
   myGLCD.setColor(255,255,255);   
   myGLCD.drawRoundRect (x-5,y-10, x+260, y+95);
   myGLCD.drawRoundRect (x-4,y-9, x+259, y+94);   
  //Bilo bi fora ubaciti da se ne ispisuje koja se zona uređuje, nego da se napravi rub oko te zone (a ono, malo nekaj boldano ili tak nekaj) -> Ma to je već napravljeno :D   
  
  //Podatke za ispis treba citati iz varijable podaciPaljenja [zona][razdoblje*4]
   
   for (int k=0; k<4; k++){
     temp=podaciPaljenja [zone][4*k];
     if (temp<10){
       myGLCD.print ("0", x, y+23*k);
       myGLCD.printNumI (temp, x+16,y+23*k);     
       }
     else myGLCD.printNumI (temp, x,y+23*k);    
     
     myGLCD.print (":", x+32, y+23*k); 
     temp=podaciPaljenja [zone][4*k+1];     
     
     if (temp<10){
       myGLCD.print ("0", x+48, y+23*k);  
       myGLCD.printNumI (temp, x+64,y+23*k);       
       }
     else myGLCD.printNumI (temp, x+48,y+23*k);
     
     myGLCD.print ("-", x+80, y+23*k);
     temp=podaciPaljenja [zone][4*k+2];   
     
     if (temp<10){
       myGLCD.print ("0", x+96, y+23*k);       
       myGLCD.printNumI (temp, x+112,y+23*k);
     }     
     else myGLCD.printNumI (temp, x+96,y+23*k);
     
     myGLCD.print (":", x+128, y+23*k);     
     temp=podaciPaljenja [zone][4*k+3];
    
     if (temp<10){
       myGLCD.print ("0", x+144, y+23*k);       
       myGLCD.printNumI (temp, x+160,y+23*k);       
       }
     else myGLCD.printNumI (temp, x+144,y+23*k);
   }
  }
  
void drawReturnButton (void){
    myGLCD.drawRoundRect (237, 13, 277, 53);
  }
void drawDurationButton (void){
    myGLCD.drawRoundRect (237, 63, 277, 103);
}  
