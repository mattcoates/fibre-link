#include <SevSeg.h>

SevSeg sevseg;

/* Pin Definitions */
#define clk_pin   7
#define data_pin  8

int count = 0;
unsigned long previousMillis;

/* State Machine Definitions */
typedef enum {
    STATE_A=0, STATE_B, STATE_C, STATE_D, STATE_E, NUM_STATES
} state_t;

typedef state_t state_func_t(void);

/* State Functions */
state_t run_state(state_t cur_state);
static state_t do_state_a(void);
static state_t do_state_b(void);
static state_t do_state_c(void);
static state_t do_state_d(void);
static state_t do_state_e(void);

/* State Table */
state_func_t* const state_table[NUM_STATES] = {
    do_state_a, do_state_b, do_state_c, do_state_d,
    do_state_e
};

/* State Table Lookup */
state_t run_state(state_t cur_state){
    return state_table[cur_state]();
};

/* Initilise State Machine */
state_t cur_state = STATE_A;

/* Setup Function */
void setup() {

  /* Setup Interrupt */
  pinMode(clk_pin, INPUT); 
  pinMode(data_pin, INPUT); 

  attachInterrupt(digitalPinToInterrupt(clk_pin), tick, FALLING);

  /* Setup Display */
  byte numDigits = 4;   
  byte digitPins[] = {10,16,14,15}; // 1,2,3,4
  byte segmentPins[] = {18, 19, 20, 21, 3, 2, 4, 5}; // A,B,C,D,E,F,G,Period

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(10);
  
}


/* Main Loop */
void loop() {
  
  sevseg.setNumber(count, 0);
  Serial.println(count);
  count = 0;
  previousMillis = millis();
  while (millis() - previousMillis < 1000){
      sevseg.refreshDisplay();
  }

  
}

/* Clock ISR - Falling Edge */
void tick(){
  
  /* Tick State Machine */
  cur_state = run_state(cur_state);
  
}


/* State 0 */
static state_t do_state_a(void){
    
    if(digitalRead(data_pin)){
      return STATE_B;
    } else {
      return STATE_A;
    }
}

/* State 1 */
static state_t do_state_b(void){

    if(digitalRead(data_pin)){
      return STATE_B;
    } else {
      return STATE_C;
    }
}


/* State 10 */
static state_t do_state_c(void){
  
    if(digitalRead(data_pin)){
      return STATE_B;
    } else {
      return STATE_D;
    }
}

/* State 100 */
static state_t do_state_d(void){

    if(digitalRead(data_pin)){
      return STATE_E;
    } else {
      return STATE_A;
    }
}

/* State 1001 */
static state_t do_state_e(void){
     
    count = count + 1;
    
    if(digitalRead(data_pin)){
      return STATE_B;
    } else {
      return STATE_A;
    }
}

