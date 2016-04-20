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
    
}

uint64_t random_residue(uint64_t array[], int n){
    int* soln = (int*) malloc(sizeof(int)*n);
    uint64_t set_A = 0;
    uint64_t set_B = 0;
    uint64_t residue;

    for (int i = 0; i < n; i++){
        soln[i] = (rand() % 2);
    }

    for (int i = 0; i < n; i++){
        if (soln[i] == 0){
            set_A += array[i];
        }
        else{
            set_B += array[i];
        }
    }

    residue = abs(set_A - set_B);
    return residue;
}

uint64_t repeated_random(uint64_t array[], int n,  int iterations){
    printf("1array[1]: %llu\n", array[1]);
    uint64_t res_keep = random_residue(array, n);
    printf("2array[1]: %llu\n", array[1]);
    uint64_t res_try;
    int first = -1;


    for (int i = 1; i < iterations; i++){
        res_try = random_residue(array, n);
        x
        if (res_try < res_keep){
            res_keep = res_try;
        }
    }
    return res_keep;
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
    }
    
    return max - max2;
}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    
    FILE *fp = fopen("numbers.txt", "r");

    // int n = 100;
    // uint64_t array[n];
    uint64_t num;
    // read_file(array, fp, n);

    uint64_t array[9] = {1,4,5,2,10,18,9,7,2};
    int n = 9;

    uint64_t check = repeated_random(array, n, 2500);
    printf("CHECK %llu\n", check);

    // uint64_t random_test = random_residue(array, n);
    

    uint64_t k = karmakar_karp(array, n);
    printf("Hi: %llu\n", k);

    return 0;

}





