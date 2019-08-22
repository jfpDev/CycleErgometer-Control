
#include <LiquidCrystal.h>


int       pinA  = 22;                                         // Pins used to control the system
int       pinB  = 23;
int       pinC  = 24;
/*
 *  Put as many pins as you need
 */
int       pinD  = 25;
int       pinE  = 26;
int       pinF  = 27;

float            sensorValue;                                 //  Variable to store the analog value of the RPM sensor
unsigned long    past_time = 0, current_time = 0;             //  Variables to store the running time
unsigned long    stageTime = 1000 * 60 * 2;                   //  1000 (1 sec) * 60 (1 min) * 2 (2 minutes)
int              pins_up = 0;                                 //  Variable to enable each stage
int              stage = 0;                                   //  Variable to set the current state
int              rp = 0, buttonState, stateStart = 0;
const int        rs = 44, en = 45, d0 = 46, d1 = 47, d2 = 48, d3 = 49, d4 = 50, d5 = 51, d6 = 52, d7 = 53;          // Pins used to control the LCD
const int start = 42;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);   // Initialazing the LCD with lcd variable




void setStage(int stage){           // This function sets the output pins as required for designer

  if (stage == 0){                  // First stage: 25 W
    digitalWrite(pinA,LOW);
    digitalWrite(pinB,HIGH);
    digitalWrite(pinC,HIGH);
/*
 *  Pins used to control what you need: Motors, regulators, etc.
 */
    digitalWrite(pinD,HIGH);       
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("RPM");
   
    lcd.setCursor(6,0);
    lcd.print("||");
  
    lcd.setCursor(9,0);
    lcd.print("CARGA");
  
    lcd.setCursor(6,1);
    lcd.print("||");
    lcd.setCursor(9,1);
    lcd.print("25 W");
    }

   if (stage == 1){                 // Second stage: 50 W
    digitalWrite(pinA,HIGH);
    digitalWrite(pinB,LOW);
    digitalWrite(pinC,HIGH);
    digitalWrite(pinD,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("RPM");
   
    lcd.setCursor(6,0);
    lcd.print("||");
  
    lcd.setCursor(9,0);
    lcd.print("CARGA");
  
    lcd.setCursor(6,1);
    lcd.print("||");
    lcd.setCursor(9,1);
    lcd.print("50 W");
    }

/*    
 *    #######################################################
 * 
 *      Put as many stages as you need to control the system
 * 
 *    #######################################################
 */    
   
   if (stage == 5){                    // sixth stage: 150 W
    digitalWrite(pinA,LOW);
    digitalWrite(pinB,HIGH);
    digitalWrite(pinC,HIGH);
    digitalWrite(pinD,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,LOW);

    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("RPM");
   
    lcd.setCursor(6,0);
    lcd.print("||");
  
    lcd.setCursor(9,0);
    lcd.print("CARGA");
  
    lcd.setCursor(6,1);
    lcd.print("||");
    
    lcd.setCursor(9,1);
    lcd.print("150 W");
    }
  
  } // End of the setStage function

void setRPM(void){                                           // This function sets the RPM of the user in the LCD
  
  sensorValue = analogRead(A0);
      
  if ((sensorValue > 680.0) && (rp == 0))
    past_time = millis();      
  if ((sensorValue < 390.0) && (rp == 0))
    rp = 1;
  if ((sensorValue > 680.0) && (rp == 1)){
    current_time = millis();
    lcd.setCursor(2,1);
    lcd.print(60000/(current_time - past_time));            // Efficient way to measure the RPM
    rp = 0;
  }
 
 } // End of the setRPM function


 
void setup() {
  
  pinMode(pinA, OUTPUT);                                      // Set up the control pins as outputs
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  
  pinMode(start,INPUT);

  
  lcd.begin(16, 2);                 
 
  lcd.setCursor(4,0);                                         // Put some greetings and information on the screen
  lcd.print("WELCOME!");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(4,0);
  lcd.print("CPE Test");   
  lcd.setCursor(2,1);
  lcd.print("Do your best!");
  delay (3000);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Press BEGIN");
  
}
  
  

void loop() {
    
  // Can either use type int or float to store voltage, int takes up less memory and is recommend
  // Memory is a huge concern when programming microcontollers, be careful what datatypes are used 
  // in order to make the most of the available memory  
  // You can compare the size of the code by running the program using int and then running with float
  // You will see ~4k bytes for int vs ~6k bytes for float just by changing the datatype, quite astonishing. 


  buttonState = digitalRead(start);

 
  if (buttonState == HIGH){                                             //    Condition needed to the user start the test
    stateStart = 1;
    delay(10);
  }
  if (stateStart == 1){
    if (millis() < stageTime){                                          //    First stage, 2-minute pedaling: 25 W
      if (pins_up == 0){
        setStage(stage);
        stage++;     
        pins_up = 1;
      }
      setRPM();      
    } // -- ########     
    if ((millis() > stageTime) && (millis() < (2*stageTime))){          //    Second stage, 2-minute pedaling: 50 W. 
      if (pins_up == 1){
        setStage(stage);
        stage++;
        pins_up = 0;
      }
      setRPM();
    } // -- ########  

/*    
 *    #######################################################
 * 
 *      Put as many stages as you need to control the system
 * 
 *    #######################################################
 */
    
    if ((millis() > (5*stageTime)) && (millis() < (6*stageTime))) {     //    Sixth stage, 2-minute pedaling: 150 W
      if (pins_up == 0){
        setStage(stage);
        stage++;        
        pins_up = 1;
      }
      setRPM();
    } // -- ########
    if (millis() > (6*stageTime)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The test has");
      lcd.setCursor(0,1);
      lcd.print("been ended");
    }           
  } 
}// -- ########  End of code!      
  
   
 
