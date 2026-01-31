/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD

Title       : Create Database

Description : 
              This function reads each file in the linked list and extracts words.
              It stores the words in the hash table along with file names and 
              their occurrence count, forming a searchable database.

Prototype   : int create_database(Slist *head, hash_t hash[]);

Input       : head → Pointer to the list of input text files
              hash → Hash table to store processed word data

Output      : Returns SUCCESS if database is created, otherwise FAILURE

*******************************************************************************************************************************************************************/

#include "main.h"   // Include header file

int create_database(Slist *head, hash_t hash[])
{
    if (head == NULL) // Check if file list is empty
    {
        printf("❌ Error: File list is empty, cannot create database\n"); // Print error
        return FAILURE; // Return failure
    }

    Slist *temp = head; // Pointer to traverse file list

    while (temp != NULL) // Loop through each file
    {
        char *curr_file = temp->file; // Get current filename
        FILE *fptr = fopen(curr_file, "r"); // Open file

        if (fptr == NULL) // Check if file opened successfully
        {
            printf("❌ Error: Cannot open file %s\n", curr_file); // Print error
            temp = temp->link; // Move to next file
            continue; // Skip file
        }

        printf("📄 Processing file: %s\n", curr_file); // Print file being processed

        char word_buff[30]; // Buffer to store extracted words
        while (fscanf(fptr, "%29s", word_buff) != EOF) // Read words until file ends
        {
            int index; // Variable for hash index

            if (isalpha(word_buff[0])) // Check if first char is alphabet
                index = tolower(word_buff[0]) - 'a'; // Compute index for letter
            else
                index = 26; // Index for non-alphabet words

            main_t *temp1 = hash[index].link; // Search word list in hash slot
            main_t *prev1 = NULL; // Pointer to previous word node
            int found_word = 0; // Flag if word exists

            while (temp1 != NULL) // Traverse word nodes
            {
                if (strcmp(temp1->word, word_buff) == 0) // Check if word exists
                {
                    found_word = 1; // Mark found
                    break; // Stop loop
                }
                prev1 = temp1; // Move previous pointer
                temp1 = temp1->m_link; // Move next node
            }

            if (found_word) // If word exists in list
            {
                sub_t *temp2 = temp1->S_link; // Pointer to file list for word
                sub_t *prev2 = NULL; // Previous file node
                int found_file = 0; // Flag if file entry exists

                while (temp2 != NULL) // Traverse file entries
                {
                    if (strcmp(temp2->file_name, curr_file) == 0) // Check if file matches
                    {
                        found_file = 1; // Found
                        break; // Stop loop
                    }
                    prev2 = temp2; // Move previous
                    temp2 = temp2->sub_link; // Next file node
                }

                if (found_file) // If file entry exists
                {
                    temp2->word_count++; // Increase count
                }
                else // Add new file entry
                {
                    sub_t *new_sub = malloc(sizeof(sub_t)); // Allocate new subnode
                    new_sub->word_count = 1; // First occurrence
                    strcpy(new_sub->file_name, curr_file); // Store filename
                    new_sub->sub_link = NULL; // No next node

                    prev2->sub_link = new_sub; // Link new file entry
                    temp1->file_count++; // Increase file count
                }
            }
            else // Word not found, create new nodes
            {
                main_t *new_main = malloc(sizeof(main_t)); // Allocate main node
                sub_t *new_sub = malloc(sizeof(sub_t)); // Allocate sub node

                strcpy(new_main->word, word_buff); // Store word
                new_main->file_count = 1; // First file count
                new_main->m_link = NULL; // No next node
                new_main->S_link = new_sub; // Link subnode

                new_sub->word_count = 1; // First count
                strcpy(new_sub->file_name, curr_file); // Store file name
                new_sub->sub_link = NULL; // No next subnode

                if (hash[index].link == NULL) // If first node at hash index
                    hash[index].link = new_main; // Insert node
                else
                    prev1->m_link = new_main; // Append node
            }
        }

        fclose(fptr); // Close current file
        temp = temp->link; // Move to next file
    }

    return SUCCESS; // Return success
}
