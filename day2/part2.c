#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool safe(int* arr, int len){
    bool sortedAsc = true;
    bool sortedDesc = true;
    for(int x=0;x<len-1;x++){
        if(arr[x] > arr[x+1]){
           sortedDesc = false;
        }

        if(arr[x] < arr[x+1]){
            sortedAsc = false;
        }

        int distance =arr[x] - arr[x+1];
        if(distance<0){
            distance = -distance;
        }
        if(distance <1 || distance > 3){
            return false;
        }
    }
    return (sortedAsc|| sortedDesc);
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
        if(safe(tokens,i)){
            ++res;
            continue;
        }
        for(int x=0;x<=i;++x){ 
            int temp_arr[i-1];

            //Create an array missing [x] char
            for (int j=0;j<i;++j){
                if(j>=x){
                    temp_arr[j] = tokens[j+1];
                    continue;
                }
                temp_arr[j] = tokens[j];
            }

            if(safe(temp_arr, i-1)){
                ++res;
                break;
            }
        }
    }
    printf("%d\n",res);
    fclose(fptr);
} 
