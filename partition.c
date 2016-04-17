#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include

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


int main(){//int argc, char *argv[]){
    FILE *fp = fopen("numbers.txt", "r");
    uint64_t array[100];
    read_file(array, fp, 100);
    for(int i=0; i<10; i++) {
        printf("%i\n", array[i]);
    }
    //unsigned long long 
}


