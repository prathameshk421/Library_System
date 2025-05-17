#include "../include/Library.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_menu()
{
    cout << "\n=== Library Management System ===\n";
    cout << "1. Add a new book\n";
    cout << "2. Remove a book\n";
    cout << "3. Borrow a book\n";
    cout << "4. Return a book\n";
    cout << "5. Update book information\n";
    cout << "6. List all books\n";
    cout << "7. Save data\n";
    cout << "8. Load data\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void add_book_test(Library &lib)
{
    string isbn, title, author, genre;
    int copies;

    cout << "\nEnter book details:\n";
    cout << "ISBN: ";
    cin >> isbn;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Genre: ";
    getline(cin, genre);
    cout << "Number of copies: ";
    cin >> copies;

    try
    {
        Book new_book(isbn, title, author, copies, copies, {}, genre);
        lib.add_book(new_book);
        cout << "Book added successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void remove_book_test(Library &lib)
{
    string isbn;
    cout << "Enter ISBN of book to remove: ";
    cin >> isbn;

    try
    {
        lib.remove_book(isbn);
        cout << "Book removed successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void borrow_book_test(Library &lib)
{
    string isbn, due_date;
    cout << "Enter ISBN of book to borrow: ";
    cin >> isbn;
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> due_date;

    try
    {
        int id = lib.borrow_book(isbn, due_date);
        cout << "Book borrowed successfully! Borrow ID: " << id << "\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void return_book_test(Library &lib)
{
    string isbn;
    int id;
    cout << "Enter ISBN of book to return: ";
    cin >> isbn;
    cout << "Enter borrow ID: ";
    cin >> id;

    try
    {
        lib.return_book(isbn, id);
        cout << "Book returned successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void update_book_test(Library &lib)
{
    string isbn, title, author, genre;
    int copies;

    cout << "Enter ISBN of book to update: ";
    cin >> isbn;

    Book *existing_book = lib.find_book(isbn);
    if (!existing_book)
    {
        cout << "Book not found!\n";
        return;
    }

    cout << "Enter new details (press Enter to keep current value):\n";
    cout << "Title [" << existing_book->get_info() << "]: ";
    cin.ignore();
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Genre: ";
    getline(cin, genre);
    cout << "Number of copies: ";
    cin >> copies;

    try
    {
        Book updated_book(isbn, title, author, copies, copies, {}, genre);
        lib.update_book(updated_book);
        cout << "Book updated successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void list_books_test(Library &lib)
{
    vector<string> books = lib.listAllBooks();
    if (books.empty())
    {
        cout << "No books in the library.\n";
        return;
    }

    cout << "\n=== Library Catalog ===\n";
    for (const string &book_info : books)
    {
        cout << book_info << "\n";
    }
}

int main()
{
    Library lib;
    int choice;
    const string BOOKS_FILE = "data/books.csv";
    const string BORROWED_FILE = "data/borrowed.csv";

    try
    {
        lib.load_data(BOOKS_FILE, BORROWED_FILE);
        cout << "Data loaded successfully!\n";
    }
    catch (const runtime_error &e)
    {
        cout << "No existing data found. Starting with empty library.\n";
    }

    while (true)
    {
        print_menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_book_test(lib);
            break;
        case 2:
            remove_book_test(lib);
            break;
        case 3:
            borrow_book_test(lib);
            break;
        case 4:
            return_book_test(lib);
            break;
        case 5:
            update_book_test(lib);
            break;
        case 6:
            list_books_test(lib);
            break;
        case 7:
            try
            {
                lib.save_data(BOOKS_FILE, BORROWED_FILE);
                cout << "Data saved successfully!\n";
            }
            catch (const runtime_error &e)
            {
                cout << "Error saving data: " << e.what() << "\n";
            }
            break;
        case 8:
            try
            {
                lib.load_data(BOOKS_FILE, BORROWED_FILE);
                cout << "Data loaded successfully!\n";
            }
            catch (const runtime_error &e)
            {
                cout << "Error loading data: " << e.what() << "\n";
            }
            break;
        case 0:
            cout << "Saving data before exit...\n";
            try
            {
                lib.save_data(BOOKS_FILE, BORROWED_FILE);
                cout << "Data saved successfully!\n";
            }
            catch (const runtime_error &e)
            {
                cout << "Error saving data: " << e.what() << "\n";
            }
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
