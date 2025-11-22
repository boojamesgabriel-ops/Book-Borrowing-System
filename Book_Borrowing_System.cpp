#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <chrono>
#include <limits>
#include <fstream>
#include <deque>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;

class BOOK {
public:

    struct books {
        string book_id;
        string book_title;
        string book_author;
        string book_availability;
        books* next;
    };

stack<string> borrowHistory;

    deque<books> bookList = {
        {"B001", "1984", "George Orwell", "Available"},
        {"B002", "To Kill a Mockingbird", "Harper Lee", "Available"},
        {"B003", "The Great Gatsby", "F. Scott Fitzgerald", "Available"},
        {"B004", "Pride and Prejudice", "Jane Austen", "Available"},
        {"B005", "The Hobbit", "J.R.R. Tolkien", "Available"},
        {"B006", "Dune", "Frank Herbert", "Available"},
        {"B007", "Ender's Game", "Orson Scott Card", "Available"},
        {"B008", "Foundation", "Isaac Asimov", "Available"},
        {"B009", "Necromancer", "William Gibson", "Available"},
        {"B010", "Snow Crash", "Neal Stephenson", "Available"},
        {"B011", "Programming Pearls", "Jon Bentley", "Available"},
        {"B012", "C++ Primer", "Stanley B. Lippman", "Available"},
        {"B013", "Effective Modern C++", "Scott Meyers", "Available"},
        {"B014", "Fluent Python", "Luciano Ramalho", "Available"},
        {"B015", "Effective Java", "Joshua Bloch", "Available"},
        {"B016", "A Game of Thrones", "George R.R. Martin", "Available"},
        {"B017", "The name of the WInd", "Patrick Rothfuss", "Available"},
        {"B018", "Pedagogy of the Oppressed", "Paulo Freire", "Available"},
        {"B019", "MPL", "Doggie Saber", "Available"},
        {"B020", "The 48 Laws of Power", "Robert Greene", "Available"},
    };

books* head = nullptr;

    struct borrower {
        string name;
        string borrower_name;
        string BookID;
        string bookBorrowed;
        int borrower_ID, borrow_date, return_date;
        char confirm, again;
        bool returnedLate;
    };

    string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    ostringstream datetime;
    datetime << setfill('0') << setw(2) << ltm->tm_mon + 1 << "/"
             << setw(2) << ltm->tm_mday << "/"
             << 1900 + ltm->tm_year << " "
             << setw(2) << ltm->tm_hour << ":"
             << setw(2) << ltm->tm_min;
    return datetime.str();
}


    BOOK() {
        ifstream infile("library_data.txt");
        if (!infile) {
            database_file();
        }
        infile.close();
        LoadFromFile();
        }

    void database_file() {
        ofstream LIST("library_data.txt");
        if (!LIST) {
            cout << "Error in Opening the database\n";
            return;
        }
        for (auto& b : bookList) {
            LIST << b.book_id << "|"
                 << b.book_title << "|"
                 << b.book_author << "|"
                 << b.book_availability << "\n";
        }
        LIST.close();
    }

    void LoadFromFile() {
        ifstream LIST("library_data.txt");
        if (!LIST) {
            cout << "Error opening library_data.txt\n";
            return;
        }
        while (head != nullptr) {
            books* temp = head;
            head = head->next;
            delete temp;
        }

        string line;
        books* tail = nullptr;

        while (getline(LIST, line)) {
            istringstream iss(line);
            string id, title, author, status;

            if (getline(iss, id, '|') && 
                getline(iss, title, '|') && 
                getline(iss, author, '|') && 
                getline(iss, status)) {

                books* newBook = new books;
                newBook->book_id = id;
                newBook->book_title = title;
                newBook->book_author = author;
                newBook->book_availability = status;
                newBook->next = nullptr;

                if (head == nullptr) {
                    head = tail = newBook;
                } 
                else {
                    tail->next = newBook;
                    tail = newBook;
                }
            }
        }
        LIST.close();
    }

    void SaveToFile() {
        ofstream LIST("library_data.txt");
        if (!LIST) {
            cout << "Error opening library_data.txt\n";
            return;
        }

        books* current = head;
        while (current != nullptr) {
            LIST << current->book_id << "|"
                 << current->book_title << "|"
                 << current->book_author << "|"
                 << current->book_availability << "\n";
            current = current->next;
        }
        LIST.close();
    }

    void Menu() {
        cout << "\n==========================================\n";
        cout << "\t\t  MENU \t\t\t\n";
        cout << "==========================================\n";
        cout << "||          [1] - Show Books            ||\n";       
        cout << "||          [2] - Search Book           ||\n";
        cout << "||          [3] - Borrow Book           ||\n";
        cout << "||          [4] - Return Book           ||\n";
        cout << "||          [5] - View History          ||\n";
        cout << "||          [6] - Exit                  ||\n";
        cout << "==========================================\n";
    }

    void ShowBook() {
        LoadFromFile();
        cout << "\n===============================================================================\n";
        cout << "\t\t                    BOOK LIST\n";
        cout << "===============================================================================\n";
        cout << left << setw(10) << "Book ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Availability" << endl;
        cout << "-------------------------------------------------------------------------------\n";

        books* temp = head;
        while (temp != nullptr) {
            cout << left << setw(10) << temp->book_id
                 << setw(30) << temp->book_title
                 << setw(25) << temp->book_author
                 << setw(15) << temp->book_availability << endl;
            temp = temp->next;
        }
        cout << "-------------------------------------------------------------------------------\n";
    }

    void sortingData(){ 
    if (head == nullptr || head->next == nullptr) return;

    bool wow;

    do {
        wow = false;
        books* current = head;

        while (current->next != nullptr){

            bool needswapped = false;

            if (current->book_availability == "Available" && current->next->book_availability == "Borrowed") {
                needswapped = true;
            } else if (current->book_availability == current->next->book_availability && current->book_id > current->next->book_id){
                needswapped = true;
            }

                if (needswapped){
                swap(current->book_id,current->next->book_id);
                swap(current->book_title,current->next->book_title);
                swap(current->book_author,current->next->book_author);
                swap(current->book_availability,current->next->book_availability);

                wow = true;
            }
                current = current->next;
        }
    } while (wow);
};
 
    void SearchBook() { 
    char again;
    do{
        string se;
        books* current = nullptr;
        bool found = false;

        do{
            cout << "\n================================\n";
            cout << "\t Search Book \t\t\t\n";
            cout << "================================\n";
            cout << "Enter Book ID (B001-B020): ";
            cin  >> se;

            if (se[0] == 'b') {
                se[0] = 'B';
            } 
            
        current = head;
    
        while (current != nullptr){
         if (current->book_id == se){
        	cout << "================================================================\n";
            cout << "\nBook Found | ";
            cout << current->book_id << " | " << current->book_title << " BY " << current->book_author << " ---------- " << current->book_availability <<"\n" << endl;
            cout << "================================================================\n";
            found = true;
            break;
        }
        current = current->next;
    }

    if(!found){
        cout << "\nBook not found. Enter a valid Book ID: ";
        }   

    }while (!found); 

    cout << "\nDo you want to search another book (Y/N)?";
    cin >> again;
 }while (toupper(again) == 'Y');
}

    void date_time(){
        time_t current_dt=time(0);
        char* result=ctime(&current_dt);
        cout << "Date Borrowed: \n" << result << endl; 
    }

    void BorrowBook() {
        borrower b;
        string inputBookID;
        bool validDate = false;

        do {
            cout << "================================\n";
            cout << "\t  BORROW BOOK \t\t\t\n";
            cout << "================================\n";

            cout << "Name: ";
            cin.ignore();
            getline(cin, b.borrower_name);
            while(!checkName(b.borrower_name)){
                cout<<"Invalid Name. Please only use letters, no space.\nName:";
                getline(cin, b.borrower_name);
            }

            cout << "ID number (9 digits): ";
            while (true) {
                cin >> b.borrower_ID;
                if (cin.fail() || to_string(b.borrower_ID).length() != 9){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\nEnter the correct 9-digit ID Number:";
                } else if (isBanned(b.borrower_ID)) {
                    cout << "This ID is banned from borrowing due to late return.\n";
                    return;
                } else {
                    break;
                }
            }


            ShowBook();
            books* current = nullptr;
        do
        {   
            cout << "ID of Book (e.g., B001 - B020): ";
            cin >> inputBookID;

            if (inputBookID[0] == 'b'){
                inputBookID [0] = 'B';
            }
        
            current = head;
            bool found = false;
            while (current != nullptr) {
                if (current->book_id == inputBookID) {
                    found = true;
                    if (current->book_availability == "Available") {
                        b.BookID = current->book_id;
                        b.bookBorrowed = current->book_title;
                    }else{
                      cout << "Book not available!\n";
                      current = nullptr;
                    }
                    break;
                }
                current = current->next;
            }

            if (!found) {
                cout << "Book ID not found!\nEnter a valid Book ID:";
                current = nullptr;
            }

        }while (current == nullptr);
        
            validDate = false;
            cout << "Borrowing Terms & Conditions\n\n";
            cout << "Failure to return within 7 days\n\n";
            cout << "will result to permanent ban\n";
            
            do {
    cout << "\nConfirm borrowing (Y/N)? ";
    cin >> b.confirm;

    if (cin.fail() || (toupper(b.confirm) != 'Y' && toupper(b.confirm) != 'N')) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter Y or N only.\n";
    }
} while (toupper(b.confirm) != 'Y' && toupper(b.confirm) != 'N');
            

            if (toupper(b.confirm) == 'Y') {
                books* bookToBorrow = findBookById(inputBookID);
                if (bookToBorrow) {
                    bookToBorrow->book_availability = "Borrowed";
                    SaveToFile();
                    cout << "Book borrowed successfully!\n";
                    cout << "Return the Book within 7 days. " << endl; 
                        date_time();


                    string entry = "ID: " + to_string(b.borrower_ID) + " | \"" +
                bookToBorrow->book_title + "\" | Date: " + getCurrentDateTime();

                        borrowHistory.push(entry);

                        ofstream out("borrow_history.txt", ios::app);
                        if (out) {
                            out << entry << endl;
                        }
                        out.close();

                }
            } else {
                cout << "Borrowing canceled.\n";
            }
            

            do {
    cout << "Borrow another book (Y/N)? ";
    cin >> b.again;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid Input. Please enter Y/N only\n";
    }
} while (toupper(b.again) != 'Y' && toupper(b.again) != 'N');

        } while (toupper(b.again) == 'Y');
    }

    books* findBookById(const string& id) {
        books* current = head;
        while (current != nullptr) {
            if (current->book_id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    

    void ReturnBook() {
        borrower r;
        string bookId;

        do {
            cout << "================================\n";
            cout << "\t  RETURN BOOK \t\t\t\n";
            cout << "================================\n";

            cout << "Name: ";
            cin.ignore();
            getline(cin, r.borrower_name);
            while (!checkName(r.borrower_name)) {
                cout << "Invalid Name. Please only use letters, no space.\nName: ";
                getline(cin, r.borrower_name);
            }

            cout << "ID number (9 digits): ";
            while (!(cin >> r.borrower_ID) || to_string(r.borrower_ID).length() != 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter the correct 9-digit ID Number: ";
            }

            books* book = nullptr;
            do{
                cout << "ID of Book (B00*): ";
                cin >> bookId;
                
                if (bookId[0] == 'b') {
                bookId[0] = 'B';
                }


            book = findBookById(bookId);
            if (!book) {
                cout << "Book ID not found!\nEnter a valid Book ID:";
            }else if (book->book_availability != "Borrowed") {
                cout << "The book ID entered was not borrowed.\n";
                book = nullptr;
            }
        }while (book == nullptr); 

        getCurrentDateTime();
        
        auto now = chrono::system_clock::now();
        ifstream in("borrow_history.txt");
        string line, matchedLine;
        while (getline(in, line)) {
            if (line.find(to_string(r.borrower_ID)) != string::npos && line.find(book->book_title) != string::npos) {
                matchedLine = line;
            }
        }
        in.close();


    size_t pos = matchedLine.find("Date: ");

            cout << "\nConfirm return (Y/N)? ";
            cin >> r.confirm;

           if (toupper(r.confirm) == 'Y') {
            if (pos != string::npos) {
    string timeStr = matchedLine.substr(pos + 6);
    tm t = {};
istringstream ss(timeStr);
string month, day, year, hour, minute;

getline(ss, month, '/');
getline(ss, day, '/');
getline(ss, year, ' '); 

getline(ss, hour, ':');
getline(ss, minute);

t.tm_mon = stoi(month) - 1;
t.tm_mday = stoi(day);
t.tm_year = stoi(year) - 1900;
t.tm_hour = stoi(hour);
t.tm_min = stoi(minute);


    time_t borrow_time = mktime(&t);
    time_t current_time = time(0);
    double minutesPassed = difftime(current_time, borrow_time) / 60;
    cout << "\nBorrowed on: " << timeStr;
cout << "\nMinutes passed (simulated days): " << minutesPassed << endl;

    if (minutesPassed > 7) {  
        cout << "\n You have returned the book late!";
        cout << "\n You are now permanently banned from borrowing.\n\n";

        ofstream ban("Banned_data.txt", ios::app);
        ban << r.borrower_ID << endl;
        ban.close();
    }
    else {
    }
}
                    book->book_availability = "Available";
                    SaveToFile();
                    cout << "Book returned successfully!\n\n";

                    stack<string> temp;
                    bool found = false;

                    while (!borrowHistory.empty()) {
                        string topEntry = borrowHistory.top();
                        borrowHistory.pop();

                        if (!found &&
                            topEntry.find(book->book_title) != string::npos &&
                            topEntry.find("RETURNED") == string::npos) {
                            found = true;
                        } else {
                            temp.push(topEntry);
                        }
                    }

                    while (!temp.empty()) {
                        borrowHistory.push(temp.top());
                        temp.pop();
                    }

                    ifstream in("borrow_history.txt");
                    vector<string> allLines;
                    string line;
                    bool removed = false;

                    while (getline(in, line)) {
                        if (!removed &&
                            line.find(book->book_title) != string::npos &&
                            line.find("RETURNED") == string::npos) {
                            removed = true; // skip this line
                        } else {
                            allLines.push_back(line);
                        }
                    }
                    in.close();

                    ofstream out("borrow_history.txt");
                    for (const string& l : allLines) {
                        out << l << endl;
                    }

                    out.close();

            } else {
                cout << "Return canceled.\n";
            }

            cout << "Return another book (Y/N)? ";
            cin >> r.again;
        } while (toupper(r.again) == 'Y');
    }


    void history() {
    ifstream in("borrow_history.txt");
    if (!in || in.peek() == ifstream::traits_type::eof()) {
        cout << "\n=== LIST OF BORROWED BOOK ===\n";
        cout << "No borrow history yet.\n";
        cout << "==============================\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    cout << "\n===== Borrow History (Latest on Top) =====\n";
    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        cout << *it << endl;

        size_t pos = it->find("Date: ");
        if (pos != string::npos) {
            string dateStr = it->substr(pos + 6);

            tm t = {};
            istringstream ss(dateStr);
            string month, day, year;
            getline(ss, month, '/');
            getline(ss, day, '/');
            getline(ss, year);

            t.tm_mon = stoi(month) - 1;
            t.tm_mday = stoi(day);
            t.tm_year = stoi(year) - 1900;

            time_t borrowTime = mktime(&t);
            borrowTime += 7 * 24 * 60 * 60; 

            tm* due = localtime(&borrowTime);
            cout << "Due Date: "
                 << setw(2) << due->tm_mon + 1 << "/"
                 << setw(2) << due->tm_mday << "/"
                 << 1900 + due->tm_year << "\n";
        }

        cout << "------------------------------------------\n";
    }
    cout << "==========================================\n";
}


    bool checkName(const string& name) {
    for (char check: name)
        if (!isalpha(check)) {
            return false;
        }
        return true;
    } 

bool isBanned(int id) {
    ifstream in("Banned_data.txt");
    if (!in) return false;  

    string line;
    while (getline(in, line)) {
        if (line == to_string(id)) {
            return true;
        }
    }
    return false;
}


    void Alis(){
    borrower e;
    cout << "\nExiting Program";
    cout << "\nAre you sure? (Y/N): ";
        while (!(cin >> e.again) || (toupper(e.again) != 'Y' && toupper(e.again) != 'N')){
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Invalid Input. Please enter Y or N: ";
            }
            cin.ignore();
       
        if (toupper(e.again) == 'Y'){
        cout << "Thank you for using the library management system :)\n";
        cout << "Exiting...";
        exit(0);
        }else {
            cout<<"Returning to Main Menu";
        }
    return;
            
        }
};
 
int main() {  
    BOOK obj;
    int option;
    do{
        obj.Menu();
        while (true){
            
            cout <<"\n";
			cout <<"        Input your Choice (1-6) : ";
            cin >> option;

            if (cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Invalid Input. Please enter a number from 1-6\n";
            }else if(option < 1 || option > 6){
                cout<<"Invalid Input. Please enter a number from 1-6\n";
            }else{
                break;
            }
        }
   
        switch (option) {
            case 1: 
                obj.LoadFromFile();
                obj.sortingData();
                obj.SaveToFile();
                obj.ShowBook();
                break;
            case 2: 
                obj.LoadFromFile(); 
                obj.sortingData();
                obj.SearchBook(); 
                obj.SaveToFile();
                break;
            case 3:
                obj.sortingData();
                obj.BorrowBook();
                break;
            case 4:
                obj.ReturnBook();
                break;
            case 5: 
                obj.history();
                break;
            case 6: 
                obj.Alis();
                option = 0;
                break;
            default:
                cout << "Invalid input. Please try again.\n";
                break;
        }
    }while (option != 6);
   
    return 0;
}