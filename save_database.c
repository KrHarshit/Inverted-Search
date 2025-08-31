#include "inverted_search.h"

/*
 * Function: save_database
 * -----------------------
 * Saves the inverted search word database to a user-specified file.
 *
 * head: Array of pointers to the head of the word list for each alphabet (a-z + non-alphabetic)
 */
void save_database(Wlist *head[])
{
    char file_name[FNAME_SIZE];  // Buffer to store the file name input from the user

    // Prompt user for the output file name
    printf("\nEnter the file name\n");
    scanf("%s", file_name);

    // Open the specified file in write mode
    FILE *fptr = fopen(file_name, "w");

    // Write table header to the file
    fprintf(fptr, "%-8s %-20s %-15s %-20s %-8s\n", "Index", "Word", "File Count", "File Name", "Word Count");
    fprintf(fptr, "-----------------------------------------------------------------------------\n");

    // Loop through all 27 buckets (0-25 = a-z, 26 = non-alphabetic)
    for (int i = 0; i < 27; i++)
    {
        // If a linked list exists at this index, write its content to file
        if (head[i] != NULL)
        {
            write_databasefile(head[i], fptr);
        }
    }

    // Inform user of successful save
    printf("\nDatabase saved to %s successfully\n", file_name);

    // Close the file
    fclose(fptr);
}



/*
 * Function: write_databasefile
 * ----------------------------
 * Writes word and file information of one linked list bucket to the database file.
 *
 * head: Pointer to the head of the word list (Wlist)
 * databasefile: Pointer to the already open file where data will be written
 */
void write_databasefile(Wlist *head, FILE *databasefile)
{
    // Loop through each word node in the list
    while (head != NULL)
    {
        // Determine index based on first character of the word
        // 'a' to 'z' → 0–25; non-alphabetic → 26
        int index = isalpha(head->word[0]) ? tolower(head->word[0]) - 'a' : 26;

        // Write the word node's details (index, word, file count)
        fprintf(databasefile, "%-8d %-20s %-15d", index, head->word, head->file_count);

        // Get pointer to the first file node where the word appears
        Ltable *Thead = (Ltable *)head->Tlink;

        // Write the first file's name and word count on the same line
        fprintf(databasefile, " %-20s %-8d\n", Thead->file_name, Thead->word_count);

        // Move to the next file node
        Thead = Thead->table_link;

        // Loop through remaining file nodes (if any)
        while (Thead)
        {
            // Indent to align with "File Name" and "Word Count" columns
            fprintf(databasefile, "%46s", "");

            // Write file name and word count for this file
            fprintf(databasefile, "%-20s %-8d\n", Thead->file_name, Thead->word_count);

            // Move to the next file node
            Thead = Thead->table_link;
        }

        // Print a newline to separate entries for readability
        fprintf(databasefile, "\n");

        // Move to the next word node
        head = head->link;
    }
}
