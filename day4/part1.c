#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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
int countCols(char * fileName){
    int cols= 0;
    size_t len = 0;
    FILE *fptr = fopen(fileName, "r");
    assert(fptr != NULL);
    char *line;
    getline(&line, &len, fptr);
    fclose(fptr);
    cols = strlen(line) - 1;
    printf("cols %d\n",cols);
    return cols;
}
int xmas_count(int MAX_ROWS,int MAX_COLS,char array[MAX_ROWS][MAX_COLS]){
    int count =0;
    for (int i = 0; i < MAX_ROWS; i++) { 
        for (int j = 0; j < MAX_COLS && array[i][j] != 0; j++) { 
            if(array[i+0][j+0] == 'X'){
                if(j+3 < MAX_COLS)
                    if(array[i+0][j+1] == 'M')
                    if(array[i+0][j+2] == 'A')
                    if(array[i+0][j+3] == 'S')
                        count++;
                if(i+3 < MAX_ROWS)
                        if(array[i+1][j+0] == 'M')
                        if(array[i+2][j+0] == 'A')
                        if(array[i+3][j+0] == 'S')
                            count++;
                if(i+3 < MAX_ROWS && j+3 < MAX_COLS)
                        if(array[i+1][j+1] == 'M')
                        if(array[i+2][j+2] == 'A')
                        if(array[i+3][j+3] == 'S')
                            count++;
                if(i+3 < MAX_ROWS && j-3 >= 0)
                        if(array[i+1][j-1] == 'M')
                        if(array[i+2][j-2] == 'A')
                        if(array[i+3][j-3] == 'S')
                            count++;
            }
            else if(array[i+0][j+0] == 'S'){
                if(j+3 < MAX_COLS)
                    if(array[i+0][j+1] == 'A')
                    if(array[i+0][j+2] == 'M')
                    if(array[i+0][j+3] == 'X')
                        count++;
                if(i+3 < MAX_ROWS)
                    if(array[i+1][j+0] == 'A')
                    if(array[i+2][j+0] == 'M')
                    if(array[i+3][j+0] == 'X')
                        count++;
                if(i+3 < MAX_ROWS && j+3 < MAX_COLS)
                    if(array[i+1][j+1] == 'A')
                    if(array[i+2][j+2] == 'M')
                    if(array[i+3][j+3] == 'X')
                        count++;
                if(i+3 < MAX_ROWS && j-3 >= 0)
                        if(array[i+1][j-1] == 'A')
                        if(array[i+2][j-2] == 'M')
                        if(array[i+3][j-3] == 'X')
                            count++;
            }
        } 
    }
    return count;
}

int x_mas_count(int MAX_ROWS,int MAX_COLS,char array[MAX_ROWS][MAX_COLS]){
    int count =0;
    for (int i = 1; i < MAX_ROWS-1; i++) { 
        for (int j = 1; j < MAX_COLS-1 && array[i][j] != 0; j++) { 
            if(array[i+0][j+0] == 'A'){
                if(((array[i+1][j+1] == 'M' && array[i-1][j-1]== 'S') ||
                    (array[i+1][j+1] == 'S' && array[i-1][j-1]== 'M')) && 

                    ((array[i+1][j-1] == 'M' && array[i-1][j+1]== 'S') ||
                    (array[i+1][j-1] == 'S' && array[i-1][j+1]== 'M'))){

                        ++count;
                     }
            }
        } 
    }
    return count;
}
int main(int argc, char * argv[]){
    int MAX_ROWS= countLines(argv[1]);
    int MAX_COLS = countCols(argv[1]);
    FILE *fp = fopen(argv[1], "r");    
    assert(fp != NULL);
    char line[256]; 
    char array[MAX_ROWS][MAX_COLS]; 
    int row = 0;
    // Read the file line by line 
    while (fgets(line, sizeof(line), fp) && row < MAX_ROWS) { 
        for (int x=0;x<=MAX_COLS-1;++x){ 
            array[row][x] = line[x]; 
        } 
        row++; 
    } 
 
    fclose(fp);
    int count = xmas_count(MAX_ROWS,MAX_COLS,array);
    printf("part1:%d\n",count); 
    count = x_mas_count(MAX_ROWS,MAX_COLS,array);
    printf("part2:%d\n",count); 
    return 0;
} 
