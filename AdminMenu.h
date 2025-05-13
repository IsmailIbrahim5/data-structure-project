#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Course.h"
#include "Student.h"
#include "Admin.h"



enum class AdminFocusedField {
    None,
    Code,
    Name,
    Instructor,
    Syllabus,
    Hours,
    Perquisite,
    Grade
};

class AdminMenu
{
public:
    static std::string codeInput;
    static std::string nameInput;
    static std::string instructorInput;
    static std::string syllabusInput;
    static std::string hoursInput;
    static std::string periquisiteInput;
    static std::string gradeInput;
    static Course* selectedCourse;
    static Student* selectedStudent;
    static int page;
    static AdminFocusedField activeField;
    static void drawMenu(sf::RenderWindow& window);
    static void drawAddCourse(sf::RenderWindow& window);
    static void drawChooseCourse(sf::RenderWindow& window);
    static void drawChooseStudent(sf::RenderWindow& window);
    static void drawCoursePerquisites(sf::RenderWindow& window);
    static void drawModifyGrade(sf::RenderWindow& window);
    static void handleInput(const std::optional<sf::Event>& event);
};

