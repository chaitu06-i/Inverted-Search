/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD

Title       : Save Database

Description :
              This function writes the database records into a file named "Saved.txt"
              in a structured format so the database can be loaded later.

Prototype   : int save_database(hash_t arr[]);

Input       : arr → Hash table containing stored words and file information

Output      : Returns SUCCESS if saved successfully, otherwise FAILURE

*******************************************************************************************************************************************************************/

#include "main.h"   // Include header file

int save_database(hash_t arr[])
{
    char ch = '#';   // Special marker character
    FILE *fptr = fopen("Saved.txt", "w");  // Open file for writing

    if(fptr == NULL)   // Check file open failure
    {
        printf("❌ Memory allocation failed.\n");  // Print error
        return FAILURE;  // Return failure
    }

    for(int i=0; i<=26; i++)   // Loop through hash table
    {
        if(arr[i].link != NULL)   // Check non-empty index
        {
            main_t *mtemp = arr[i].link;   // Pointer to main node

            while(mtemp != NULL)   // Traverse main list
            {
                fprintf(fptr, "%c%d;%s;%d;", ch, i, mtemp->word, mtemp->file_count);  // Write word info

                sub_t *stemp = mtemp->S_link;   // Pointer to subnode

                while(stemp != NULL)   // Traverse file entries
                {
                    fprintf(fptr, "%s;%d;", stemp->file_name, stemp->word_count);  // Write file data
                    stemp = stemp->sub_link;   // Move to next subnode
                }

                mtemp = mtemp->m_link;   // Move to next word
                fprintf(fptr, "%c\n", ch);   // End record with marker
            }
        }
    }

    return SUCCESS;   // Return success
}
