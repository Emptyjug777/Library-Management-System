//gcc -c external/sqlite/sqlite3.c -o sqlite3.o
//g++ src/main.cpp src/database/Database.cpp src/models/Book.cpp src/services/BookService.cpp sqlite3.o -Iinclude -Iexternal/sqlite -o LMS.exe
#include <iostream>
#include <vector>

#include "database/Database.h"
#include "services/BookService.h"
#include "models/Book.h"

int main()
{
    Database database;

    if (!database.connect("database/library.db"))
    {
        return 1;
    }

    database.createTables();

    BookService bookService(database);
Book book = bookService.getBookByISBN("9780132350884");

if (bookService.deleteBook(book.getId()))
{
    std::cout << "Book Deleted Successfully!\n";
}
else
{
    std::cout << "Delete Failed!\n";
}
}