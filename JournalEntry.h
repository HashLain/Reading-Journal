#ifndef JOURNAL_ENTRY_H
#define JOURNAL_ENTRY_H

#include <string>

class JournalEntry {
  private:
    std::string bookTitle;
    std::string author;
    std::string genre;
    std::string entry;
    std::string startDate;
    std::string endDate;

  public:
    //Construct
    JournalEntry(const std::string& bookTitle, const std::string& author, const std::string& genre = "", const std::string& entry = "", const std::string& startDate = "", const std::string& endDate = "");

    //Getters
    std::string getBookTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    std::string getEntry() const;
    std::string getStartDate() const;
    std::string getEndDate() const;

    //Setters
    void setBookTitle(const std::string& bookTitle);
    void setAuthor(const std::string& author);
    void setGenre(const std::string& genre);
    void setEntry(const std::string& entry);
    void setStartDate(const std::string& startDate);
    void setEndDate(const std::string& endDate);

    //Update for Entry
    void appendEntry(const std::string& addEntry);
    void updateEntry(const std::string& updateEntry);
};

#endif
