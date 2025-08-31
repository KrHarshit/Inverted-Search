#include "inverted_search.h"

extern char *fname;  // Global file name used in link table updates

/*
 * Function: insert_at_last
 * ------------------------
 * Inserts a new word at the end of the Wlist (word list).
 * Also calls a helper function to initialize and attach the corresponding Ltable (file list).
 *
 * head: Double pointer to the head of the Wlist
 * data: The word to be inserted
 *
 * Returns:
 *   - SUCCESS (0) if insertion is successful
 *   - FAILURE (1) if memory allocation fails
 */
int insert_at_last(Wlist **head, char *data)
{
    // Allocate memory for new Wlist node
    Wlist *new = malloc(sizeof(Wlist));
    if (new == NULL)
    {
        return FAILURE;  // Memory allocation failed
    }

    // Initialize word node
    new->file_count = 1;             // Word appears in one file (initially)
    strcpy(new->word, data);         // Store the word
    new->Tlink = NULL;               // No file links yet (will be added below)
    new->link = NULL;                // Next word node is NULL (end of list)

    // Create and attach Ltable node (file info) for this word
    update_link_table(&new);

    // Case 1: If list is empty, insert as the first node
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    // Case 2: List is not empty → traverse to the last node
    Wlist *temp = *head;
    while (temp->link)
    {
        temp = temp->link;
    }

    // Attach new node at the end
    temp->link = new;
    return SUCCESS;
}

/*
 * Function: update_link_table
 * ---------------------------
 * Creates a new Ltable node (file info) for a given word node and links it.
 * Uses global 'fname' variable as the file name source.
 *
 * head: Double pointer to the Wlist node where Ltable should be added
 *
 * Returns:
 *   - SUCCESS (0) if created successfully
 *   - FAILURE (1) if memory allocation fails
 */
int update_link_table(Wlist **head)
{
    // Allocate memory for new Ltable node
    Ltable *new = malloc(sizeof(Ltable));
    if (new == NULL)
    {
        return FAILURE;  // Memory allocation failed
    }

    // Initialize Ltable fields
    new->word_count = 1;                 // Word appears once in this file initially
    strcpy(new->file_name, fname);       // Set file name from global variable
    new->table_link = NULL;              // No next file yet

    // Link this Ltable node to the Wlist node
    (*head)->Tlink = (struct Ltable *)new;

    return SUCCESS;
}
