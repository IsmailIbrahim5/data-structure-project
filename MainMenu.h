#pragma once
#include "SFML/Graphics.hpp"
#include "Admin.h"
#include "Student.h"
#include "WindowManager.h"


enum class FocusedField {
    None,
    Username,
    Name,
    Password
};


class MainMenu {
public:
    static std::string usernameInput;
    static std::string error;
    static std::string nameInput;
    static std::string passwordInput;
    static FocusedField activeField;
    static void drawLogin(sf::RenderWindow& window);
    static void drawSignUp(sf::RenderWindow& window);
    static void handleInput(const std::optional<sf::Event>& event);
};
