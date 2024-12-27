#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//moves 
//evaluation 
int main(int argc, char * argv[]){
    FILE *fptr;

    fptr = fopen(argv[1], "r"); 
    assert(fptr != NULL);
    char line[100]; 
    int line_count = 0;
    while(fgets(line, sizeof(line),fp)){
        if(strcmp(line, "\n") == 0){
            break;
        }
        ++rule_count;
    }
    rewind(fp);
    printf("Part 1: %d\n",line_count);
    fclose(fptr);
} 
