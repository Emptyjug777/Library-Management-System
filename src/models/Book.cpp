#include "models/Book.h"

Book::Book()
{
    id = 0;
    available = true;
}

Book::Book(int id,
           const std::string& title,
           const std::string& author,
           const std::string& isbn,
           bool available)
{
    this->id = id;
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->available = available;
}

int Book::getId() const
{
    return id;
}

std::string Book::getTitle() const
{
    return title;
}

std::string Book::getAuthor() const
{
    return author;
}

std::string Book::getISBN() const
{
    return isbn;
}

bool Book::isAvailable() const
{
    return available;
}

void Book::setTitle(const std::string& title)
{
    this->title = title;
}

void Book::setAuthor(const std::string& author)
{
    this->author = author;
}

void Book::setISBN(const std::string& isbn)
{
    this->isbn = isbn;
}

void Book::setAvailability(bool available)
{
    this->available = available;
}