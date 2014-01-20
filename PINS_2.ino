
//define analog inputs to which we have connected our sensors
int const moistureSensorRed = 3; //red -- outPin5
int const moistureSensorBlue = 4; //blue -- outPin6
int const moistureSensorYellow = 5; //yellow --outPin7

//define digital pin to use - pinValve is really valve1-3 = value is the board pin
int const outPinRed = 5; //red
int const outPinBlue = 6; //blue
int const outPinYellow = 7; //yellow

//water if higher than this value = 1023 means leads are touching .
int blueWaterValue = 100;
int redWaterValue = 100;
int yellowWaterValue = 100;

//define variables to store moisture, light, and temperature values
int moistureVal = 1; //1 equals touching, 1023 = not touching

//value to water plants when below - resistance
//int waterPlantValue = 600;

boolean debugMode = true;

//10 seconds
int waitTime = 15000;

void setup() {
//open serial port
Serial.begin(9600);
//wait time for serial data
Serial.setTimeout(3000);

//setup the pins
pinMode(outPinRed, OUTPUT);
pinMode(outPinBlue, OUTPUT);
pinMode(outPinYellow, OUTPUT);

} //end setup


void loop() {  
    
  //set up debug mode during startup
  if (debugMode)  
   {
    
      Serial.println("\nPress any key to enter debug mode or wait 10 seconds to proceed >>> ");
      String strValue = Serial.readString();
      if (strValue.length() > 0)
      {
      
        runDebugPrompt();
      
      }

     //debug mode is false for the rest of the function until restarted  
     debugMode = false;

  }
  
  else //run normal
  
  {
       //yellow
       moistureVal = analogRead(moistureSensorYellow);
       Serial.print("\nYellow mositure value: ");
       Serial.println(moistureVal);
       
       //water yellow plant
       if ( moistureVal < yellowWaterValue)
        {
          
          waterYellowPlant();

         } //water yellow plant
         
         
         
       //blue
       moistureVal = analogRead(moistureSensorBlue);
       Serial.print("\nBlue mositure value: ");
       Serial.println(moistureVal);
       
       //water blue plant
       if ( moistureVal < blueWaterValue)
        {
           waterBluePlant();
    
         } //water blue plant
     
   
    
       //red
       moistureVal = analogRead(moistureSensorRed);
       Serial.print("\nRed mositure value: ");
       Serial.println(moistureVal);
       
       //water blue plant
       if ( moistureVal < redWaterValue)
       {
          waterRedPlant();
    
        } //water red plant
  

    }//run normal
  
 // Serial.println("\nEnd Loop");
  delay(waitTime);
  
 

} //end loop



void waterYellowPlant() {
  
       //Serial.print
       Serial.println("Start Yellow");
       digitalWrite(outPinYellow, HIGH);
    
       delay(waitTime);
          
       digitalWrite(outPinYellow, LOW);
       Serial.println("Stop Yellow");
  
  
}

void waterBluePlant() {
  
       //Serial.print
       Serial.println("Start Blue");
       digitalWrite(outPinBlue, HIGH);
    
       delay(waitTime);
          
       digitalWrite(outPinBlue, LOW);
       Serial.println("Stop Blue");
}

void waterRedPlant() {
  
         //Serial.print
         Serial.println("Start Red");
         digitalWrite(outPinRed, HIGH);
    
         delay(waitTime);
          
         digitalWrite(outPinRed, LOW);
         Serial.println("Stop Red");
  
}

void runDebugPrompt() {
 
 
     String userInput;
      
     DebugPrompt(); 

  
 // capture the incoming
  while (true) 
    {
    
      
      //wait for input
      while (Serial.available() > 0)
      {
        
        
        
        // If it is, we'll use parseInt() to pull out any numbers:
        userInput = Serial.readString();
        userInput.trim();

      
        //check if setup and parse 
        char charInput = userInput.charAt(0);        
        
        if (charInput == 's' || charInput == 'S')
        {
          
          //plant number
          char plantNum = userInput.charAt(1);
          
          //waterValueNumber
          String strWaterVal = userInput.substring(2,6);
          int intWaterVal = strWaterVal.toInt();
        
          //yellow
          if (plantNum == '1' && (intWaterVal < 1024 && intWaterVal > 0)) {
            
            yellowWaterValue = intWaterVal;
            Serial.print("\nYellow Water Value has been set: S");
            Serial.print(plantNum);
            Serial.print(" == ");
            Serial.print(intWaterVal);
            Serial.println("");
            
          } //(plantNum == '1')
          
          //blue
          else if (plantNum == '2') {
            
            blueWaterValue = intWaterVal;
            Serial.print("\nBlue Water Value has been set: S");
            Serial.print(plantNum);
            Serial.print(" == ");
            Serial.print(intWaterVal);
            Serial.println("");
            
          } //(plantNum == '2')
          
          
          //red
          else if (plantNum == '3') {
            
            
            redWaterValue = intWaterVal;
            Serial.print("\nRed Water Value has been set: S");
            Serial.print(plantNum);
            Serial.print(" == ");
            Serial.print(intWaterVal);
            Serial.println("");
            
          } //(plantNum == '3')
          
          
          else {
            Serial.println("Invalid Input");
          }
                 
    
        } // if (charInput == 's' || charInput == 'S')
               
        
        else if (userInput.equalsIgnoreCase("p"))
        {
            Serial.println(""); //extra spacing
            
            Serial.print("Water Time set to: ");
            Serial.println(waitTime);
            
            Serial.println(""); //extra spacing
          
            //yellow plant values
            Serial.print("Yellow Plant water value is: "); 
            Serial.println(yellowWaterValue);
            Serial.print("Yellow moisture  value is: ");
            Serial.println(analogRead(moistureSensorYellow));
            Serial.println("");
            delay(5000);
          
          
            //Blue plant values
            Serial.print("Blue Plant water value is: ");
            Serial.println(blueWaterValue);
            Serial.print("Blue moisture value value is: ");
            Serial.println(analogRead(moistureSensorBlue));
            Serial.println("");
            delay(5000);
          
                    
            //Red plant values
            Serial.print("Red Plant water value is: ");
            Serial.println(redWaterValue);
            Serial.print("Red moisture value value is: ");
            Serial.println(analogRead(moistureSensorRed));
            Serial.println("");
            delay(5000);
          
        } //if (userInput.equalsIgnoreCase("p"))
        
        else if (userInput.equalsIgnoreCase("r"))
        {
          Serial.println("");
          waterYellowPlant();
          Serial.println("");
          waterBluePlant();
          Serial.println("");
          waterRedPlant();
          
        } //else if (userInput.equalsIgnoreCase("r"))
        
        
        else if (charInput == 't' || charInput == 'T')
        {
          //waterValueNumber
          String strWaterTime = userInput.substring(1,6);
          waitTime = strWaterTime.toInt();
          //Serial.print(waitTime);
          waitTime = constrain(waitTime, 5000, 30000);
          Serial.print("Water Time set to: ");
          Serial.print(waitTime);
          Serial.println(" MilliSeconds");
          
        }
        
        else if (userInput.equalsIgnoreCase("e"))
        {
           Serial.println("\nExit Debug Mode");
           return;
       
        } //if (userInput.equalsIgnoreCase("e"))
        
         else {
               
               Serial.println("Invalid Input");
               delay(5000);
                      
        }
        
         DebugPrompt();
      
      } //if (Serial.available() > 0)
    
    }   //while (true)
 
} 


void DebugPrompt() 
{

      Serial.println("\nMenu");
      Serial.println("P - Print all values");
      Serial.println("S - Set Plant Water Value [S], [plant number] (1 digit, Yellow = 1, Blue = 2, Red = 3, [water value number] (4 digits, 0000-1023) -- i.e. set yellow plant water val to 1023 == S10323");
      Serial.println("R - Run all valves");
      Serial.println("T - Set Water Time in MilliSeconds (5000-30000 MilliSeconds) i.e set time to 6 seconds == T06000");
      Serial.println("E - Exit Debug Mode\n");
    
} //void DebugPrompt



