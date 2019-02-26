int mode =0;
int starts=1;
unsigned long time;
unsigned long time_stop;
unsigned long heater_start;
//voltmeter//
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 12000.0; // resistance of R1 (12K)
float R2 = 4700.0; // resistance of R2 (4.7K)
int value = 0;

void setup()
{
  pinMode(2,INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4,HIGH);
  pinMode(5, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(12, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(5) == HIGH){
      digitalWrite(10,LOW); //kontakt
      Serial.print("vatre");
      delay(1000);
      engine_start();
      Serial.print("izhod");
    }
  if(digitalRead(5) == LOW){
    Serial.println("spiram");
    digitalWrite(10,HIGH);
    starts = 1;
    delay(100);
  }
  
  if(digitalRead(2) == HIGH && digitalRead(5) == HIGH){
    if(millis() >= heater_start){
        digitalWrite(3,HIGH);
    }
  }
  
  if(digitalRead(2) == LOW){
    digitalWrite(3,LOW);
  }
  
}

float voltmeter()
{
    value = analogRead(A0);
    vout = (value * 5.0) / 1024.0;
    vin = vout / (R2/(R1+R2)); 
    if (vin<0.09){
        vin=0.0;//statement to quash undesired reading !
    }
  return vin;
}

void engine_start(){
    while(starts <= 3){ //cikal za opit za zapalvane
        Serial.println(starts);
        if(digitalRead(12) == HIGH){
          digitalWrite(4,LOW);
          time_stop = millis() + 12000;
          while(1){
            if(digitalRead(12) == LOW){
              starts = 4;
              heater_start = millis() + 5000;
              break;
            }

            if(millis() >= time_stop){
              break;
            }
          }
          digitalWrite(4,HIGH);
          starts++;
        }
        if(digitalRead(12) == HIGH){
          //delay(15000);
          delay(5000);
        }
        Serial.println(starts);
      }
}
