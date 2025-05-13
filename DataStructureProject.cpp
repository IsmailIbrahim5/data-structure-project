#include "FileOperations.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "AdminMenu.h"
#include "StudentMenu.h"

using namespace sf;



int main() {
	load_students_from_file("data.json");
	load_admins_from_file("data.json");
	loadCoursesFromFile("data.json");
    RenderWindow window(sf::VideoMode({ 1280, 800 }), "Course Registiration", sf::Style::Close);
    Image image("resources/images/app_icon.png");
    window.setIcon(image);
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                WindowManager::click_lock = false;
            }

            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<sf::Event::TextEntered>() || event->is<sf::Event::KeyPressed>())
                WindowManager::handleInput(*event);

        }

        window.clear(Color::White);

        switch (WindowManager::shownWindow)
        {
        case ShownWindow::Login:  MainMenu::drawLogin(window); break;
        case ShownWindow::SignUp:  MainMenu::drawSignUp(window); break;
        case ShownWindow::AdminPanel:  AdminMenu::drawMenu(window); break;
        case ShownWindow::AddCourse:  AdminMenu::drawAddCourse(window); break;
        case ShownWindow::ChooseCourse:  AdminMenu::drawChooseCourse(window); break;
        case ShownWindow::AdminCoursePerquisites:  AdminMenu::drawCoursePerquisites(window); break;
        case ShownWindow::ChooseStudent:  AdminMenu::drawChooseStudent(window); break;
        case ShownWindow::ModifyGrade:  AdminMenu::drawModifyGrade(window); break;
        case ShownWindow::StudentPanel:  StudentMenu::drawMenu(window); break;
        case ShownWindow::Courses:  StudentMenu::drawCourses(window); break;
        case ShownWindow::CourseDetails:  StudentMenu::drawCourseDetails(window); break;
        case ShownWindow::Report:  StudentMenu::drawReport(window); break;

        default:
            break;
        }
      

        window.display();
    }

	save_students_to_file("data.json");
	save_admins_to_file("data.json");

}
