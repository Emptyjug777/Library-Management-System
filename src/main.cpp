// gcc -c external/sqlite/sqlite3.c -o sqlite3.o
// g++ src/main.cpp src/database/Database.cpp src/models/Book.cpp src/models/Student.cpp src/services/BookService.cpp src/services/StudentService.cpp sqlite3.o -Iinclude -Iexternal/sqlite -o LMS.exe
#include "database/Database.h"
#include "services/BookService.h"
#include "models/Book.h"
#include "services/StudentService.h"
#include "models/Student.h"
#include <iostream>

int main()
{
    Database database;

    if (!database.connect("database/library.db"))
    {
        return 1;
    }

    database.createTables();

StudentService studentService(database);

Student student = studentService.getStudentByRollNumber("22CS1001");

if (studentService.deleteStudent(student.getId()))
{
    std::cout << "Student Deleted Successfully!\n";
}
else
{
    std::cout << "Delete Failed!\n";
}
}