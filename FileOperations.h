#pragma once

#include "Common.h"

// File operations implementations
void load_students_from_file(const string& filename);
void save_students_to_file(const string& filename);
void load_admins_from_file(const string& filename);
void save_admins_to_file(const string& filename);
void loadCoursesFromFile(const string& filename);
void saveCourseToFile(const string& filename);
void load_student_grades_from_csv(const string& filePath);
void save_students_grades_to_csv(const string& filename);

