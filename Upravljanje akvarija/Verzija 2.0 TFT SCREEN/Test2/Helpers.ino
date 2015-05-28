void getTime (void){
  /*
  *  This function reads data from RTC and saves data to global int filed time
  */
  
  time [0]=8;
  time [1]=5;
  time [2]=2016;
  time [3]=0;
  time [4]=0;
  time [5]=0;
  }
  
  
int getTemperature (int sensorNumber){
/*
*  This function returns current temperature from sensor sensorNumber
*/

return sensorTemp[sensorNumber];
}  
 



void incRazdoblja (int zone, int razdoblje){
    /*This function will be called when bolean inZoneMenu is true and when TS is pressed on location of digit we want to edit
    *This function will also refresh screen on the end
    */
    if (razdoblje==-1) return;
    
    int row=razdoblje/4;
    Serial.println (razdoblje);    
    int x=25, y=17; 
    int temp;
    myGLCD.setFont(BigFont);      
    myGLCD.setColor (255,255,255);  
   
    if (!(razdoblje%2)){  //If true, this is data of hour
     if (podaciPaljenja [zone][razdoblje]==23)     podaciPaljenja [zone][razdoblje]=0;
       else podaciPaljenja [zone][razdoblje]++;
    }  
    else {
     if (podaciPaljenja [zone][razdoblje]>=55)     podaciPaljenja [zone][razdoblje]=0;
       else podaciPaljenja [zone][razdoblje]+=5;
    }
   
   if (razdoblje>=20){
     switch (razdoblje){
         case 20: {
           //Toogle firste dot
           if (isActive[zone][0]){
            myGLCD.setColor (255, 0, 0);
             isActive [zone][0] = false;
             }            
           else{
             myGLCD.setColor (0,255,0);
             isActive [zone][0] = true;
             }
           drawDots(zone);
           break;
           }
         case 21: {
           //Toogle firste dot
           if (isActive[zone][1]){
             myGLCD.setColor (255, 0, 0);
             isActive [zone][1] = false;
          }             
           else{
             myGLCD.setColor (0,255,0);
             isActive [zone][1] = true;
             }
           drawDots(zone);
           break;
           }    
         case 22: {
           //Toogle firste dot
           if (isActive[zone][2]){
             myGLCD.setColor (255, 0, 0);
             isActive [zone][2] = false;
             }
           else{
             myGLCD.setColor (0,255,0);
             isActive [zone][2] = true;
             }
           drawDots(zone);
           break;
           }   
         case 23: {
           //Toogle firste dot
           if (isActive[zone][3]){
             myGLCD.setColor (255, 0, 0);
             isActive [zone][3] = false;
             }
           else{
             myGLCD.setColor (0,255,0);
             isActive [zone][3] = true;
             }
           drawDots(zone);
           break;
           }             
     }
     return; 
   }
    
    switch (razdoblje%4){
          case 0: {
                 temp=podaciPaljenja [zone][4*row];
                 if (temp<10){
                   myGLCD.print ("0", x, y+23*row);
                   myGLCD.printNumI (temp, x+16,y+23*row);     
                   }
                 else myGLCD.printNumI (temp, x,y+23*row);                      
                 break;
           }
          case 1: {
                 temp=podaciPaljenja [zone][4*row+1];     
                 if (temp<10){
                   myGLCD.print ("0", x+48, y+23*row);  
                   myGLCD.printNumI (temp, x+64,y+23*row);       
                   }
                 else myGLCD.printNumI (temp, x+48,y+23*row);                    
                 break;
           } 
          case 2: {
               temp=podaciPaljenja [zone][4*row+2];        
               if (temp<10){
                 myGLCD.print ("0", x+96, y+23*row);       
                 myGLCD.printNumI (temp, x+112,y+23*row);
               }     
               else myGLCD.printNumI (temp, x+96,y+23*row);                      
               break;
           }  
          case 3: {
               temp=podaciPaljenja [zone][4*row+3];
               if (temp<10){
                 myGLCD.print ("0", x+144, y+23*row);       
                 myGLCD.printNumI (temp, x+160,y+23*row);       
                 }
               else myGLCD.printNumI (temp, x+144,y+23*row);                      
               break;
           }                                     
   }  
}  
  
  
  
  
int zonePressed(int x, int y){
  /*
  * This function will return number of button if x and y (where pressed) are within button
  * else will return -1
  Zones coordinates:
        zoneNumber: (xStart, yStart, xEnd, yEnd)
        0: 20, 120, 72, 172
        1: 92, 120, 144, 172
        2: 164,120, 216, 172        
        3: 236,120, 288, 172        
        4: 20, 180, 72,  232        
        5: 92, 180, 144, 232        
        6:164, 180, 216, 232        
        7:236, 180, 288, 232
  */
   for (int i=0; i<32; i+=4){   
     if (buttonCoordinates [i]<x && buttonCoordinates [i+2]> x){
       if (buttonCoordinates [i+1]<y && buttonCoordinates [i+3]>y)
         return i/4;
       }
     }
     return -1;
  }

int digitPressed (int x, int y){
  /*
  This function is called when program is in zoneMenu to determine which digit we want to increment
  Function will return index on podaciPaljenja[][];
  */
   for (int k=0; k<4; k++){
     //First determine which row is pressed
     if (y>20+23*k && y<20+23*(k+1)) {
       if (x>20 && x<20+32) return 0 + k*4;
       if (x>20+48 && x<20+82) return 1 + k*4;       
       if (x>20+96 && x<20+128) return 2 + k*4;
       if (x>20+144 && x<20+176) return 3 + k*4;  
       if (x>circleX && x<20+circleX) return 20 + k;     
       }
   }
   return -1;

}  
