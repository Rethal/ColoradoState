#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  90 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      size;        /**< size of hash table                          */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr (optional)          */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int table_size, int lookup_by_addr) {
	sym_table_t* sTable;
	sTable = calloc(1,sizeof(*sTable));
	(*sTable).size = table_size;
	(*sTable).hash_table = malloc(table_size * sizeof(node_t*));

  return sTable;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
	symbol_reset(symTab);
	free(symTab->hash_table);
	free(symTab);
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
  	for(int i = 0;i<(*symTab).size;i++){		//iterates through heads
	   node_t* node = symTab->hash_table[i];	//create pointer to node
	   node_t* wipeNode = node;
	    while(wipeNode!=NULL){				//perform function on each successive node
			node = node->next;
			free(wipeNode->symbol.name);
	        free(wipeNode);
			wipeNode = node;			//next node
	  }
	  symTab->hash_table[i] = NULL;
	}
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
int hash = 0;
int index = 0;

	if (symbol_search(symTab, name, &hash, &index) == NULL) {
//		  if((*(*symTab).hash_table[index]).hash == hash){
		    node_t* node = malloc(sizeof(node_t));
		    (*node).hash = hash;
		    (*node).next = (*symTab).hash_table[index];
		    (*node).symbol.name = strdup(name);
		    (*node).symbol.addr = addr;
		    
		    (*symTab).hash_table[index] = node;
//		    printf("%s added\n",name);
		    return 1;
//		}
	}
  return 0;
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  *hash = symbol_hash(name);
  *index = *hash % (*symTab).size;
  node_t* node = (*symTab).hash_table[*index];
  while(node != NULL){
    if(node->hash == *hash){
      return node;
    }
    if(strcmp((*node).symbol.name,name)==0){
      return node;
    }
    node = (*node).next;
  }
  return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
	int hash = 0;
	int index = 0;
	node_t* done = symbol_search(symTab,name,&hash,&index);
	if (done != NULL) {
		return &(done->symbol);
	}
	return NULL;
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  return NULL;
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
	 
	for(int i = 0;i<(*symTab).size;i++){		//iterates through heads
	   node_t* node = symTab->hash_table[i];	//create pointer to node
	      while(node != NULL){			//perform function on each successive node
		  (*fnc)(&(node->symbol),data);
		  node = node->next;			//next node
		}
	}
}

