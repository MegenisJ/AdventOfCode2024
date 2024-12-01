#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int countLines(char* fileName){
    int lines = 0;
    char ch;
    FILE *fptr = fopen(fileName, "r");
    assert(fptr != NULL);
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(fptr);
    printf("Size of input file : %d \n",lines);
    return lines;
}

int compare (const void * a, const void * b){
    return (*(int*)a - *(int*)b);
}

int main (){
    printf("Hello world");
    FILE *fptr;
    const char s[2] = " ";  
    int size = countLines("input.txt");

    fptr = fopen("input.txt", "r"); 
    assert(fptr != NULL);

    int col1[size];
    int col2[size];

    char myString[50];
    int line = 0;
    while(fgets(myString, 50, fptr)){
        char *token = strtok(myString,s);
        char *end;
        col1[line] = strtol(token, &end, 10);
        token = strtok(NULL,s);

        col2[line] = strtol(token, &end, 10);
        ++line;
    }

    qsort(col1, size, sizeof(int),compare);
    qsort(col2, size, sizeof(int),compare);

    int res = 0;
    for(int x =0;x<size;x++){
        int diff = col1[x] - col2[x];
        if(diff <0){
            diff = -diff;
        }
        res = res + diff; 
    }

    printf("Total distance: %d \n", res);

    fclose(fptr);
} 
