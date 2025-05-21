#include "AdminMenu.h"
using namespace sf;
using namespace constants;


std::string AdminMenu::codeInput = "";
std::string AdminMenu::nameInput = "";
std::string AdminMenu::instructorInput = "";
std::string AdminMenu::syllabusInput = "";
std::string AdminMenu::hoursInput = "";
std::string AdminMenu::periquisiteInput = "";
std::string AdminMenu::gradeInput = "";
int AdminMenu::page = 0;
Course* AdminMenu::selectedCourse;
Student* AdminMenu::selectedStudent;
AdminFocusedField AdminMenu::activeField = AdminFocusedField::None;

void AdminMenu::handleInput(const std::optional<sf::Event>& event) {
    if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
        if (textEntered->unicode < 128) {
            char c = static_cast<char>(textEntered->unicode);
            if (c == '\b') {
                switch (activeField) {
                case AdminFocusedField::Code:
                    if (!codeInput.empty()) codeInput.pop_back();
                    break;
                case AdminFocusedField::Name:
                    if (!nameInput.empty()) nameInput.pop_back();
                    break;
                case AdminFocusedField::Instructor:
                    if (!instructorInput.empty()) instructorInput.pop_back();
                    break;
                case AdminFocusedField::Syllabus:
                    if (!syllabusInput.empty()) syllabusInput.pop_back();
                    break;
                case AdminFocusedField::Hours:
                    if (!hoursInput.empty()) hoursInput.pop_back();
                    break;
                case AdminFocusedField::Perquisite:
                    if (!periquisiteInput.empty()) periquisiteInput.pop_back();
                    break;
                case AdminFocusedField::Grade:
                    if (!gradeInput.empty()) gradeInput.pop_back();
                    break;

                default: break;
                }
            }

            else if (isprint(c)) {
                switch (activeField) {
                case AdminFocusedField::Code:
                    codeInput += c;
                    break;
                case AdminFocusedField::Name:
                    nameInput += c;
                    break;
                case AdminFocusedField::Instructor:
                    instructorInput += c;
                    break;
                case AdminFocusedField::Syllabus:
                    syllabusInput += c;
                    break;
                case AdminFocusedField::Hours:
                    if (c >= '0' && c <= '9')
                        hoursInput += c;
                    break;
                case AdminFocusedField::Perquisite:
                    periquisiteInput += c;
                    break;
                case AdminFocusedField::Grade:
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
            if (activeField == AdminFocusedField::Code) {
                activeField = AdminFocusedField::Name;
            }
            else if (activeField == AdminFocusedField::Name) {
                activeField = AdminFocusedField::Instructor;
            }
            else if (activeField == AdminFocusedField::Instructor) {
                activeField = AdminFocusedField::Syllabus;
            }
            else if (activeField == AdminFocusedField::Syllabus) {
                activeField = AdminFocusedField::Hours;
            }
            else if (activeField == AdminFocusedField::Perquisite) {
                selectedCourse->addPrerequisite(periquisiteInput);
                Admin::addPrerequisiteToCourse(selectedCourse->getCode(), periquisiteInput);
                periquisiteInput.clear();
                activeField = AdminFocusedField::None;
            }
        }

    }

}


void AdminMenu::drawMenu(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Admin Panel", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture courseButtonTexture("resources/images/course_button.png");
    Sprite courseButton(courseButtonTexture);
    courseButton.setPosition(Vector2f(screenSize.x * .25, screenSize.y * .5));
    courseButton.setOrigin(courseButton.getLocalBounds().getCenter());

    Texture perquisiteButtonTexture("resources/images/perquisite_button.png");
    Sprite perquisiteButton(perquisiteButtonTexture);
    perquisiteButton.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .5));
    perquisiteButton.setOrigin(perquisiteButton.getLocalBounds().getCenter());

    Texture gradesButtonTexture("resources/images/grades_button.png");
    Sprite gradesButton(gradesButtonTexture);
    gradesButton.setPosition(Vector2f(screenSize.x * .75, screenSize.y * .5));
    gradesButton.setOrigin(gradesButton.getLocalBounds().getCenter());


    Texture logoutButtonTexture("resources/images/logout_button.png");
    logoutButtonTexture.setSmooth(true);
    Sprite logoutButton(logoutButtonTexture);
    logoutButton.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .9));
    logoutButton.setOrigin(logoutButton.getLocalBounds().getCenter());


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (courseButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::AddCourse;

        }
        if (perquisiteButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::ChooseCourse;

        }
        if (gradesButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::ChooseStudent;
        }
        if (logoutButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::Login;
        }
        WindowManager::click_lock = true;
    }


    window.draw(title);
    window.draw(courseButton);
    window.draw(perquisiteButton);
    window.draw(gradesButton);
    window.draw(logoutButton);

}

void AdminMenu::drawAddCourse(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Add Course", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());

    Texture addButtonTexture("resources/images/add_course_button.png");
    Sprite addButton(addButtonTexture);
    addButton.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .9));
    addButton.setOrigin(addButton.getLocalBounds().getCenter());


    Text codeHint(interExtraLight, "Code", 18);
    codeHint.setFillColor(activeField == AdminFocusedField::Code ? primaryColor : black);
    codeHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .25));
    codeHint.setOrigin(codeHint.getLocalBounds().getCenter());
    Text codeText(interExtraLight, codeInput, 18);
    codeText.setFillColor(activeField == AdminFocusedField::Code ? primaryColor : black);
    codeText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .25));
    codeText.setOrigin(codeText.getLocalBounds().getCenter());
    RectangleShape codeLine({ screenSize.x * .4f , 1 });
    codeLine.setFillColor(activeField == AdminFocusedField::Code ? primaryColor : black);
    codeLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.275f });
    codeLine.setOrigin(codeLine.getLocalBounds().getCenter());

    RectangleShape codeHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    codeHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.25f });
    codeHitbox.setOrigin(codeHitbox.getLocalBounds().getCenter());
    codeHitbox.setFillColor(Color::Transparent);



    Text nameHint(interExtraLight, "Name", 18);
    nameHint.setFillColor(activeField == AdminFocusedField::Name ? primaryColor : black);
    nameHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .375));
    nameHint.setOrigin(nameHint.getLocalBounds().getCenter());
    Text nameText(interExtraLight, nameInput, 18);
    nameText.setFillColor(activeField == AdminFocusedField::Name ? primaryColor : black);
    nameText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .375));
    nameText.setOrigin(nameText.getLocalBounds().getCenter());
    RectangleShape nameLine({ screenSize.x * .4f , 1 });
    nameLine.setFillColor(activeField == AdminFocusedField::Name ? primaryColor : black);
    nameLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.4f });
    nameLine.setOrigin(nameLine.getLocalBounds().getCenter());

    RectangleShape nameHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    nameHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.375f });
    nameHitbox.setOrigin(nameHitbox.getLocalBounds().getCenter());
    nameHitbox.setFillColor(Color::Transparent);

    //------

    Text instructorHint(interExtraLight, "Instructor Name", 18);
    instructorHint.setFillColor(activeField == AdminFocusedField::Instructor ? primaryColor : black);
    instructorHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .5));
    instructorHint.setOrigin(instructorHint.getLocalBounds().getCenter());
    Text instructorText(interExtraLight, instructorInput, 18);
    instructorText.setFillColor(activeField == AdminFocusedField::Instructor ? primaryColor : black);
    instructorText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .5));
    instructorText.setOrigin(instructorText.getLocalBounds().getCenter());
    RectangleShape instructorLine({ screenSize.x * .4f , 1 });
    instructorLine.setFillColor(activeField == AdminFocusedField::Instructor ? primaryColor : black);
    instructorLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.525f });
    instructorLine.setOrigin(instructorLine.getLocalBounds().getCenter());

    RectangleShape instructorHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    instructorHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.5f });
    instructorHitbox.setOrigin(instructorHitbox.getLocalBounds().getCenter());
    instructorHitbox.setFillColor(Color::Transparent);
    //------

    Text syllabusHint(interExtraLight, "Syllabus", 18);
    syllabusHint.setFillColor(activeField == AdminFocusedField::Syllabus ? primaryColor : black);
    syllabusHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .625));
    syllabusHint.setOrigin(syllabusHint.getLocalBounds().getCenter());

    Text syllabusText(interExtraLight, syllabusInput, 18);
    syllabusText.setFillColor(activeField == AdminFocusedField::Syllabus ? primaryColor : black);
    syllabusText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .625));
    syllabusText.setOrigin(syllabusText.getLocalBounds().getCenter());
    RectangleShape syllabusLine({ screenSize.x * .4f , 1 });
    syllabusLine.setFillColor(activeField == AdminFocusedField::Syllabus ? primaryColor : black);
    syllabusLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.65f });
    syllabusLine.setOrigin(syllabusLine.getLocalBounds().getCenter());

    RectangleShape syllabusHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    syllabusHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.625f });
    syllabusHitbox.setOrigin(syllabusHitbox.getLocalBounds().getCenter());
    syllabusHitbox.setFillColor(Color::Transparent);

    //------

    Text hoursHint(interExtraLight, "Credit Hours", 18);
    hoursHint.setFillColor(activeField == AdminFocusedField::Hours ? primaryColor : black);
    hoursHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .75));
    hoursHint.setOrigin(hoursHint.getLocalBounds().getCenter());
    Text hoursText(interExtraLight, hoursInput, 18);
    hoursText.setFillColor(activeField == AdminFocusedField::Hours ? primaryColor : black);
    hoursText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .75));
    hoursText.setOrigin(hoursText.getLocalBounds().getCenter());
    RectangleShape hoursLine({ screenSize.x * .4f , 1 });
    hoursLine.setFillColor(activeField == AdminFocusedField::Hours ? primaryColor : black);
    hoursLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.775f });
    hoursLine.setOrigin(hoursLine.getLocalBounds().getCenter());

    RectangleShape hoursHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    hoursHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.75f });
    hoursHitbox.setOrigin(hoursHitbox.getLocalBounds().getCenter());
    hoursHitbox.setFillColor(Color::Transparent);


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::AdminPanel;
        }

        if (nameHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Name;
        }
        if (codeHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Code;
        }
        if (instructorHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Instructor;
        }
        if (syllabusHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Syllabus;
        }
        if (hoursHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Hours;
        }

        if (addButton.getGlobalBounds().contains(mousePos)) {
            if (!codeInput.empty() && !nameInput.empty() && !instructorInput.empty() && !syllabusInput.empty() && !hoursInput.empty()) {
                Admin::addCourse(codeInput, nameInput, instructorInput, syllabusInput, std::stof(hoursInput));
            }
            WindowManager::shownWindow = ShownWindow::AdminPanel;
        }
        WindowManager::click_lock = true;
    }


    window.draw(title);
    window.draw(backButton);

    if (nameInput.empty())
        window.draw(nameHint);
    window.draw(nameHitbox);
    window.draw(nameText);
    window.draw(nameLine);

    if (codeInput.empty())
        window.draw(codeHint);
    window.draw(codeHitbox);
    window.draw(codeText);
    window.draw(codeLine);
    if (instructorInput.empty())
        window.draw(instructorHint);
    window.draw(instructorHitbox);
    window.draw(instructorText);
    window.draw(instructorLine);
    if (syllabusInput.empty())
        window.draw(syllabusHint);
    window.draw(syllabusHitbox);
    window.draw(syllabusText);
    window.draw(syllabusLine);
    if (hoursInput.empty())
        window.draw(hoursHint);
    window.draw(hoursHitbox);
    window.draw(hoursText);
    window.draw(hoursLine);
    window.draw(addButton);

}


void drawCourseItem(RenderWindow& window, Course& course, int index) {
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


    RectangleShape courseHitbox({ screenSize.x * 1.f , screenSize.y * .125f });
    courseHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * (.25f + (.15f * index)) });
    courseHitbox.setOrigin(courseHitbox.getLocalBounds().getCenter());
    courseHitbox.setFillColor(Color::Transparent);

    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (courseHitbox.getGlobalBounds().contains(mousePos)) {
            AdminMenu::selectedCourse = &course;
            if (AdminMenu::selectedStudent==nullptr) {
                WindowManager::shownWindow = ShownWindow::AdminCoursePerquisites;
            }
            else {
                WindowManager::shownWindow = ShownWindow::ModifyGrade;
           
                if (AdminMenu::selectedStudent->getGrades().count(AdminMenu::selectedCourse->getCode())) {
                    AdminMenu::gradeInput = to_string(AdminMenu::selectedStudent->getGrades().at(AdminMenu::selectedCourse->getCode()));
                }
                else {
                    AdminMenu::gradeInput = "0";
                }
            }
            WindowManager::click_lock = true;

        }
    }

    window.draw(courseHitbox);
    window.draw(code);
    window.draw(name);
    window.draw(instructor);
    window.draw(hours);
    window.draw(syllabus);
}



void AdminMenu::drawChooseCourse(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Choose Course", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());

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
    if (selectedStudent != nullptr) {
        for (auto& [code, course] : courses) {
            if (selectedStudent->getRegisteredCourses().count(code)) {
                shownCourses[code] = &course;
            }
        }
    }
    else {
        for (auto& [code, course] : courses) {
            shownCourses[code] = &course;
        }
    }

    
    int startIndex = page * 5;
    int max = min(5, static_cast<int>(shownCourses.size()) - startIndex);

    auto it = shownCourses.begin();
    advance(it, startIndex);

    for (int i = 0; i < max; i++) {
        drawCourseItem(window, *it->second, i);  
        ++it;
    }


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            if (selectedStudent != nullptr) {
                selectedStudent = nullptr;
                WindowManager::shownWindow = ShownWindow::ChooseStudent;
            }
            else {
                WindowManager::shownWindow = ShownWindow::AdminPanel;
            }
            page = 0;

            WindowManager::click_lock = true;
        }
        if (nextButton.getGlobalBounds().contains(mousePos)) {
            if (shownCourses.size() - (page * 5) > 5) {
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
    if (shownCourses.size() - (page * 5) > 5)
        window.draw(nextButton);
    window.draw(pageText);
    window.draw(backButton);
}




void drawPerquisiteItem(RenderWindow& window, string perquisite, int index, bool canDelete) {
    Vector2u screenSize = window.getSize();
    Text name(interBold, perquisite, 28);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.1 * index)))));


    Texture deleteButtonTexture("resources/images/delete_button.png");
    deleteButtonTexture.setSmooth(true);
    Sprite deleteButton(deleteButtonTexture);
    deleteButton.setPosition(Vector2f(screenSize.x * .8, (screenSize.y * (.2 + (.1 * index)))));



    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (deleteButton.getGlobalBounds().contains(mousePos) && canDelete) {
            Admin::removePrerequisiteFromCourse(AdminMenu::selectedCourse->getCode(), perquisite);
            AdminMenu::selectedCourse->removePrerequisite(perquisite);
            WindowManager::click_lock = true;
        }
    }

    window.draw(name);
    if (canDelete)
        window.draw(deleteButton);
}




void AdminMenu::drawCoursePerquisites(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Course Perquisites", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());




    unordered_set<string>  perquisites = selectedCourse->getPrerequisites();
    int index = 0;
    for (auto x : perquisites) {
        drawPerquisiteItem(window, x, index++, true);
    }
    if (activeField == AdminFocusedField::Perquisite) {
        drawPerquisiteItem(window, periquisiteInput + '|', index++, false);
    }

    Texture addButtonTexture("resources/images/add_perquisite_button.png");
    addButtonTexture.setSmooth(true);
    Sprite addButton(addButtonTexture);
    addButton.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.1 * index)))));


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            selectedCourse = nullptr;
            WindowManager::shownWindow = ShownWindow::ChooseCourse;
            WindowManager::click_lock = true;
        }
        if (addButton.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Perquisite;
        }
    }


    window.draw(title);
    window.draw(addButton);
    window.draw(backButton);
}


void drawStudentItem(RenderWindow& window, Student& student, int index) {
    Vector2u screenSize = window.getSize();
    Text name(interBold, student.getName(), 28);
    name.setFillColor(black);
    name.setPosition(Vector2f(screenSize.x * .025, (screenSize.y * (.2 + (.1 * index)))));

    Text id(interThin, "ID: " + student.getId(), 18);
    id.setFillColor(black);
    id.setPosition(Vector2f(screenSize.x * .5, (screenSize.y * (.2 + (.1 * index)))));



    RectangleShape courseHitbox({ screenSize.x * 1.f , screenSize.y * .1f });
    courseHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * (.225f + (.1f * index)) });
    courseHitbox.setOrigin(courseHitbox.getLocalBounds().getCenter());
    courseHitbox.setFillColor(Color::Transparent);


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (courseHitbox.getGlobalBounds().contains(mousePos)) {
            AdminMenu::selectedStudent = &student;
            WindowManager::shownWindow = ShownWindow::ChooseCourse;

            WindowManager::click_lock = true;
        }
    }

    window.draw(name);
    window.draw(id);
    window.draw(courseHitbox);
}




void AdminMenu::drawChooseStudent(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Choose Student", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());


    int index = 0;
    for (auto& x : students) {
        drawStudentItem(window, x.second, index++);
    }



    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (backButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::AdminPanel;
            WindowManager::click_lock = true;
        }
    }


    window.draw(title);
    window.draw(backButton);
}


void AdminMenu::drawModifyGrade(RenderWindow& window) {
    Vector2u screenSize = window.getSize();

    Text title(interBold, "Modify Grade", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    Texture backButtonTexture("resources/images/back_button.png");
    Sprite backButton(backButtonTexture);
    backButton.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .1));
    backButton.setOrigin(backButton.getLocalBounds().getCenter());

    Text gradeHint(interExtraLight, "Grade", 18);
    gradeHint.setFillColor(activeField == AdminFocusedField::Grade ? primaryColor : black);
    gradeHint.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .5));
    gradeHint.setOrigin(gradeHint.getLocalBounds().getCenter());
    Text gradeText(interExtraLight, gradeInput, 18);
    gradeText.setFillColor(activeField == AdminFocusedField::Grade ? primaryColor : black);
    gradeText.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .5));
    gradeText.setOrigin(gradeText.getLocalBounds().getCenter());
    RectangleShape gradeLine({ screenSize.x * .4f , 1 });
    gradeLine.setFillColor(activeField == AdminFocusedField::Grade ? primaryColor : black);
    gradeLine.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.525f });
    gradeLine.setOrigin(gradeLine.getLocalBounds().getCenter());

    RectangleShape gradeHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    gradeHitbox.setPosition({ screenSize.x * 0.5f , screenSize.y * 0.5f });
    gradeHitbox.setOrigin(gradeHitbox.getLocalBounds().getCenter());
    gradeHitbox.setFillColor(Color::Transparent);



    Texture doneButtonTexture("resources/images/done_button.png");
    Sprite doneButton(doneButtonTexture);
    doneButton.setPosition(Vector2f(screenSize.x * .5, screenSize.y * .9));
    doneButton.setOrigin(doneButton.getLocalBounds().getCenter());


    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (doneButton.getGlobalBounds().contains(mousePos)) {

            if (!gradeInput.empty()) {
                Admin::setGradeToStudent(selectedStudent->getId(), selectedCourse->getCode(), stoi(gradeInput));
            }
            selectedCourse = nullptr;
            gradeInput.clear();
            WindowManager::shownWindow = ShownWindow::ChooseCourse;
            WindowManager::click_lock = true;
        }if (backButton.getGlobalBounds().contains(mousePos)) {
            selectedCourse = nullptr;
            gradeInput.clear();
            WindowManager::shownWindow = ShownWindow::ChooseCourse;
            WindowManager::click_lock = true;
        }
        if (gradeHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = AdminFocusedField::Grade;
            WindowManager::click_lock = true;
        }
    }


    window.draw(title);
    window.draw(backButton);
    window.draw(doneButton);

    if (gradeInput.empty())
        window.draw(gradeHint);
    window.draw(gradeText);
    window.draw(gradeLine);
    window.draw(gradeHitbox);
}