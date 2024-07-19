#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
  
  private:
    std::string title;
    std::string author;
    std::string genre;
    double rating;
    std::string text;

  public:
    //Constructor
    Book(const std::string& author, const std::string& title, const std::string& genre, double rating, const std::string& text)
        : author(author), title(title), genre(genre), rating(rating), text(text) {}
    
    //Getters
    std::string getAuthor() const { return author; }
    std::string getTitle() const { return title; }
    std::string getGenre() const { return genre; }
    double getRating() const { return rating; }
    std::string getText() const { return text; }
    
    //Setters
    void setAuthor(const std::string& newAuthor) { author = newAuthor; }
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setGenre(const std::string& newGenre) { genre = newGenre; }
    void setRating(double newRating) { rating = newRating; }
    void setText(const std::string& newText) { text = newText; }
};

#endif
