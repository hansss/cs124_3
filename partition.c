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
        if (res_try < res_keep){
            res_keep = res_try;
        }
    }
    printf("res_keep %llu\n", res_keep);
    printf("res_try %llu\n", res_try);
    return res_keep;
}


uint64_t hillclimbing_repeated(){

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
    for (int i = 0; i < n; i++){
        printf("%llu  ", array[i]);            
    }
    printf("\n"); 
    residue = karmakar_karp(array, n);
    return residue;
}

uint64_t rand_partition(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    int residue = 0;
    int x;
    int y;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % n;
    }
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand() % n;
        }
        x = partition(array, rand_array, n);
        y = partition(array, rand_array2, n);
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        printf("residue: %i\n", residue);
        printf("x: %i, y: %i\n", x, y);
    }
    return residue;
}


int main(){//int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    // int n = 5;
    
    FILE *fp = fopen("numbers.txt", "r");

    int n = 5;
    uint64_t array[n];
    uint64_t num;
    read_file(array, fp, n);


    uint64_t k = karmakar_karp(array, n);
    printf("Karmakar Check: %llu\n", k);

    uint64_t check = repeated_random(array, n, 50000);
    printf("Repeated Random Check: %llu\n", check);

    // uint64_t random_test = random_residue(array, n);
    



    return 0;




    /*
    FILE *fp = fopen("numbers.txt", "r");

    // int n = 100;
    // uint64_t array[n];
    uint64_t num;
    // read_file(array, fp, n);

    uint64_t array[9] = {1,4,5,2,10,18,9,7,2};
    int n = 9;
    */
    
    // Below is merge conflict code 
    
    /*read_file(array, fp, n);
    
    //printf("%llu\n", array[0]);   
    //printf("%llu\n", array[1]);
    //uint64_t array[2] = {7189431831007297, 105449836377296722};
    //uint64_t k = karmakar_karp(array, n);
    uint64_t data_array[5] = {10,8,3,6,4};
    int array[n];
    for (int i = 0; i < n; i++){
        array[i] = rand() % n;
    }
    for (int i = 0; i < n; i++){
        printf("%i  ", array[i]);
    }
    printf("\n");
    //uint64_t k = partition(data_array,array, n);
    //uint64_t k = karmakar_karp(data_array, n);
    uint64_t k = rand_partition(data_array, n, 25000);*/

    // uint64_t check = repeated_random(array, n, 2500);
    // printf("CHECK %llu\n", check);

    // uint64_t random_test = random_residue(array, n);
    

    //uint64_t k = karmakar_karp(array, n);
    //printf("Hi: %llu\n", k);

    return 0;

}





