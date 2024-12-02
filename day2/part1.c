#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool sortedDesc(int* arr, int len){
    for(int x=0;x<len-1;++x){
        if(arr[x] > arr[x+1]){
            return false;
        }
    }
    return true;
}

bool sortedAsc(int* arr, int len){
    for(int x=0;x<len-1;++x){
        if(arr[x] < arr[x+1]){
            return false;
        }
    }
    return true;
}

bool closeValues(int* arr, int len){
    for(int x=0;x<len-1;x++){
        int distance =arr[x] - arr[x+1];
        if(distance<0){
            distance = -distance;
        }
        if(distance <1 || distance > 3){
            return false;
        }
    }
    return true;
}

int main(int argc, char * argv[]){
    FILE *fptr;

    fptr = fopen(argv[1], "r"); 
    assert(fptr != NULL);
    int res=0;

    char myString[50];
    while(fgets(myString, 50, fptr)){
        char *end;
        int tokens[10];
        char *delimeter = " ";
        int i = 0;
        char *token = strtok(myString,delimeter);
        while(token != NULL){
            int v = strtol(token, &end, 10);
            tokens[i++] = v;
            token = strtok(NULL,delimeter);
        }

        if( (sortedDesc(tokens, i)  || sortedAsc(tokens,i))
                && closeValues(tokens, i) ){
            ++res;
        }
    }
    printf("%d\n",res);
    fclose(fptr);
} 
