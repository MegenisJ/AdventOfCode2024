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
    return lines;
}

//Returns count of an int from a sorted list of int
int getCount(int i,int* list, int size){
    int count =0;
    for (int a=0; a<size;a++){
        if(i == list[a]){
            ++count;
        }
    }
    return count; 
}

int main(int argc, char * argv[]){
    char* filename = argv[1];
    FILE *fptr;
    const char s[2] = " ";  
    int size = countLines(filename);
    fptr = fopen(filename, "r"); 
    assert(fptr != NULL);
    printf("Size of input file : %d \n",size);
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
        int input = col1[x];
        int count = getCount(input,col2,size); 
        res = res + (input * count );
    }
    printf("Total distance: %d \n", res);

    fclose(fptr);
} 
