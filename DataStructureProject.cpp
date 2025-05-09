#include "FileOperations.h"
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
	load_students_from_file("data.json");
	load_admins_from_file("data.json");
	loadCoursesFromFile("data.json");
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	save_students_to_file("data.json");
	save_admins_to_file("data.json");
}
