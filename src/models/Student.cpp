#include "models/Student.h"

Student::Student()
{
    id = 0;
}

Student::Student(int id, const std::string& name,
                 const std::string& rollNumber,
                 const std::string& department)
{
    this->id = id;
    this->name = name;
    this->rollNumber = rollNumber;
    this->department = department;
}

int Student::getId() const
{
    return id;
}

std::string Student::getName() const
{
    return name;
}

std::string Student::getRollNumber() const
{
    return rollNumber;
}

std::string Student::getDepartment() const
{
    return department;
}

void Student::setId(int id)
{
    this->id = id;
}

void Student::setName(const std::string& name)
{
    this->name = name;
}

void Student::setRollNumber(const std::string& rollNumber)
{
    this->rollNumber = rollNumber;
}

void Student::setDepartment(const std::string& department)
{
    this->department = department;
}
