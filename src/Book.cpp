#include "Book.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Book::Book()
{
    ISBN = title = author = genre = "";
    due_dates = {};
    copies = available_copies = 0;
}

Book::Book(const string &ISBN, const string &title, const string &author, const int &copies, const int &available_copies, const vector<pair<int, string>> &due_dates, const string &genre)
{
    this->ISBN = ISBN;
    this->author = author;
    this->title = title;
    this->genre = genre;
    this->due_dates = due_dates;
    if (copies < 0)
        throw runtime_error("Number of Copies cannot be negative");
    if (available_copies < 0)
        throw runtime_error("Number of Available Copies cannot be negative");
    if (copies < available_copies)
        throw runtime_error("Number of Available Copies cannot be more than Total Copies");
    this->copies = copies;
    this->available_copies = available_copies;
}

void Book::borrow_copy(const int &id, const string &due_date)
{
    if (available_copies == 0)
        throw runtime_error("No Copies are Available at the moment");
    due_dates.push_back({id, due_date});
    available_copies--;
}

void Book::return_copy(const int &id)
{
    bool found = false;
    for (int i = 0; i < due_dates.size(); i++)
    {
        if (due_dates[i].first == id)
        {
            due_dates.erase(due_dates.begin() + i);
            found = true;
            available_copies++;
            break;
        }
    }
    if (!found)
        throw runtime_error("Book with id not found");
}

string Book::get_info()
{
    ostringstream oss;
    oss << "ISBN: " << ISBN << "\n"
        << "Title: " << title << "\n"
        << "Author: " << author << "\n"
        << "Genre: " << genre << "\n"
        << "Copies: " << copies << "\n"
        << "Available: " << available_copies << "\n"
        << "Due dates: ";

    for (const auto &d : due_dates)
        oss << d.second << " ";
    oss << "\n";

    return oss.str();
}

void Book::update_info(const Book &updated_book)
{
    *this = updated_book;
}