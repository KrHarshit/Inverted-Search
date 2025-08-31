#include "inverted_search.h"

// Global pointer to hold current file name (used in multiple functions)
char *fname;

/*
 * Function: create_database
 * --------------------------
 * Traverses through the file linked list and reads each file's content
 * to build the inverted index.
 *
 * f_head: Pointer to the head of file linked list
 * head: Array of Wlist pointers representing the word database
 */
void create_database(Flist *f_head, Wlist *head[])
{
    // Traverse each file node in the file list
    while (f_head)
    {
        // Read and process the data in the current file
        read_datafile(f_head, head, f_head->file_name);

        // Move to next file in the list
        f_head = f_head->link;
    }
    printf("\nDatabase created successfully!\n");
}

/*
 * Function: read_datafile
 * ------------------------
 * Reads each word from a file, cleans it, and updates the database.
 *
 * file: Current file node
 * head: Array of Wlist pointers (indexed by first character of word)
 * filename: Name of the file being read
 *
 * Returns: Pointer to Wlist node (though return value not used here)
 */
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    // Open the file in read mode
    FILE *fptr = fopen(filename, "r");

    // Assign global file name
    fname = filename;

    // Temporary buffer to hold each word
    char word[WORD_SIZE];

    // Read file word by word until EOF
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Clean punctuation from word
        clean_word(word);

        // Determine which index this word should go to (0-25 for a-z, 26 for others)
        int flag = 1;
        int index = isalpha(word[0]) ? tolower(word[0]) - 'a' : 26;

        // If index already has entries, check for duplicates
        if (head[index] != NULL)
        {
            Wlist *temp = head[index];

            // Traverse word list at that index to find if word already exists
            while (temp)
            {
                if (!(strcmp(temp->word, word))) // Word found
                {
                    update_word_count(&temp, filename); // Update count
                    flag = 0;
                    break;
                }
                temp = temp->link;
            }
        }

        // If word not found, insert it at the end of the list
        if (flag == 1)
        {
            insert_at_last(&head[index], word);
        }
    }
}

/*
 * Function: update_word_count
 * ----------------------------
 * Updates word count in file-specific link table if file already exists.
 * If not, creates a new node for the file.
 *
 * head: Double pointer to word node
 * file_name: Name of file in which word occurrence is to be recorded
 *
 * Returns: SUCCESS or FAILURE macro
 */
int update_word_count(Wlist **head, char *file_name)
{
    int flag = 0;

    // Point to the link table (list of files for this word)
    Ltable *temp = (Ltable *)(*head)->Tlink;

    // Traverse the link table
    while (temp != NULL)
    {
        if (strcmp(temp->file_name, file_name) == 0) // File already present
        {
            temp->word_count++; // Just increase count
            flag = 1;
            break;
        }
        temp = temp->table_link;
    }

    // If file is not already present in link table
    if (flag == 0)
    {
        (*head)->file_count++; // Increase total file count for this word

        // Create a new file node
        Ltable *new_node = malloc(sizeof(Ltable));
        if (new_node == NULL)
        {
            return FAILURE;
        }

        // Initialize new file node
        strcpy(new_node->file_name, file_name);
        new_node->word_count = 1;
        new_node->table_link = NULL;

        // Add new node to the Tlink list
        if ((*head)->Tlink == NULL) // First file
        {
            (*head)->Tlink = (struct Ltable *)new_node;
        }
        else
        {
            Ltable *temp = (Ltable *)(*head)->Tlink;
            while (temp->table_link != NULL)
            {
                temp = temp->table_link;
            }
            temp->table_link = new_node;
        }
    }

    return SUCCESS;
}

/*
 * Function: is_punctuation
 * -------------------------
 * Checks whether a given character is a punctuation mark.
 *
 * ch: Character to check
 *
 * Returns: 1 if punctuation, 0 otherwise
 */
int is_punctuation(char ch) {
    // Extended set of punctuation characters
    const char *punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~“”‘’";
    return strchr(punctuation, ch) != NULL;
}

/*
 * Function: contains_alpha
 * -------------------------
 * Checks if a string contains at least one alphabet character.
 *
 * word: Word to check
 *
 * Returns: 1 if contains alphabets, 0 otherwise
 */
int contains_alpha(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            return 1; // Found alphabet
        }
    }
    return 0; // No alphabets
}

/*
 * Function: clean_word
 * ---------------------
 * Removes leading/trailing punctuation from a word and converts it to lowercase.
 *
 * word: Word to be cleaned (modified in-place)
 */
void clean_word(char *word) {
    // If no alphabets, don't process further
    if (!contains_alpha(word)) {
        return;
    }

    int start = 0, end = strlen(word) - 1;

    // If the word is a single punctuation symbol, skip cleaning
    if (start == end && is_punctuation(word[start])) {
        return;
    }

    // Remove leading punctuation
    while (start <= end && is_punctuation(word[start])) {
        start++;
    }

    // Remove trailing punctuation
    while (end >= start && is_punctuation(word[end])) {
        end--;
    }

    // Copy cleaned word back to original buffer with lowercase conversion
    int i, j = 0;
    for (i = start; i <= end; i++) {
        word[j++] = tolower((unsigned char)word[i]);
    }
    word[j] = '\0'; // Null-terminate the cleaned string
}
