#include "Journal.h"
#include "JournalEntry.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void Journal::addEntry(const JournalEntry& page) {
  pages.push_back(page);
}

std::vector<JournalEntry> Journal::getEntries() const {
  return pages; 
}

std::vector<JournalEntry> Journal::getEntriesByCatergory(const std::string& category) const {
  if (categories.find(category) != categories.end()) {
    return categories.at(category);
  }
  return {};
}

void Journal::addEntryToCategory(const std::string& category, const JournalEntry& page) {
  if (categories.find(category) != categories.end()) {
    categories[category].push_back(page);
  }
}

bool Journal::categoryExists(const std::string& category) const {
  return categories.find(category) != categories.end();
}

void Journal::deleteCategory(const std::string& category) {
  auto it = categories.find(category);
  if (it != categories.end()) {
    categories.erase(it);
  }
}

void Journal::saveToFile(std::string& filename) const {
  std::ofstream outFile(filename);
  if (!outFile) {
    throw std::runtime_error("Unable to open file: " + filename);
  }

  for (const auto& categoryEntry : categories) {
    outFile << "CATEGORY:" << categoryEntry.first << '\n';
    for (const auto& entry : categoryEntry.second) {
      outFile << "ENTRY\n"
              << entry.getBookTitle() << '\n'
              << entry.getAuthor() << '\n'
              << entry.getGenre() << '\n'
              << entry.getEntry() << '\n'
              << entry.getStartDate() << '\n'
              << entry.getEndDate() << '\n'
              << "---\n";
    }
  }

  outFile.close();
}

void Journal::loadFromFile(const std::string& filename) {
  std::ifstream inFile(filename);
  if (!inFile) {
    throw std::runtime_error("Unable to read from file: " + filename);
  }

  pages.clear();
  categories.clear();

  std::string line;
  std::string category;
  std::string bookTitle, author, genre, entry, startDate, endDate;

  while(std::getline(inFile, line)) {
    
    if (line.find("CATEGORY:") == 0) {
      category = line.substr(9);
      createCategory(category);

    } else if (line == "ENTRY") {
      
      std::getline(inFile, bookTitle);
      std::getline(inFile, author);
      std::getline(inFile, genre);
      std::getline(inFile, entry);
      std::getline(inFile, startDate);
      std::getline(inFile, endDate);
      std::getline(inFile, line);

      JournalEntry newEntry(bookTitle, author, genre, entry, startDate, endDate);
      addEntry(newEntry);

      if (!category.empty()) {
        addEntryToCategory(category, newEntry);
      }

    }
  }

  inFile.close();
}
