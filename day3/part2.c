#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int valid(char * input, int len){
    char start[]="mul(";
    int startlen = strlen(start);
    if(strncmp(input,start,startlen)!=0){
        return -1;
    }
    if(input[len-1] != ')'){
        return -1;
    } 
    char delimeter[2]=",";
    char *token = strtok(input+startlen,delimeter);
    char *c;
    int first = strtol(token,&c,10);
    
    token = strtok(NULL,delimeter);
    if(token == NULL){
        return -1;
    }
    token[strlen(token)-1] = '\0'; //remove trailing ')'
    int second = strtol(token,&c,10);
    if(first == 0L || second == 0L){
        return -1;
    }
    if(first >999 || second > 999){
        return -1;
    }
    return first*second; 
}

int main(int argc, char * argv[]){
    FILE *fptr;

    fptr = fopen(argv[1], "r"); 
    assert(fptr != NULL);
    int res=0;
    bool enableInstructions=true;
    char myString[3600];
    while(fgets(myString, 3600, fptr)){
        //printf("%s\n", myString);
        int size = strlen(myString);
        int result = -1;
        int right= 1;//minimum length of a valid string is 8
        for(int left=0;left<size-8;++left){
            while(result == -1){
                int size = right-left;
                if( size>12){
                    break;
                }
                char substring[13]=""; 
                strncpy(substring, myString+left,size);
                substring[12] = '\0';
                if(strncmp(substring, "do()",4)==0){
                    enableInstructions = true;
                } 
                if(strncmp(substring, "don't()",6) ==0 ){
                    enableInstructions = false;
                } 
                result = valid(substring,size);
                ++right; 
            }
            if(result != -1 ){
                if(enableInstructions){
                    res = res+result;
                }
                result = -1;
            }
            right = left;
        }
    }
    printf("%d\n",res);
    fclose(fptr);
} 
