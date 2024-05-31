#include "Page.h"

void to_json(nlohmann::json& j, Page& page) {
  j = nlohmann::json{{"title", page.title}, {"author", page.title}, {"genre", page.genre}, {"text", page.text}, {"rating", page.rating}};
}

void from_json(const nlohmann::json& j, Page& page) {
  j.at("title").get_to(page.title);
  j.at("author").get_to(page.author);
  j.at("genre").get_to(page.genre);
  j.at("text").get_to(page.text);
  j.at("rating").get_to(page.rating);
}
