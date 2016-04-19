#include <stdio.h>
#include <stdlib.h>
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


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    /*for (int i=0; i< 10; i++) {
        printf("%d\n", rand() % 50);
    }*/
    
    FILE *fp = fopen("numbers.txt", "r");
    uint64_t array[100];
    read_file(array, fp, 100);
   
    uint64_t num;
    
    for (int i=0; i< 100; i++) {
        num = (num << 32) | rand();
        //num = num % 18446744073709551615;
        //num = num % 9223372036854775807;
        printf("%llu\n", num);
    }
   
    /*for(int i=0; i<25; i++) {
        printf("%ld\n", array[i]);
    }*/

}


