#include<SoftwareSerial.h>
// Grove - EMG Sensor demo code
// This demo will need a Grove - Led Bar to show the motion 
// Grove - EMG Sensor connect to A0
// Grove - LED Bar connect to D8, D9
// note: it'll take about serval seconds to detect static analog value
// when you should hold your muscle static. You will see led bar from level 10 turn to 
// level 0, it means static analog value get ok

int static_analog_dta   = A0;                // static analog data

volatile long val;

void interruptSetup(){  // CHECK OUT THE Timer_Interrupt_Notes TAB FOR MORE ON INTERRUPTS 
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}

// get analog value
void setup()
{
    Serial.begin(9600);
    interruptSetup();
}

ISR(TIMER2_COMPA_vect){                         // triggered when Timer2 counts to 124
    val = analogRead(static_analog_dta);
}

void loop()
{
    Serial.println(val);
    delay(20);
}
