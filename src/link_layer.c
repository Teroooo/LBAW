// Link layer protocol implementation

#include "link_layer.h"
#include "serial_port.h"
#include <fcntl.h>
#include <stdio.h>



// MISC
#define _POSIX_SOURCE 1 // POSIX compliant source
#define BUF_SIZE 5

////////////////////////////////////////////////
// LLOPEN
////////////////////////////////////////////////
int llopen(LinkLayer connectionParameters)
{
    if (openSerialPort(connectionParameters.serialPort,
                       connectionParameters.baudRate) < 0)
    {
        return -1;
    }
    
    
    if(connectionParameters.role== LlTx){
        unsigned char F= 0x7E;
        unsigned char A= 0x03;
        unsigned char C= 0x00;
        unsigned char BCC1= A^C;
    
        unsigned char informationFrames[BUF_SIZE]={F,A,C,BCC1,F};
        int nBytes = writeBytesSerialPort(informationFrames,BUF_SIZE);
        printf("%d bytes written\n", nBytes);
        if(nBytes<5){
            printf("error");
        }
        return 0;
    }
    else if (connectionParameters.role==LlRx){
        volatile int STOP = FALSE;
        unsigned char buf[5 + 1] = {0}; // +1: Save space for the final '\0' char
        int counter=0;
        while (STOP == FALSE)
        {
            counter++;
            // Returns after 5 chars have been input
            int byte=readByteSerialPort( buf);
            if (byte<1)
                return byte;
            
            
            if(counter==5){
                buf[counter] = '\0'; // Set end of string to '\0', so we can printf
                printf(":%s:%d\n", buf, counter);
                STOP = TRUE;
            }
        }
        return 0;

    }
    else
        return -1;
}

////////////////////////////////////////////////
// LLWRITE
////////////////////////////////////////////////
int llwrite(const unsigned char *buf, int bufSize)
{
    // TODO

    return 0;
}

////////////////////////////////////////////////
// LLREAD
////////////////////////////////////////////////
int llread(unsigned char *packet)
{
    // TODO

    return 0;
}

////////////////////////////////////////////////
// LLCLOSE
////////////////////////////////////////////////
int llclose(int showStatistics)
{
    // TODO

    int clstat = closeSerialPort();
    return clstat;
}
