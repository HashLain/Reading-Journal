#include <iostream>
#include <string>
#include "Journal/Journal.h"
#include "JournalEntry/JournalEntry.h"

void displayMenu() {
  std::cout << "Reading Journal\n";
  std::cout << "1. Add Entry\n";
  std::cout << "2. Create Category\n";
  std::cout << "3. Add Entry to Category\n";
  std::cout << "4. List All Entries\n";
  std::cout << "5. List Entries in Category\n";
  std::cout << "6. Delete Category\n";
  std::cout << "7. Save Journal\n";
  std::cout << "8. Load Journal\n";
  std::cout << "9. Exit Program\n";
}

void addEntry(Journal& journal) {
  std::cout << "Enter Book Information. Leave Blank if no Entry\n";
  std::string bookTitle, author, genre, entry, startDate, endDate;
  std::cout << "Enter Book Title\n";
  std::getline(std::cin, bookTitle);
  std::cout << "Enter Author Name\n";
  std::getline(std::cin, author);
  std::cout << "Enter Book's Genre\n";
  std::getline(std::cin, genre);
  std::cout << "Enter Start Date of Book Read\n";
  std::getline(std::cin, startDate);
  std::cout << "Enter Finish Date of Book Read\n";
  std::getline(std::cin, endDate);

  JournalEntry newEntry(bookTitle, author, genre, entry, startDate, endDate);
  journal.addEntry(newEntry);
  std::cout << "New Entry Added to Reading Journal\n";
}

void createCategory(Journal& journal) {
  std::string category;
  std::cout << "Enter Name of New Category\n";
  std::getline(std::cin, category);
  journal.createCategory(category);
  std::cout << "Category Added to Reading Journal\n";
}

void addEntryToCategory(Journal& journal) {
  std::string category, bookTitle; 
  std::cout << "Which Book Would You Like to Add to a Category?\n";
  std::getline(std::cin, bookTitle);
  std::cout << "Which Category Would You Like to Put the Book in?\n";
  std::getline(std::cin, category);

  for (const auto& entry : journal.getEntries()) {
    if (entry.getBookTitle() == bookTitle) {
      journal.addEntryToCategory(category, entry);
      std::cout << "Book Entry Added to Category\n";
      return;
    }
  }

  std::cout << "Category or Book Entry Does Not Exist. Please Try Again\n"; 
}

void listEntriesInCategory(Journal& journal) {
  std::string category;
  std::cout << "Which Category Do You Want To View?\n";
  std::getline(std::cin, category);
  if (journal.categoryExists(category)) {
    for (const auto& entry : journal.getEntriesByCatergory(category)) {
      std::cout << "Book Title: " << entry.getBookTitle() << "\n";
      std::cout << "Author: " << entry.getAuthor() << "\n";
      std::cout << "Genre: " << entry.getGenre() << "\n";
      std::cout << "Entry: " << entry.getEntry() << "\n";
      std::cout << "Start Date: " << entry.getStartDate() << "\n";
      std::cout << "Date Finished: " << entry.getEndDate() << "\n";
      std::cout << "-------------------------------------------\n";
    }
  } else {
    std::cout << "Category Not Found\n";
  }
}

void ListEntries(Journal& journal) {
  for (const auto& entry : journal.getEntries()) {
    std::cout << "Book Title: " << entry.getBookTitle() << "\n";
  }
}

void deleteCategory(Journal& journal) {
  std::string category;
  std::cout << "Which Category Do You Want to Delete?\n";
  std::getline(std::cin, category);
  journal.deleteCategory(category);
  std::cout << "Category Deleted\n";
}

void saveJournal(const Journal& journal) {
  std::string filename;
  std::cout << "What file would you like to save the journal in?\n";
  std::getline(std::cin, filename);
  journal.saveToFile(filename);
  std::cout << "Filed Saved\n";
}

void loadJournal(Journal& journal) {
  std::string filename;
  std::cout << "What Journal would you like to open?\n";
  std::getline(std::cin, filename);
  journal.loadFromFile(filename);
  std::cout << "Journal Loaded From " << filename << "\n";
}

int main() {
  Journal journal;
  int choice;
  do {
    displayMenu();
    std::cout << "Enter your choice: \n";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1:
        addEntry(journal);
        break;
      case 2:
        createCategory(journal);
        break;
      case 3:
        addEntryToCategory(journal);
        break;
      case 4: 
        ListEntries(journal);
        break;
      case 5:
        listEntriesInCategory(journal);
        break;
      case 6:
        deleteCategory(journal);
        break;
      case 7: 
        saveJournal(journal);
        break;
      case 8:
        loadJournal(journal);
        break;
      case 9:
        std::cout << "Exiting Program...\n";
        break;
      default:
        std::cout << "Invalid Choice. Please Select a Valid Optition.\n";
        break;
    } 
  } while (choice != 9);

  return 0;
}
