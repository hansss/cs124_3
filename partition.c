#define _GNU_SOURCE
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
    size_t nbytes = 1000;
    uint64_t *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
 
    while ((read = getline(&line, &len, fp)) != -1 && i < n) {
        array[i] = atoll(line);
        printf("%" PRIu64 "\n", array[i]); 
        i++;                 
    }
    
    /*uint64_t bytes_read;
    size_t nbytes = 1000;
    uint64_t *line = NULL;
 
    line = (uint64_t *) malloc(nbytes);

    for(int i=0; i<n; i++) {
        bytes_read = getline(&line, &nbytes, fp);
        printf("%" PRIu64 "\n", &line);                   
        array[i] = atoi(line);
        printf("%" PRIu64 "\n", array[i]);                   
    }*/

}



uint64_t karmakar_karp(uint64_t array[], int n){
    uint64_t max = 0;
    uint64_t max2 = 0;
    int index1 = 0;
    int index2 = 0;                              
    for (int j = 0; j < n; j++){
        max = 0;
        max2 = 0;
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
       /* for (int i = 0; i < n; i++){
            printf("%llu", array[i]);            
        }*/
       // printf("\n");            
    
    }
    
   /* printf("max1: %llu\n", max);
    printf("max2: %llu\n", max2);
    printf("index1: %i\n", index1);
    printf("index2: %i\n", index2);*/
    return max - max2;
}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    
    FILE *fp = fopen("numbers.txt", "r");

    int n = 100;
    uint64_t array[n];
    uint64_t num;

    read_file(array, fp, n);
    
    //printf("%llu\n", array[0]);   
    //printf("%llu\n", array[1]);
    //uint64_t array[2] = {7189431831007297, 105449836377296722};
    uint64_t k = karmakar_karp(array, n);
    printf("Hi: %llu\n", k);
    return 0;

}





