#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include "partition.h"
#include <time.h>


void read_file(uint64_t array[], FILE* fp, int n){
    int bytes_read;
    size_t nbytes = 32;
    char *line;
 
    line = (char *) malloc(nbytes);

    for(int i=0; i<n; i++) {
        bytes_read = getline(&line, &nbytes, fp);
        array[i] = atoi(line);
    }

}


int main(){//int argc, char *argv[]){
    FILE *fp = fopen("numbers.txt", "r");
    uint64_t ints_array[100];
    read_file(ints_array, fp, 100);
    for(int i=0; i<100; i++) {
        printf("%llu\n", ints_array[i]);
    }

    // Make random numbers in text file 64 bit unsigned ints
    // uint64_t t;
}


//GET MAX

//

// int karmakar_karp(uint){


// }


