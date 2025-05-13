#pragma once

#include "Common.h"

class Student {
private:
    int semester;
    int termCreditHours;
    string id;
    string name;
    string password;
    unordered_set<string> completedCourses;
    unordered_set<string> registeredCourses;
    unordered_map<string, int> grades; // calculate GPA

public:
    Student();
    Student(string id, string name, string password);

    // Getters
    int getSemester() const;
    int getTermCreditHours() const;
    string getId() const;
    string getName() const;
    string getPassword() const;
    const unordered_set<string>& getCompletedCourses() const;
    const unordered_set<string>& getRegisteredCourses() const;
    const unordered_map<string, int>& getGrades() const;

    // Setters
    void setSemester(int semester);
    void setTermCreditHours(int hours);
    void setId(const string& id);
    void setName(const string& name);
    void setPassword(const string& password);

    // Methods to modify collections
    void addCompletedCourse(const string& code);
    bool removeCompletedCourse(const string& code);

    void addRegisteredCourse(const string& code);
    bool removeRegisteredCourse(const string& code);

    void setGrade(const string& course, int grade);
    bool removeGrade(const string& course);

    void studentMenu();
    static string signUpStudent(string id, string name, string password);
    static string loginStudent(string id, string password);
    void viewCourses();
    void searchCourse(string code);
    string RegisterForCourse(string code);
    void viewGrades();
    void showPrerequisites();
    void showPrerequisitesForOneCourse(string code);
    void generateReports();
    void goBack();

    bool checkPrerequisites(string code);
    double grade_to_gpa_point(int grade);
    double calculate_gpa();
};

