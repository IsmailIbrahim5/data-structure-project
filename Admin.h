#pragma once

#include "Common.h"

class Admin {
private:
    string username;
    string password;
    string name;

public:
    Admin();
    Admin(string username, string name, string password);

    // Getters
    string getUsername() const;
    string getName() const;
    string getPassword() const;

    // Setters
    void setUsername(const string& username);
    void setName(const string& name);
    void setPassword(const string& password);

    static string signUpAdmin(string username, string name, string password);
    static string loginAdmin(string username, string password);
    static void addCourse(string code, string name, string instractor_name,
        string syllabus, float credit_hours);
    static void addPrerequisiteToCourse(const string& courseCode, const string& prerequisiteCode);
    static void removePrerequisiteFromCourse(const string& courseCode, const string& prerequisiteCode);
    void uploadGradesFromCsv(string& filePath);
};

