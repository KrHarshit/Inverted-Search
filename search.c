#include "inverted_search.h"

/*
 * Function: search
 * ----------------
 * Searches for a given word in the linked list and prints all file names where it appears,
 * along with the number of times it appears in each file.
 *
 * head: Pointer to the head of the word linked list (Wlist)
 * word: Word to be searched in the list
 *
 * Returns:
 *   - 0 if word is found and search is complete
 *   - 0 if list is empty or word is not found (prints appropriate message)
 */
int search(Wlist *head, char *word)
{
    // Check if the word list is empty
    if (head == NULL)
    {
        printf("List is empty, search not possible\n");
        return 0;
    }

    // The list is not empty; start traversing from the head
    while (head)
    {
        // Compare the current node's word with the search word
        if (!(strcmp(head->word, word)))
        {
            // Match found
            printf("Word [%s] is present in %d file/s\n", word, head->file_count);
            printf("%-20s %-8s\n", "File Name", "Word Count");

            // Get pointer to the file list (Ltable) from the word node
            Ltable *Thead = (Ltable *)head->Tlink;

            // Traverse through all files where the word appears
            while (Thead)
            {
                // Print file name and number of times the word appears in that file
                printf("%-20s %-8d\n", Thead->file_name, Thead->word_count);

                // Move to the next file node
                Thead = Thead->table_link;
            }

            // Print a newline for readability after result
            printf("\n");

            return 0; // Word found and printed, exit function
        }

        // Move to the next word node in the list
        head = head->link;
    }

    // Word not found after traversing the list
    printf("Search word not found\n");
    return 0;
}
