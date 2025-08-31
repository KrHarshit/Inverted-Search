#include "inverted_search.h"

/*
 * Function: display_database
 * ---------------------------
 * Displays the entire word database that has been built using the input files.
 * Each word entry is shown along with the number of files it appears in,
 * and the word count per file.
 *
 * head[]: Array of pointers to Wlist (indexed by 0–25 for a–z, and 26 for non-alphabetic)
 */
void display_database(Wlist *head[])
{
    // Print table headers with formatted columns
    printf("%-8s %-20s %-15s %-20s %-8s\n", "Index", "Word", "File Count", "File Name", "Word Count");
    printf("-----------------------------------------------------------------------------\n");

    // Loop through all 27 indices (26 letters + 1 for non-alpha)
    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL) // If there's a word list at this index
        {
            // Call function to print word and associated file info
            print_word_count(head[i]);
        }
    }
}

/*
 * Function: print_word_count
 * ---------------------------
 * Prints the detailed information for each word node in the list.
 * For every word, it shows:
 *   - its index in the database
 *   - the word string
 *   - number of files it appears in
 *   - each file name and its word count
 *
 * head: Pointer to the first node in the Wlist for a specific index
 *
 * Returns: 0 always (could be used for success/failure in future)
 */
int print_word_count(Wlist *head)
{
    // Traverse through the word list at current index
    while (head != NULL)
    {
        // Calculate index again based on first character of word
        int index = isalpha(head->word[0]) ? tolower(head->word[0]) - 'a' : 26;

        // Print index, word, and how many files the word appears in
        printf("%-8d %-20s %-15d", index, head->word, head->file_count);

        // Get pointer to the first file entry in the link table (Ltable)
        Ltable *Thead = (Ltable *)head->Tlink;

        // Print the first file name and word count on the same line
        printf(" %-20s %-8d\n", Thead->file_name, Thead->word_count);
        Thead = Thead->table_link;

        // For any additional files, print them in new lines, indented
        while (Thead)
        {
            // Print empty space under "Index", "Word", and "File Count" columns
            printf("%46s", "");  // Align the file names and word counts

            // Print remaining file entries and their word counts
            printf("%-20s %-8d\n", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link;
        }

        printf("\n"); // Add space between word entries
        head = head->link; // Move to next word node in Wlist
    }

    return 0;
}
