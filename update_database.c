#include "inverted_search.h"

/*
 * Function: update_database
 * -------------------------
 * Adds a new file to the existing inverted index database (if valid and not duplicated).
 * It checks if the file is available and non-empty, inserts it into the file list,
 * and updates the word database structure with its contents.
 *
 * head: Array of pointers to word list heads (inverted index for each alphabet + non-alpha)
 * f_head: Pointer to the head pointer of the file list (Flist)
 */
void update_database(Wlist *head[], Flist **f_head)
{
    char file_name[FNAME_SIZE];  // Buffer to store the name of the new file to be added

    // Prompt user to enter a new file name to update the database
    printf("\nEnter the new file name to update the database\n");
    scanf("%s", file_name);

    // Validate the new file (check if it exists and is not empty)
    int empty = isFileEmpty(file_name);

    if (empty == FILE_NOTAVAILABLE)
    {
        // Case 1: File does not exist
        printf("File %s is not available\n", file_name);
        printf("Unable to add to the database\n");
    }
    else if (empty == FILE_EMPTY)
    {
        // Case 2: File is empty
        printf("File %s is empty\n", file_name);
        printf("Unable to add to the database\n");
    }
    else
    {
        // Case 3: File is valid and has content

        // Try to insert the file into the file linked list
        int ret_val = create_list_of_files(f_head, file_name);

        if (ret_val == SUCCESS)
        {
            // File inserted successfully
            printf("Successfull in inserting %s into the database\n", file_name);
        }
        else if (ret_val == REPEATATION)
        {
            // File already exists in the database
            printf("Filename: %s is repeated\n", file_name);
            printf("Unable to add to the database\n");
        }
        else
        {
            // Insertion failed due to memory or other issues
            printf("Failure: Unable to add to the database\n");
        }
    }

    /*
     * At this point, the file has been inserted into the file list (if valid and not duplicate).
     * Now we need to update the word database (Wlist) using the file's contents.
     */

    // Traverse the file list to locate the newly added file node
    while (*f_head)
    {
        // Check for a matching file name
        if (!(strcmp(file_name, (*f_head)->file_name)))
        {
            // Match found, create/update the word database with the file's content
            create_database(*f_head, head);
        }

        // Move to the next file node
        *f_head = (*f_head)->link;
    }
}
