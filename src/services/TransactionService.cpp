#include "services/TransactionService.h"
#include<iostream>
#include<vector>

TransactionService::TransactionService(Database& db)
    : database(db)
{
}
bool TransactionService::issueBook(const Transaction& transaction)
{
    sqlite3_stmt* stmt;

    // Check if Book ID exists
    std::string bookSql = "SELECT COUNT(*) FROM books WHERE id = ?;";

    if (sqlite3_prepare_v2(database.getDatabase(), bookSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, transaction.getBookId());

    if (sqlite3_step(stmt) != SQLITE_ROW || sqlite3_column_int(stmt, 0) == 0)
    {
        sqlite3_finalize(stmt);
        std::cout << "Book not found.\n";
        return false;
    }

    sqlite3_finalize(stmt);

    // Check if Student ID exists
    std::string studentSql = "SELECT COUNT(*) FROM students WHERE id = ?;";

    if (sqlite3_prepare_v2(database.getDatabase(), studentSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, transaction.getStudentId());

    if (sqlite3_step(stmt) != SQLITE_ROW || sqlite3_column_int(stmt, 0) == 0)
    {
        sqlite3_finalize(stmt);
        std::cout << "Student not found.\n";
        return false;
    }

    sqlite3_finalize(stmt);

    // Check if the book is available
    std::string checkSql =
        "SELECT available FROM books WHERE id = ?;";

    if (sqlite3_prepare_v2(database.getDatabase(), checkSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, transaction.getBookId());

    bool available = false;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        available = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (!available)
    {
        std::cout << "Book is already issued!\n";
        return false;
    }

    // Insert transaction
    std::string insertSql =
        "INSERT INTO transactions (bookId, studentId, issueDate, returnDate) VALUES (" +
        std::to_string(transaction.getBookId()) + ", " +
        std::to_string(transaction.getStudentId()) + ", '" +
        transaction.getIssueDate() + "', '" +
        transaction.getReturnDate() + "');";

    // Update availability
    std::string updateSql =
        "UPDATE books SET available = 0 WHERE id = " +
        std::to_string(transaction.getBookId()) + ";";

    return database.execute(insertSql) &&
           database.execute(updateSql);
}
bool TransactionService::returnBook(int transactionId)
{
    sqlite3_stmt* stmt;

    std::string checkSql =
        "SELECT bookId, returnDate FROM transactions WHERE id = ?;";

    if (sqlite3_prepare_v2(database.getDatabase(), checkSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, transactionId);

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        std::cout << "Transaction not found.\n";
        return false;
    }

    int bookId = sqlite3_column_int(stmt, 0);

    const unsigned char* returnDateText = sqlite3_column_text(stmt, 1);

    if (returnDateText != nullptr &&
        std::string(reinterpret_cast<const char*>(returnDateText)) != "")
    {
        sqlite3_finalize(stmt);
        std::cout << "Book has already been returned.\n";
        return false;
    }

    sqlite3_finalize(stmt);

    std::string updateTransaction =
        "UPDATE transactions SET returnDate = '2026-07-18' WHERE id = " +
        std::to_string(transactionId) + ";";

    std::string updateBook =
        "UPDATE books SET available = 1 WHERE id = " +
        std::to_string(bookId) + ";";

    return database.execute(updateTransaction) &&
           database.execute(updateBook);
}
std::vector<Transaction> TransactionService::getAllTransactions()
{
    std::vector<Transaction> transactions;

    sqlite3_stmt* stmt;

    std::string sql =
        "SELECT id, bookId, studentId, issueDate, returnDate FROM transactions;";

    if (sqlite3_prepare_v2(database.getDatabase(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return transactions;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Transaction transaction(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
                ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
                : ""
        );

        transactions.push_back(transaction);
    }

    sqlite3_finalize(stmt);

    return transactions;
}