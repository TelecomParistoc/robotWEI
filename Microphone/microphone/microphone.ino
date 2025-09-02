//Utiliser la board "ESP Dev Module" du paquet ESP32 pour la carte AZ-Delivery D1 R32

#define DIGITAL_PIN 26
#define ANALOG_PIN 34
#define ledPin 2 

#define BLUE_PIN 17
#define RED_PIN 26
#define GREEN_PIN 25

int threshold = 100;

int ampl0 =0;
int ampl1 =0;
int ampl =0;

TaskHandle_t led_control_handle;
TaskHandle_t clap_detection_handle;

void setup() {
  pinMode(DIGITAL_PIN, INPUT) ;
  Serial.begin(2000000) ;
  pinMode(ledPin, OUTPUT) ;

  

  xTaskCreatePinnedToCore(
                    led_control,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &led_control_handle,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  xTaskCreatePinnedToCore(
                    clap_detection,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &clap_detection_handle,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500); 


}



void loop() {

}


void clap_detection(void * pvParameters){
  while(1){
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
}

void led_control(void * pvParameters){
  while(1){
    for(int j=0; j<6;j++){
      for(int i=0; i<255;i+=1){
        switch (j) {
          case 0:
            color(255,i,0);
            break;
          case 1:
            color(255-i,255,0);
            break;
          case 2:
            color(0,255,i);
            break;
          case 3:
            color(0,255-i,i);
            break;
          case 4:
            color(i,0,255);
            break;
          case 5:
            color(255,0,255-i);
            break;
        }
        delay(2);
      } 
    }
  }
}

void color (unsigned char red, unsigned char green, unsigned char blue)
{
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
}

