#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>

int state=1;//state=0 cand jocul este inchis, state=1 cand jocul se afla in meniu, state=2 atunci cand ruleaza jocul, state=3 atunci cand dorim sa afisam leaderboard-ul;
sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");
sf::Font font;
sf::Text text;
sf::Text error;
sf::Texture logoTexture;
sf::Texture bkTexture;
sf::Texture floorTexture;
sf::Sprite logoImage;
sf::Sprite bkImage;
sf::Sprite floorImage;
//sf::SoundBuffer get_point_buffer;
//sf::SoundBuffer go_up_buffer;
//sf::SoundBuffer die_buffer;
sf::Texture birdTexture;
sf::Sprite birdImage;
//sf::Sound get_point;
//sf::Sound go_up;
//sf::Sound die;
float y = 300;
float x_bird = 30;
float length = 50;
float width = 50;
int points = 0;
float speed_bird = 3.5;
sf::Texture pipe_downTexture;
sf::Texture pipe1Texture;
sf::Texture pipe_upTexture;
sf::Texture pipe2_downTexture;
sf::Sprite pipe_downImage;
sf::Sprite pipe1Image;
sf::Sprite pipe_upImage;
int free_space = 150;
float x = 800;
float y_up = 100;
float y_down = 100;
float pipe_len = 375;
float pipe_width = 150;
float speed_pipe= 4.5;


void Menu()
{
	if (!font.loadFromFile("font/good.ttf"))
		throw std::runtime_error("Could not load good.ttf");
	// Getting Error here!
	if (!bkTexture.loadFromFile("Images/background.png"))
		throw std::runtime_error("Could not load background.png");
	bkImage.setTexture(bkTexture);
	bkImage.setPosition(0, 0);

	if (!logoTexture.loadFromFile("Images/flappy.png"))
		throw std::runtime_error("Could not load flappy.png");
	logoImage.setTexture(logoTexture);
	logoImage.setPosition(50, 10);

	if (!pipe_downTexture.loadFromFile("Images/pipe_down.png"))
		throw std::runtime_error("Could not load pipe_down.png");
	pipe_downImage.setTexture(pipe_downTexture);
	pipe_downImage.setPosition(30, 400);

	if (!pipe1Texture.loadFromFile("Images/pipe_down.png"))
		throw std::runtime_error("Could not load pipe_down.png");
	pipe1Image.setTexture(pipe1Texture);
	pipe1Image.setPosition(620, 330);

	//MENU
	sf::Text menu("Menu", font, 135);
	menu.setStyle(sf::Text::Bold);
	menu.setFillColor(sf::Color(255, 69, 0));
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

	while (state == 1)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
				event.key.code == sf::Keyboard::Escape)
				state = 0;


			else if (buttons_text[0].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = 2;
			}
			/*else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
				(event.type == sf::Event::MouseButtonReleased) &&
				(event.key.code == sf::Mouse::Left))
			{
				state = 3;
			}
			*/
			else if (buttons_text[2].getGlobalBounds().contains(mouse) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = 0;
			}

		}
		window.clear();

		for (int i = 0; i<buttons; i++)
		{
			if (buttons_text[i].getGlobalBounds().contains(mouse))
				buttons_text[i].setFillColor(sf::Color(255, 69, 0));
			else
				buttons_text[i].setFillColor(sf::Color(255, 215, 0));
		}

		window.draw(bkImage);
		window.draw(logoImage);
		window.draw(pipe_downImage);
		window.draw(pipe1Image);
		window.draw(menu);
		for (int i = 0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}
		window.display();
	}
}

void Play()
{
	if (!bkTexture.loadFromFile("Images/background.png"))
		throw std::runtime_error("Could not load background.png");
	bkImage.setTexture(bkTexture);
	bkImage.setPosition(0, 0);
	if (!floorTexture.loadFromFile("Images/floor.png"))
		throw std::runtime_error("Could not load floor.png");
	floorImage.setTexture(floorTexture);
	floorImage.setPosition(0, 550);
	if (!pipe_upTexture.loadFromFile("Images/pipe_up.png")){
		throw std::runtime_error("Could not load floor.png");
		state = 0;
	}
	pipe_upImage.setTexture(pipe_upTexture);
	pipe_upImage.setPosition(300, -150);
	if (!pipe_downTexture.loadFromFile("Images/pipe_down.png"))
	{
		throw std::runtime_error("Could not load pipe_down.png");
		//state = 0;
	}
	pipe_downImage.setTexture(pipe_downTexture);
	pipe_downImage.setPosition(300, 400);

	while (state == 2)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
				event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		window.clear();
		window.draw(bkImage);
		window.draw(pipe_upImage);
		window.draw(pipe_downImage);
		//window.draw(pipe2_up);
		//window.draw(pipe2_down);
		window.draw(floorImage);
		window.display();
	}
}

void startGame()
{
	while (state != 0)
	{
		switch (state)
		{
		case 1:
			Menu();
			break;
		case 2:
			Play();
			break;
		/*case 3:
			Leaderboard();
			break;*/
		case 0:
			break;
		}
	}
}

int main()
{
	startGame();
	return 0;
}