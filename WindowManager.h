#pragma once

#include "SFML/Graphics.hpp"
#include "constants.h"


enum class ShownWindow {
    Login,
    SignUp,
    AdminPanel,
    StudentPanel,
    AddCourse,
    ChooseCourse,
    AdminCoursePerquisites,
    ChooseStudent,
    ModifyGrade,
    Courses,
    CourseDetails,
    Report
};

class WindowManager {
public:
    static ShownWindow shownWindow;
    static bool click_lock;
    static void handleInput(const std::optional<sf::Event>& event);
};
