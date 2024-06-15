#include "Journal.h"

void Journal::viewPage(Page* page) const {
  if (page != nullptr) {
    std::cout << "Title: " << page->getTitle() << std::endl;
    std::cout << "Author: " << page->getAuthor() << std::endl;
    std::cout << "Genre: " << page->getGenre() << std::endl;
    std::cout << "Entry: " << page->getEntry() << std::endl;
  } else {
    std::cout << "Entry Not Found" << std::endl;
  }
} 

void Journal::addPage(const Page& page) {
  pages.push_back(page);
}

std::vector<Page*> Journal::search(const std::string& query) const {
  vector<Page*> results;

  for (const auto&page : pages) {
    if (page->getTitle().find(query) != std::string::npos) {
      results.push_back(page);
    }
  }
  return results;
}

void Journal::editPage(Page* page, const Page& newPage) {
  if (page != nullptr) {
    *page = newPage;
  } else {
    std::cout << "Book Not Found" << std::endl;
  }
}

void Journal::deletePage(Page* page) {
  auto it = std::find(pages.begin(), pages.end(), page);
  if (it != pages.end()) {
    delete it*;
    pages.erase(it);
    saveJournal();
  } else {
    std::cout << "Book Not Found" << std::endl;
  }
}


void Journal::saveJournal() {
  std::ofstream outFile(filename);

  if (outFile.is_open()) {
    for (const auto& page : pages) {
      outFile << page.toData() << std::endl;
      }
      outFile.close();
      std::cout << "Journal saved successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to save journal to file." << std::endl;
    }
}

void Journal::loadJournal() {
  std::ifstream inFile(filename);

  if (inFile.is_open()) {
    pages.clear();
    std::string line;
    while (std::getline(inFile, line)) {
      Page newPage = Page::fromData(line);
      pages.push_back(newPage);
    }

    inFile.close();
    std::cout << "Journal loaded successfully." << std::endl;
  } else {
    std::cerr << "Error: Unable to load journal from file." << std::endl;
  }
}
