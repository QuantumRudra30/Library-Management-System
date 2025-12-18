#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    bool issued;

public:
    Book(int id, string t, string a, bool i = false) {
        bookID = id;
        title = t;
        author = a;
        issued = i;
    }

    int getID() {
        return bookID;
    }

    bool isIssued() {
        return issued;
    }

    void issueBook() {
        issued = true;
    }

    void returnBook() {
        issued = false;
    }

    void display() {
        cout << bookID << "\t" << title << "\t" << author << "\t";
        if (issued)
            cout << "Issued\n";
        else
            cout << "Available\n";
    }

    string toFileString() {
        return to_string(bookID) + "|" + title + "|" + author + "|" + to_string(issued);
    }

    static Book fromFileString(string line) {
        int id, iss;
        string t, a;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        id = stoi(line.substr(0, p1));
        t = line.substr(p1 + 1, p2 - p1 - 1);
        a = line.substr(p2 + 1, p3 - p2 - 1);
        iss = stoi(line.substr(p3 + 1));

        return Book(id, t, a, iss);
    }
};

class Library {
private:
    vector<Book> books;

public:
    void loadFromFile() {
        ifstream file("D:/library.txt");
        string line;

        while (getline(file, line)) {
            books.push_back(Book::fromFileString(line));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("D:/library.txt");
        for (Book &b : books) {
            file << b.toFileString() << endl;
        }
        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        saveToFile();

        cout << "Book added successfully.\n";
    }

    void displayBooks() {
        cout << "\nID\tTitle\tAuthor\tStatus\n";
        for (Book &b : books) {
            b.display();
        }
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                if (!b.isIssued()) {
                    b.issueBook();
                    saveToFile();
                    cout << "Book issued successfully.\n";
                } else {
                    cout << "Book already issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                if (b.isIssued()) {
                    b.returnBook();
                    saveToFile();
                    cout << "Book returned successfully.\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library lib;
    lib.loadFromFile();

    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3:
            lib.issueBook();
            break;
        case 4:
            lib.returnBook();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
