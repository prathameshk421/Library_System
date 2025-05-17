#pragma once
#include <vector>
#include "Book.h"

using namespace std;

class Library
{
    vector<Book> books;
public:
    Library();
    void load_data(const string &books_data_path,const string& borrow_books_data_path);
    void save_data(const string &books_data_path,const string& borrow_books_data_path);
    void add_book(const Book &book);
    void remove_book(const string& isbn);
    Book *find_book(const string &isbn);
    vector<string> listAllBooks();
    int borrow_book(const string& isbn,const string& due_date);
    void return_book(const string &isbn,const int& id);
    void update_book(const Book &book);
};