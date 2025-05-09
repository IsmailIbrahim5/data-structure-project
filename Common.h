#pragma once

#include <fstream>
#include <iostream>
#include <conio.h>
#include <ctype.h>
#include "json.hpp"
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using json = nlohmann::json;
using namespace std;

// Forward declarations of classes
class Course;
class Student;
class Admin;

// Shared global data structures
extern unordered_map<string, Course> courses;
extern unordered_map<string, Student> students;
extern unordered_map<string, Admin> admins;

// File operation functions
void load_students_from_file(const string &filename);
void save_students_to_file(const string &filename);
void load_admins_from_file(const string &filename);
void save_admins_to_file(const string &filename);
void loadCoursesFromFile(const string &filename);
void saveCourseToFile(const string &filename);

// Main menu function
void mainMenu();
