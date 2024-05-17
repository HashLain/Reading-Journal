#ifndef JOURNAL_H
#define JOURNAL_H

#include "JournalEntry.h"
#include <vector>
#include <unordered_map>
#include <string>

class Journal {
  private:
    std::vector<JournalEntry> pages;
    std::unordered_map<std::string, std::vector<JournalEntry>> categories;

  public:
    
    void addEntry(const JournalEntry& page);
    
    std::vector<JournalEntry> getEntries() const;
    
    std::vector<JournalEntry> getEntriesByCatergory(const std::string& category) const;

    void createCategory(const std::string& category);

    void addEntryToCategory(const std::string& category, const JournalEntry& page);

    bool categoryExists(const std::string& category) const;

    void deleteCategory(const std::string& category);

    void saveToFile(std::string& filename) const;

    void loadFromFile(const std::string& filename);
};

#endif
