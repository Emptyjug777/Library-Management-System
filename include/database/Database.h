#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database
{
private:
    sqlite3* db;

public:
    Database();
    ~Database();//To close the database

    bool connect(const std::string& dbName);
    void close();

    bool execute(const std::string& sql);
    bool createTables();
};

#endif