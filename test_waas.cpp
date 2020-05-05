#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int main () 
{
    printf("opening waas.bin\n");
    FILE* fp = fopen("waas.bin", "r");
    struct stat stat_buf;
    fstat(fileno(fp), &stat_buf);
    off_t filesize = stat_buf.st_size;
    printf("filesize = %ld\n", filesize);
}




