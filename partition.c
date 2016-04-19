#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include "partition.h"
#include <time.h>


void read_file(uint64_t array[], FILE* fp, int n){
    uint64_t bytes_read;
    size_t nbytes = 64;
    uint64_t *line;
 
    line = (uint64_t *) malloc(nbytes);

    for(int i=0; i<n; i++) {
        bytes_read = getline(&line, &nbytes, fp);
        array[i] = atoi(line);
    }

}



uint64_t karmakar_karp(uint64_t ints_array[], int n_of_ints){


}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    
    FILE *fp = fopen("numbers.txt", "r");

    int n = 100;
    uint64_t ints_array[n];
    uint64_t num;

    read_file(ints_array, fp, n);
    for(int i=0; i<n; i++) {
        num = (num << 32) | rand();
        printf("%llu\n", ints_array[i]);
    }

    karmakar_karp(ints_array, n);



}


//GET MAX

//




