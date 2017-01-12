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
float yBird = 300;
float xBird = 30;

float length = 50;
float width = 50;

int points = 0;

float speed_bird = 3.5;
sf::Texture pipe_downTexture;
sf::Texture pipe_upTexture;

sf::Sprite pipeMenu_Image;

sf::Sprite pipe1_upImage;
sf::Sprite pipe1_downImage;

sf::Sprite pipe2_upImage;
sf::Sprite pipe2_downImage;

sf::Sprite pipe3_upImage;
sf::Sprite pipe3_downImage;

float xPipe1;
float xPipe2 ;
float xPipe3 ;

float yPipe1 ;
float yPipe2 ;
float yPipe3 ;

int free_space = 150;
float pipe_len = 375;
float pipe_width = 150;
float speed_pipe= 4.5;
void replay();

int getRand(int A, int B)
{
	return rand() % (A - B) + A;
}

void loadFiles()
{
	if (!bkTexture.loadFromFile("Images/background.png"))
		throw std::runtime_error("Could not load background.png");
	bkImage.setTexture(bkTexture);

	if (!floorTexture.loadFromFile("Images/floor.png"))
		throw std::runtime_error("Could not load floor.png");
	floorImage.setTexture(floorTexture);

	if (!pipe_upTexture.loadFromFile("Images/pipe_up.png"))
		throw std::runtime_error("Could not load floor.png");

	if (!pipe_downTexture.loadFromFile("Images/pipe_down.png"))
		throw std::runtime_error("Could not load pipe_down.png");

	if (!font.loadFromFile("font/good.ttf"))
		throw std::runtime_error("Could not load good.ttf");

	if (!logoTexture.loadFromFile("Images/flappy.png"))
		throw std::runtime_error("Could not load flappy.png");

	if (!birdTexture.loadFromFile("Images/bird.png"))
		throw std::runtime_error("Could not load bird.png");
}

void setPipeAtPos(int x, int carePipe)
{
	switch (carePipe)
	{
	case 1:
	{
			  pipe1_upImage.setPosition(x, yPipe1);
			  pipe1_downImage.setPosition(x, yPipe1 + pipe_len + free_space);
			  break;
	}
	case 2:
	{
			  pipe2_upImage.setPosition(x, yPipe2);
			  pipe2_downImage.setPosition(x, yPipe2 + pipe_len + free_space);
			  break;
	}
	case 3:
	{
			  pipe3_upImage.setPosition(x, yPipe3);
			  pipe3_downImage.setPosition(x, yPipe3 + pipe_len + free_space);
			  break;
	}
	}

}

void Menu()
{
	bkImage.setTexture(bkTexture);
	bkImage.setPosition(0, 0);

	logoImage.setTexture(logoTexture);
	logoImage.setPosition(50, 10);

	pipe1_downImage.setTexture(pipe_downTexture);
	pipe1_downImage.setPosition(30, 410);

	pipeMenu_Image.setTexture(pipe_downTexture);
	pipeMenu_Image.setPosition(620, 310);

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
		window.draw(pipe1_downImage);
		window.draw(pipeMenu_Image);
		window.draw(menu);
		for (int i = 0; i<buttons; i++)
		{
			window.draw(buttons_text[i]);
		}
		window.display();
	}
}

void resetBird()
{
	speed_bird = 3.5; 
	yBird = 300;
	xBird = 30; 
	length = 50;
	width = 50;
	
}

void resetPipes()
{
	 xPipe1 = 800;
	 xPipe2 = 1200;
	 xPipe3 = 1600;
	 speed_pipe = 4.5;
	yPipe1 = getRand(-275, -75);
	yPipe2 = getRand(-275, -75);
	yPipe3 = getRand(-275, -75);
}
bool checkCollision(int x, int y)
{
	if(x <= xBird + width && x + pipe_width >= xBird + width)
	{
		if(yBird <= y + pipe_len)
		return true;
		if (yBird + length >= y + pipe_len + free_space)
		return true;
	}

	if (yBird + length > 550)
		return true;

	return false;
}

void getPoints(int x, int y)
{
	if (x > xBird - pipe_width - 4.5 && x + pipe_width <= xBird && checkCollision(x, y) == false )
	{
		points++;
	}
	std::cout << points;
}

void Play()
{
	
	points = 0;
	resetPipes();
	resetBird();
	bkImage.setPosition(0, 0);
	floorImage.setPosition(0, 550);
	birdImage.setTexture(birdTexture);
	birdImage.setPosition(xBird, yBird);

	sf::Text back("Press Esc for going back to MENU", font, 20);
	back.setStyle(sf::Text::Bold);
	back.setFillColor(sf::Color(255, 0, 0));
	back.setPosition(0, 573);

	sf::Text button("Replay", font, 20);
	button.setStyle(sf::Text::Bold);
	button.setFillColor(sf::Color(255, 0, 0));
	button.setPosition(740, 573);

	pipe1_upImage.setTexture(pipe_upTexture);
	pipe1_downImage.setTexture(pipe_downTexture);
	setPipeAtPos(xPipe1, 1);


	pipe2_downImage.setTexture(pipe_downTexture);
	pipe2_upImage.setTexture(pipe_upTexture);
	setPipeAtPos(xPipe2, 2);
	

	pipe3_downImage.setTexture(pipe_downTexture);
	pipe3_upImage.setTexture(pipe_upTexture);
	setPipeAtPos(xPipe3, 3);


	window.setFramerateLimit(60);
	while (state == 2)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				state = 0;
			else if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Escape)
				state = 1;
			else if (button.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))//Jocul o ia de la capat
			{
				replay();
			}
			else if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Space)
			{
				if (speed_bird != 0)
				{
					yBird= yBird - 70;
					//if (sounds) bird.go_up.play();
				}
			}
			/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && speed_bird == 0)
			{
				state = 2;
			}*/
		}

		if (checkCollision(xPipe1, yPipe1) || checkCollision(xPipe2, yPipe2) || checkCollision(xPipe3, yPipe3))
		{
			speed_bird = 0;
			speed_pipe = 0;
		}

		getPoints(xPipe1, yPipe1);
		getPoints(xPipe2, yPipe2);
		getPoints(xPipe3, yPipe3);

		if (xPipe1 <= -400)
		{
			xPipe1 = 800;
			yPipe1 = getRand(-275, -75);
		}

		if (xPipe2 <= -400)
		{
			xPipe2 = 800;
			yPipe2 = getRand(-275, -75);
		}

		if (xPipe3 <= -400)
		{
			xPipe3 = 800;
			yPipe3 = getRand(-275, -75);
		}

		xPipe1 = xPipe1 - speed_pipe;
		xPipe2 = xPipe2 - speed_pipe;
		xPipe3 = xPipe3 - speed_pipe;

		setPipeAtPos(xPipe1, 1);
		setPipeAtPos(xPipe2, 2);
		setPipeAtPos(xPipe3, 3);
		yBird = yBird + speed_bird;

		birdImage.setPosition(xBird, yBird);

		window.clear();
		window.draw(bkImage);
		
		window.draw(pipe1_upImage);
		window.draw(pipe1_downImage);
		window.draw(pipe2_upImage);
		window.draw(pipe2_downImage);
		window.draw(pipe3_upImage);
		window.draw(pipe3_downImage);

		window.draw(floorImage);
		window.draw(birdImage);
		window.draw(back);
		window.draw(button);

		window.display();
	}
}

void replay()
{
	resetPipes();
	Play();
}

void startGame()
{
	loadFiles();

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