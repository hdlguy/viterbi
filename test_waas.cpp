#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>

int main () 
{

    // read waas LLR file
    printf("opening waas.bin\n");
    FILE* fp = fopen("waas.bin", "r");
    struct stat stat_buf;
    fstat(fileno(fp), &stat_buf);
    off_t filesize = stat_buf.st_size;
    printf("filesize = %ld\n", filesize);

    uint8_t* waasdat = (uint8_t*)malloc((size_t) 1*filesize);
    fread(waasdat, 1, filesize, fp);

    // convert LLR data to binary uint8_t data
    uint8_t* waassym = (uint8_t*)malloc((size_t) 2*filesize);
    for (int i=0; i<filesize; i++){
        waassym[i*2+0] = ((waasdat[i])>>2)&1;  // bit 2 of the low nibble
        waassym[i*2+1] = ((waasdat[i])>>6)&1;  // bit 2 of the high nibble
    }





    // call the Viterbi decoder

    
    // find sync pattern (if not found rerun Viterbi with other two bit framing)


    // parse messages


    // write messages to file

    
    free(waasdat);
    free(waassym);
}




