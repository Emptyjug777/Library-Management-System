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