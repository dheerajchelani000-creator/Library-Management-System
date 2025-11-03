#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

int totalBooksAdded = 0;
vector<vector<int>> issuedBooks; // Stores registration no + issued books
vector<vector<int>> purchasedBooks; 


class Book
{
protected:
    vector<bool> isBookPresent;
    vector<int> bookIds;
    vector<string> bookNames;

    string currentBookName;
    int currentBookId;
    bool currentBookPresent;

public:
    void operator++()
    {
        cout << "\nEnter Book Name: ";
        cin.ignore();
        getline(cin, currentBookName);

        cout << "Enter Book ID: ";
        cin >> currentBookId;

              try
        {
            if (currentBookId >= 1000)
                throw "Book ID must be less than 1000!";  
             currentBookPresent = true;
        bookNames.push_back(currentBookName);
        bookIds.push_back(currentBookId);
        isBookPresent.push_back(currentBookPresent);
        
        totalBooksAdded++;
        cout << "Book \"" << currentBookName << "\" with ID " << currentBookId << " added successfully.\n";
        }
        catch (const char *msg)
        {
            cout << "Error: " << msg << endl;
        }
    }



       
    

    void removeBook()
    {
        bool found = false;
        cout << "\nEnter Book Name to Remove: ";
        cin.ignore();
        getline(cin, currentBookName);

        for (int index = 0; index < bookNames.size(); index++)
        {
            if (currentBookName == bookNames[index])
            {
                found = true;
                totalBooksAdded--;
                cout << "Book \"" << bookNames[index] << "\" removed successfully.\n";
                bookNames.erase(bookNames.begin() + index);
                bookIds.erase(bookIds.begin() + index);
                isBookPresent.erase(isBookPresent.begin() + index);
                break;
            }
        }
        if (!found)
            cout << "Book not found in the library.\n";
    }

    void displayBooks()
    {
        cout << "\nAvailable Books in Library:\n";
        if (bookNames.empty())
            cout << "No books available.\n";

        else
        {
            for (int index = 0; index < bookNames.size(); index++)
            {
                cout << "- " << bookNames[index] << " (ID: " << bookIds[index] << ")\n";
            }
            cout << "Total Books: " << totalBooksAdded << "\n";
        }
    }

    // store data in booksdata.txt
void saveBooksToFile()
    {
        ofstream fout("BooksData.txt");
        if (!fout)
        {
            cout << "Error creating BooksData.txt file.\n";
            return;
        }

        fout << "===== Library Books Data =====\n";
        for (size_t i = 0; i < bookNames.size(); ++i)
        {
            fout << "Book ID: " << bookIds[i] << " | Book Name: " << bookNames[i] << "\n";
        }
        fout << "Total Books: " << totalBooksAdded << "\n";
        fout.close();

        cout << "\n Books data saved to 'BooksData.txt' successfully.\n";
    }

    friend class Student;
    friend class Admin;
};


// POLYMORPHISM BASE CLASS 


class Registration
{
protected:
    vector<int> registrationNumbers;
    vector<bool> isRegistrationActive;

public:
   
    virtual ~Registration() {}

    void addRegistration()
    {
        int newRegNo;
        cout << "\nEnter Student Registration Number: ";
        cin >> newRegNo;


         try
        {
            if (newRegNo <= 1000)
                throw "Registration number must be greater than 1000!";  

           registrationNumbers.push_back(newRegNo);
        isRegistrationActive.push_back(true);

        cout << "Student with Registration Number " << newRegNo << " added successfully.\n";
        }
        catch (const char *msg)
        {
            cout << "Error: " << msg << endl;
        }



        
    }

    void removeRegistration()
    {
        int regToRemove;
        cout << "\nEnter Registration Number to Remove: ";
        cin >> regToRemove;

        bool found = false;
        for (int index = 0; index < registrationNumbers.size(); index++)
        {
            if (regToRemove == registrationNumbers[index])
            {
                found = true;
                cout << "Student with Registration Number " << registrationNumbers[index] << " removed successfully.\n";
                registrationNumbers.erase(registrationNumbers.begin() + index);
                isRegistrationActive.erase(isRegistrationActive.begin() + index);
                break;
            }
        }
        if (!found)
            cout << "Registration Number not found.\n";
    }
    
    // VIRTUAL FUNCTION:
    virtual void displayRole() const {
        cout << "Role: Generic Library User\n";
    }
    
    friend class Admin;

    void registration(){
        cout << "\n--- All Registered Numbers ---\n";
        for(int i=0;i<registrationNumbers.size();i++){
            cout<<registrationNumbers[i]<<endl;
        }
    }

    //  store data of student in studentdata.txt
 void saveRegistrationsToFile()
    {
        ofstream fout("StudentData.txt");
        if (!fout)
        {
            cout << "Error creating StudentData.txt file.\n";
            return;
        }

        fout << "===== Registered Students =====\n";
        for (size_t i = 0; i < registrationNumbers.size(); ++i)
        {
            fout << "Reg No: " << registrationNumbers[i]
                 << " | Status: " << (isRegistrationActive[i] ? "Active" : "Inactive") << "\n";
        }
        fout.close();

        cout << "\n Student registration data saved to 'StudentData.txt' successfully.\n";
    }




};


// DERIVED CLASS 1: Admin


class Admin : public Book, public Registration // Inherits from Registration
{
    int enteredBookId;
    int enteredRegNo;
    int activeStudentIndex;
    int bookIndexToRemove;

public:
    vector<pair<int, string>> removedBooks; // temporarily store issued books
    
    // OVERRIDE: Admin-specific role display
    void displayRole() const  {
        cout << "Role: Admin (Can Add/Remove Books, Issue/Submit/Purchase)\n";
    }


    void issueBooks(Book &bookObj, Registration &regObj)
    {
        cout << "\nEnter Your Registration Number: ";
        cin >> enteredRegNo;

        bool isValidReg = false;
        for (int index = 0; index < regObj.registrationNumbers.size(); index++)
        {
            if (enteredRegNo == regObj.registrationNumbers[index])
            {
                isValidReg = true;
                break;
            }
        }
        if (isValidReg)
        {
            int numberOfBooks;
            cout << "How many books do you want to issue? ";
            cin >> numberOfBooks;

            issuedBooks.push_back(vector<int>());
            issuedBooks.back().push_back(enteredRegNo);

            for (int i = 1; i <= numberOfBooks; i++)
            {
                cout << "Enter Book ID: ";
                cin >> enteredBookId;

                bool found = false;
                for (int d = 0; d < bookObj.bookIds.size(); d++)
                {
                    if (bookObj.bookIds[d] == enteredBookId)
                    {
                        // store temporarily
                        removedBooks.push_back({bookObj.bookIds[d], bookObj.bookNames[d]});
                        // remove from library
                        bookObj.bookIds.erase(bookObj.bookIds.begin() + d);
                        bookObj.bookNames.erase(bookObj.bookNames.begin() + d);
                        bookObj.isBookPresent.erase(bookObj.isBookPresent.begin() + d);
                        totalBooksAdded--;
                        found = true;
                        break;
                    }
                }
                if (found)
                    issuedBooks.back().push_back(enteredBookId);

                else
                    cout << "Book ID " << enteredBookId << " not available in library.\n";
            }
            cout << "Books issued successfully to Registration Number " << enteredRegNo << ".\n";
        }
        else
            cout << "Registration Number not found.\n";
    }
    void submitBooks(Book &bookObj, Registration &regObj)
    {
        cout << "\nEnter Your Registration Number: ";
        int submitRegNo;
        cin >> submitRegNo;

        bool validReg = false;
        bool hasIssuedBooks = false;

        for (int index = 0; index < regObj.registrationNumbers.size(); index++)
        {
            if (submitRegNo == regObj.registrationNumbers[index])
            {
                validReg = true;
                for (int arrIndex = 0; arrIndex < issuedBooks.size(); arrIndex++)
                {
                    if (submitRegNo == issuedBooks[arrIndex][0])
                    {
                        hasIssuedBooks = true;
                        activeStudentIndex = arrIndex;
                    }
                }

                if (!hasIssuedBooks)
                    break;

                int numberOfReturns;
                cout << "How many books do you want to submit? ";
                cin >> numberOfReturns;

                for (int i = 0; i < numberOfReturns; i++)
                {
                    cout << "Enter Book ID: ";
                    int bookIdToSubmit;
                    cin >> bookIdToSubmit;

                    bool found = false;
                    for (int j = 0; j < issuedBooks[activeStudentIndex].size(); j++)
                    {
                        if (bookIdToSubmit == issuedBooks[activeStudentIndex][j])
                        {
                            bookIndexToRemove = j;
                            found = true;
                            break;
                        }
                    }
                    if (found)
                    {
                        issuedBooks[activeStudentIndex].erase(issuedBooks[activeStudentIndex].begin() + bookIndexToRemove);

                        // Restore to library
                        for (int d = 0; d < removedBooks.size(); d++)
                        {
                            if (removedBooks[d].first == bookIdToSubmit)
                            {
                                bookObj.bookIds.push_back(removedBooks[d].first);
                                bookObj.bookNames.push_back(removedBooks[d].second);
                                bookObj.isBookPresent.push_back(true);
                                totalBooksAdded++;
                                removedBooks.erase(removedBooks.begin() + d);
                                break;
                            }
                        }

                        cout << "Book with ID " << bookIdToSubmit << " submitted successfully.\n";
                    }
                    else
                        cout << "This book was not issued under your registration.\n";
                }
            }
        }
        if (!validReg)
            cout << "Invalid Registration Number.\n";
        else if (!hasIssuedBooks)
            cout << "You have not issued any books.\n";
        if (hasIssuedBooks && issuedBooks[activeStudentIndex].size() == 1)
            issuedBooks.erase(issuedBooks.begin() + activeStudentIndex);
    }

    void issueBooks(Book &bookObj, Registration &regObj,int numberOfBooks)
    {
        cout << "\nEnter Your Registration Number: ";
        cin >> enteredRegNo;

        bool isValidReg = false;
        for (int index = 0; index < regObj.registrationNumbers.size(); index++)
        {
            if (enteredRegNo == regObj.registrationNumbers[index])
            {
                isValidReg = true;
                break;
            }
        }
        if (isValidReg)
        {
            purchasedBooks.push_back(vector<int>());
            purchasedBooks.back().push_back(enteredRegNo);

            for (int i = 1; i <= numberOfBooks; i++)
            {
                cout << "Enter Book ID: ";
                cin >> enteredBookId;

                bool found = false;
                for (int d = 0; d < bookObj.bookIds.size(); d++)
                {
                    if (bookObj.bookIds[d] == enteredBookId)
                    {
                     // remove from library
                        bookObj.bookIds.erase(bookObj.bookIds.begin() + d);
                        bookObj.bookNames.erase(bookObj.bookNames.begin() + d);
                        bookObj.isBookPresent.erase(bookObj.isBookPresent.begin() + d);
                        totalBooksAdded--;

                        found = true;
                        break;
                    }
                }
                if (found)
                    purchasedBooks.back().push_back(enteredBookId);

                else
                    cout << "Book ID " << enteredBookId << " not available in library.\n";
            }
            cout << "Books issued successfully to Registration Number " << enteredRegNo << ".\n";
        }
        else
            cout << "Registration Number not found.\n";
    }

};


// DERIVED CLASS 2: Student


class Student : public Registration // Inherits from Registration
{
    string searchBookName;

public:
    // OVERRIDE: Student-specific role display
    void displayRole() const  {
        cout << "Role: Student (Can Search Books)\n";
    }

    void searchBook(Book &bookObj)
    {
        cout << "\nEnter Book Name to Search: ";
        cin.ignore();
        getline(cin, searchBookName);

        bool found = false;
        for (int index = 0; index < bookObj.bookNames.size(); index++)
        {
            if (searchBookName == bookObj.bookNames[index])
            {
                cout << "Book \"" << searchBookName << "\" is available in the library.\n";
                found = true;
            }
        }
        if (!found)
            cout << "Book \"" << searchBookName << "\" is not available at this time.\n";
    }
};


// MAIN FUNCTION


int main()
{
    Book bookManager;
    
    Registration registrationManager; 
    Student studentUser;             
    Admin adminUser;               

    cout << "================ Library Management System ================\n";
    cout << "1. Add Books (Admin)\n";
    cout << "2. Remove Books (Admin)\n";
    cout << "3. Add Students\n";
    cout << "4. Remove Students\n";
    cout << "5. save data to file\n";
    cout << "6. Display Books\n";
    cout << "7. Search Book (Student)\n";
    cout << "8. Issue Books (Admin)\n";
    cout << "9. Submit Books (Admin)\n";
    cout << "10. Purchase Books (Admin)\n";
    cout << "11. Display Role (Polymorphic Call) \n"; 
    cout << "12. Display Registration No\n";
    cout << "13. Exit\n";
  
    

    while (1)
    {
        int userChoice;
        cout << "\nEnter Your Choice: ";
        cin>>userChoice;
        
       
       
        
        switch (userChoice)
        {
        case 1:
        {
            int numberOfBooks;
            cout << "\nHow many books do you want to add? ";
            cin >> numberOfBooks;
            for (int i = 0; i < numberOfBooks; i++)
                ++bookManager;
            break;
        }

        case 2:
        {
            int numberOfBooks;
            cout << "\nHow many books do you want to remove? ";
            cin >> numberOfBooks;
            for (int i = 0; i < numberOfBooks; i++)
                bookManager.removeBook();
            break;
        }

        case 3:
        {
            int numberOfStudents;
            cout << "\nHow many students do you want to add? ";
            cin >> numberOfStudents;
            for (int i = 0; i < numberOfStudents; i++)

                studentUser.addRegistration();
            break;
        }

        case 4:
        {
            int numberOfStudents;
            cout << "\nHow many students do you want to remove? ";
            cin >> numberOfStudents;
            for (int i = 0; i < numberOfStudents; i++)
                studentUser.removeRegistration(); 
            break;
        }

        case 13:
        {
            cout << "Exiting the program. Thank you!\n";
            exit(0);
            break;
        }
        case 6:
        {
            bookManager.displayBooks();
            break;
        }

  

        case 7:
        {
            studentUser.searchBook(bookManager);
            break;
        }
        case 8:
        {
            adminUser.issueBooks(bookManager, studentUser); 
            break;
        }
        case 9:
        {
            adminUser.submitBooks(bookManager, studentUser); 
            break;
        }
        case 10:
        {int n;
            cout<<"enter how many book you want to purchase: ";
            cin>>n;
            adminUser.issueBooks(bookManager, studentUser,n);
            break; 
        }
        case 11: 
        {
            cout << "\n--- Demonstrating RUNTIME POLYMORPHISM (Option 11) ---\n";
            
            Registration* userPtr; // Base Class Pointer

            // Pointer points to Student object
            userPtr = &studentUser;
            cout << "Calling displayRole() via Student object pointer:\n";
            userPtr->displayRole(); 

            
            userPtr = &adminUser;
            cout << "\nCalling displayRole() via Admin object pointer:\n";
            userPtr->displayRole(); 
            


            break;
        }
        case 12:
        {
            studentUser.registration(); 
            break;
        }

         case 5: {
            bookManager.saveBooksToFile();
            studentUser.saveRegistrationsToFile();
            break;
         }

        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }
}
