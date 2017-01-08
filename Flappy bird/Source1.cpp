#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>

int main()
{
	//enum GameState { MENU, GAME, SCORE, OPTIONS, GAME_OVER, END };
	//GameState state;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");
	//sf::Style::Resize;
	sf::Texture logoTexture, bkTexture, pipeTexture, pipe1Texture;
	sf::Sprite logoImage, bkImage, pipeImage, pipe1Image;
	sf::Font font;
	if (!font.loadFromFile("font/good.ttf"))
		throw std::runtime_error("Could not load good.ttf");
	sf::Text play, leaderbord, quit;
	sf::Vector2f mouse(sf::Mouse::getPosition(window));
	//MENU
	sf::Text menu("Menu", font, 135);
	menu.setStyle(sf::Text::Bold);
	menu.setFillColor(sf::Color(255,69,0));
	menu.setPosition(240, 210);

	const int buttons = 3;

	sf::Text buttons_text[buttons];
	buttons_text[0].setString("Play");
	buttons_text[1].setString("Leaderboard");
	buttons_text[2].setString("Quit");
	for (int i = 0; i < buttons; i++)
	{
		buttons_text[i].setFont(font);
		buttons_text[i].setCharacterSize(50);
		buttons_text[i].setPosition(800 / 2 - buttons_text[i].getGlobalBounds().width / 2, 380 + i * 70);
	}
	// Getting Error here!
	if (!bkTexture.loadFromFile("Images/background.png"))
		throw std::runtime_error("Could not load background.png");
	bkImage.setTexture(bkTexture);
	bkImage.setPosition(0, 0);

	if (!logoTexture.loadFromFile("Images/flappy.png"))
		throw std::runtime_error("Could not load flappy.png");
	logoImage.setTexture(logoTexture);
	logoImage.setPosition(50, 10);

	if (!pipeTexture.loadFromFile("Images/pipe_down.png"))
		throw std::runtime_error("Could not load pipe_down.png");
	pipeImage.setTexture(pipeTexture);
	pipeImage.setPosition(30, 400);

	if (!pipe1Texture.loadFromFile("Images/pipe_down.png"))
		throw std::runtime_error("Could not load pipe_down.png");
	pipe1Image.setTexture(pipe1Texture);
	pipe1Image.setPosition(620, 330);


	while (window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(bkImage);
		window.draw(logoImage);
		window.draw(pipeImage);
		window.draw(pipe1Image);
		window.draw(menu);
		for (int i = 0; i<buttons; i++)
		{
			if (buttons_text[i].getGlobalBounds().contains(mouse))
				buttons_text[i].setFillColor(sf::Color(255, 69, 0));
			else
				buttons_text[i].setFillColor(sf::Color(255, 215, 0));
		}
		for (int i = 0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}

		window.display();
	}
	return 0;
}