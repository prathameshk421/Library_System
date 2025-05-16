#pragma once
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Book
{
private:
    string ISBN, title, author, genre;
    vector<pair<int, string>> due_dates;
    int copies;
    int available_copies;

public:
    Book(const string &isbn, const string &title, const string &author, const int &copies, const int &available_copies, const vector<pair<int, string>> &due_dates, const string &genre);
    Book();
    void borrow_copy(const int &id, const string &due_date);
    void return_copy(const int &id);
    string get_info();
    void update_info(const Book &updated_book);
};