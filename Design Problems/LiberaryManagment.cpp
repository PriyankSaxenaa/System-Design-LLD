
#include <bits/stdc++.h>
using namespace std;


enum BookStatus {
    AVAILABLE,
    ISSUED
};

enum LoanStatus {
    ACTIVE,
    RETURNED
};


class Book {
public:
    int id;
    string title;
    string author;
    string ISBN;

    Book(int id, string title, string author, string ISBN) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->ISBN = ISBN;
    }
};

// ==================== BOOK COPY ====================

class BookCopy {
public:
    int copyId;
    Book* book;
    BookStatus status;

    BookCopy(int copyId, Book* book) {
        this->copyId = copyId;
        this->book = book;
        status = AVAILABLE;
    }
};


class Member {
public:
    int id;
    string name;

    Member(int id, string name) {
        this->id = id;
        this->name = name;
    }
};


class Loan {
public:
    int id;
    Member* member;
    BookCopy* copy;
    time_t issueDate;
    time_t dueDate;
    time_t returnDate;
    LoanStatus status;

    Loan(int id, Member* member, BookCopy* copy) {
        this->id = id;
        this->member = member;
        this->copy = copy;

        issueDate = time(nullptr);
        dueDate = issueDate + 7 * 24 * 60 * 60;
        returnDate = 0;

        status = ACTIVE;
    }
};


class Library {
public:
    vector<Book*> books;
    vector<BookCopy*> copies;
    vector<Member*> members;
    vector<Loan*> loans;
};

// ==================== FINE STRATEGY ====================

class FineStrategy {
public:
    virtual int calculateFine(time_t dueDate,time_t returnDate) = 0;

    virtual ~FineStrategy() = default;
};

class DailyFineStrategy : public FineStrategy {
public:
    int calculateFine(time_t dueDate,time_t returnDate) override {
        if (returnDate <= dueDate)
            return 0;

        long long seconds = returnDate - dueDate;

        // Charge for every started overdue day.
        long long days = (seconds + 86400 - 1) / 86400;

        return static_cast<int>(days * 10);
    }
};

// ==================== SEARCH STRATEGY ====================

class BookSearchStrategy {
public:
    virtual vector<Book*> search(const vector<Book*>& books,string query) = 0;

    virtual ~BookSearchStrategy() = default;
};

class SearchByTitle : public BookSearchStrategy {
public:
    vector<Book*> search(const vector<Book*>& books,string query) override {
        vector<Book*> result;

        transform(query.begin(),query.end(),query.begin(),::tolower);

        for (Book* book : books) {
            string title = book->title;
            transform(title.begin(),title.end(),title.begin(),::tolower);
            if (title.find(query) != string::npos)
                result.push_back(book);
        }
        return result;
    }
};

class SearchByAuthor : public BookSearchStrategy {
public:
    vector<Book*> search(const vector<Book*>& books,string query) override {
        vector<Book*> result;

        transform(query.begin(), query.end(), query.begin(), ::tolower);

        for (Book* book : books) {
            string author = book->author;
            transform(author.begin(), author.end(),author.begin(), ::tolower);
            if (author.find(query) != string::npos)
                result.push_back(book);
        }
        return result;
    }
};

class SearchByISBN : public BookSearchStrategy {
public:
    vector<Book*> search(
        const vector<Book*>& books,string query) override {
        vector<Book*> result;
        for (Book* book : books) {
            if (book->ISBN==query)
                result.push_back(book);
        }
        return result;
    }
};

// ==================== LIBRARY SERVICE ====================

class LibraryService {
private:
    Library* library;
    FineStrategy* fineStrategy;

    int bookId = 0;
    int copyId = 0;
    int memberId = 0;
    int loanId = 0;

public:
    LibraryService(Library* library,FineStrategy* fineStrategy) {
        this->library = library;
        this->fineStrategy = fineStrategy;
    }

    // Add a book and its physical copies.
    Book* addBook(string title, string author,string ISBN, int numberOfCopies) {
        Book* book = new Book(++bookId, title, author, ISBN);

        library->books.push_back(book);

        for (int i = 0; i < numberOfCopies; i++) {
            BookCopy* copy = new BookCopy(++copyId, book );
            library->copies.push_back(copy);
        }

        return book;
    }

    // Register a member.
    Member* registerMember(string name) {
        Member* member = new Member(++memberId, name);

        library->members.push_back(member);
        return member;
    }

    // Search using a selected strategy.
    vector<Book*> searchBooks(BookSearchStrategy* strategy,string query) {
        return strategy->search(library->books, query);
    }

    // Display matching books and available copies.
    void displayBooks(vector<Book*> books) {
        for (Book* book : books) {
            int available = 0;
            int total = 0;

            for (BookCopy* copy : library->copies) {
                if (copy->book == book) {
                    total++;

                    if (copy->status == AVAILABLE)
                        available++;
                }
            }

            cout << "\nBook ID: " << book->id;
            cout << "\nTitle: " << book->title;
            cout << "\nAuthor: " << book->author;
            cout << "\nISBN: " << book->ISBN;
            cout << "\nAvailable copies: "
                 << available << "/" << total << "\n";
        }

        if (books.empty())
            cout << "No books found.\n";
    }

    // Issue a book by title ID.
    Loan* issueBook(int memberId, int bookId) {
        Member* member = nullptr;
        Book* book = nullptr;

        for (Member* m : library->members) {
            if (m->id == memberId) {
                member = m;
                break;
            }
        }

        for (Book* b : library->books) {
            if (b->id == bookId) {
                book = b;
                break;
            }
        }

        if (member == nullptr) {
            cout << "Member not found.\n";
            return nullptr;
        }

        if (book == nullptr) {
            cout << "Book not found.\n";
            return nullptr;
        }

        // Find an available physical copy.
        BookCopy* selectedCopy = nullptr;

        for (BookCopy* copy : library->copies) {
            if (copy->book == book && copy->status == AVAILABLE) {
                selectedCopy = copy;
                break;
            }
        }

        if (selectedCopy == nullptr) {
            cout << "No available copies.\n";
            return nullptr;
        }

        selectedCopy->status = ISSUED;

        Loan* loan = new Loan(++loanId, member, selectedCopy);

        library->loans.push_back(loan);

        cout << "Book issued successfully.\n";
        cout << "Loan ID: " << loan->id << "\n";
        cout << "Copy ID: " << selectedCopy->copyId << "\n";

        return loan;
    }

    // Return a book using its loan ID.
    void returnBook(int loanId,time_t returnTime = time(nullptr)) {
        Loan* loan = nullptr;

        for (Loan* l : library->loans) {
            if (l->id == loanId) {
                loan = l;
                break;
            }
        }

        if (loan == nullptr) {
            cout << "Loan not found.\n";
            return;
        }

        if (loan->status == RETURNED) {
            cout << "Book already returned.\n";
            return;
        }

        if (returnTime < loan->issueDate) {
            cout << "Invalid return time.\n";
            return;
        }

        loan->returnDate = returnTime;
        loan->status = RETURNED;

        loan->copy->status = AVAILABLE;

        int fine = fineStrategy->calculateFine(loan->dueDate, loan->returnDate);

        cout << "Book returned successfully.\n";
        cout << "Fine: Rs. " << fine << "\n";
    }

    // Display active loans for a member.
    void displayActiveLoans(int memberId) {
        bool found = false;

        for (Loan* loan : library->loans) {
            if (loan->member->id == memberId &&
                loan->status == ACTIVE) {
                found = true;

                cout << "\nLoan ID: " << loan->id;
                cout << "\nBook: "
                     << loan->copy->book->title;
                cout << "\nCopy ID: "
                     << loan->copy->copyId;
                cout << "\nDue date: "
                     << ctime(&loan->dueDate);
            }
        }

        if (!found)
            cout << "No active loans.\n";
    }
};

// ==================== MAIN ====================

int main() {
    Library* library = new Library();

    LibraryService* service = new LibraryService(
        library,
        new DailyFineStrategy()
    );

    // Add books.
    service->addBook(
        "Clean Code", "Robert C. Martin",
        "ISBN101", 2
    );

    service->addBook(
        "Atomic Habits", "James Clear",
        "ISBN102", 1
    );

    // Register members.
    Member* m1 = service->registerMember("Priyank");
    Member* m2 = service->registerMember("Rahul");

    // Search by title.
    SearchByTitle titleSearch;

    cout << "\n--- Search Results ---\n";

    vector<Book*> results = service->searchBooks(
        &titleSearch, "clean"
    );

    service->displayBooks(results);

    // Issue books.
    Loan* l1 = service->issueBook(m1->id, 1);
    Loan* l2 = service->issueBook(m2->id, 1);

    // A third issue should fail: only two copies exist.
    service->issueBook(m1->id, 1);

    // Display active loans.
    cout << "\n--- Priyank's Active Loans ---\n";
    service->displayActiveLoans(m1->id);

    // Return after eight days to demonstrate a fine.
    if (l1 != nullptr) {
        time_t simulatedReturn =
            l1->dueDate + 24 * 60 * 60;

        cout << "\n--- Return Book ---\n";
        service->returnBook(l1->id, simulatedReturn);
    }

    // Search by author.
    SearchByAuthor authorSearch;

    cout << "\n--- Search by Author ---\n";
    service->displayBooks(
        service->searchBooks(&authorSearch, "james")
    );

    // Search by ISBN.
    SearchByISBN isbnSearch;

    cout << "\n--- Search by ISBN ---\n";
    service->displayBooks(
        service->searchBooks(&isbnSearch, "ISBN102")
    );

    delete service;

    return 0;
}
