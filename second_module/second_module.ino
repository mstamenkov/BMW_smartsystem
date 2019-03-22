//voltmeter//
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 1000.0; // resistance of R1 (12K)
float R2 = 600.0; // resistance of R2 (4.7K)
int value = 0;
int started = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(voltmeter());
    delay(1000);
}

float voltmeter()
{
    value = analogRead(A0);
    vout = (value * 5.0) / 1024.0;
    vin = vout / (R2 / (R1 + R2));
    if (vin < 0.09) {
        vin = 0.0; //statement to quash undesired reading !
    }
    return vin;
}
