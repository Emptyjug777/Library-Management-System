#include "database/Database.h"
#include <iostream>

Database::Database()
{
    db = nullptr;
}

Database::~Database()
{
    close();
}

bool Database::connect(const std::string& dbName)
{
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK)
    {
        std::cout << "Database connected successfully!\n";
        return true;
    }

    std::cout << "Failed to connect to database!\n";
    return false;
}

void Database::close()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::execute(const std::string& sql)
{
    char* errMsg = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cout << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
bool Database::createTables()
{
    std::string booksTable =
        "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "author TEXT NOT NULL,"
        "isbn TEXT UNIQUE,"
        "available INTEGER DEFAULT 1"
        ");";

    std::string studentsTable =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "rollNumber TEXT UNIQUE"
        ");";

    std::string transactionsTable =
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "bookId INTEGER,"
        "studentId INTEGER,"
        "issueDate TEXT,"
        "returnDate TEXT,"
        "FOREIGN KEY(bookId) REFERENCES books(id),"
        "FOREIGN KEY(studentId) REFERENCES students(id)"
        ");";

    return execute(booksTable) &&
           execute(studentsTable) &&
           execute(transactionsTable);
}
sqlite3* Database::getDatabase()
{
    return db;
}