// BT kontrollü araba
// ANDROID uygulaması olarak ROBOREMO isimli program kullanılabilir. Baska alternatiflerde vardır. 
    
    #define Led_Far 10
    #define Led_Fren 11
    #define Led_Sol 9
    #define Led_Sag 12
    
    #define SesCikisi 3
    
    #define trigpini 13  // TRIG pini
    #define echopini 8  // ECHO pini
    #define IRSensor 4  //ir alici pini
    
    #define MotorSolYonPin 4
    #define MotorSolPWMPin 5
    #define MotorSagYonPin 7
    #define MotorSagPWMPin 6
    
    #define SensorSol A2
    #define SensorSag A3
    #define SensorSolPIN  A2
    #define SensorSagPIN  A3

int HIZ=0;
int VeriGelmiyorSayac=0;
int BeepSayac=0;
boolean beepon=false;

//bluetooth uzerinden gelen bilginin alinmasi
char BT_rx(){
  char gelenveri='_';
  if (Serial.available() > 0) //Serial portun kontrollü
  {
    gelenveri = Serial.read(); //Telefondan gelen verilerin kontrollü  
    Serial.println(gelenveri);
    VeriGelmiyorSayac=0;
  }
  
  return gelenveri;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Robot hazir");
  
  pinMode(Led_Far,OUTPUT); 
  pinMode(Led_Fren,OUTPUT);
  pinMode(Led_Sol,OUTPUT); 
  pinMode(Led_Sag,OUTPUT);
  pinMode(MotorSolYonPin,OUTPUT); 
  pinMode(MotorSagYonPin,OUTPUT); 
  pinMode(SesCikisi,OUTPUT);   
  

  HIZ=250;
  Robot_Dur();
}

void beep(){
  digitalWrite(SesCikisi,1);
  delay(1);
  digitalWrite(SesCikisi,0);
  delay(1);
  
}
void Robot_Dur(){
    digitalWrite(MotorSolYonPin, 1);
    digitalWrite(MotorSagYonPin, 1);
    analogWrite(MotorSolPWMPin,0);
    analogWrite(MotorSagPWMPin,0);

              
    digitalWrite(Led_Sol, 0);
    digitalWrite(Led_Sag, 0);
    digitalWrite(Led_Far, 0);
    digitalWrite(Led_Fren, 0);

    beepon=false;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay (1);
  //beep sesini olusturan bolum
  if (beepon==true){
      BeepSayac++;
      if (BeepSayac<250){
        digitalWrite(SesCikisi,1 - digitalRead(SesCikisi));   
      }
      if (BeepSayac>500){
        BeepSayac=0;
      }
  }
  //beep sesini olusturan bolum sonu
  
  
  switch (BT_rx())
  {
    case '_': //veri gelmiyor ise 10sn sonra otomatik dursun
      if (VeriGelmiyorSayac<10000){
        VeriGelmiyorSayac++;
      }else{
        Robot_Dur();
        beepon=false;

      }
      
    break;
    
    case '8'://ileri
          digitalWrite(MotorSolYonPin, 1);
          digitalWrite(MotorSagYonPin, 1);
          analogWrite(MotorSolPWMPin,HIZ);
          analogWrite(MotorSagPWMPin,HIZ);
          
                    
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 1);
          digitalWrite(Led_Fren, 0);
    break;
    
    case '2'://geri
          digitalWrite(MotorSolYonPin, 0);
          digitalWrite(MotorSagYonPin, 0);
          analogWrite(MotorSolPWMPin,HIZ);
          analogWrite(MotorSagPWMPin,HIZ);
              
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 1);
    break;
    
    case '0'://stop
      Robot_Dur();
    break;

    case '4'://sol
          digitalWrite(MotorSolYonPin, 1);
          digitalWrite(MotorSagYonPin, 1);
          analogWrite(MotorSolPWMPin,0);
          analogWrite(MotorSagPWMPin,HIZ);

          
          digitalWrite(Led_Sol, 1);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 0);          
    break;

    case '6'://sag
          digitalWrite(MotorSolYonPin, 1);
          digitalWrite(MotorSagYonPin, 1);
          analogWrite(MotorSolPWMPin,HIZ);
          analogWrite(MotorSagPWMPin,0);

              
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 1);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 0);
    break;
    
    case '5'://beep
      
      beepon=not beepon;
      

    break;
    
    case '7'://ileri+sol
    break;

    case '9'://ileri+sag
    break;
    
    case '1'://gerii+sol
    break;

    case '3'://geri+sag
    break;
    
    case 'q'://korna on
      beepon=true;
    break;

    case 'a'://korna off
      beepon=false;
    break;

    case 13:
        Serial.println("UYCEP MODELA - Ostim Mesleki ve Teknik Anadolu Lisesi");
        /*
        Serial.print("Batarya:");
        Serial.print(analogRead(A0));
        Serial.println(" "); 
        Serial.print("sensor:");
        Serial.print(Sensorler[0]);
        Serial.print(",");
        Serial.print(Sensorler[1]);
        Serial.print(",");
        Serial.print(Sensorler[2]);
        Serial.println(" ");
        */
    break;
    default:
    break;
  }  

}
