#include <RGBTools.h>

//////////////////////////////////////////////
//RGB
//////////////////////////////////////////////
RGBTools rgb1(9,10,11);
RGBTools rgb2(3,5,6);

//////////////////////////////////////////////
//Processing
//////////////////////////////////////////////


//////////////////////////////////////////////
//MIDI
//////////////////////////////////////////////
byte commandByte;
byte noteByte;
byte velocityByte;

void setup(){
  
  Serial.begin(31250);
  //////////////////////////////////////////////
  // Interrupt 
  //////////////////////////////////////////////
  cli();//stop interrupts

  //set timer2 interrupt every 128us
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 7.8khz increments
  OCR2A = 255;// = (16*10^6) / (7812.5*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS11 bit for 8 prescaler
  TCCR2B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts
}

ISR(TIMER2_COMPA_vect) {//checks for incoming midi every 128us
  do{
    if (Serial.available()){
      commandByte = Serial.read();//read first byte
      noteByte = Serial.read();//read next byte
      velocityByte = Serial.read();//read final byte
    }
  }
  while (Serial.available() > 2);//when at least three bytes available
}

void loop(){
  //do whatever here
}

