/*******************************************************************************************************************************************************************
Name        : G. CHAITANYA GOWD
Title       : Main Program
Description : Handles file input, stores filenames in a list, and provides menu options
              to create, display, search, save, and update the database.

Prototype   : int main(int argc, char *argv[]);

Inputs      : argc → number of arguments
              argv → list of input filenames (.txt)

Output      : SUCCESS / FAILURE
*******************************************************************************************************************************************************************/

#include "main.h"

int main(int argc, char *argv[])
{
    Slist *head = NULL;
    hash_t hash_table[27];

    for(int i=0;i<27;i++)
    {
        hash_table[i].index = i;
        hash_table[i].link = NULL;
    }

    if(argc < 2)
    {
        printf("⚠️  Error: Please provide input text file as argument\n");
        return FAILURE;
    }
    else
    {
        for(int i=1; i<argc; i++)
        {
            if(strstr(argv[i], ".txt") == NULL)
            {
                printf("❌ Error: Invalid file extension. Please give valid input.\n");
                continue;
            }

            FILE *fptr = fopen (argv[i], "r");
            if(fptr == NULL)
            {
                printf("📁 Error: File not found.\n");
                continue;
            }

            fseek(fptr,0, SEEK_END);
            long size = ftell(fptr);
            if(size == 0)
            {
                printf("⚠️  Warning: File is empty (Skipping)\n");
                continue;
            }

            Slist *temp = head;
            int dup = 0;
            char *current_file = argv[i];

            while(temp != NULL)
            {
                if(strcmp (temp -> file, current_file) == 0)
                {
                    dup = 1;
                    break;
                }
                temp = temp -> link;
            }

            if(dup)
            {
                printf("⚠️  File '%s' is already in the list.\n",current_file);
                continue;
            }

            if(insert_at_last(&head, argv[i]) != SUCCESS)
            {
                return FAILURE;
            }
        }
    }

    if(head == NULL)
    {
        printf("❌ ERROR: No valid files provided.\n");
        return FAILURE;
    }

    printf("\n📂 Files have been successfully added to the list.\n");
    int flag = 1, flag1 = 0,  flag2 =0;

    while(flag)
    {
        int option;

        printf("\n🔹🔹🔹 MAIN MENU 🔹🔹🔹\n");
        printf("✨ 1. Create Data Base\n");
        printf("📄 2. Display Data Base\n");
        printf("🔍 3. Search Data Base\n");
        printf("💾 4. Save Data Base\n");
        printf("🔄 5. Update Data Base\n");
        printf("❌ 6. Exit\n");
        printf("🔹🔹🔹🔹🔹🔹🔹🔹🔹🔹🔹\n");
        printf("👉 Enter Choice: ");
        scanf("%d", &option);
        getchar();

        switch(option)
        {
            case 1:
                    if(flag1 != 0)
                    {
                        printf("Info , Database already exists\n");
                    }
                    else
                    {
                        if(create_database(head,hash_table) == SUCCESS)
                        {
                           printf("✅ Create Database completed successfully.\n");
                           flag1 = 1;
                           flag2 = 1;
                        }
                        else
                        {
                            printf("❌ Create Database failed.\n");
                        }
                    }
                    break;

            case 2:
                printf("========================\n");
                printf("|  Display DataBase    |\n");
                printf("========================\n");
                display_database(hash_table);
                printf("\n✅ Display Database Done \n");
                printf("\n");
                break;

            case 3:
                if(search_database(hash_table) == SUCCESS)
                {
                    printf("✅ Word found successfully in Database\n");
                }
                else
                {
                    printf("❌ Word not found in Database\n");
                }
                break;

            case 4:
                if(flag1 == 1 && flag2 == 1)
                {
                    if(save_database(hash_table) == SUCCESS)
                    {
                        printf("✅ Saving the database is done successfully\n");
                    }
                    else
                    {
                        printf("❌ Saving the database is failed\n");
                    }
                }
                else
                {
                    printf("🚫 Saving the Database is not possible, because of creation of database is not done\n");
                }
                break;

            case 5:
                if (flag1 == 1)
                {
                    printf("Info, Database is already created. Update operation is not required.\n");
                }
                else
                {
                    if (update_database(hash_table, &head) == SUCCESS)
                    {
                        flag2 = 1;
                        flag1 = 1;
                        printf("✅ Update Database Done Successfully \n");
                    }
                    else
                    {
                        printf("❌ Update Database Failed\n");
                    }
                }
                break;

            case 6:
               printf("👋 Exiting program...\n");
               flag = 0;
               break;

            default:
                printf("⚠️  Invalid option. Try again.\n");
                break;
        }
    }
}

int insert_at_last(Slist **head, char *file)
{
    Slist *new = malloc(sizeof(Slist));
    if(new == NULL)
    {
        printf("Memory Allocation not Completed");
        return FAILURE;
    }

    strcpy(new -> file, file);
    new -> link = NULL;

    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    else
    {
        Slist *temp = *head;
        while(temp -> link != NULL)
        {
            temp = temp -> link;
        }
        temp -> link = new;
        return SUCCESS;
    }
}
