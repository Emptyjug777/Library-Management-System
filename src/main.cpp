#include <iostream>
#include "database/Database.h"

int main()
{
    Database database;

    if (database.connect("database/library.db"))
    {
        std::cout << "Application Started Successfully!" << std::endl;
    }

    return 0;
}