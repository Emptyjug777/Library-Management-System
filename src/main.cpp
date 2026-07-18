// gcc -c external/sqlite/sqlite3.c -o sqlite3.o
//g++ src/main.cpp src/database/Database.cpp src/models/Book.cpp src/models/Student.cpp src/models/Transaction.cpp src/services/BookService.cpp src/services/StudentService.cpp src/services/TransactionService.cpp sqlite3.o -Iinclude -Iexternal/sqlite -o LMS.exe
 #include "database/Database.h"
#include "services/BookService.h"
#include "models/Book.h"
#include "services/StudentService.h"
#include "models/Student.h"
#include "services/TransactionService.h"
#include <iostream>

int main()
{
    Database database;

    if (!database.connect("database/library.db"))
    {
        return 1;
    }

    database.createTables();
    TransactionService transactionService(database);

std::vector<Transaction> transactions = transactionService.getAllTransactions();

for (const auto& transaction : transactions)
{
    std::cout << "Transaction ID: " << transaction.getId() << "\n";
    std::cout << "Book ID: " << transaction.getBookId() << "\n";
    std::cout << "Student ID: " << transaction.getStudentId() << "\n";
    std::cout << "Issue Date: " << transaction.getIssueDate() << "\n";
    std::cout << "Return Date: " << transaction.getReturnDate() << "\n\n";
}

}