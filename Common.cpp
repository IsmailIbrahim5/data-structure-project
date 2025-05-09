#include "Admin.h"
#include "Student.h"


void mainMenu() {
    Student s;
    Admin a;
    int number = 0;
    cout << "1-Login as Student\n";
    cout << "2-Login as Admin\n";
    cout << "3-SignUp as Student\n";
    cout << "4-SignUP as Admin\n";
    cout << "0-Exit\n";
    cin >> number;
    switch (number) {
    case 1:
        s.loginStudent();
        break;
    case 2:
        a.loginAdmin();
        break;
    case 3:
        s.signUpStudent();
        break;
    case 4:
        a.signUpAdmin();
        break;
    case 0:
        return;
    default:
        break;
    }
}