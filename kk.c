#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
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
        //printf("%" PRIu64 "\n", array[i]); 
        i++;                 
    }
    
}

uint64_t check_residue(uint64_t array[], uint64_t int_array[], int n){
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;
    uint64_t residue = 0;   

    for (int i = 0; i < n; i++){
        if (int_array[i] == 0){
            sum1 = sum1 + array[i];
        }
    }
    for (int i = 0; i < n; i++){
        if (int_array[i] == 1){
            sum2 = sum2 + array[i];
        }  
    }   
   /* if (sum1 > sum2){
        residue = sum1 - sum2;
    } 
    else{
        residue = sum2 - sum1;
    }*/
    residue = abs(sum1 - sum2);
    return residue;
}


uint64_t c_rr(uint64_t array[], int n, int max_iter){
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
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand() % 2;
        }
        x = check_residue(array, rand_array, n);
           //printf("x: %" PRIu64 "\n", x); 
        y = check_residue(array, rand_array2, n);
             //  printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        //printf("residue: %" PRIu64 "\n", residue); 
    }
    return residue;
}

uint64_t c_hill(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    uint64_t residue = 0;
    uint64_t x;
    uint64_t y;
    int rand_change = 0;
    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % 2;
    }
    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand() % 2;
        }
        rand_change = rand() % 2;
        rand_array2[rand_change] = rand () % n;
        x = check_residue(array, rand_array, n);
           //printf("x: %" PRIu64 "\n", x); 
        y = check_residue(array, rand_array2, n);
           //printf("y: %" PRIu64 "\n", y); 
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
            residue = y;
        }
        else {
            residue = x;
        }
        //printf("residue: %" PRIu64 "\n", residue); 
    }
    return residue;
}

uint64_t rand_sim_a(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    int rand_array3[n];
    uint64_t residue = 0;

    uint64_t x = 0;
    uint64_t y = 0;
    uint64_t z = 0;
    
    long double exp_result = 0;
    long double exp_result1 = 0;
    long double iter_change = 0;
    long double iter_rand = 0;
    int rand_change = 0;

    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % 2;
    }
    memcpy(rand_array3, rand_array, sizeof(rand_array));
    for (double iter = 0; iter < max_iter; iter++){
        // Random neighbor
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
        }
        rand_change = rand() % 2;
        rand_array2[rand_change] = rand () % 2;
        
        x = check_residue(array, rand_array, n);
        y = check_residue(array, rand_array2, n);
        z = check_residue(array, rand_array3, n);
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
        }
        else {
            iter_rand = rand() % 2;
            exp_result = -1*((y-x)/((pow(10,10))*pow(0.8,(floor(iter/300)))));
            exp_result1 = exp(exp_result);
            if (iter_rand > exp_result1){
                memcpy(rand_array, rand_array2, sizeof(rand_array));
            } 

        }
        if (x < z){
            memcpy(rand_array3, rand_array, sizeof(rand_array));
        }
        residue = z; 
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
    residue = karmakar_karp(array, n);
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
    }
    return residue;
}


uint64_t sim_a(uint64_t array[], int n, int max_iter){
    time_t t;
    srand((unsigned) time(&t));
    int rand_array[n];
    int rand_array2[n];
    int rand_array3[n];
    uint64_t residue = 0;

    uint64_t x = 0;
    uint64_t y = 0;
    uint64_t z = 0;
    
    long double exp_result = 0;
    long double exp_result1 = 0;
    long double iter_change = 0;
    long double iter_rand = 0;
    int rand_change = 0;

    for (int i = 0; i < n; i++){
        rand_array[i] = rand() % n;
    }
    memcpy(rand_array3, rand_array, sizeof(rand_array));
    for (double iter = 0; iter < max_iter; iter++){
        // Random neighbor
        for (int i = 0; i < n; i++){
            rand_array2[i] = rand_array[i];
        }
        rand_change = rand() % n;
        rand_array2[rand_change] = rand () % n;
        
        x = partition(array, rand_array, n);
        y = partition(array, rand_array2, n);
        z = partition(array, rand_array3, n);
        if (y < x){
            memcpy(rand_array, rand_array2, sizeof(rand_array));
        }
        else {
            iter_rand = rand() % 2;
            exp_result = -1*((y-x)/((pow(10,10))*pow(0.8,floor((iter/300)))));
            exp_result1 = exp(exp_result);
            if (iter_rand > exp_result1){
                memcpy(rand_array, rand_array2, sizeof(rand_array));
            } 

        }
        if (x < z){
            memcpy(rand_array3, rand_array, sizeof(rand_array));
        }
        residue = z; 
    }
    return residue;
}



int main(int argc, char *argv[]){
    
    FILE *fp = fopen(argv[1], "r");


    int n = 100;
    uint64_t array[n];
    uint64_t num;
    read_file(array, fp, n);


    clock_t t = clock();
    
    uint64_t b = karmakar_karp(array, n);    
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    float the_time = (float)t/CLOCKS_PER_SEC;
    printf("KK: %f seconds \n", the_time);
    printf("KK: %" PRIu64 "\n", b); 


    uint64_t d = c_rr(array, n, 25000);    
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("RR S: %f seconds \n", the_time);
    printf("RR S: %" PRIu64 "\n", d);   
    

    uint64_t a = rand_partition(array, n, 25000);
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("RR P: %f seconds \n", the_time);
    printf("RR P: %" PRIu64 "\n", a); 
    //uint64_t k = check(array, n, 25000);
    

    uint64_t e = c_hill(array, n, 25000);
     t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("Hill S: %f seconds \n", the_time);
    printf("Hill S: %" PRIu64 "\n", e); 
    
    uint64_t f = hill_climbing(array, n, 25000);   
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("Hill P: %f seconds \n", the_time);
    printf("Hill P: %" PRIu64 "\n", f); 
    
    uint64_t g = rand_sim_a(array, n, 25000);
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("Anneal S: %f seconds \n", the_time);
    printf("Anneal S: %" PRIu64 "\n", g);    


    uint64_t c = sim_a(array, n, 25000);   
    t = clock() - t; 
    // Time that elapsed to calculate the fibonacci nth number
    the_time = (float)t/CLOCKS_PER_SEC;
    printf("Anneal P: %f seconds \n", the_time);
    printf("Anneal P: %" PRIu64 "\n", c);      

    return 0;
}

