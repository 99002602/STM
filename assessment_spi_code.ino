#include <SPI.h>
#define LEDpin 7
volatile boolean received;
volatile word Slavereceived;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDpin,OUTPUT); 
  Serial.begin(250000);
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  received = false;
  SPI.attachInterrupt();  
}

ISR (SPI_STC_vect)
{
  Slavereceived = SPDR;                  
  received = true;                       
}

void loop() {
  // put your main code here, to run repeatedly:
  if(received) 
  {
    if(Slavereceived==0)
    {
      digitalWrite(LEDpin,LOW);
      Serial.println("No presence detected");
    }
    else if(Slavereceived==1)
    {
      digitalWrite(LEDpin,HIGH);
      Serial.println("Presence detected");
    }
    else
    {
      digitalWrite(LEDpin,LOW);
      Serial.println("No output");
    }
    delay(1000);
  }
}
