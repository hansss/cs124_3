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

uint64_t random_residue(uint64_t array[], int n){
    int* soln = (int*) malloc(sizeof(int)*n);
    uint64_t set_A = 0;
    uint64_t set_B = 0;
    uint64_t residue;

    for (int i = 0; i < n; i++){
        soln[i] = (rand() % 2);
        printf("soln[i]: %llu\n", soln[i]);
    }

    for (int i = 0; i < n; i++){
        if (soln[i] == 0){
            set_A += array[i];
            printf("array[i]: %llu\n", array[i]);
            printf("set_A: %llu\n", set_A);
        }
        else{
            set_B += array[i];
            printf("set_B: %llu\n", set_B);
        }
    }

    residue = abs(set_A - set_B);
    printf("Random Residue In: %llu\n", residue);
    return residue;
}




uint64_t karmakar_karp(uint64_t array[], int n){

    uint64_t max = 0;
    uint64_t max2 = 0;
    int index1 = -1;
    int index2 = -1; 

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
        if (array[index1] > array[index2]){
            array[index2] = 0;
            array[index1] = max - max2;
        }
        else{
            array[index2] = max - max2;
            array[index1] = 0;  
        }

    
    }
    
    printf("max1: %llu\n", max);
    printf("max2: %llu\n", max2);
    printf("index1: %i\n", index1);
    printf("index2: %i\n", index2);
    return max - max2;
}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    
    FILE *fp = fopen("numbers.txt", "r");

    int n = 100;
    uint64_t ints_array[n];
    uint64_t num;

    read_file(ints_array, fp, n);
    uint64_t array[9] = {1,4,5,2,10,18,9,7,2};
    n = 9;



    uint64_t random_test = random_residue(array, n);
    printf("Random Residue Out: %llu\n", random_test);
    // uint64_t k = karmakar_karp(array, n);
    // printf("Hi: %llu \n", k);
    
    return 0;

}





