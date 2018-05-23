#ifndef USB_SERIAL_LINK_H
#define USB_SERIAL_LINK_H

#define TYPE_COUNTS 1

/* Log Message */
typedef struct __attribute__((packed)) {

    uint8_t type;
    systime_t timestamp;
    uint8_t payload[123]; 
    
} log_message;

/* Start USB Serial Thread */
void usb_serial_init(void);

/* Upload Functions */
void upload_counts(uint32_t counts);

#endif

