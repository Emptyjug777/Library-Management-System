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

    std::string insertSql =
        "INSERT INTO transactions (bookId, studentId, issueDate, returnDate) VALUES (" +
        std::to_string(transaction.getBookId()) + ", " +
        std::to_string(transaction.getStudentId()) + ", '" +
        transaction.getIssueDate() + "', '" +
        transaction.getReturnDate() + "');";

    std::string updateSql =
        "UPDATE books SET available = 0 WHERE id = " +
        std::to_string(transaction.getBookId()) + ";";

    return database.execute(insertSql) &&
           database.execute(updateSql);
}
bool TransactionService::returnBook(int transactionId)
{
    std::string updateTransaction =
        "UPDATE transactions SET returnDate = '2026-07-18' WHERE id = " +
        std::to_string(transactionId) + ";";

    std::string updateBook =
        "UPDATE books SET available = 1 WHERE id = ("
        "SELECT bookId FROM transactions WHERE id = " +
        std::to_string(transactionId) + ");";

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