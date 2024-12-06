#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

    // If the list is empty, set head to the new node
    if (*head == NULL) {
        *head = newNode;
        return *head;
    }

    // Traverse to the end of the list
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return *head;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
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

int main(int argc, char * argv[]){
    FILE *fp = fopen(argv[1], "r");    
    assert(fp != NULL);
    
    char line[50]; 
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
    //Read page ordering rules 
    while (fgets(line, sizeof(line), fp)) { 
        //printf("%s\n",line);
        if(strcmp(line, "\n") == 0){
            break;
        }
        char *token = strtok(line,"|");
        int pos  = strtol(token, &end, 10);
        token = strtok(NULL,"|");
        int rule  = strtol(token, &end, 10);
        printf("%d | %d\n",pos,rule);
        append(&rules[pos], rule);
        

    } 
    for (int i = 0; i < ruleSize; i++) {
        if(rules[i] != NULL){
            printf("Linked list at index %d: ", i);
            printList(rules[i]);
        }
    }
    //read pages
    int middlePageNumberSum =0;
    while (fgets(line, sizeof(line), fp)) { 
        while(strtok(line,",") != NULL){
            //convert each line into its own LL 
            
        }
        //navigate through the LL checking if theres a rule. Then go through each next checking
        //if it exists i??TBD
    } 
    
    fclose(fp);
    // Free all linked lists
    for (int i = 0; i < ruleSize; i++) {
        freeList(rules[i]);
    }

    // Free the array of pointers
    free(rules);
    return 0;
} 
