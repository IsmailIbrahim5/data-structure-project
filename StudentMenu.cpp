#include "StudentMenu.h"
using namespace sf;
using namespace constants;


std::string StudentMenu::codeInput = "";
std::string StudentMenu::nameInput = "";
std::string StudentMenu::instructorInput = "";
std::string StudentMenu::syllabusInput = "";
std::string StudentMenu::hoursInput = "";
std::string StudentMenu::periquisiteInput = "";
std::string StudentMenu::gradeInput = "";
std::string StudentMenu::error = "";
int StudentMenu::page = 0;
Course* StudentMenu::selectedCourse;
Student* StudentMenu::currentStudent;
StudentFocusedField StudentMenu::activeField = StudentFocusedField::None;

void StudentMenu::handleInput(const std::optional<sf::Event>& event) {
    if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
        if (textEntered->unicode < 128) {
            char c = static_cast<char>(textEntered->unicode);
            if (c == '\b') {
                switch (activeField) {
                case StudentFocusedField::Code:
                    if (!codeInput.empty()) codeInput.pop_back();
                    break;
                case StudentFocusedField::Name:
                    if (!nameInput.empty()) nameInput.pop_back();
                    break;
                case StudentFocusedField::Instructor:
                    if (!instructorInput.empty()) instructorInput.pop_back();
                    break;
                case StudentFocusedField::Syllabus:
                    if (!syllabusInput.empty()) syllabusInput.pop_back();
                    break;
                case StudentFocusedField::Hours:
                    if (!hoursInput.empty()) hoursInput.pop_back();
                    break;
                case StudentFocusedField::Perquisite:
                    if (!periquisiteInput.empty()) periquisiteInput.pop_back();
                    break;
                case StudentFocusedField::Grade:
                    if (!gradeInput.empty()) gradeInput.pop_back();
                    break;

                default: break;
                }
            }

            else if (isprint(c)) {
                switch (activeField) {
                case StudentFocusedField::Code:
                    codeInput += c;
                    break;
                case StudentFocusedField::Name:
                    nameInput += c;
                    break;
                case StudentFocusedField::Instructor:
                    instructorInput += c;
                    break;
                case StudentFocusedField::Syllabus:
                    syllabusInput += c;
                    break;
                case StudentFocusedField::Hours:
                    if (c >= '0' && c <= '9')
                        hoursInput += c;
                    break;
                case StudentFocusedField::Perquisite:
                    periquisiteInput += c;
                    break;
                case StudentFocusedField::Grade:
                    if (c >= '0' && c <= '9')
                        gradeInput += c;
                    break;
                default: break;
                }
            }
        }
    }
    if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Enter || keyEvent->code == sf::Keyboard::Key::Tab) {
            if (activeField == StudentFocusedField::Code) {
                activeField = StudentFocusedField::Name;
            }
            else if (activeField == StudentFocusedField::Name) {
                activeField = StudentFocusedField::Instructor;
            }
            else if (activeField == StudentFocusedField::Instructor) {
                activeField = StudentFocusedField::Syllabus;
            }
            else if (activeField == StudentFocusedField::Syllabus) {
                activeField = StudentFocusedField::Hours;
            }
            else if (activeField == StudentFocusedField::Perquisite) {
                selectedCourse->addPrerequisite(periquisiteInput);
                //St::addPrerequisiteToCourse(selectedCourse.getCode(), periquisiteInput);
                periquisiteInput.clear();
                activeField = StudentFocusedField::None;
            }
        }

    }

}


void StudentMenu::drawMenu(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Student Panel", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture courseButtonTexture("resources/images/courses_button.png");
    Sprite courseButton(courseButtonTexture);
    courseButton.setPosition(Vector2f(screenSize.x * .35, screenSize.y * .5));
    courseButton.setOrigin(courseButton.getLocalBounds().getCenter());

    Texture reportButtonTexture("resources/images/report_button.png");
    Sprite reportButton(reportButtonTexture);
    reportButton.setPosition(Vector2f(screenSize.x * .65, screenSize.y * .5));
    reportButton.setOrigin(reportButton.getLocalBounds().getCenter());


    Texture logoutButtonTexture("resources/images/logout_button.png");
    logoutButtonTexture.setSmooth(true);
    Sprite logoutButton(logoutButtonTexture);
    logoutButton.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .9));
    logoutButton.setOrigin(logoutButton.getLocalBounds().getCenter());


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (courseButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::Courses;

        }
        if (reportButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::Report;
        }
        if (logoutButton.getGlobalBounds().contains(mousePos)) {
            currentStudent = nullptr;
            WindowManager::shownWindow = ShownWindow::Login;
        }
        WindowManager::click_lock = true;
    }


    window.draw(title);
    window.draw(courseButton);
    window.draw(reportButton);
    window.draw(logoutButton);

}



void drawStudentCourseItem(RenderWindow& window, Course& course, int index) {
    Vector2u screenSize = window.getSize();
    Text code(interExtraLight, course.getCode(), 18);
    code.setFillColor(black);
    code.setPosition(Vector2f(screenSize.x * .025, screenSize.y * (.2 + (.15 * index))));
    Text name(interBold, course.getName(), 28);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.15 * index))) + code.getLocalBounds().size.y + 8));

    Text instructor(interRegular, "Taught by: " + course.getInstractorName(), 18);
    instructor.setFillColor(black);
    instructor.setPosition(Vector2f(screenSize.x * .5, (screenSize.y * (.2 + (.15 * index))) + code.getLocalBounds().size.y + 16));

    Text hours(interRegular, "Credit Hours:" + to_string(course.getCreditHours()), 18);
    hours.setFillColor(black);
    hours.setPosition(Vector2f(screenSize.x * .7, (screenSize.y * (.2 + (.15 * index))) + code.getLocalBounds().size.y + 16));

    Text syllabus(interExtraLight, course.getSyllabus(), 18);
    syllabus.setFillColor(black);
    syllabus.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.15 * index))) + code.getLocalBounds().size.y + name.getLocalBounds().size.y + 24));

    Texture enrollButtonTexture("resources/images/enroll_button.png");
    enrollButtonTexture.setSmooth(true);
    Sprite enrollButton(enrollButtonTexture);
    enrollButton.setPosition(Vector2f(screenSize.x * .875, (screenSize.y * (.2 + (.15 * index)) + code.getLocalBounds().size.y + 16)));



    RectangleShape courseHitbox({ screenSize.x * 1.f , screenSize.y * .125f });
    courseHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * (.25f + (.15f * index)) });
    courseHitbox.setOrigin(courseHitbox.getLocalBounds().getCenter());
    courseHitbox.setFillColor(Color::Transparent);

    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (enrollButton.getGlobalBounds().contains(mousePos)) {
            StudentMenu::error = StudentMenu::currentStudent->RegisterForCourse(course.getCode());
            WindowManager::click_lock = true;
        }
        else if (courseHitbox.getGlobalBounds().contains(mousePos)) {
            StudentMenu::error.clear();
            StudentMenu::selectedCourse = &course;
            WindowManager::shownWindow = ShownWindow::CourseDetails;
            WindowManager::click_lock = true;

        }
    }

    window.draw(courseHitbox);
    window.draw(code);
    window.draw(name);
    window.draw(instructor);
    window.draw(hours);
    window.draw(syllabus);

    if (StudentMenu::currentStudent->getRegisteredCourses().count(course.getCode())) {
        int grade = 0;
        auto it = StudentMenu::currentStudent->getGrades().find(course.getCode());
        if (it != StudentMenu::currentStudent->getGrades().end()) {
            grade = it->second;
        }
        Text gradeText(interRegular, "Grade: " + to_string(grade), 24);
        gradeText.setFillColor(Color::Color(82, 209, 124));
        gradeText.setPosition(Vector2f(screenSize.x * .9, (screenSize.y * (.2 + (.15 * index))) + code.getLocalBounds().size.y + 20));

        window.draw(gradeText);
    }
    else {
        window.draw(enrollButton);
    }
}



void StudentMenu::drawCourses(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Courses", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());

    Text errorText(interThin, error, 24);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .175));
    errorText.setOrigin(errorText.getLocalBounds().getCenter());

    Text pageText(interBold, to_string(page), 48);
    pageText.setFillColor(black);
    pageText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .95));
    pageText.setOrigin(pageText.getLocalBounds().getCenter());


    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());

    Texture previousButtonTexture("resources/images/previous_button.png");
    previousButtonTexture.setSmooth(true);
    Sprite previousButton(previousButtonTexture);
    previousButton.setPosition(Vector2f(screenSize.x * .45, screenSize.y * .95));
    previousButton.setOrigin(previousButton.getLocalBounds().getCenter());


    Texture nextButtonTexture("resources/images/next_button.png");
    nextButtonTexture.setSmooth(true);
    Sprite nextButton(nextButtonTexture);
    nextButton.setPosition(Vector2f(screenSize.x * .55, screenSize.y * .95));
    nextButton.setOrigin(nextButton.getLocalBounds().getCenter());


    unordered_map<string, Course*> shownCourses;
    for (auto& [code, course] : courses) {
        shownCourses[code] = &course; 
    }
    int startIndex = page * 5;
    int max = min(5, static_cast<int>(shownCourses.size()) - startIndex);
    auto it = shownCourses.begin();
    advance(it, startIndex);
    for (int i = 0; i < max; i++) {
        drawStudentCourseItem(window, *it->second, i);
        ++it;
    }


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
                WindowManager::shownWindow = ShownWindow::StudentPanel;
                error.clear();
                page = 0;
            WindowManager::click_lock = true;
        }
        if (nextButton.getGlobalBounds().contains(mousePos)) {
            if (courses.size() - (page * 5) > 5) {
                WindowManager::click_lock = true;
                page++;
            }
        }
        if (previousButton.getGlobalBounds().contains(mousePos)) {
            if (page != 0) {
                WindowManager::click_lock = true;
                page--;
            }
        }

    }

    window.draw(title);
    if (page != 0)
        window.draw(previousButton);
    if (courses.size() - (page * 5) > 5)
        window.draw(nextButton);
    if (!error.empty())
        window.draw(errorText);
    window.draw(pageText);
    window.draw(backButton);
}



void drawStudentPerquisiteItem(RenderWindow& window, string perquisite, int index) {
    Vector2u screenSize = window.getSize();
    Text name(interBold, perquisite, 28);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.1 * index)))));

    window.draw(name);
}



void StudentMenu::drawCourseDetails(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, selectedCourse->getName(), 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());

    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());

    int index = 0;
    for (auto x : selectedCourse->getPrerequisites()) {
        drawStudentPerquisiteItem(window, x, index++);
    }

    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            selectedCourse = nullptr;
            WindowManager::shownWindow = ShownWindow::Courses;
            WindowManager::click_lock = true;
        }

    }

  

    window.draw(title);
    window.draw(backButton);


}

void drawStudentGradeItem(RenderWindow& window, pair<string, int> grade_pair, int index) {
    Vector2u screenSize = window.getSize();
    const string& courseCode = grade_pair.first;
    int courseGrade = grade_pair.second;
    string courseName;
    string courseSemster;

    if (courses.find(courseCode) != courses.end()) {
        auto& course = courses[courseCode];
        courseSemster = course.getSemester();
        courseName = course.getName();
    }
    else {
        courseName = "Unknown";
        courseSemster = "Unknown";
    }
    

    Text name(interRegular, courseName, 20);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.3 + (.1 * index)))));

    Text semster(interRegular, "Semster: " + courseSemster, 20);
    semster.setFillColor(black);
    semster.setPosition(Vector2f(screenSize.x * .5, (screenSize.y * (.3 + (.1 * index)))));
    
    Text grade(interRegular, "Grade: " + to_string(courseGrade), 20);
    grade.setFillColor(Color::Color(82, 209, 124));
    grade.setPosition(Vector2f(screenSize.x * .8, (screenSize.y * (.3 + (.1 * index)))));


    window.draw(name);
    window.draw(semster);
    window.draw(grade);

}


void StudentMenu::drawReport(RenderWindow& window) {

    Vector2u screenSize = window.getSize();

    Text title(interBold, "Report", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());

    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());


    Text name(interBold, "Student Name: " + currentStudent->getName(), 28);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, screenSize.y * .2 ));

    Text id(interBold, "ID: " + currentStudent->getId(), 28);
    id.setFillColor(black);
    id.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .2));

    Text cgpa(interBold, "CGPA: " + to_string(currentStudent->calculate_gpa()), 28);
    cgpa.setFillColor(black);
    cgpa.setPosition(Vector2f(screenSize.x * .8, screenSize.y * .2));



    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            selectedCourse = nullptr;
            WindowManager::shownWindow = ShownWindow::StudentPanel;
            WindowManager::click_lock = true;
        }

    }
    int index = 0;
    for (const auto& grade_pair : currentStudent->getGrades()) {
        drawStudentGradeItem(window, grade_pair, index++);
    }
 

    window.draw(title);
    window.draw(backButton);
    window.draw(name);
    window.draw(id);
    window.draw(cgpa);

}