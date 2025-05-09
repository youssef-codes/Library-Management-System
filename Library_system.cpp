#include <iostream>
#include <string>
using namespace std;

const int Max_Book = 10;
int IDS[Max_Book];
string Titles[Max_Book];
string Authors[Max_Book];
bool Availability[Max_Book];
int TotalBooks = 0;

int searchBookById(int id) {
    for (int i = 0; i < TotalBooks; i++) {
        if (IDS[i] == id) return i;
    }
    return -1;
}

void displayAllBooks() {
    if (TotalBooks == 0) {
        cout << "No books available in the library.\n";
        return;
    }

    cout << "\n====== Library Books ======\n";
    for (int i = 0; i < TotalBooks; i++) {
        cout << "\nBook #" << i + 1 << endl;
        cout << "ID          : " << IDS[i] << endl;
        cout << "Title       : " << Titles[i] << endl;
        cout << "Author      : " << Authors[i] << endl;
        cout << "Availability: " << (Availability[i] ? "Available" : "Borrowed") << endl;
    }
    cout << "===========================\n";
}

void addBook(string title, string author) {
    if (TotalBooks == Max_Book) {
        cout << "The library is full. Cannot add more books.\n";
        return;
    }

    IDS[TotalBooks] = TotalBooks + 1;
    Titles[TotalBooks] = title;
    Authors[TotalBooks] = author;
    Availability[TotalBooks] = true;
    TotalBooks++;

    cout << "Book added successfully.\n";
}

void updateBook(int id, string new_title, string new_author) {
    int index = searchBookById(id);
    if (index != -1) {
        Titles[index] = new_title;
        Authors[index] = new_author;
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}

void borrowBook(int id) {
    int index = searchBookById(id);
    if (index != -1) {
        if (Availability[index]) {
            Availability[index] = false;
            cout << "Book borrowed successfully.\n";
        } else {
            cout << "Book is already borrowed.\n";
        }
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}

void returnBook(int id) {
    int index = searchBookById(id);
    if (index != -1) {
        if (!Availability[index]) {
            Availability[index] = true;
            cout << "Book returned successfully.\n";
        } else {
            cout << "Book was not borrowed.\n";
        }
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}


void removeBook(int id) {
    int index = searchBookById(id);
    if (index != -1) {
        char confirm;
        cout << "Are you sure you want to delete this book? (y/n): ";
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Book deletion cancelled.\n";
            return;
        }

        for (int j = index; j < TotalBooks - 1; j++) {
            IDS[j] = IDS[j + 1];
            Titles[j] = Titles[j + 1];
            Authors[j] = Authors[j + 1];
            Availability[j] = Availability[j + 1];
        }
        TotalBooks--;
        cout << "Book removed successfully.\n";
    } else {
        cout << "Book with ID " << id << " not found.\n";
    }
}


bool getValidInt(string message, int& value) {
    cout << message;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        return false;
    }
    return true;
}


void showMenu() {
    cout << "\n====== Library Management System ======\n";
    cout << "1. Add Book\n";
    cout << "2. Update Book\n";
    cout << "3. Remove Book\n";
    cout << "4. Borrow Book\n";
    cout << "5. Return Book\n";
    cout << "6. Display Books\n";
    cout << "7. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
}

int main() {
    string title, author;
    int choice, id;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

        if (choice == 7) {
            cout << "Exiting the system. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                addBook(title, author);
                break;
            case 2:
                if (!getValidInt("Enter book ID to update: ", id)) break;
                cout << "Enter new book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter new book author: ";
                getline(cin, author);
                updateBook(id, title, author);
                break;
            case 3:
                if (!getValidInt("Enter book ID to remove: ", id)) break;
                removeBook(id);
                break;
            case 4:
                if (!getValidInt("Enter book ID to borrow: ", id)) break;
                borrowBook(id);
                break;
            case 5:
                if (!getValidInt("Enter book ID to return: ", id)) break;
                returnBook(id);
                break;
            case 6:
                displayAllBooks();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
