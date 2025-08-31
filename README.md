# 🔎 Inverted Search (C Project)

A **command-line Inverted Search application in C** that indexes words from multiple text files and allows efficient searching.  
It builds an **inverted index database** where each word maps to the files it appears in, along with its frequency.

---

## 🚀 Features
- 📂 **Create Database** → Build inverted index from multiple files  
- 👀 **Display Database** → View all words and their occurrences in each file  
- ➕ **Update Database** → Add new files without rebuilding from scratch  
- 🔍 **Search** → Find how many times a word appears across files  
- 💾 **Save Database** → Save current state to a file for later use  
- ✅ Handles empty files, duplicate files, and punctuation cleanup  

---

## 📂 Project Structure
```text
InvertedSearch/
├── main.c               # Menu-driven main program
├── inverted_search.h    # Header file (structures & prototypes)
├── file_validation.c    # File validation & file list handling
├── create_database.c    # Reads files & builds inverted index
├── insert.c             # Inserts words into word list
├── display.c            # Displays database
├── search.c             # Search a word in database
├── save.c               # Save database to file
├── update.c             # Update database with new file
└── README.md            # Project documentation

## 🛠️ Compilation & Usage
**Compile the project**
gcc main.c create_database.c display.c search.c save.c update.c insert.c file_validation.c -o InvertedSearch

Run with input files
./InvertedSearch file1.txt file2.txt file3.txt
