#include "inverted_search.h"

/*
 * Function: file_validation_n_file_list
 * -------------------------------------
 * Validates each file from command-line arguments and adds it to a linked list if valid.
 * 
 * f_head: Pointer to the head of the file linked list (Flist)
 * argv[]: Command-line arguments (filenames passed from main)
 */
void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1, empty;

    // Loop through all command-line arguments starting from index 1 (skip program name)
    while (argv[i] != NULL)
    {
        // Check if file is available and non-empty
        empty = isFileEmpty(argv[i]);

        if (empty == FILE_NOTAVAILABLE)
        {
            // File does not exist
            printf("File %s is not available\n", argv[i]);
            printf("Unable to add to the file linked list\n");
            i++;
            continue;
        }
        else if (empty == FILE_EMPTY)
        {
            // File is empty
            printf("File %s is empty\n", argv[i]);
            printf("Unable to add to the file linked list\n");
            i++;
            continue;
        }
        else
        {
            // Try to add the file to the linked list
            int ret_val = create_list_of_files(f_head, argv[i]);

            if (ret_val == SUCCESS)
            {
                printf("Successfully inserted file %s into file linked list\n", argv[i]);
            }
            else if (ret_val == REPEATATION)
            {
                printf("Filename: %s is repeated\n", argv[i]);
                printf("Unable to add to the file list\n");
            }
            else
            {
                printf("Failure: Unable to add to the file list\n");
            }
            i++;
        }
    }
}

/*
 * Function: isFileEmpty
 * ---------------------
 * Checks whether the specified file exists and is non-empty.
 * 
 * filename: Name of the file to check
 * 
 * Returns:
 *   - FILE_NOTAVAILABLE: If file does not exist or cannot be opened
 *   - FILE_EMPTY: If file is empty
 *   - SUCCESS: If file exists and has content
 */
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r"); // Try to open the file in read mode

    if (fptr == NULL)
    {
        // If file pointer is NULL and error is "file not found", return not available
        if (errno == ENOENT)
        {
            return FILE_NOTAVAILABLE;
        }
    }

    // Move file pointer to end of file to check size
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
    {
        // File size is 0 → empty file
        return FILE_EMPTY;
    }

    fclose(fptr);
    return SUCCESS; // File exists and has content
}

/*
 * Function: create_list_of_files
 * ------------------------------
 * Adds a valid and unique file name to the linked list.
 * Prevents duplicate entries in the file list.
 *
 * f_head: Pointer to the head pointer of the file list
 * name: File name to insert
 *
 * Returns:
 *   - SUCCESS if inserted successfully
 *   - REPEATATION if file already exists in the list
 *   - FAILURE if memory allocation failed
 */
int create_list_of_files(Flist **f_head, char *name)
{
    // Allocate memory for the new file node
    Flist *new_node = (Flist *)malloc(sizeof(Flist));
    if (!new_node)
    {
        return FAILURE; // Memory allocation failed
    }

    // Copy filename and initialize link
    strcpy(new_node->file_name, name);
    new_node->link = NULL;

    // Check for duplicates
    Flist *temp = *f_head;
    while (temp)
    {
        if (strcmp(temp->file_name, name) == 0)
        {
            // If the file already exists in the list, free the new node and return
            free(new_node);
            return REPEATATION;
        }
        temp = temp->link;
    }

    // Insert the node at the end of the list
    if (*f_head == NULL)
    {
        *f_head = new_node; // First node in the list
    }
    else
    {
        temp = *f_head;
        while (temp->link)
        {
            temp = temp->link;
        }
        temp->link = new_node; // Append at the end
    }

    return SUCCESS;
}
