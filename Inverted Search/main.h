#ifndef MAIN_H   // Header guard start
#define MAIN_H

#include <stdio.h>   // Standard I/O
#include <stdlib.h>  // Dynamic memory
#include <string.h>  // String functions
#include <ctype.h>   // Character checks

#define SUCCESS 0    // Success return value
#define FAILURE -1   // Failure return value

// Sub node structure (file details)
typedef struct subnode
{
    char file_name[100];      // File name
    int word_count;           // Word count in file
    struct subnode *sub_link; // Next sub node
} sub_t;

// Main node structure (word details)
typedef struct main_node
{
    char word[100];       // Word stored
    int file_count;       // Number of files containing word
    struct main_node *m_link; // Next main node
    sub_t *S_link;        // Sub node link
} main_t;

// Hash table bucket
typedef struct hashtable
{
    int index;       // Hash index
    main_t *link;    // Main node link
} hash_t;

// File list node
typedef struct list
{
    char file[100];  // File name
    struct list *link; // Next file node
} Slist;

// Function prototypes
int insert_at_last(Slist **head, char *file);           // Insert filename into list
int create_database(Slist *head, hash_t hash[]);        // Build database
int display_database(hash_t hash[]);                    // Print database
int search_database(hash_t hash[]);                     // Search word
int save_database(hash_t hash[]);                       // Save database to file
int update_database(hash_t hash[], Slist **head);       // Restore and merge database
int remove_slist_node(Slist **head, const char *name);  // Remove file node

#endif  // Header guard end
