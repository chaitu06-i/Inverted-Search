/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD

Title       : Search Database

Description :
              This function searches for a given word in the hash table and 
              displays the files where the word exists along with its frequency.

Prototype   : int search_database(hash_t arr[]);

Input       : arr → Hash table containing stored words and file info

Output      : Returns SUCCESS if word found, otherwise FAILURE

*******************************************************************************************************************************************************************/

#include "main.h"   // Include header file

int search_database(hash_t arr[])
{
    int flag = 0;                       // Flag to track match
    char word[20];                      // Buffer for search input

    printf("🔍 Enter the word : ");     // Ask user for word
    scanf("%s", word);                  // Read input

    for(int i = 0; i <= 26; i++)        // Loop through hash table
    {
        if(arr[i].link != NULL)         // Check if bucket has data
        {
            main_t *mtemp = arr[i].link; // Pointer to word list

            while (mtemp != NULL)        // Traverse stored words
            {
                if(strcmp(mtemp->word, word) == 0) // Check word match
                {
                    flag = 1;            // Mark found
                    printf("📌 The word [%s] is present in %d file(s)\n", mtemp->word, mtemp->file_count); // Print summary

                    sub_t *stemp = mtemp->S_link; // Pointer to file list

                    while(stemp != NULL) // Traverse file entries
                    {
                        printf("📁 %s → %d time(s)\n",stemp->file_name, stemp->word_count); // Print file info
                        stemp = stemp->sub_link; // Move to next file
                    }

                    printf("\n");        // Line break
                }

                mtemp = mtemp->m_link;   // Move to next word node
            }
        }
    }

    if(!flag)                             // If not found
    {
        return FAILURE;                   // Return failure
    }

    return SUCCESS;                       // Return success
}
