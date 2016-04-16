#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void read_file(int array[], FILE* fp, int n){
    int bytes_read;
    size_t nbytes = 32;
    char *line;
 
    line = (char *) malloc(nbytes);

    for(int i=0; i<n; i++) {
        bytes_read = getline(&line, &nbytes, fp);
        array[i] = atoi(line);
    }

}


int main(){//int argc, char *argv[]){
    FILE *fp = fopen("numbers.txt", "r");
    int array[100];
    read_file(array, fp, 100);
    for(int i=0; i<10; i++) {
        printf("%i\n", array[i]);
    }
}


