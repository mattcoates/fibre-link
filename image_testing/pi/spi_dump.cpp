/******************************************************************************

wiringPi Setup:
http://wiringpi.com/download-and-install/

wiringPi SPI API:
https://projects.drogon.net/raspberry-pi/wiringpi/spi-library/

Build Instructions:
>  g++ image_dump.cpp -lwiringPi

Run With:
> ./a.out

******************************************************************************/
#include<fstream>
#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>

using namespace std;

/* Chip Select */
static const int CHANNEL = 1;

int main() {

    /* SPI Buffer */
    int fd;
    unsigned char buffer[100];
    
    /* Set Speed Here */
    fd = wiringPiSPISetup(CHANNEL, 2000000);


   /* Open Image File */
    ifstream photo;    
    photo.open("image.ppm", ios::binary|ios::in);
   
    /* Get Length */
    photo.seekg (0, photo.end);
    int length = photo.tellg();
    photo.seekg (0, photo.beg);
    
    /* Voimit File */
    for(int i=0; i<length; i+=100){

        /* Read Byte */
        photo.read((char *)buffer, 100);

        /* Write Buffer */
        wiringPiSPIDataRW(CHANNEL, buffer, 100);
    }
    
    photo.close();

    return 0;  

}
