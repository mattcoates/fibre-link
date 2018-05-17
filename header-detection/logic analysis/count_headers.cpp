#include <iostream>
#include<fstream>
#include <string.h>
using namespace std;

int count = 0;
int data = 0;


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


/* Enrty Point */
int main() {
    fstream fin("./data_stream.txt", fstream::in);
    while (true) {
        data = fin.get();
        if (data==-1){
            break;
        }
        cur_state = run_state(cur_state);
    }
    
    cout << count << " Headers Detected" << endl;
}


/* State 0 */
static state_t do_state_a(void){

    if(data==49){
      return STATE_B;
    } else {
      return STATE_A;
    }
}

/* State 1 */
static state_t do_state_b(void){

    if(data==49){
      return STATE_B;
    } else {
      return STATE_C;
    }
}


/* State 10 */
static state_t do_state_c(void){
  
    if(data==49){
      return STATE_B;
    } else {
      return STATE_D;
    }
}

/* State 100 */
static state_t do_state_d(void){

    if(data==49){
      return STATE_E;
    } else {
      return STATE_A;
    }
}

/* State 1001 */
static state_t do_state_e(void){
     
    count = count + 1;
    
    if(data==49){
      return STATE_B;
    } else {
      return STATE_A;
    }
}
