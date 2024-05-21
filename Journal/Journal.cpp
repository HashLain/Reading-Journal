#include "Journal.h"
#include "../JournalEntry/JournalEntry.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void Journal::addEntry(const JournalEntry& page) {
  pages.push_back(page);
}

std::vector<JournalEntry> Journal::getEntries() const {
  return pages; 
}

void Journal::createCategory(const std::string& category) {
  if (categories.find(category) == categories.end()) {
    categories[category] = std::vector<int>();
  }
}

std::vector<JournalEntry> Journal::getEntriesByCatergory(const std::string& category) const {
  std::vector<JournalEntry> result;
  if (categories.find(category) != categories.end()) {
    const auto& entryIds = categories.at(category);
    for (int id : entryIds) {
      for (const auto& entry : pages) {
        if (entry.getId() == id) {
          result.push_back(entry);
          break;
        }
      }
    }
  }
  return result;
}

void Journal::addEntryToCategory(const std::string& category, int entryId) {
  if (categories.find(category) != categories.end()) {
    categories[category].push_back(entryId);
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
  std::ofstream outfile(filename);
  if (!outfile) {
    throw std::runtime_error("Unable to write into file " + filename);
  }

  for (const auto& entry : pages) {
    outfile << "ENTRY" << std::endl;
    outfile << entry.getId() << std::endl;
    outfile << entry.getBookTitle() << std::endl;
    outfile << entry.getAuthor() << std::endl;
    outfile << entry.getGenre() << std::endl;
    outfile << entry.getEntry() << std::endl;
    outfile << entry.getStartDate() << std::endl;
    outfile << entry.getEndDate() << std::endl;
  }

  for (const auto& categoryPair : categories) {
    outfile << "CATEGORY:" << categoryPair.first << std::endl;
    for (int entryId : categoryPair.second) {
      outfile << entryId << std::endl;
    }
    outfile << "END_CATEGORY" << std::endl;
  }
  outfile.close();
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
  int id;
  std::string bookTitle, author, genre, entry, startDate, endDate;

  while (std::getline(inFile, line)) {
    if (line == "ENTRY") {
      inFile >> id; inFile.ignore();
      std::getline(inFile, bookTitle);
      std::getline(inFile, author);
      std::getline(inFile, genre);
      std::getline(inFile, entry);
      std::getline(inFile, startDate);
      std::getline(inFile, endDate);

      JournalEntry newEntry(bookTitle, author, genre, entry, startDate, endDate);
      newEntry.setId(id);
      addEntry(newEntry);
    } 
    else if (line.find("CATEGORY:") == 0){
      category = line.substr(9);
      createCategory(category);
    }
    else if (line == "END_CATEGORY") {
      category.clear();
    }
    else if (!category.empty()) {
      int entryId = std::stoi(line);
      addEntryToCategory(category, entryId);
    }
  }

  inFile.close();
}
