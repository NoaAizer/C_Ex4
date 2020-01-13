
#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0 , TRUE=1} boolean;
typedef struct node{
    char letter;
    long unsigned int count;
    boolean is_word;// if the node is a the last letter in the word.
    boolean has_kids;// if the node is a leaf or not.
    struct node* children[NUM_LETTERS];
}node;

typedef struct trie{
    node* children[NUM_LETTERS];
    node* current;
    boolean empty;
    int max_word_length;
    char* word;
}trie;

void memory_allocation_error();
node* new_node(char);
void free_node(node* );
trie* init_trie(trie* );
trie* new_trie();
void close_word(trie* );
boolean is_empty(trie* );
int char2index(char );
int read_character(trie* , int , int );
trie* read_text();
void print_words_reverse(trie* );
void print_trie_reverse(trie* );
void print_words(trie*);
void print_trie(trie* );
void free_trie(trie* t);
void usage(char* ,char* );
boolean should_reverse(int , char*[]);
