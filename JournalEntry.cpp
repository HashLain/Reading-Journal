#include "JournalEntry.h"

JournalEntry::JournalEntry(const std::string& bookTitle, const std::string& author, const std::string& genre, const std::string& entry, const std::string& startDate, const std::string& endDate) : bookTitle(bookTitle), author(author), genre(genre), entry(entry), startDate(startDate), endDate(endDate) {}

std::string JournalEntry::getBookTitle() const {
  return bookTitle;
}

std::string JournalEntry::getAuthor() const {
  return author;
}

std::string JournalEntry::getEntry() const {
  return entry;
}

std::string JournalEntry::getGenre() const {
  return genre;
}

std::string JournalEntry::getStartDate() const {
  return startDate;
}

std::string JournalEntry::getEndDate() const {
  return endDate;
}

void JournalEntry::setBookTitle(const std::string& bookTitle) {
  this->bookTitle = bookTitle;
}

void JournalEntry::setAuthor(const std::string& author) {
  this->author = author;
}

void JournalEntry::setGenre(const std::string& genre) {
  this->genre = genre;
}

void JournalEntry::setEntry(const std::string& entry) {
  this->entry = entry;
}

void JournalEntry::setStartDate(const std::string& startDate) {
  this->startDate = startDate;
}

void JournalEntry::setEndDate(const std::string& endDate) {
  this->endDate = endDate;
}

void JournalEntry::appendEntry(const std::string& addEntry) {
  if (!this->entry.empty()) {
    this->entry += "\n";
  }
  this->entry += addEntry;
}

void JournalEntry::updateEntry(const std::string& updateEntry) {
  this->entry = updateEntry;
}
