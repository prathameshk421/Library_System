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
    void remove_book(const Book &book);
    Book *find_book(const Book &book);
    vector<string> listAllBooks() const;
    void borrow_book(const Book &book);
    void return_book(const Book &book);
    void update_book(const Book &book);
};