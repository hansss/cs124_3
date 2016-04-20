#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include "partition.h"
#include <time.h>
// mercen twister, seed implementation


void read_file(uint64_t array[], FILE* fp, int n){
    uint64_t bytes_read;
    size_t nbytes = 1000;
    uint64_t *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
 
    while ((read = getline(&line, &len, fp)) != -1 && i < n) {
        array[i] = atoll(line);
        //printf("%" PRIu64 "\n", array[i]); 
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

uint64_t random_residue_provide_soln(uint64_t array[], uint64_t soln[], int n){
    uint64_t set_A = 0;
    uint64_t set_B = 0;
    uint64_t residue;

    // for (int i = 0; i < n; i++){
    //     soln[i] = (rand() % 2);
    // }

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
        if (res_try < res_keep){
            res_keep = res_try;
        }
    }
    printf("res_keep %llu\n", res_keep);
    printf("res_try %llu\n", res_try);
    return res_keep;
}


uint64_t hillclimbing_random(uint64_t array[], int n,  int iterations){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % 2;
    }
    for (int iter = 0; iter < iterations; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
        }

        int rand_place = rand() % n;

        if (rand_array[rand_place] == 0){
            rand_array2[rand_place] = 1;
        }
        else{
            rand_array2[rand_place] = 0;
        }


        x = random_residue_provide_soln(array, rand_array, n);
                //printf("x: %" PRIu64 "\n", x); 
        y = random_residue_provide_soln(array, rand_array2, n);
                //printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
    }
    return residue;
}

uint64_t annealing_random(uint64_t array[], int n,  int iterations){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    int rand_array3[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % 2;
    }
    for (int iter = 0; iter < iterations; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
            rand_array3[i] = rand_array[i];
        }

        int rand_place = rand() % n;

        if (rand_array[rand_place] == 0){
            rand_array2[rand_place] = 1;
        }
        else{
            rand_array2[rand_place] = 0;
        }


        x = random_residue_provide_soln(array, rand_array, n);
                //printf("x: %" PRIu64 "\n", x); 
        y = random_residue_provide_soln(array, rand_array2, n);
                //printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
            // DOOOOOOOO
        }
        if (random_residue_provide_soln(array, rand_array, n) < array, rand_array3, n){
            memcpy(rand_array3, rand_array, sizeof(rand_array));
        }
    }
    return residue;
}





uint64_t karmakar_karp(uint64_t array2[], int n){
    uint64_t max = 0;
    uint64_t max2 = 0;
    int index1 = 0;
    int index2 = 0;
    uint64_t array[n];
    for (int i = 0; i < n; i++){
        array[i] = array2[i];
    }    
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


uint64_t partition(uint64_t array2[], int int_array[], int n){
    uint64_t sum = 0;
    uint64_t residue = 0;   
    int temp = 0;
    uint64_t array[n];
    for (int i = 0; i < n; i++){
        array[i] = array2[i];
    }   
    /*for (int i = 0; i < n; i++){
        printf("%llu  ", array[i]);            
    }
    printf("\n"); */
    for (int i = 0; i < n; i++){
        sum = 0;
        temp = int_array[i];
        for (int j = 0; j < n; j++){
            if (int_array[j] == temp) {
                sum = sum + array[j];
                array[j] = 0;
            }
        }
        array[i] = sum;
    }  
   /* for (int i = 0; i < n; i++){
        printf("%llu  ", array[i]);            
    }
    printf("\n"); */    
    residue = karmakar_karp(array, n);
      //  printf("Residue: %" PRIu64 "\n", residue); 
    return residue;
}

uint64_t rand_partition(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % n;
    }
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand() % n;
        }
        x = partition(array, rand_array, n);
           printf("x: %" PRIu64 "\n", x); 
        y = partition(array, rand_array2, n);
               printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        printf("residue: %" PRIu64 "\n", residue); 
    }
    return residue;
}

uint64_t hill_climbing(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    int rand_change = 0;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % n;
    }
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
        }
        rand_change = rand() % n;
        rand_array2[rand_change] = rand () % n;
        x = partition(array, rand_array, n);
               // printf("x: %" PRIu64 "\n", x); 
        y = partition(array, rand_array2, n);
               // printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        //printf("residue: %" PRIu64 "\n", residue); 
        //printf("residue: %i\n", residue);
        //printf("x: %i, y: %i\n", x, y);
    }
    return residue;
}


uint64_t sim_a(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    int rand_change = 0;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % n;
    }
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
        }
        rand_change = rand() % n;
        rand_array2[rand_change] = rand () % n;
        x = partition(array, rand_array, n);
                //printf("x: %" PRIu64 "\n", x); 
        y = partition(array, rand_array2, n);
                //printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        //printf("residue: %" PRIu64 "\n", residue); 
        //printf("residue: %i\n", residue);
        //printf("x: %i, y: %i\n", x, y);
    }
    return residue;
}



int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));

    // int n = 5;
    
    FILE *fp = fopen("numbers5.txt", "r");

    int n = 100;
    uint64_t array[n];
    uint64_t num;
    read_file(array, fp, n);

/*
    uint64_t k = karmakar_karp(array, n);
    printf("Karmakar Check: %llu\n", k);

    uint64_t check = repeated_random(array, n, 25000);
    printf("Repeated Random Check: %llu\n", check);

    uint64_t hcr = hillclimbing_random(array, n, 25000);
    printf("Hillclimbing Random Check: %llu\n", hcr);

    uint64_t kk_rand = rand_partition(array, n, 25000);
    printf("Repeated Rand KK: %llu\n", kk_rand);*/

    // uint64_t random_test = random_residue(array, n);
    

    //uint64_t random_test = random_residue(array, n);
    //uint64_t data_array[5] = {3,4,5,5,1};
    uint64_t k = rand_partition(array, n, 25000);
    //uint64_t k = hill_climbing(array, n, 25000);
    //uint64_t k = karmakar_karp(array, n);
    printf("Hi: %llu\n", k);


    return 0;




}





