#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TRIE.h"

void memory_allocation_error(void){// throw exception if there is no memroy space and exit.
    printf("Memory allocation error.\n");
    exit(1);
}

node* new_node(char letter){
    node* n;
    if (!(n=(node*)malloc(sizeof(node)))){// if there is no memory space for the new node
        memory_allocation_error();
    }
    //otherwise, create new  node with the given letter.
    int i;
     n->letter=letter;
     n->count=0;
     n->is_word=FALSE;
     n->has_kids=FALSE;
     for(i=0;i<NUM_LETTERS;++i){
         (n->children)[i]=NULL;
     }
    return n;
}

void free_node(node* n){
    int i;
    if(n==NULL){
        return;
    }
    if(n->has_kids){// the node is a leaf
        for (i = 0; i <NUM_LETTERS; i++)// free all the children of the node
        {
           free_node((n->children)[i]);
        }
    }
    free(n);
    return; 
}

trie* init_trie(trie* t){
  int i;
    for (i=0; i<NUM_LETTERS; ++i) {
        t->children[i]=NULL;
    }
    t->current=NULL;
    t->empty=TRUE;
    t->max_word_length=0;
    t->word=NULL;
    return t;
}

trie* new_trie(void){
    trie* t;
    if(!(t=(trie*)malloc(sizeof(trie)))){// if there is no memory space for the new trie
        memory_allocation_error();
    }
    //otherwise, create new trie.
    return init_trie(t);
  
}


void close_word(trie* root) {
    if (root->current == NULL)// if there is no word.
        return;
    root->current->count++;
    root->current->is_word = TRUE;// the last letter in the word
    root->current=NULL;
}
boolean is_empty(trie* root) {
    return root->empty;
}
int char2index(char c) {
    return c-'a';
}
int read_character(trie* root, int c, int word_length) {
    int index;
    //int word_length=0;
    if(!isalpha(c)) {// the char is not a letter (finish to read the word)
        close_word(root);
        return word_length;
    }
    word_length++;
    c=tolower(c);
    index= char2index(c);
    if (root->current==NULL) { //new word - start from root 
        if (root->children[index] == NULL) {
            root->children[index] = new_node(c);
        }
        root->current = root->children[index];
        root->empty=FALSE;
    }
    else {
        root->current->has_kids = TRUE;
        if (root->current->children[index] == NULL)
            root->current->children[index] = new_node(c);
        root->current=root->current->children[index];
    }
    return word_length;
}

trie* read_text() {
    int c;
    int word_length=0;
    trie* root;
    root = new_trie();
    while( EOF!=(c=getchar()) ) {
        word_length=read_character(root,c,word_length);
        if (word_length>root->max_word_length)
            root->max_word_length=word_length;
        if(!isalpha(c))
            word_length=0;
    }
   free(root->word);
    if (!(root->word=(char*)malloc(1+sizeof(char)*(root->max_word_length))) )// there is no memory space for the longest word
        memory_allocation_error();
    return root;
}
void print_words_reverse(trie* root) {
    static int p=0;
    int i;
    node* current;
    root->word[p++]=root->current->letter;
    if (root->current->has_kids){
        for (i=NUM_LETTERS-1; i>=0; --i) {
            if (root->current->children[i] == NULL)
                continue;
            current = root->current; /* remember */
            root->current = root->current->children[i];
            print_words_reverse(root);
            root->current = current; /* recall */
        }
    } else {
        if (root->current->is_word) {// the end of a word
            root->word[p]='\0';
            printf("%s\t%ld\n",root->word,root->current->count);
        }
        --p;
        return;
    }
    if (root->current->is_word) {
        root->word[p]='\0';
        printf("%s\t%ld\n",root->word,root->current->count);
    }
    --p;
}
void print_trie_reverse(trie* root) {
    int i;
    if (root == NULL)
        return;
    if (is_empty(root))
        return;
    for (i=NUM_LETTERS-1; i>=0; --i) {
        if (root->children[i] == NULL)
            continue;
        root->current = root->children[i];
        print_words_reverse(root);
    }
}
void print_words(trie* root) {
    static int p=0;
    int i;
    node* current = NULL;
    root->word[p++]=root->current->letter;
    if (root->current->is_word) {//end of the word
        root->word[p]='\0';
        printf("%s\t%ld\n",root->word,root->current->count);
    }
    if (root->current->has_kids) {
        for(i=0; i<NUM_LETTERS; ++i) {
            if (root->current->children[i] == NULL)
                continue;
            current=root->current;
            root->current = root->current->children[i];
            print_words(root);
            root->current = current; /* recall */
        }
    }
    else {
        --p;
        return;
    }
    --p;
}
void print_trie(trie* root) {
    int i;
    if (root == NULL)
        return;
    if (is_empty(root))
        return;
    for (i=0; i<NUM_LETTERS; ++i) {
        if (root->children[i] == NULL)
            continue;
        root->current = root->children[i];
        print_words(root);
    }
}
void free_trie(trie* t) {
    int i;
    if (t == NULL)
        return;
    for(i=0;i<NUM_LETTERS; ++i) {
        free_node(t->children[i]);
    }
    free(t->word);
    free(t);
}
void usage(char* program_name,char* message) {
    //print errors
    printf("\n%s\n\n",message);
    printf("USAGE:\n\t%s: %s\n\n",program_name,message);
    exit(1);
}
boolean should_reverse(int argc, char* argv[]) {
    if (argc > 2)// if there are more than 2 arguments
        usage(argv[0],"Wrong number of arguments.");
    if ( (argc == 2) && (argv[1][0]=='r' || argv[1][0]=='R') )// the secnod argument is the parameter 'r'
        return TRUE;
    if (argc == 1)// there is no parameter
        return FALSE;
    usage(argv[0],"Bad command line arguments.");
    return FALSE; // will never get here 
}
int main(int argc, char* argv[]) {
    trie* root;
    boolean r = should_reverse(argc,argv);
    root = read_text();
    if (r)
        print_trie_reverse(root);
    else
        print_trie(root);
    free_trie(root);
    return 0;
}

