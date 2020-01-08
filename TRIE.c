#include "TRIE.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0 , TRUE=1} boolean;
typedef struct node{
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    boolean is_last_letter;// if the node is a the last letter in the node.
    boolean has_kids;// if the node is a leaf or not.
}node;

typedef struct trie{
    node* current;
    node* children[NUM_LETTERS];
    boolean is_empty;
    int max_word_length;
    char* word;
}TRIE;

void memory_allocation_error(void){
    printf("Memory allocation error.\n");
    exit(1);
}

node* new_node(void){
    node* n;
    if (!(n=(node*)malloc(sizeof(node)))){
        memory_allocation_error();
    }
    return n;
}

 node* init_node(node* n, char letter){
     n->letter=letter;
     n->count=0;
     n->is_last_letter=NO;
     n->has_kids=NO;
     for(int i=0;i<NUM_LETTERS;i++){
         (n->children)[i]=NULL;
     }
      return n;    
 }
 
node* create_node(char letter){
    node* cr_node;
    cr_node=new_node();
    return init_node(cr_node, letter);
}

void free_node(node* n){
    if(n==NULL){
        return;
    }
    if((n->has_kids)==0){
        free(n);
    }
    else{
        for (int i = 0; i <NUM_LETTERS; i++)
        {
           free_node((n->children)[i]);
        }
    }
    return; 
}