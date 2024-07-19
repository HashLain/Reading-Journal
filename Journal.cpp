#include <iostream>
#include <string>
#include "Book.h"
#include "JournalDatabase.h"

void displayMenu() {
  std::cout << "Journal Menu\n";
  std::cout << "1. Add a book\n";
  std::cout << "2. List all books\n";
  std::cout << "3. Edit a book\n";
  std::cout << "4. Delete a book\n";
  std::cout << "5. Exit\n";
  std::cout << "Enter a numbered option: ";
}

Book makeBook() {
  std::string author, title, genre, text;
  double rating;

  std::cout << "Enter author: ";
  std::getline(std::cin, author);
  std::cout << "Enter title: ";
  std::getline(std::cin, title);
  std::cout << "Enter genre: ";
  std::getline(std::cin, genre);
  std::cout << "Enter rating: ";
  std::cin >> rating;
  std::cin.ignore();
  std::cout << "Enter text: ";
  std::getline(std::cin, text);

  return Book(author, title, genre, rating, text);
}

int main() {
  JournalDatabase db;
  db.createTable();

  int choice;
  while (true) {
    displayMenu();
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1: {
        Book book = makeBook();
        db.insertEntry(book);
        break;
      }
      case 2: {
        db.listEntries();
        break;
      }
      case 3: {
        int id;
        db.listEntries();
        std::cout << "Enter book id you wish to edit: ";
        std::cin >> id;
        std::cin.ignore();
        Book book = makeBook();
        db.updateEntry(id, book);
        break;
      }
      case 4: {
        int id;
        db.listEntries();
        std::cout << "Enter id of book you wish to delete: ";
        std::cin >> id;
        std::cin.ignore();
        db.deleteEntry(id);
        break;
      }
      case 5: {
        return 0;
      }
      default: {
        std::cout << "Invalid option. Please select one of the numbered choices.\n";
        break;
      }
    }
  }

  return 0;
}
