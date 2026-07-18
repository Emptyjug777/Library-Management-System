#include "models/Transaction.h"

Transaction::Transaction()
{
    id = 0;
    bookId = 0;
    studentId = 0;
}

Transaction::Transaction(int id, int bookId, int studentId,
                         const std::string& issueDate,
                         const std::string& returnDate)
{
    this->id = id;
    this->bookId = bookId;
    this->studentId = studentId;
    this->issueDate = issueDate;
    this->returnDate = returnDate;
}

int Transaction::getId() const
{
    return id;
}

int Transaction::getBookId() const
{
    return bookId;
}

int Transaction::getStudentId() const
{
    return studentId;
}

std::string Transaction::getIssueDate() const
{
    return issueDate;
}

std::string Transaction::getReturnDate() const
{
    return returnDate;
}

void Transaction::setId(int id)
{
    this->id = id;
}

void Transaction::setBookId(int bookId)
{
    this->bookId = bookId;
}

void Transaction::setStudentId(int studentId)
{
    this->studentId = studentId;
}

void Transaction::setIssueDate(const std::string& issueDate)
{
    this->issueDate = issueDate;
}

void Transaction::setReturnDate(const std::string& returnDate)
{
    this->returnDate = returnDate;
}