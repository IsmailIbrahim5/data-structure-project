#include "WindowManager.h"
#include "MainMenu.h"
#include "AdminMenu.h"
using namespace sf;

ShownWindow WindowManager::shownWindow = ShownWindow::Login;
bool WindowManager::click_lock = false;



void WindowManager::handleInput(const std::optional<sf::Event>& event) {
	switch (shownWindow)
	{
	case ShownWindow::Login:
		MainMenu::handleInput(event);
		break;
	case ShownWindow::SignUp:
		MainMenu::handleInput(event);
		break;
	case ShownWindow::AddCourse:
		AdminMenu::handleInput(event);
		break;
	case ShownWindow::AdminCoursePerquisites:
		AdminMenu::handleInput(event);
		break;
	case ShownWindow::ModifyGrade:
		AdminMenu::handleInput(event);
		break;
	default:
		break;
	}
}