#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include <time.h>

void read_file(uint64_t array[], FILE* fp, int n);
int karmakar_karp(uint64_t ints_array[], int karmakar_karp_iter);
