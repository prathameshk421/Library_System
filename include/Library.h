#pragma once
#include <vector>
#include "Book.h"

using namespace std;

class Library
{
    vector<Book> books;

public:
    Library();
    bool load_data(const string &file_path);
    bool save_data(const string &file_path);
    void add_book(const Book &book);
    bool remove_book(const Book &book);
    Book *find_book(const Book &book);
    vector<string> listAllBooks() const;
    bool borrow_book(const Book &book);
    bool return_book(const Book &book);
    bool update_book(const Book &book);
};