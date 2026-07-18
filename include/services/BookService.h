#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include <vector>

#include "database/Database.h"
#include "models/Book.h"

class BookService
{
private:
    Database& database;

public:
    BookService(Database& database);

    bool addBook(const Book& book);

    std::vector<Book> getAllBooks();

    Book getBookByISBN(const std::string& isbn);
    bool updateBook(const Book& book);
    bool deleteBook(int id);
};

#endif