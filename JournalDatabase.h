#ifndef JOURNALDATABASE_H
#define JOURNALDATABASE_H

#include <iostream>
#include <sqlite3.h>
#include "Book.h"

class JournalDatabase {
private:
    sqlite3* db;

    void executeSQL(const std::string& sql) {
        char* errMsg = 0;
        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
        return 0;
    }

    static int callbackPrintEntries(void* data, int argc, char** argv, char** azColName) {
        int id = std::stoi(argv[0]); 
        std::string title = argv[2] ? argv[2] : "NULL";
        std::string author = argv[1] ? argv[1] : "NULL";

        std::cout << id << ". " << title << " by " << author << std::endl;

        return 0;
    }

public:
    JournalDatabase() {
        std::string dbName = "bookshelf.db";
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(1);
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }
    }

    ~JournalDatabase() {
        sqlite3_close(db);
    }

    void createTable() {
        std::string sql = "CREATE TABLE IF NOT EXISTS JOURNAL("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "AUTHOR_NAME TEXT NOT NULL,"
                          "BOOK_TITLE TEXT NOT NULL,"
                          "GENRE TEXT NOT NULL,"
                          "RATING REAL NOT NULL,"
                          "TEXT TEXT NOT NULL);";
        executeSQL(sql);
    }

    void insertEntry(const Book& book) {
        std::string sql = "INSERT INTO JOURNAL (AUTHOR_NAME, BOOK_TITLE, GENRE, RATING, TEXT) VALUES ('" +
                          book.getAuthor() + "', '" + book.getTitle() + "', '" + book.getGenre() + "', " +
                          std::to_string(book.getRating()) + ", '" + book.getText() + "');";
        executeSQL(sql);
    }

    void retrieveEntries() {
        std::string sql = "SELECT * FROM JOURNAL;";
        char* errMsg = 0;
        int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    void deleteEntry(int id) {
        std::string sql = "DELETE FROM JOURNAL WHERE ID = " + std::to_string(id) + ";";
        executeSQL(sql);
    }

    void updateEntry(int id, const Book& updatedBook) {
        std::string sql = "UPDATE JOURNAL SET "
                          "AUTHOR_NAME = '" + updatedBook.getAuthor() + "', "
                          "BOOK_TITLE = '" + updatedBook.getTitle() + "', "
                          "GENRE = '" + updatedBook.getGenre() + "', "
                          "RATING = " + std::to_string(updatedBook.getRating()) + ", "
                          "TEXT = '" + updatedBook.getText() + "' "
                          "WHERE ID = " + std::to_string(id) + ";";
        executeSQL(sql);
    }

    void listEntries() {
        std::string sql = "SELECT ID, AUTHOR_NAME, BOOK_TITLE, GENRE, RATING, TEXT FROM JOURNAL;";

        char* errMsg = 0;
        int rc = sqlite3_exec(db, sql.c_str(), callbackPrintEntries, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
};

#endif 
