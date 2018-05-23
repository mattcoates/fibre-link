#include "ch.h"
#include "hal.h"

#include "status.h"
#include "usb_serial_link.h"

bool status = true;

/* Status Thread */ 
static THD_WORKING_AREA(waSTAT, 128);
static THD_FUNCTION(STAT, arg) {
  
    (void)arg;
    chRegSetThreadName("status");    
    while (true) {
        
        if (status == TRUE) {        
            palSetPad(GPIOD, GPIOD_STATUS);
        }
        
        chThdSleepMilliseconds(100);
        
        palClearPad(GPIOD, GPIOD_STATUS);  
        chThdSleepMilliseconds(500);
    }
}

void begin_status(void){

    chThdCreateStatic(waSTAT, sizeof(waSTAT), NORMALPRIO, STAT, NULL);
}

/* Global System Status */
void set_status(bool stat) {
    
    status = stat;
}
