#include "Library.h"
#include "Book.h"
#include <fstream>
#include <sstream>

void Library::load_data(const string &books_data_path,const string& borrow_books_data_path){
    vector<Book> books;
    ifstream books_data(books_data_path);
    ifstream borrow_books_data(borrow_books_data_path);
    if(!books_data.is_open())
        throw runtime_error("Cannot Open Books Data");
    if(!borrow_books_data.is_open())
        throw runtime_error("Cannot Open Borrow Books Data");
    int header=true;
    string book_info;
    // getline returns a reference to input stream which has a conversion to bool that reflects if the stream is EOF or not 
    while(getline(books_data,book_info)){ 
        if(header){
            header=0;
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
        //index,ISBN,title,author,genre,copies,available_copies
        getline(book_object,index,',');
        getline(book_object,ISBN,',');
        getline(book_object,title,',');
        getline(book_object,author,',');
        getline(book_object,genre,',');
        getline(book_object,copies_str,',');
        getline(book_object,available_copies_str,',');
        // Implement try ,catch in main.cpp for this as stoi gives invalid_argument error
        copies=stoi(copies_str);
        available_copies=stoi(available_copies_str);
        string borrow_book_info;
        // Finding borrowed books of this index
        while(getline(borrow_books_data,borrow_book_info)){
            //id,index,due_date
            string id_str,index,due_date;
            stringstream borrowed_book(borrow_book_info);
            getline(borrowed_book,id_str,',');
            getline(borrowed_book,index,',');
            getline(borrowed_book,due_date,',');
            int id=stoi(id_str);
            due_dates.push_back({id,due_date});
        }
        if((copies - due_dates.size()) !=available_copies)
            throw runtime_error("Data provided is not matching available copies");
        Book book_obj(ISBN, title,author, copies, available_copies,due_dates,genre);
        books.push_back(book_obj);
    }
}
