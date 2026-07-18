#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include "database/Database.h"
#include "models/Transaction.h"
#include<vector>

class TransactionService
{
private:
    Database& database;

public:
    TransactionService(Database& db);

    bool issueBook(const Transaction& transaction);
    bool returnBook(int transactionId);
    std::vector<Transaction> getAllTransactions();
};

#endif