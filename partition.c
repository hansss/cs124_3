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

    int n = 100;
    uint64_t array[n];
    uint64_t num;

<<<<<<< HEAD
    read_file(ints_array, fp, n);
    uint64_t array[9] = {1,4,5,2,10,18,9,7,2};
    n = 9;



    uint64_t random_test = random_residue(array, n);
    printf("Random Residue Out: %llu\n", random_test);
    // uint64_t k = karmakar_karp(array, n);
    // printf("Hi: %llu \n", k);
    
=======
    read_file(array, fp, n);
    
    //printf("%llu\n", array[0]);   
    //printf("%llu\n", array[1]);
    //uint64_t array[2] = {7189431831007297, 105449836377296722};
    uint64_t k = karmakar_karp(array, n);
    printf("Hi: %llu\n", k);
>>>>>>> 35815b7c3d16980b2b2d2308b7f0340b66708ecc
    return 0;

}





