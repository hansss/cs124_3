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



uint64_t karmakar_karp(uint64_t array[], int n){
    uint64_t max = array[1];
    uint64_t max2 = array[1];
    int index1 = 0;
    int index2 = 0; 
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if (max < array[i]){
                max = array[i];
                index1 = i;
            }
        }
        array[index1] = 0;
        for (int i = 0; i < n; i++){
            if (max2 < array[i]){
                max2 = array[i];
                index2 = i;
            }
        }
        array[index2] = 0;
        array[index1] = max - max2;
    
    }
}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    
    FILE *fp = fopen("numbers.txt", "r");

    int n = 100;
    uint64_t ints_array[n];
    uint64_t num;

    read_file(ints_array, fp, n);

    karmakar_karp(ints_array, n);

}





