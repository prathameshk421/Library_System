#include "../include/Library.h"
#include "../include/Book.h"
#include <iostream>
#include <fstream>
#include <sstream>

Library::Library()
{
    cout << "Welcome to Library Management System!!\n";
}

void Library::load_data(const string &books_data_path, const string &borrow_books_data_path)
{
    ifstream books_data(books_data_path);
    ifstream borrow_books_data(borrow_books_data_path);
    if (!books_data.is_open())
        throw runtime_error(books_data_path);
    if (!borrow_books_data.is_open())
        throw runtime_error(borrow_books_data_path);
    bool header = true;
    string book_info;
    while (getline(books_data, book_info))
    {
        if (header)
        {
            header = 0;
            continue;
        }
        stringstream book_object(book_info);
        string index;
        string ISBN, title, author, genre;
        vector<pair<int, string>> due_dates;
        int copies;
        int available_copies;
        string copies_str;
        string available_copies_str;
        getline(book_object, index, ',');
        getline(book_object, ISBN, ',');
        getline(book_object, title, ',');
        getline(book_object, author, ',');
        getline(book_object, genre, ',');
        getline(book_object, copies_str, ',');
        getline(book_object, available_copies_str);
        copies = stoi(copies_str);
        available_copies = stoi(available_copies_str);
        string borrow_book_info;
        borrow_books_data.clear();
        borrow_books_data.seekg(0);
        bool borrow_header = true;
        while (getline(borrow_books_data, borrow_book_info))
        {
            if (borrow_header)
            {
                borrow_header = false;
                continue;
            }
            string id_str, borrow_index, due_date;
            stringstream borrowed_book(borrow_book_info);
            getline(borrowed_book, id_str, ',');
            getline(borrowed_book, borrow_index, ',');
            getline(borrowed_book, due_date);
            int id = stoi(id_str);
            if (index == borrow_index)
                due_dates.push_back({id, due_date});
        }
        if ((copies - due_dates.size()) != available_copies)
            throw runtime_error(book_info);
        Book book_obj(ISBN, title, author, copies, available_copies, due_dates, genre);
        books.push_back(book_obj);
    }
    books_data.close();
    borrow_books_data.close();
}

void Library::add_book(const Book &b)
{
    books.push_back(b);
}

void Library::remove_book(const string &isbn)
{
    int found = 0;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].get_isbn() == isbn)
        {
            books.erase(books.begin() + i);
            found = 1;
            break;
        }
    }
    if (!found)
        throw runtime_error("Book to be deleted not found");
}

Book *Library::find_book(const string &isbn)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].get_isbn() == isbn)
        {
            return &books[i];
        }
    }
    return nullptr;
}

vector<string> Library::listAllBooks()
{
    vector<string> all_info;
    for (int i = 0; i < books.size(); i++)
    {
        all_info.push_back(books[i].get_info());
    }
    return all_info;
}

int Library::borrow_book(const string &isbn, const string &due_date)
{
    Book *target = find_book(isbn);
    if (target == nullptr)
        throw runtime_error("Book with ISBN Code give not found");
    Book &b = *target;
    return b.borrow_copy(due_date);
}

void Library::return_book(const string &isbn, const int &id)
{
    Book *target = find_book(isbn);
    if (target == nullptr)
        throw runtime_error("Book with ISBN Code give not found");
    Book &b = *target;
    b.return_copy(id);
}

void Library::update_book(const Book &b)
{
    Book *target = find_book(b.get_isbn());
    if (target == nullptr)
        throw runtime_error("Book with ISBN Code give not found");

    if (b.get_copies() < target->get_available_copies())
        throw runtime_error("New total copies cannot be less than currently available copies");

    Book &target_book = *target;
    target_book.update_info(b);
}

void Library::save_data(const string &books_data_path, const string &borrow_books_data_path)
{
    ofstream books_data(books_data_path);
    ofstream borrow_books_data(borrow_books_data_path);
    if (!books_data.is_open())
        throw runtime_error("Cannot Open Books Data");
    if (!borrow_books_data.is_open())
        throw runtime_error("Cannot Open Borrow Books Data");
    string header = "index,ISBN,title,author,genre,copies,available_copies\n";
    string header2 = "id,index,due_date\n";
    books_data.clear();
    borrow_books_data.clear();
    books_data << header;
    borrow_books_data << header2;
    for (int i = 0; i < books.size(); i++)
    {
        Book &b = books[i];
        stringstream data;
        data << i;
        vector<string> book_info = b.books_info_data();
        for (int i = 0; i < book_info.size(); i++)
        {
            data << "," << book_info[i];
        }
        books_data << data.str() << '\n';
        vector<pair<int, string>> due_dates = b.borrow_book_info();
        for (int j = 0; j < due_dates.size(); j++)
        {
            stringstream data2;
            data2 << due_dates[j].first;
            data2 << "," << i << "," << due_dates[j].second << '\n';
            borrow_books_data << data2.str();
        }
    }
    books_data.close();
    borrow_books_data.close();
}