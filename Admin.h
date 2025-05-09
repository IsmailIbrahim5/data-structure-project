#pragma once

#include "Common.h"

class Admin {
private:
    string username;
    string password;

public:
    Admin();
    Admin(string username, string password);

    // Getters
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setUsername(const string& username);
    void setPassword(const string& password);

    void signUpAdmin();
    void loginAdmin();
    void addCourse(string code, string name, string instractor_name,
        string syllabus, float credit_hours);
    void addPrerequisiteToCourse(const string& courseCode, const string& prerequisiteCode);
    void removePrerequisiteFromCourse(const string& courseCode, const string& prerequisiteCode);
    void uploadGradesFromCsv(string& filePath);
};

