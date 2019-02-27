#include<SoftwareSerial.h>
// Watch video here: https://www.youtube.com/watch?v=O5Ye5xJF44c

/* 
GSR connection pins to Arduino microcontroller

Arduino           GSR

GND               GND
5V                VCC
A2                SIG

D13             RED LED

*/

/*
 GSR, standing for galvanic skin response, is a method of 
 measuring the electrical conductance of the skin. Strong 
 emotion can cause stimulus to your sympathetic nervous 
 system, resulting more sweat being secreted by the sweat 
 glands. Grove – GSR allows you to spot such strong emotions 
 by simple attaching two electrodes to two fingers on one hand,
 an interesting gear to create emotion related projects, like 
 sleep quality monitor. http://www.seeedstudio.com/wiki/Grove_-_GSR_Sensor
 */

const int GSR=A0;
int sensorValue;

void interruptSetup(){  // CHECK OUT THE Timer_Interrupt_Notes TAB FOR MORE ON INTERRUPTS 
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

void setup(){
  Serial.begin(9600);
  interruptSetup();
}

ISR(TIMER2_COMPA_vect){                         // triggered when Timer2 counts to 124
  cli();                                      // disable interrupts while we do this
  sensorValue=analogRead(GSR);              // read the Pulse Sensor
}

void loop(){
  Serial.println(sensorValue);
  delay(20);
}

