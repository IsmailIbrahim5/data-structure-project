#include "MainMenu.h"
#include <iostream>
#include "StudentMenu.h"
using namespace sf;
using namespace constants;



std::string MainMenu::usernameInput = "";
std::string MainMenu::nameInput = "";
std::string MainMenu::passwordInput = "";
std::string MainMenu::error = "";
FocusedField MainMenu::activeField = FocusedField::None;


void MainMenu::handleInput(const std::optional<sf::Event>& event) {
    if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
        if (textEntered->unicode < 128) {
            char c = static_cast<char>(textEntered->unicode);
            if (c == '\b') {
                switch (activeField) {
                case FocusedField::Username:
                    if (!usernameInput.empty()) usernameInput.pop_back();
                    break;
                case FocusedField::Name:
                    if (!nameInput.empty()) nameInput.pop_back();
                    break;
                case FocusedField::Password:
                    if (!passwordInput.empty()) passwordInput.pop_back();
                    break;
                default: break;
                }
            }

            else if (isprint(c)) {
                switch (activeField) {
                case FocusedField::Username:
                    usernameInput += c;
                    break;
                case FocusedField::Name:
                    nameInput += c;
                    break;
                case FocusedField::Password:
                    passwordInput += c;
                    break;
                default: break;
                }
            }
        }
    }
    if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Enter || keyEvent->code == sf::Keyboard::Key::Tab) {
            if (activeField == FocusedField::Username) {
                if (WindowManager::shownWindow == ShownWindow::Login) {
                    activeField = FocusedField::Password;
                }
                else {
                    activeField = FocusedField::Name;
                }
            }
            else if (activeField == FocusedField::Name) {
                activeField = FocusedField::Password;
            }
            else {
                activeField = FocusedField::Username;
            }
        }
    }
}

void MainMenu::drawLogin(RenderWindow& window) {


    Vector2u screenSize = window.getSize();
    Texture imageTexture("resources/images/login.png");
    Sprite image(imageTexture);
    image.setPosition(Vector2f(0, 0));
    window.draw(image);


    Text title(interBold, "LOGIN", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .75, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());


    // Username


    Text usernameHint(interExtraLight, "Student ID or admin username", 18);
    usernameHint.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameHint.setPosition(Vector2f(screenSize.x * .55, screenSize.y * .35));
    Text usernameText(interExtraLight, usernameInput, 18);
    usernameText.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameText.setPosition(Vector2f(screenSize.x * .55, screenSize.y * .35));
    RectangleShape usernameLine({ screenSize.x * .4f , 1 });
    usernameLine.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameLine.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.4f });
    usernameLine.setOrigin(usernameLine.getLocalBounds().getCenter());
    RectangleShape usernameHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    usernameHitbox.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.4f });
    usernameHitbox.setOrigin(usernameHitbox.getLocalBounds().getCenter());
    usernameHitbox.setFillColor(Color::Transparent);


    // Password

    Text passwordHint(interExtraLight, "Password", 18);
    passwordHint.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordHint.setPosition(Vector2f(screenSize.x * .55, screenSize.y * .5));
    RectangleShape passwordHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    passwordHitbox.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.5f });
    passwordHitbox.setOrigin(passwordHitbox.getLocalBounds().getCenter());
    passwordHitbox.setFillColor(Color::Transparent);
    Text passwordText(interExtraLight, passwordInput, 18);
    passwordText.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordText.setPosition(Vector2f(screenSize.x * .55, screenSize.y * .5));
    RectangleShape passwordLine({ screenSize.x * .4f , 1 });
    passwordLine.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordLine.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.55f });
    passwordLine.setOrigin(passwordLine.getLocalBounds().getCenter());



    RectangleShape studentLoginButtonBg({ screenSize.x * .4f , screenSize.y * .1f });
    studentLoginButtonBg.setFillColor(primaryColor);
    studentLoginButtonBg.setOrigin(studentLoginButtonBg.getLocalBounds().getCenter());
    studentLoginButtonBg.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.65f });
    Text studentLoginButtonText(interBold, "Login as student", 32);
    studentLoginButtonText.setFillColor(Color::White);
    studentLoginButtonText.setPosition(Vector2f(screenSize.x * .75, screenSize.y * .65));
    studentLoginButtonText.setOrigin(studentLoginButtonText.getLocalBounds().getCenter());


    RectangleShape adminLoginButtonBg({ screenSize.x * .4f , screenSize.y * .1f });
    adminLoginButtonBg.setOutlineColor(primaryColor);
    adminLoginButtonBg.setOutlineThickness(2);
    adminLoginButtonBg.setOrigin(adminLoginButtonBg.getLocalBounds().getCenter());
    adminLoginButtonBg.setPosition({ screenSize.x * 0.75f , screenSize.y * 0.775f });
    Text adminLoginButtonText(interBold, "Login as admin", 32);
    adminLoginButtonText.setFillColor(primaryColor);
    adminLoginButtonText.setPosition(Vector2f(screenSize.x * .75, screenSize.y * .775));
    adminLoginButtonText.setOrigin(adminLoginButtonText.getLocalBounds().getCenter());

    Text errorText(interMedium, error, 14);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(Vector2f(screenSize.x * .75, screenSize.y * .575));
    errorText.setOrigin(errorText.getLocalBounds().getCenter());

    Text hintText(interMedium, "Don't have an account?", 14);
    hintText.setFillColor(black);
    hintText.setPosition(Vector2f(screenSize.x * .675, screenSize.y * .9));

    Text hintTextButton(interMedium, "Sign up", 14);
    hintTextButton.setFillColor(primaryColor);
    hintTextButton.setPosition(Vector2f((screenSize.x * .675) + hintText.getLocalBounds().size.x + 2, screenSize.y * .9));
    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (usernameHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = FocusedField::Username;
        }
        if (passwordHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = FocusedField::Password;

        }
        if (studentLoginButtonBg.getGlobalBounds().contains(mousePos)) {
            std::string result = Student::loginStudent(usernameInput, passwordInput);
            if (result.empty()) {
                WindowManager::shownWindow = ShownWindow::StudentPanel;
                auto it = students.find(usernameInput);
                StudentMenu::currentStudent = &it->second;
            }
            else {
                error = result;
            }
        }
        if (adminLoginButtonBg.getGlobalBounds().contains(mousePos)) {
            std::string result = Admin::loginAdmin(usernameInput, passwordInput);
            if (result.empty()) {
                WindowManager::shownWindow = ShownWindow::AdminPanel;
            }
            else {
                error = result;
            }
        }
        if (hintTextButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::SignUp;
            error = "";
        }
        WindowManager::click_lock = true;
    }

    window.draw(title);
    if (usernameInput.empty())
        window.draw(usernameHint);
    window.draw(usernameHitbox);
    if (!error.empty())
        window.draw(errorText);
    window.draw(usernameText);
    if (passwordInput.empty())
        window.draw(passwordHint);
    window.draw(passwordHitbox);
    window.draw(passwordText);
    window.draw(usernameLine);
    window.draw(passwordLine);
    window.draw(studentLoginButtonBg);
    window.draw(studentLoginButtonText);
    window.draw(adminLoginButtonBg);
    window.draw(adminLoginButtonText);
    window.draw(hintText);
    window.draw(hintTextButton);
}



void MainMenu::drawSignUp(RenderWindow& window) {


    Vector2u screenSize = window.getSize();
    Texture imageTexture("resources/images/signup.png");
    Sprite image(imageTexture);
    image.setPosition(Vector2f(screenSize.x * .5f, 0));
    window.draw(image);


    Text title(interBold, "SIGN UP", 48);
    title.setFillColor(black);
    title.setPosition(Vector2f(screenSize.x * .25, screenSize.y * .1));
    title.setOrigin(title.getLocalBounds().getCenter());

    // Username

    Text usernameHint(interExtraLight, "Student ID or admin username", 18);
    usernameHint.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameHint.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .25));
    Text usernameText(interExtraLight, usernameInput, 18);
    usernameText.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameText.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .25));
    RectangleShape usernameLine({ screenSize.x * .4f , 1 });
    usernameLine.setFillColor(activeField == FocusedField::Username ? primaryColor : black);
    usernameLine.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.3f });
    usernameLine.setOrigin(usernameLine.getLocalBounds().getCenter());
    RectangleShape usernameHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    usernameHitbox.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.25f });
    usernameHitbox.setOrigin(usernameHitbox.getLocalBounds().getCenter());
    usernameHitbox.setFillColor(Color::Transparent);

    // Name

    Text nameHint(interExtraLight, "Full Name", 18);
    nameHint.setFillColor(activeField == FocusedField::Name ? primaryColor : black);
    nameHint.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .375));
    Text nameText(interExtraLight, nameInput, 18);
    nameText.setFillColor(activeField == FocusedField::Name ? primaryColor : black);
    nameText.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .375));
    RectangleShape nameLine({ screenSize.x * .4f , 1 });
    nameLine.setFillColor(activeField == FocusedField::Name ? primaryColor : black);
    nameLine.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.425f });
    nameLine.setOrigin(nameLine.getLocalBounds().getCenter());

    RectangleShape nameHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    nameHitbox.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.375f });
    nameHitbox.setOrigin(nameHitbox.getLocalBounds().getCenter());
    nameHitbox.setFillColor(Color::Transparent);


    // Password

    Text passwordHint(interExtraLight, "Password", 18);
    passwordHint.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordHint.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .5));
    RectangleShape passwordHitbox({ screenSize.x * .4f , screenSize.y * .1f });
    passwordHitbox.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.5f });
    passwordHitbox.setOrigin(passwordHitbox.getLocalBounds().getCenter());
    passwordHitbox.setFillColor(Color::Transparent);
    Text passwordText(interExtraLight, passwordInput, 18);
    passwordText.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordText.setPosition(Vector2f(screenSize.x * .05, screenSize.y * .5));
    RectangleShape passwordLine({ screenSize.x * .4f , 1 });
    passwordLine.setFillColor(activeField == FocusedField::Password ? primaryColor : black);
    passwordLine.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.55f });
    passwordLine.setOrigin(passwordLine.getLocalBounds().getCenter());



    RectangleShape studentLoginButtonBg({ screenSize.x * .4f , screenSize.y * .1f });
    studentLoginButtonBg.setFillColor(primaryColor);
    studentLoginButtonBg.setOrigin(studentLoginButtonBg.getLocalBounds().getCenter());
    studentLoginButtonBg.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.65f });
    Text studentLoginButtonText(interBold, "Sign up as student", 32);
    studentLoginButtonText.setFillColor(Color::White);
    studentLoginButtonText.setPosition(Vector2f(screenSize.x * .25, screenSize.y * .65));
    studentLoginButtonText.setOrigin(studentLoginButtonText.getLocalBounds().getCenter());


    RectangleShape adminLoginButtonBg({ screenSize.x * .4f , screenSize.y * .1f });
    adminLoginButtonBg.setOutlineColor(primaryColor);
    adminLoginButtonBg.setOutlineThickness(2);
    adminLoginButtonBg.setOrigin(adminLoginButtonBg.getLocalBounds().getCenter());
    adminLoginButtonBg.setPosition({ screenSize.x * 0.25f , screenSize.y * 0.775f });
    Text adminLoginButtonText(interBold, "Sign up as admin", 32);
    adminLoginButtonText.setFillColor(primaryColor);
    adminLoginButtonText.setPosition(Vector2f(screenSize.x * .25, screenSize.y * .775));
    adminLoginButtonText.setOrigin(adminLoginButtonText.getLocalBounds().getCenter());

    Text errorText(interMedium, error, 14);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(Vector2f(screenSize.x * .25, screenSize.y * .575));
    errorText.setOrigin(errorText.getLocalBounds().getCenter());

    Text hintText(interMedium, "Already have an account?", 14);
    hintText.setFillColor(black);
    hintText.setPosition(Vector2f(screenSize.x * .175, screenSize.y * .9));

    Text hintTextButton(interMedium, "Log in", 14);
    hintTextButton.setFillColor(primaryColor);
    hintTextButton.setPosition(Vector2f((screenSize.x * .175) + hintText.getLocalBounds().size.x + 2, screenSize.y * .9));
    if (Mouse::isButtonPressed(Mouse::Button::Left) && !WindowManager::click_lock) {
        Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
        if (usernameHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = FocusedField::Username;
        }
        if (nameHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = FocusedField::Name;
        }
        if (passwordHitbox.getGlobalBounds().contains(mousePos)) {
            activeField = FocusedField::Password;
        }
        if (studentLoginButtonBg.getGlobalBounds().contains(mousePos)) {
            std::string result = Student::signUpStudent(usernameInput, nameInput, passwordInput);
            if (result.empty()) {
                auto it = students.find(usernameInput);
                StudentMenu::currentStudent = &it->second;   
                WindowManager::shownWindow = ShownWindow::StudentPanel;
               
            }
            else {
                error = result;
            }
        }
        if (adminLoginButtonBg.getGlobalBounds().contains(mousePos)) {
            std::string result = Admin::signUpAdmin(usernameInput, nameInput, passwordInput);
            if (result.empty()) {
                WindowManager::shownWindow = ShownWindow::AdminPanel;
            }
            else {
                error = result;
            }
        }
        if (hintTextButton.getGlobalBounds().contains(mousePos)) {
            WindowManager::shownWindow = ShownWindow::Login;
            error = "";
        }
        WindowManager::click_lock = true;

    }

    window.draw(title);
    if (usernameInput.empty())
        window.draw(usernameHint);
    window.draw(usernameHitbox);
    window.draw(usernameText);
    if (!error.empty())
        window.draw(errorText);
    if (nameInput.empty())
        window.draw(nameHint);
    window.draw(nameHitbox);
    window.draw(nameText);
    if (passwordInput.empty())
        window.draw(passwordHint);
    window.draw(passwordHitbox);
    window.draw(passwordText);
    window.draw(usernameLine);
    window.draw(nameLine);
    window.draw(passwordLine);
    window.draw(studentLoginButtonBg);
    window.draw(studentLoginButtonText);
    window.draw(adminLoginButtonBg);
    window.draw(adminLoginButtonText);
    window.draw(hintText);
    window.draw(hintTextButton);
}