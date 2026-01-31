/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD

Title       : Display Database

Description : 
              This function prints the stored database from the hash table.
              It displays each word, number of files it appears in, and the
              frequency of that word in each file.

Prototype   : int display_database(hash_t arr[]);

Input       : arr → Hash table containing stored words and file info

Output      : Returns SUCCESS after displaying the database

*******************************************************************************************************************************************************************/

#include "main.h"   // Include header file

int display_database(hash_t arr[])
{
    for(int i=0; i<=26; i++)   // Loop through all hash table indexes
    {
        if(arr[i].link != NULL)   // Check if index contains data
        {
            main_t *mtemp = arr[i].link;   // Pointer to main node list

            while (mtemp != NULL)   // Traverse main list
            {
                printf("📌 [%d] -> [%s] -> %d -> ", i, mtemp->word, mtemp->file_count); // Print word and file count

                sub_t *stemp = mtemp->S_link;   // Pointer to subnode list

                while(stemp != NULL)   // Traverse sub list
                {
                    printf("%s -> %d ->", stemp->file_name, stemp->word_count); // Print file name and count
                    stemp = stemp->sub_link;   // Move to next subnode
                }

                mtemp = mtemp->m_link;   // Move to next word node
                printf("\n");            // New line after each word
            }
        }
    }

    return SUCCESS;   // Return success
}
