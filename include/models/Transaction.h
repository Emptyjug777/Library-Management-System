#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
private:
    int id;
    int bookId;
    int studentId;
    std::string issueDate;
    std::string returnDate;

public:
    Transaction();

    Transaction(int id, int bookId, int studentId,
                const std::string& issueDate,
                const std::string& returnDate);

    int getId() const;
    int getBookId() const;
    int getStudentId() const;
    std::string getIssueDate() const;
    std::string getReturnDate() const;

    void setId(int id);
    void setBookId(int bookId);
    void setStudentId(int studentId);
    void setIssueDate(const std::string& issueDate);
    void setReturnDate(const std::string& returnDate);
};

#endif