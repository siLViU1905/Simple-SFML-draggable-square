#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Draggable square");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Vector2i mousePos;

	bool mouseLeftPressed = false;
	bool cursorContained = false;


	sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
	rect.setPosition(sf::Vector2f(400.f, 300.f));
	rect.setFillColor(sf::Color::Blue);

	sf::Color lightBlue(170, 180, 230), darkBlue(0, 0, 140);

	std::optional<sf::Event> event;
	while (window.isOpen())
	{
		while (event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
			else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left && cursorContained)
					rect.setFillColor(darkBlue), mouseLeftPressed = true;
				
			}
			else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
				if (mouseButtonReleased->button == sf::Mouse::Button::Left)
					rect.setFillColor(sf::Color::Blue), mouseLeftPressed = false;
		}

		mousePos = sf::Mouse::getPosition(window);
		cursorContained = rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

		if (mouseLeftPressed) 
			rect.setPosition(static_cast<sf::Vector2f>(mousePos) - sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
		
		else 
			rect.setFillColor(cursorContained ? lightBlue : sf::Color::Blue);
		
		window.clear();

		window.draw(rect);

		window.display();
	}
	return 0;
}
