#ifndef PAGE_H
#define PAGE_H

#include <string>
#include "nlohmann/json.hpp"

struct Page {

  std::string title;
  std::string author;
  std::string genre;
  std::string text;
  int rating;

  friend void to_json(nlohmann::json& j, const Page& page);
  friend void from_json(const nlohmann::json& j, Page& page);

};

#endif
