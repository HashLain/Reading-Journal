#ifndef JOURNAL_H
#define JOURNAL_H

#include "Page.h"
#include <vector>
#include <fstream>
#include <iostream>

class Journal {
  public:

    void viewPage(Page* page) const;

    void addPage(const Page& page);

    std::vector<Page*> search(const std::string& query) const;

    void editPage(Page* page, const Page& newPage);

    void deletePage(Page* page);

    void saveJournal();

    void loadJournal();

  private:

    std::vector<Page*> pages;

    const std::string filename = "Library";
};

#endif; 
