
#include <LiquidCrystal.h>


int       pinA  = 22;
int       pinB  = 23;
int       pinC  = 24;
int       pinD  = 25;
int       pinE  = 26;
int       pinF  = 27;

float     sensorValue;
unsigned long    past_time = 0, current_time = 0;
unsigned long stageTime = 1000 * 20;                      //  1000 (1 sec) * 60 (1 min) * 2 (2 minutes)
int pins_up = 0;
int stage = 0;
int rp = 0, buttonState, stateStart = 0;
const int rs = 44, en = 45, d0 = 46, d1 = 47, d2 = 48, d3 = 49, d4 = 50, d5 = 51, d6 = 52, d7 = 53;
const int start = 42;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);


// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  
  pinMode(start,INPUT);

  
  lcd.begin(16, 2);
 
  lcd.setCursor(3,0);
  lcd.print("BIENVENIDO!");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Cicloergometro");   
  lcd.setCursor(0,1);
  lcd.print("en modo \"Prueba\"");
  delay (3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PRESIONE INICIAR");
  
}


void setStage(int stage){

  if (stage == 0){                  // First stage: 25 W
    digitalWrite(pinA,LOW);
    digitalWrite(pinB,HIGH);
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

   if (stage == 2){                   // Third stage: 75 W
    digitalWrite(pinA,HIGH);
    digitalWrite(pinB,HIGH);
    digitalWrite(pinC,LOW);
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
    lcd.print("75 W");
    }

   if (stage == 3){                   // Fourth stage: 100 W
    digitalWrite(pinA,HIGH);
    digitalWrite(pinB,HIGH);
    digitalWrite(pinC,HIGH);
    digitalWrite(pinD,LOW);
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
    lcd.print("100 W");
    }

   if (stage == 4){                   // Fifth stage: 125 W
    digitalWrite(pinA,HIGH);
    digitalWrite(pinB,HIGH);
    digitalWrite(pinC,HIGH);
    digitalWrite(pinD,HIGH);
    digitalWrite(pinE,LOW);
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
    lcd.print("125 W");
    }

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

void setRPM(void){
  
  sensorValue = analogRead(A0);
      
  if ((sensorValue > 680.0) && (rp == 0))
    past_time = millis();      
  if ((sensorValue < 390.0) && (rp == 0))
    rp = 1;
  if ((sensorValue > 680.0) && (rp == 1)){
    current_time = millis();
    lcd.setCursor(2,1);
    lcd.print(60000/(current_time - past_time));
    rp = 0;
  }
 
 } // End of the setRPM function

  
  

// the loop routine runs over and over again forever:
void loop() {
    
  // Can either use type int or float to store voltage, int takes up less memory and is recommend
  // Memory is a huge concern when programming microcontollers, be careful what datatypes are used 
  // in order to make the most of the available memory  
  // You can compare the size of the code by running the program using int and then running with float
  // You will see ~4k bytes for int vs ~6k bytes for float just by changing the datatype, quite astonishing. 


  buttonState = digitalRead(start);

 
  if (buttonState == HIGH){
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
    if ((millis() > (2*stageTime)) && (millis() < (3*stageTime))){      //    Third stage, 2-minute pedaling: 75 W
      if (pins_up == 0){
        setStage(stage);
        stage++;
        pins_up = 1;
      }
      setRPM();
    } // -- ########
    if ((millis() > (3*stageTime)) && (millis() < (4*stageTime))) {     //    Fourth stage, 2-minute pedaling: 100 W
      if (pins_up == 1){
        setStage(stage);
        stage++;
        pins_up = 0;
      }
      setRPM();
    } // -- ########
    if ((millis() > (4*stageTime)) && (millis() < (5*stageTime))) {     //    Fifth stage, 2-minute pedaling: 125 W
      if (pins_up == 0){
        setStage(stage);
        stage++;        
        pins_up = 1;
      }
      setRPM();
    } // -- ########
    if ((millis() > (5*stageTime)) && (millis() < (6*stageTime))) {     //    Sixth stage, 2-minute pedaling: 150 W
      if (pins_up == 1){
        setStage(stage);
        stage++;        
        pins_up = 0;
      }
      setRPM();
    } // -- ########     
  } 
}// -- ########  End of code!      
  
   
  
  
  
  
  /*
  
  if (buttonState == HIGH){
    // print out the value you read:
     for (int k=0; k < 1000;k++){
       //sensorValue = analogRead(A0);
      //voltage = sensorValue * (2.73 / 3300.0);  //(3.0 / 1023.0);
      //Serial.print("Sensor: ");
      //Serial.println(millis());
      //Serial.println(sensorValue);
      //Serial.print("Voltage: ");
      //Serial.println(sensorValue);
      //Serial.println(voltage);
      lcd.setCursor(2,1);
      lcd.print(k);
      delay(700);
      }
      
      rp = 0;
    } 
  
    */





// Código alterno para el cálculo de las RPM como el del pulso cardiaco

 /*  if (millis() < (Seguidor*TIEMPO_PULSO + 20)) {
     
      sensorValue = analogRead(A3);
      //voltage = sensorValue * (2.73 / 3300.0);  //(3.0 / 1023.0); 
      //Serial.println(voltage);
      if ((sensorValue > 4000.0) && (rp == 0)){
        RPM++;
        rp = 1;
       // Serial.println(voltage);
      //digitalWrite(ledPin, HIGH);   // sets the LED on
      //delay(15000);                 // waits for a second
      //digitalWrite(ledPin, LOW);    // sets the LED off
      //delay(15000);                 // waits for a second
      }
      else {
        if (sensorValue < 300.0){
          rp = 0;
        //Serial.println(0.5);
          }
      }        
    } 
    else {
      //Serial.println(voltage);
      Serial.print("RPM: ");
      Serial.println(RPM*6);
      rp = 0;
      Seguidor++;
      RPM = 0;
      //Serial.println(millis());
    }
    //Serial.println(millis());
  //} */


  /*if (buttonState == LOW){
  
    if ((millis() > (Seguidor*TIEMPO_PULSO - 20)) && (millis() < (Seguidor*TIEMPO_PULSO + 20)) ) {
      //Serial.println(voltage);
      Serial.print("PPM: ");
      Serial.println(PPM*4);
      PPM = 0;
      rp = 0;
      Seguidor++;
      //Serial.println(millis());
    } 
    else {
      sensorValue = analogRead(A3);
      voltage = sensorValue * (2.73 / 3300.0);  //(3.0 / 1023.0); 
      //Serial.println(voltage);
      if (voltage > 2.70 && rp == 0){
        PPM++;
        rp = 1;
        //Serial.println(266666.60);
      //digitalWrite(ledPin, HIGH);   // sets the LED on
      //delay(15000);                 // waits for a second
      //digitalWrite(ledPin, LOW);    // sets the LED off
      //delay(15000);                 // waits for a second
      }
      if (voltage < 0.5){
        rp = 0;
        //Serial.println(0.5);
        }
    }
    //Serial.println(millis());
  } */ 


  
  // Código para conocer el valor de entrada análoga       


/*

  if (rp == 0){
  // print out the value you read:
   for (int k=0; k < 1000;k++){
     sensorValue = analogRead(A0);
    //voltage = sensorValue * (2.73 / 3300.0);  //(3.0 / 1023.0);
    //Serial.print("Sensor: ");
    Serial.println(millis());
    //Serial.println(sensorValue);
    //Serial.print("Voltage: ");
    //Serial.println(sensorValue);
    //Serial.println(voltage);
    }
    rp = 1;
  }
   
*/
 
