#include "ch.h"
#include "hal.h"

#include "status.h"
#include "header.h"
#include "usb_serial_link.h"

BSEMAPHORE_DECL(clock_evt, TRUE);

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
uint32_t counts = 0;
state_t cur_state = STATE_A;
binary_semaphore_t clock_evt;
systime_t prevtime = 0;

/* Clock ISR */
void tick_state(EXTDriver *extp, expchannel_t channel) {
    
    (void)extp;
	(void)channel;
	
    chSysLockFromISR();
    chBSemSignalI(&clock_evt);
    chSysUnlockFromISR();

}


/* Header Detection Thread */ 
static THD_WORKING_AREA(waHEAD, 4096);
static THD_FUNCTION(HEAD, arg) {
  
    (void)arg;
    
    while(TRUE){
    
        /* Wait for Clock Event */
        chBSemWait(&clock_evt);
      
        /* Tick State Machine */
        cur_state = run_state(cur_state);
        
        if((chVTGetSystemTime()-prevtime) > MS2ST(1000)) {
        
            prevtime = chVTGetSystemTime();
            upload_counts(counts);
            counts = 0;
        }
    }
}


/* State 0 */
static state_t do_state_a(void){
    
    if(palReadPad(GPIOA, GPIOA_PWM_2)==PAL_HIGH){
      return STATE_B;
    } else {
      return STATE_A;
    }
}


/* State 1 */
static state_t do_state_b(void){

    if(palReadPad(GPIOA, GPIOA_PWM_2)==PAL_HIGH){
      return STATE_B;
    } else {
      return STATE_C;
    }
}


/* State 10 */
static state_t do_state_c(void){
  
    if(palReadPad(GPIOA, GPIOA_PWM_2)==PAL_HIGH){
      return STATE_B;
    } else {
      return STATE_D;
    }
}


/* State 100 */
static state_t do_state_d(void){

    if(palReadPad(GPIOA, GPIOA_PWM_2)==PAL_HIGH){
      return STATE_E;
    } else {
      return STATE_A;
    }
}


/* State 1001 */
static state_t do_state_e(void){
     
    counts = counts + 1;
    
    if(palReadPad(GPIOA, GPIOA_PWM_2)==PAL_HIGH){
      return STATE_B;
    } else {
      return STATE_A;
    }
}


/* Start Thread */
void begin_header_detection(void){

    chThdCreateStatic(waHEAD, sizeof(waHEAD), NORMALPRIO, HEAD, NULL);
}
