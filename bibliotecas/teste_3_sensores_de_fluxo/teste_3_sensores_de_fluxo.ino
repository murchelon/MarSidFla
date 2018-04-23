
#define FLOWSENSORPIN 36
#define FLOWSENSORPIN2 37 
#define FLOWSENSORPIN3 38 

// count how many pulses!
volatile uint16_t pulses = 0;
volatile uint16_t pulses2 = 0;
volatile uint16_t pulses3 = 0;

// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
volatile uint8_t lastflowpinstate2;
volatile uint8_t lastflowpinstate3;

// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
volatile uint32_t lastflowratetimer2 = 0;
volatile uint32_t lastflowratetimer3 = 0;

// and use that to calculate a flow rate
volatile float flowrate;
volatile float flowrate2;
volatile float flowrate3;

// Interrupt is called once a millisecond, looks for any pulses from the sensor!

SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN);
  
  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}


SIGNAL(TIMER2_COMPA_vect) {
  
  uint8_t x2 = digitalRead(FLOWSENSORPIN2);
  
  if (x2 == lastflowpinstate2) {
    lastflowratetimer2++;
    return; // nothing changed!
  }
  

  if (x2 == HIGH) {
    //low to high transition!
    pulses2++;
  }


  lastflowpinstate2 = x2;
  flowrate2 = 1000.0;
  flowrate2 /= lastflowratetimer2;  // in hertz
  lastflowratetimer2 = 0;
}

SIGNAL(TIMER3_COMPA_vect) {
  
  uint8_t x3 = digitalRead(FLOWSENSORPIN3);
  
  if (x3 == lastflowpinstate3) {
    lastflowratetimer3++;
    return; // nothing changed!
  }
  

  if (x3 == HIGH) {
    //low to high transition!
    pulses3++;
  }


  lastflowpinstate3 = x3;
  flowrate3 = 1000.0;
  flowrate3 /= lastflowratetimer3;  // in hertz
  lastflowratetimer3 = 0;
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}


void useInterrupt2(boolean b) {
  if (b) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR2A = 0xAF;
    TIMSK2 |= _BV(OCIE2A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK2 &= ~_BV(OCIE2A);
  }
}

void useInterrupt3(boolean w) {
  if (w) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR3A = 0xAF;
    TIMSK3 |= _BV(OCIE3A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK3 &= ~_BV(OCIE3A);
  }
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(FLOWSENSORPIN, INPUT);
  digitalWrite(FLOWSENSORPIN, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN);
  
  pinMode(FLOWSENSORPIN2, INPUT);
  digitalWrite(FLOWSENSORPIN2, HIGH);
  lastflowpinstate2 = digitalRead(FLOWSENSORPIN2);

  pinMode(FLOWSENSORPIN3, INPUT);
  digitalWrite(FLOWSENSORPIN3, HIGH);
  lastflowpinstate3 = digitalRead(FLOWSENSORPIN3);
  
  useInterrupt(true);
  useInterrupt2(true);
  useInterrupt3(true);
  
}


void loop() {
  

  float liters = pulses;
  liters /= 23;
  liters /= 60.0;

  float liters2 = pulses2;
  liters2 /= 23;
  liters2 /= 60.0;

  float liters3 = pulses3;
  liters2 /= 23;
  liters2 /= 60.0;
 
  //Serial.println(level);
  Serial.print(liters); Serial.print(" Liters"); Serial.print("        "); Serial.print(liters2); Serial.println(" Liters");  
  Serial.print("        "); Serial.print(liters3); Serial.println(" Liters");
  
 delay(1000);
}
