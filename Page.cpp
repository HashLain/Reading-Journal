#include "Page.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

// Constructor
Page::Page(const std::string& title, const std::string& author, const std::string& genre, const std::string& thoughts)
    : title(title), author(author), genre(genre), thoughts(thoughts) {}

// Getter methods
std::string Page::getTitle() const {
    return title;
}

std::string Page::getAuthor() const {
    return author;
}

std::string Page::getGenre() const {
    return genre;
}

std::string Page::getThoughts() const {
    return thoughts;
}

// Serialization & Deserialization functions
std::string Page::toData() const {
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("title", rapidjson::Value(title.c_str(), allocator).Move(), allocator);
    doc.AddMember("author", rapidjson::Value(author.c_str(), allocator).Move(), allocator);
    doc.AddMember("genre", rapidjson::Value(genre.c_str(), allocator).Move(), allocator);
    doc.AddMember("entry", rapidjson::Value(thoughts.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

Page Page::fromData(const std::string& data) {
    rapidjson::Document doc;
    doc.Parse(data.c_str());

    std::string title = doc["title"].GetString();
    std::string author = doc["author"].GetString();
    std::string genre = doc["genre"].GetString();
    std::string entry = doc["entry"].GetString();

    return {title, author, genre, entry};
}
