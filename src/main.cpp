#include <iostream>
#include "database/Database.h"

int main()
{
    Database database;

    if (database.connect("database/library.db"))
    {
        if (database.createTables())
        {
            std::cout << "Database initialized successfully!\n";
        }
    }

    return 0;
}