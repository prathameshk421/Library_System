# 📚 Library Management System in C++

A simple Library Management System built in C++ using object-oriented programming, CSV-based file handling, and exception handling. This is a command-line mini project intended for learning and demonstration purposes.

---

## 🔧 Features

- Add, remove, and update books
- Borrow and return books with due date tracking
- Track multiple copies of each book
- Store book data in `.csv` files using `fstream`
- Exception handling with `try-catch` blocks
- Clean modular design using OOP (Book and Library classes)

---

## ✅ Requirements

- C++11 or later
- Standard C++ libraries only (no external dependencies)

---

## 🚀 How to Compile and Run

Open your terminal and run one of the following commands:

For g++ (Linux):
```bash
g++ -std=c++11 -I./include src/Book.cpp src/Library.cpp src/main.cpp -o library_system
```

For clang++ (macOS):
```bash
clang++ -std=c++11 -I./include src/Book.cpp src/Library.cpp src/main.cpp -o library_system
```

Then run the program:
```bash
./library_system
```

Note: If you encounter compilation errors with g++ on macOS, use clang++ instead as it's the default compiler on macOS.
