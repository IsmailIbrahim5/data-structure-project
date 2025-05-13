#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Course.h"
#include "Student.h"

enum class StudentFocusedField {
    None,
    Code,
    Name,
    Instructor,
    Syllabus,
    Hours,
    Perquisite,
    Grade
};

class StudentMenu
{
public:
    static std::string codeInput;
    static std::string nameInput;
    static std::string instructorInput;
    static std::string syllabusInput;
    static std::string hoursInput;
    static std::string periquisiteInput;
    static std::string gradeInput;
    static std::string error;
    static Course* selectedCourse;
    static Student* currentStudent;
    static int page;
    static StudentFocusedField activeField;
    static void drawMenu(sf::RenderWindow& window);
    static void drawCourses(sf::RenderWindow& window);
    static void drawCourseDetails(sf::RenderWindow& window);
    static void drawReport(sf::RenderWindow& window);
    static void handleInput(const std::optional<sf::Event>& event);
};

