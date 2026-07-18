#ifndef STUDENTSERVICE_H
#define STUDENTSERVICE_H

#include <vector>
#include "database/Database.h"
#include "models/Student.h"

class StudentService
{
private:
    Database& database;

public:
    StudentService(Database& db);

    bool addStudent(const Student& student);
    std::vector<Student> getAllStudents();
    Student getStudentByRollNumber(const std::string& rollNumber);
    bool updateStudent(const Student& student);
    bool deleteStudent(int id);
};

#endif