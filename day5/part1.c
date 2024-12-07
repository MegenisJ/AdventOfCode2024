#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Append to the linked list
Node* append(Node **head, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return *head;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return *head;
}

// Free the linked list
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int middleValue(Node *head){
    int count=0;
    Node *current = head;
    while(current != NULL){
        ++count;
        current = current->next;
    }
    int middlePos = (count/2) + 1; // c rounds down 😺
    current = head;
    for(int x=0;x<middlePos-1;++x){ 
        current = current->next;
    }
    return current->data;
}
//Assumes value exists in pages 
//returns 0 if no rule broke, returns value in wrong place if broken
int isValid(Node *pages,int value, Node *rule){
    Node *current = pages;
    while(current->data !=value){
        Node *r =rule;
        while(r != NULL){
            if(current->data == r->data){
                return current->data;
            }
            r = r->next;
        }
        current = current->next;
    }

    return 0;
}
//swap nodes with given values 
void swapNodes(struct Node** head, int x, int y) {
    printf("Swapping %d and  %d\n",x,y);
    if (x == y) return;

    struct Node *prevX = NULL, *currX = *head;
    while (currX && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }

    struct Node *prevY = NULL, *currY = *head;
    while (currY && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }

    if (!currX || !currY) return;

    if (prevX){
        prevX->next = currY;
    }
    else{
        *head = currY;
    }
    if (prevY){
        prevY->next = currX;
    }
    else{
        *head = currX;
    }
    struct Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main(int argc, char * argv[]){
    FILE *fp = fopen(argv[1], "r");    
    assert(fp != NULL);
    
    char line[100]; 
    int rule_count =0;
    while(fgets(line, sizeof(line),fp)){
        if(strcmp(line, "\n") == 0){
            break;
        }
        ++rule_count;
    }
    rewind(fp);
    printf("Rule Count %d\n",rule_count);
    int ruleSize = 100;
    Node **rules = malloc(ruleSize*sizeof(Node));
    assert(rules != NULL);
    for(int i =0;i<ruleSize;i++){
        rules[i] = NULL;
    }
    
    char * end;
    char * del = "|";
    //Read page ordering rules 
    while (fgets(line, sizeof(line), fp)) { 
        if(strcmp(line, "\n") == 0){
            break;
        }
        char *token = strtok(line,del);
        int pos  = strtol(token, &end, 10);
        token = strtok(NULL,del);
        int rule  = strtol(token, &end, 10);
        append(&rules[pos], rule);
    } 

    int middlePageNumberSum =0;
    int sortedPagesSum=0;
    char *delimeter = ",";
    while (fgets(line, sizeof(line), fp)) { 
        printf("%s\n",line);
        char *token = strtok(line,delimeter);
        Node *pages = NULL;
        while(token != NULL){
            int t  = strtol(token, &end, 10);
            append(&pages, t);
            token = strtok(NULL, delimeter);
        }
        bool valid_update = true;   
        Node *current = pages;
        while(current != NULL){
            int x = current->data;
            if(rules[x] != NULL && isValid(pages,x,rules[x])!=0){
                valid_update = false;
            }
            current = current->next;
        }
        int m = middleValue(pages);
        if(valid_update){
            middlePageNumberSum += m;
            continue;
        }

        int sorted = false;
        Node *a = pages; //stores the list as its sorted
        while(sorted == false){
            sorted = true;
            Node * temp = a; // used to loop through all the nodes in the sorted list
            while(temp != NULL){ //find the index for every rule that applies 
                int x = temp->data;
                if(rules[x] != NULL){ // if not valid swap positions
                    int invalid = isValid(a, x, rules[x]);
                    if(invalid !=0){
                        swapNodes(&a, x,invalid );
                        sorted = false;
                    }
                }
                

                temp = temp ->next;
            }

        }
        printf("Sorted List "); 
        printList(a);
        int x = middleValue(a);
        sortedPagesSum += x;
        
    } 
    
    fclose(fp);
    // Free all linked lists
    for (int i = 0; i < ruleSize; i++) {
        freeList(rules[i]);
    }

    // Free the array of pointers
    free(rules);
    printf("Part1: %d\n",middlePageNumberSum);
    printf("Part2: %d\n",sortedPagesSum);
    return 0;
} 
