#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    bool available;

public:
    Book();

    Book(int id,
         const std::string& title,
         const std::string& author,
         const std::string& isbn,
         bool available);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isAvailable() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setISBN(const std::string& isbn);
    void setAvailability(bool available);
};

#endif