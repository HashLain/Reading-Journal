#ifndef PAGE_H
#define PAGE_H

#include <string>
private:
  std::string title;
  std::string author;
  std::string genre;
  std::string entry;

public:
  Page(const std::string& title, const std::string& author, const std::string& genre, const std::string& thoughts);
  std::string getTitle() const;
  std::string getAuthor() const;
  std::string getGenre() const;
  std::string getEntry() const;
  
  std::string toData() const;
  static Page fromDate(const std::string& data);

 
#endif
