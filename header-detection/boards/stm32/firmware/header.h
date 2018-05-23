#ifndef HEADER_H
#define HEADER_H

/* Run State Machine */
void tick_state(EXTDriver *extp, expchannel_t channel);

/* Starts State Machine Thread */
void begin_header_detection(void);

#endif
