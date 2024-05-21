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
  std::cout << "9. Update an Entry\n";
  std::cout << "10. Exit Program\n";
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
  std::cout << "What Are You're Thoughts on the Book?\n";
  std::getline(std::cin, entry);
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
      journal.addEntryToCategory(category, entry.getId());
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

void updateEntry(Journal& journal) {
  std::string bookTitle;
  std::cout << "Which book Would You Like to Update?\n";
  std::cout << "Select one of the numbered options\n";
  std::getline(std::cin, bookTitle);

  for (auto& entry : journal.getEntries()) {
    if (entry.getBookTitle() == bookTitle) {
      std::cout << "What Would You Like to Update?/n";
      std::cout <<"1. Book Title\n";
      std::cout << "2. Author\n";
      std::cout << "3. Genre\n";
      std::cout << "4. Book's Entry\n";
      std::cout << "5. Start Date\n";
      std::cout << "6. End Date\n";
      std::cout << "7. Exit\n";

      int choice;
      std::cout << "Enter your choice\n";
      std::cin >> choice;
      std::cin.ignore();

      std::string input;
      switch (choice) {
        case 1:
          std::cout << "Enter New Book Title\n";
          std::getline(std::cin, input);
          entry.setBookTitle(input);
          break;
        case 2:
          std::cout << "Enter New Author Name\n";
          std::getline(std::cin, input);
          entry.setAuthor(input);
          break;
        case 3:
          std::cout << "Enter New Genre\n";
          std::getline(std::cin, input);
          entry.setGenre(input);
          break;
        case 4: 
          std::cout << "Update Book Entry\n";
          std::getline(std::cin, input);
          entry.setEntry(input);
          break;
        case 5:
          std::cout << "Enter New Start Date\n";
          std::getline(std::cin, input);
          entry.setStartDate(input);
          break;
        case 6:
          std::cout << "Enter New Finish Date\n";
          std::getline(std::cin, input);
          entry.setEntry(input);
          break;
        case 7:
          std::cout << "Update Cancelled\n";
          return;
        default:
          std::cout << "Invalid Option, Choose Again\n";
          break;
      }
      return;
    }
  }
  std::cout << "Book Entry Not Found. Try Again\n";
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
        updateEntry(journal);
        break;
      case 10: 
        std::cout << "Exiting Program...\n";
        break;
      default:
        std::cout << "Invalid Choice. Please Select a Valid Optition.\n";
        break;
    } 
  } while (choice != 10);

  return 0;
}
