#define DIGITAL_PIN 26
#define ANALOG_PIN 34
int ledPin = 2 ;
int threshold = 100;

int ampl0;
int ampl1;
int ampl;

void setup() {
  pinMode(DIGITAL_PIN, INPUT) ;
  Serial.begin(2000000) ;
  pinMode(ledPin, OUTPUT) ;
  ampl0 = 0;
  ampl1 = 0;
  ampl = 0;
    
}
void loop() {
  ampl0 = analogRead(ANALOG_PIN);

  ampl = abs(ampl0-ampl1);

  Serial.println(ampl) ;  

  ampl1=ampl0;  
  
  if (ampl>threshold){
    digitalWrite(ledPin, HIGH) ; 
    delay(1000);

    digitalWrite(ledPin, LOW) ; 
  }

}



