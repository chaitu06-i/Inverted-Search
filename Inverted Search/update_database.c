/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD

Title       :  Update_Database
Purpose    : Loads previously saved data from file and merges new input files into the existing database.
Prototype  : int update_database(hash_t hash[], Slist **head);
Input      : hash → hash table to restore data into
             head → list of newly provided input files
Output     : Returns SUCCESS on successful restore/update, otherwise FAILURE

*******************************************************************************************************************************************************************/

#include "main.h"

int update_database(hash_t hash[], Slist **head)
{
    char backup_file[] = "Saved.txt";   // Match the filename used in save_database()
    FILE *fp = fopen(backup_file, "r");

    if (fp == NULL)
    {
        printf("\n⚠️ No backup found to update from.\n");
        printf("💡 First save your database using option 4 before using update.\n\n");
        return FAILURE;
    }

    int index, fileCount, wordCount;
    char word[30], filename[30];

    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &fileCount) == 3)
    {
        main_t *new_main = malloc(sizeof(main_t));
        if (!new_main)
        {
            printf("❌ Memory allocation failed (main node)\n");
            fclose(fp);
            return FAILURE;
        }

        strcpy(new_main->word, word);
        new_main->file_count = fileCount;
        new_main->m_link = NULL;
        new_main->S_link = NULL;

        // Insert into hash slot
        main_t *curr = hash[index].link;

        if (!curr)
            hash[index].link = new_main;
        else
        {
            while (curr->m_link)
                curr = curr->m_link;
            curr->m_link = new_main;
        }

        // Process subnodes (file occurrences)
        sub_t *prev = NULL;

        for (int i = 0; i < fileCount; i++)
        {
            if (fscanf(fp, "%[^;];%d;", filename, &wordCount) != 2)
            {
                printf("❌ Format Error: Could not read file details.\n");
                fclose(fp);
                return FAILURE;
            }

            // Remove from file list if already present
            remove_slist_node(head, filename);

            sub_t *new_sub = malloc(sizeof(sub_t));
            if (!new_sub)
            {
                printf("❌ Memory allocation failed (sub node)\n");
                fclose(fp);
                return FAILURE;
            }

            strcpy(new_sub->file_name, filename);
            new_sub->word_count = wordCount;
            new_sub->sub_link = NULL;

            // Link subnode
            if (!new_main->S_link)
                new_main->S_link = new_sub;
            else
                prev->sub_link = new_sub;

            prev = new_sub;
        }

        // Skip marker line (#)
        char ch;
        fscanf(fp, "%c", &ch);
    }

    fclose(fp);
    printf("\n✅ Database successfully restored from '%s'.\n", backup_file);

    // Check if new files need merging
    if (*head != NULL)
    {
        printf("📁 Adding new files to the restored database...\n");

        if (create_database(*head, hash) == SUCCESS)
            printf("✅ Database successfully updated with new files.\n");
        else
            printf("❌ Failed updating with new files.\n");
    }
    else
    {
        printf("✨ No new files to merge. Database up-to-date.\n");
    }

    return SUCCESS;
}



// Remove matching file name from list (used during update)
int remove_slist_node(Slist **head, const char *name)
{
    Slist *curr = *head, *prev = NULL;

    while (curr)
    {
        if (strcmp(curr->file, name) == 0)
        {
            if (!prev)
                *head = curr->link;
            else
                prev->link = curr->link;

            free(curr);
            return SUCCESS;
        }

        prev = curr;
        curr = curr->link;
    }

    return FAILURE;
}
