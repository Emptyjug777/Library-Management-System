# 📚 Library Management System

A console-based **Library Management System** developed in **C++** using **SQLite** for persistent data storage. The project follows Object-Oriented Programming (OOP) principles and provides complete book, student, and transaction management.

---

## ✨ Features

### 📖 Book Management
- Add Book
- View Books
- Update Book
- Delete Book
- Search Book by ISBN
- Search Book by Title

### 👨‍🎓 Student Management
- Add Student
- View Students
- Update Student
- Delete Student
- Search Student by Roll Number

### 🔄 Library Transactions
- Issue Book
- Return Book
- View Transaction History

### ✅ Data Validation
- Prevent duplicate ISBN entries
- Prevent duplicate Roll Number entries
- Validate Book ID before issuing
- Validate Student ID before issuing
- Prevent issuing unavailable books
- Validate Transaction ID before returning
- Prevent returning an already returned book
- Input validation for menu options

---

# 🛠 Tech Stack

- **Language:** C++
- **Database:** SQLite3
- **Programming Paradigm:** Object-Oriented Programming (OOP)
- **Libraries:** Standard Template Library (STL)
- **Version Control:** Git & GitHub

---

# 📂 Project Structure

```
Library-Management-System/
│
├── database/
│   └── library.db
│
├── external/
│   └── sqlite/
│
├── include/
│
├── src/
│   ├── database/
│   ├── models/
│   ├── services/
│   └── main.cpp
│
├── README.md
└── .gitignore
```

---

# 🚀 Build & Run

## 1. Compile SQLite

```bash
gcc -c external/sqlite/sqlite3.c -o sqlite3.o
```

## 2. Compile the Project

```bash
g++ src/main.cpp src/database/Database.cpp src/models/Book.cpp src/models/Student.cpp src/models/Transaction.cpp src/services/BookService.cpp src/services/StudentService.cpp src/services/TransactionService.cpp sqlite3.o -Iinclude -Iexternal/sqlite -o LMS.exe
```

## 3. Run

```bash
./LMS.exe
```

or on Windows PowerShell:

```powershell
.\LMS.exe
```

---

# 📸 Screenshots

Add screenshots after pushing the project.

Example:

```
screenshots/
│
├── menu.png
├── books.png
├── students.png
├── transactions.png
```

Then include them:

```markdown
## Main Menu

![Main Menu](screenshots/menu.png)

## Book Management

![Books](screenshots/books.png)

## Transaction History

![Transactions](screenshots/transactions.png)
```

---

# 🎯 Sample Menu

```
=====================================================
           LIBRARY MANAGEMENT SYSTEM
=====================================================

1. Add Book
2. View Books
3. Update Book
4. Delete Book
5. Add Student
6. View Students
7. Update Student
8. Delete Student
9. Issue Book
10. Return Book
11. View Transactions
12. Search Book by ISBN
13. Search Student by Roll Number
14. Search Book by Title
0. Exit
```

---

# 🔮 Future Improvements

- User Authentication
- Fine Calculation
- Due Date Tracking
- Book Reservation
- GUI Version
- Barcode Support

---

# 👨‍💻 Author

**Mithil Ravirala**