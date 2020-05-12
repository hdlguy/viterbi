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

using namespace std;

int main () 
{

    // read waas LLR file
    printf("opening waas.bin\n");
    FILE* fp = fopen("waas.bin", "r");
    // get the file size.
    struct stat stat_buf;
    fstat(fileno(fp), &stat_buf);
    off_t filesize = stat_buf.st_size;
    printf("filesize = %ld\n", filesize);

    uint8_t* waasdat = (uint8_t*)malloc((size_t) 1*filesize);
    fread(waasdat, 1, filesize, fp);


    // convert LLR data to string, two symbols per byte
    char* waassym = (char*)malloc((size_t) 2*filesize);
    for (int i=0; i<filesize; i++){
        if (1 == ((waasdat[i])>>2)&1) waassym[i*2+0] = '1'; else waassym[i*2+0] = '0';
        if (1 == ((waasdat[i])>>6)&1) waassym[i*2+1] = '1'; else waassym[i*2+1] = '0';
    }
    string bits (waassym, (size_t)(filesize*2));  // ViterbiCodec::Decode wants C++ string.
    //bits.insert(0,1,'0'); // insert a zero at beginning to get other framing.

    //char waassym[] = {'0','0','0','0','1','1','1','0','1','1','1','1','1','1','1','1','0','0','1','1','0','0','0','1','1','1','0','0','0','0','0','0'};
    //string bits (waassym, (size_t)32);

    //string bits = "00001110111111110011000111000000";

    // set the Viterbi constraint length and polynomials.
    cout << "bits.length() = " << bits.length() << "\n";
    const int constraint = 7;
    vector<int> polynomials;
    polynomials.push_back(121);  // G1
    polynomials.push_back( 91);  // G2
    for (int i = 0; i < polynomials.size(); i++) polynomials[i] = ReverseBits(constraint, polynomials[i]);

    // call the Viterbi decoder
    ViterbiCodec codec(constraint, polynomials);
    string result_string = codec.Decode(bits);
    //std::cout << bits << std::endl;
    //std::cout << result_string << std::endl;

    // preamble patterns (if not found rerun Viterbi with other two bit framing)
    string p_a("01010011"); string p_b("10011010"); string p_c("11000110");

/*
    // faux preamble words
    for (int i=0; i<result_string.length()/750; i++) {
        result_string.replace(i*750+  0, 8, p_a);
        result_string.replace(i*750+250, 8, p_b);
        result_string.replace(i*750+500, 8, p_c);
    }
*/

    cout << "searching for preamble patterns in positive results\n";
    for (int i=0; i<result_string.length()-750; i++) {
        if ( (0==result_string.substr(i+0,8).compare(p_a)) && (0==result_string.substr(i+250,8).compare(p_b)) && (0==result_string.substr(i+500,8).compare(p_c)) ) {
            cout << "p_a, p_b and p_c found at: " << i << '\n'; 
        }
    }

    // make copy of bits and negate it
    string negbits (bits); 
    for (int i=0; i<negbits.length(); i++) if (negbits[i]=='0') negbits[i]='1'; else negbits[i]='0';
    // run viterbi decoder
    //std::cout << negbits << std::endl;
    result_string = codec.Decode(negbits);

    cout << "searching for preamble patterns in negative results\n";
    for (int i=0; i<result_string.length()-750; i++) {
        if ( (0==result_string.substr(i+0,8).compare(p_a)) && (0==result_string.substr(i+250,8).compare(p_b)) && (0==result_string.substr(i+500,8).compare(p_c)) ) {
            cout << "p_a, p_b and p_c found at: " << i << '\n'; 
        }
    }

    
    // parse messages


    // write messages to file

    
    free(waasdat);
    free(waassym);
}




