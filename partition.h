#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include <time.h>

void read_file(uint64_t array[], FILE* fp, int n);
uint64_t karmakar_karp(uint64_t ints_array[], int n_of_ints);
uint64_t random_residue(uint64_t array[], int n);

