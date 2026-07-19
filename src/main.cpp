// gcc -c external/sqlite/sqlite3.c -o sqlite3.o
// g++ src/main.cpp src/database/Database.cpp src/models/Book.cpp src/models/Student.cpp src/models/Transaction.cpp src/services/BookService.cpp src/services/StudentService.cpp src/services/TransactionService.cpp sqlite3.o -Iinclude -Iexternal/sqlite -o LMS.exe

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

#include "database/Database.h"
#include "models/Book.h"
#include "services/BookService.h"
#include "services/StudentService.h"
#include "services/TransactionService.h"

using namespace std;

int main()
{
    Database database;

    if (!database.connect("database/library.db"))
    {
        return 1;
    }

    database.createTables();

    BookService bookService(database);
    StudentService studentService(database);
    TransactionService transactionService(database);

    while (true)
    {
        cout << "\n=====================================================\n";
        cout << "           LIBRARY MANAGEMENT SYSTEM\n";
        cout << "=====================================================\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Update Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Add Student\n";
        cout << "6. View Students\n";
        cout << "7. Update Student\n";
        cout << "8. Delete Student\n";
        cout << "9. Issue Book\n";
        cout << "10. Return Book\n";
        cout << "11. View Transactions\n";
        cout << "12. Search book by ISBN\n";
        cout << "13. Search student by Roll Number\n";
        cout << "14. Search book by Title\n";

        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        int choice;

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string title, author, isbn;

            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Author: ";
            getline(cin, author);

            cout << "Enter ISBN: ";
            getline(cin, isbn);

            Book book(0, title, author, isbn, true);

            if (bookService.addBook(book))
                cout << "\nBook Added Successfully!\n";
            else
                cout << "\nFailed to Add Book!\n";

            break;
        }

        case 2:
        {
            vector<Book> books = bookService.getAllBooks();

            if (books.empty())
            {
                cout << "\nNo books found!\n";
            }
            else
            {
                cout << "\n==============================================================\n";
                cout << left
                     << setw(5) << "ID"
                     << setw(25) << "Title"
                     << setw(20) << "Author"
                     << setw(12) << "ISBN"
                     << setw(10) << "Status" << endl;

                cout << "==============================================================\n";

                for (const auto &book : books)
                {
                    cout << left
                         << setw(5) << book.getId()
                         << setw(25) << book.getTitle()
                         << setw(20) << book.getAuthor()
                         << setw(12) << book.getISBN()
                         << setw(10) << (book.isAvailable() ? "Available" : "Issued")
                         << endl;
                }
            }

            break;
        }

        case 3:
        {
            int id;

            cout << "\nEnter Book ID: ";
            cin >> id;

            if (!(cin))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string title, author, isbn;

            cout << "Enter New Title: ";
            getline(cin, title);

            cout << "Enter New Author: ";
            getline(cin, author);

            cout << "Enter New ISBN: ";
            getline(cin, isbn);

            Book updatedBook(id, title, author, isbn, true);

            if (bookService.updateBook(updatedBook))
                cout << "\nBook updated successfully!\n";
            else
                cout << "\nFailed to update book!\n";

            break;
        }

        case 4:
        {
            int id;

            cout << "\nEnter Book ID to delete: ";
            cin >> id;

            if (!(cin))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            if (bookService.deleteBook(id))
                cout << "\nBook deleted successfully!\n";
            else
                cout << "\nBook not found or deletion failed!\n";

            break;
        }

        case 5:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string name, rollNumber, department;

            cout << "Enter Student Name: ";
            getline(cin, name);

            cout << "Enter Roll Number: ";
            getline(cin, rollNumber);

            cout << "Enter Department: ";
            getline(cin, department);

            Student student(0, name, rollNumber, department);

            if (studentService.addStudent(student))
                cout << "\nStudent added successfully!\n";
            else
                cout << "\nFailed to add student!\n";

            break;
        }
        case 6:
        {
            vector<Student> students = studentService.getAllStudents();

            if (students.empty())
            {
                cout << "\nNo students found!\n";
            }
            else
            {
                cout << "\n=============================================================\n";
                cout << left
                     << setw(5) << "ID"
                     << setw(25) << "Name"
                     << setw(20) << "Roll Number"
                     << setw(20) << "Department" << endl;

                cout << "=============================================================\n";

                for (const auto &student : students)
                {
                    cout << left
                         << setw(5) << student.getId()
                         << setw(25) << student.getName()
                         << setw(20) << student.getRollNumber()
                         << setw(20) << student.getDepartment()
                         << endl;
                }
            }

            break;
        }

        case 7:
        {
            int id;

            cout << "Enter Student ID: ";
            cin >> id;

            if (!(cin))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string name, rollNumber, department;

            cout << "Enter New Name: ";
            getline(cin, name);

            cout << "Enter New Roll Number: ";
            getline(cin, rollNumber);

            cout << "Enter New Department: ";
            getline(cin, department);

            Student student(id, name, rollNumber, department);

            if (studentService.updateStudent(student))
                cout << "\nStudent updated successfully!\n";
            else
                cout << "\nFailed to update student!\n";

            break;
        }

        case 8:
        {
            int id;

            cout << "Enter Student ID to delete: ";
            cin >> id;

            if (!(cin))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID!\n";
                break;
            }

            if (studentService.deleteStudent(id))
                cout << "\nStudent deleted successfully!\n";
            else
                cout << "\nStudent not found or deletion failed!\n";

            break;
        }

        case 9:
        {
            int bookId, studentId;
            string issueDate;

            cout << "Enter Book ID: ";
            cin >> bookId;

            cout << "Enter Student ID: ";
            cin >> studentId;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Issue Date (YYYY-MM-DD): ";
            getline(cin, issueDate);

            Transaction transaction(0, bookId, studentId, issueDate, "");

            if (transactionService.issueBook(transaction))
                cout << "\nBook issued successfully!\n";
            else
                cout << "\nFailed to issue book!\n";

            break;
        }

        case 10:
        {
            int transactionId;

            cout << "Enter Transaction ID: ";
            cin >> transactionId;

            if (!(cin))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Transaction ID!\n";
                break;
            }

            if (transactionService.returnBook(transactionId))
                cout << "\nBook returned successfully!\n";
            else
                cout << "\nFailed to return book!\n";

            break;
        }

        case 11:
        {
            vector<Transaction> transactions = transactionService.getAllTransactions();

            if (transactions.empty())
            {
                cout << "\nNo transactions found!\n";
            }
            else
            {
                cout << "\n=================================================================================\n";

                cout << left
                     << setw(8) << "Txn ID"
                     << setw(10) << "Book ID"
                     << setw(12) << "Student"
                     << setw(15) << "Issue Date"
                     << setw(15) << "Return Date"
                     << endl;

                cout << "=================================================================================\n";

                for (const auto &transaction : transactions)
                {
                    cout << left
                         << setw(8) << transaction.getId()
                         << setw(10) << transaction.getBookId()
                         << setw(12) << transaction.getStudentId()
                         << setw(15) << transaction.getIssueDate()
                         << setw(15)
                         << (transaction.getReturnDate().empty() ? "Not Returned"
                                                                 : transaction.getReturnDate())
                         << endl;
                }
            }

            break;
        }
        case 12:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string isbn;

            cout << "Enter ISBN: ";
            getline(cin, isbn);

            Book book = bookService.getBookByISBN(isbn);

            if (book.getId() == 0)
            {
                cout << "\nBook not found!\n";
            }
            else
            {
                cout << "\n========== BOOK DETAILS ==========\n";
                cout << "ID        : " << book.getId() << endl;
                cout << "Title     : " << book.getTitle() << endl;
                cout << "Author    : " << book.getAuthor() << endl;
                cout << "ISBN      : " << book.getISBN() << endl;
                cout << "Available : "
                     << (book.isAvailable() ? "Yes" : "No") << endl;
            }

            break;
        }
        case 13:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string rollNumber;

            cout << "Enter Roll Number: ";
            getline(cin, rollNumber);

            Student student = studentService.getStudentByRollNumber(rollNumber);

            if (student.getId() == 0)
            {
                cout << "\nStudent not found!\n";
            }
            else
            {
                cout << "\n========== STUDENT DETAILS ==========\n";
                cout << "ID         : " << student.getId() << endl;
                cout << "Name       : " << student.getName() << endl;
                cout << "Roll Number: " << student.getRollNumber() << endl;
                cout << "Department : " << student.getDepartment() << endl;
            }

            break;
        }
        case 14:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string title;

            cout << "Enter Book Title: ";
            getline(cin, title);

            Book book = bookService.getBookByTitle(title);

            if (book.getId() == 0)
            {
                cout << "\nBook not found!\n";
            }
            else
            {
                cout << "\n========== BOOK DETAILS ==========\n";
                cout << "ID        : " << book.getId() << endl;
                cout << "Title     : " << book.getTitle() << endl;
                cout << "Author    : " << book.getAuthor() << endl;
                cout << "ISBN      : " << book.getISBN() << endl;
                cout << "Available : "
                     << (book.isAvailable() ? "Yes" : "No") << endl;
            }

            break;
        }

        case 0:
            cout << "\nExiting...\n";
            database.close();
            return 0;

        default:
            cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}