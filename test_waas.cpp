#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <stdint.h>
#include <cstdint>

#include <stdio.h>
#include <stdlib.h>

#include "viterbi.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    // convert LLR data to string
    char* waassym = (char*)malloc((size_t) 2*filesize);
    for (int i=0; i<filesize; i++){
        if (1 == ((waasdat[i])>>2)&1) waassym[i*2+0] = '1'; else waassym[i*2+0] = '0';
        if (1 == ((waasdat[i])>>6)&1) waassym[i*2+1] = '1'; else waassym[i*2+1] = '0';
    }
    //const std::string& bits = "00001110111111110011000111000000";
    //const std::string bits = "00001110111111110011000111000000";
    //const std::string bits ((size_t)(filesize*2), 'x');
    const std::string bits (waassym, (size_t)(filesize*2));  // ViterbiCodec::Decode wants C++ string.

    // set the Viterbi constraint length and polynomials.
    const int constraint = 7;
    std::vector<int> polynomials;
    polynomials.push_back(121);
    polynomials.push_back( 91);
    for (int i = 0; i < polynomials.size(); i++) polynomials[i] = ReverseBits(constraint, polynomials[i]);

    // call the Viterbi decoder
    ViterbiCodec codec(constraint, polynomials);
    //std::cout << codec.Decode(bits) << std::endl;
    std::string result_string = codec.Decode(bits);
    std::cout << result_string << std::endl;

    
    // find sync pattern (if not found rerun Viterbi with other two bit framing)


    // parse messages


    // write messages to file

    
    free(waasdat);
    free(waassym);
}




