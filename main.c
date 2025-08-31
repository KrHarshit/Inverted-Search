#include "inverted_search.h" 



int main(int argc, char *argv[])
{
	system("clear"); // Clear the terminal screen for better user interface visibility

	// Declare and initialize an array of 27 pointers to Wlist structures to NULL
	// Each index corresponds to a letter a-z (0-25) and 26 for non-alphabet characters
	Wlist *head[27] = {NULL};

	// Check if any command-line arguments (files) are passed
	if(argc <= 1)
	{
		// If no input files are given, print error and usage instructions
		printf("Enter the valid number of arguments\n");
		printf("./main.exe file1.txt file2.txt ....\n");
		return 1; // Exit with error
	}

	Flist *f_head = NULL; // Initialize file linked list head pointer to NULL

	// Validate input files and build a linked list of valid files
	file_validation_n_file_list(&f_head, argv);

	// If file list remains empty after validation, print error and terminate
	if(f_head == NULL)
	{
		printf("No files added to file linked list\n");
		printf("Hence the process got terminated\n");
	}

	int flag = 1; // Flag to control menu loop
	while(flag == 1) // Loop until user chooses to exit
	{
		int choice; // To store user menu choice
		char word[WORD_SIZE]; // Buffer to hold word entered for search

		// Display menu options to the user
		printf("\n1. Create Database\n2. Display Database\n3. Update Database\n4. Search\n5. Save Database\n6. Exit\n\n");
		scanf("%d", &choice); // Get user choice

		switch(choice) // Perform operation based on user's choice
		{
			case 1:
				// Create the inverted index database from words in files
				create_database(f_head, head);
				break;

			case 2:
				// Display the entire database with words and their file occurrences
				display_database(head);
				break;

			case 3:
				// Update database when a new file is added
				update_database(head, &f_head);
				break;

			case 4:
				// Prompt the user to enter a word for search
				printf("\nEnter the search word\n");
				scanf("%s", word);

				// Calculate index based on first character of word
				// If alphabetic: map 'a'-'z' to 0-25
				// If non-alphabetic: use 26th index
				int index = isalpha(word[0]) ? tolower(word[0]) - 'a' : 26;

				// Search the word in the corresponding list
				search(head[index], word);
				break;

			case 5:
				// Save the current state of the database to a file
				save_database(head);
				break;

			case 6:
				// Exit the loop and terminate the program
				flag = 0;
				break;

			default:
				// Invalid input handler (optional)
				printf("Invalid choice. Please try again.\n");
		}
	}
}
