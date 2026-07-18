#include "services/StudentService.h"

StudentService::StudentService(Database& db)
    : database(db)
{
}

bool StudentService::addStudent(const Student& student)
{
    std::string sql =
        "INSERT INTO students (name, roll_number, department) VALUES ('" +
        student.getName() + "', '" +
        student.getRollNumber() + "', '" +
        student.getDepartment() + "');";

    return database.execute(sql);
}
std::vector<Student> StudentService::getAllStudents()
{
    std::vector<Student> students;

    std::string sql = "SELECT * FROM students;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            Student student(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
            );

            students.push_back(student);
        }
    }

    sqlite3_finalize(stmt);

    return students;
}
Student StudentService::getStudentByRollNumber(const std::string& rollNumber)
{
    Student student;

    std::string sql = "SELECT * FROM students WHERE roll_number = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, rollNumber.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            student.setId(sqlite3_column_int(stmt, 0));
            student.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            student.setRollNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            student.setDepartment(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        }
    }

    sqlite3_finalize(stmt);

    return student;
}
bool StudentService::updateStudent(const Student& student)
{
    std::string sql =
        "UPDATE students SET "
        "name = '" + student.getName() +
        "', department = '" + student.getDepartment() +
        "' WHERE roll_number = '" + student.getRollNumber() + "';";

    return database.execute(sql);
}
bool StudentService::deleteStudent(int id)
{
    std::string sql =
        "DELETE FROM students WHERE id = " + std::to_string(id) + ";";

    return database.execute(sql);
}