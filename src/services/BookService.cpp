#include "services/BookService.h"

BookService::BookService(Database& database)
    : database(database)
{
}

bool BookService::addBook(const Book& book)
{
    std::string sql =
        "INSERT INTO books (title, author, isbn, available) VALUES ('" +
        book.getTitle() + "', '" +
        book.getAuthor() + "', '" +
        book.getISBN() + "', " +
        std::to_string(book.isAvailable()) +
        ");";

    return database.execute(sql);
}
std::vector<Book> BookService::getAllBooks()
{
    std::vector<Book> books;

    sqlite3_stmt* stmt;

    std::string sql = "SELECT * FROM books;";

    if (sqlite3_prepare_v2(database.getDatabase(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return books;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Book book(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4)
        );

        books.push_back(book);
    }

    sqlite3_finalize(stmt);

    return books;
}
Book BookService::getBookByISBN(const std::string& isbn)
{
    sqlite3_stmt* stmt;

    std::string sql = "SELECT * FROM books WHERE isbn = ?;";

    if (sqlite3_prepare_v2(database.getDatabase(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return Book();
    }

    sqlite3_bind_text(stmt, 1, isbn.c_str(), -1, SQLITE_STATIC);

    Book book;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        book = Book(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4)
        );
    }

    sqlite3_finalize(stmt);

    return book;
}
bool BookService::updateBook(const Book& book)
{
    std::string sql =
        "UPDATE books SET "
        "title = '" + book.getTitle() +
        "', author = '" + book.getAuthor() +
        "', isbn = '" + book.getISBN() +
        "', available = " + std::to_string(book.isAvailable()) +
        " WHERE id = " + std::to_string(book.getId()) + ";";

    return database.execute(sql);
}
bool BookService::deleteBook(int id)
{
    std::string sql =
        "DELETE FROM books WHERE id = " + std::to_string(id) + ";";

    return database.execute(sql);
}