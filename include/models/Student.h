#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
private:
    int id;
    std::string name;
    std::string rollNumber;
    std::string department;

public:
    Student();
    Student(int id, const std::string& name, const std::string& rollNumber,
            const std::string& department);

    int getId() const;
    std::string getName() const;
    std::string getRollNumber() const;
    std::string getDepartment() const;

    void setId(int id);
    void setName(const std::string& name);
    void setRollNumber(const std::string& rollNumber);
    void setDepartment(const std::string& department);
};

#endif