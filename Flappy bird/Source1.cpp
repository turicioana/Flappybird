#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
#include <stdio.h>
using namespace std;

int state=1;//state=0 cand jocul este inchis, state=1 cand jocul se afla in meniu, state=2 atunci cand ruleaza jocul, state=3 atunci cand dorim sa afisam leaderboard-ul;
sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");
sf::Font font;
sf::Text text;
sf::Texture upTexture;
sf::Sprite upImage;
sf::Texture speedTexture;
sf::Texture no_speedTexture;
sf::Texture logoTexture;
sf::Texture bkTexture;
sf::Texture floorTexture;
sf::Texture overTexture;
sf::Sprite speedImage;
sf::Sprite no_speedImage;
sf::Sprite overImage;
sf::Sprite logoImage;
sf::Sprite bkImage;
sf::Sprite floorImage;

sf::Clock cronometru;

int points = 0;
int highScore[5];
void readScore()
{
		std::ifstream fin("Images/score.txt");
		int i;
		for (i = 0; i < 5; i++)
			fin >> highScore[i];
		fin.close();
}
void updateScore()
{
	int i, j, auxA, auxB;
	for (i = 0; i < 5; i++)
	{
		if (points >= highScore[i])
		{
			auxA = highScore[i];
			highScore[i] = points;
			for (j = i + 1; j < 5; j++)
			{
				auxB = highScore[j];
				highScore[j] = auxA;
				auxA = auxB;
			}
			return;
		}
	}
}
void updateFile()
{
	int i;
	std:: ifstream fin("Images/score.txt");
	fin.close();

	std::ofstream ofs("Images/score.txt",std::ios::out | ios::trunc);
	for (i = 0; i < 5; i++)
		ofs << highScore[i] << endl;
}

sf::Music get_pointMusic;
sf::Music go_upMusic;
sf::Music dieMusic;

sf::Texture birdTexture;
sf::Sprite birdImage;

float yBird = 300;
float xBird = 30;

float length = 50;
float width = 50;

int timeScurs = 0;
char scorText[32];
char timeText[32];
char leaderScores[32];


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
	readScore();
	if (!upTexture.loadFromFile("Images/up.png"))
		throw std::runtime_error("Could not load up.png");
	upImage.setTexture(upTexture);

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

	if (!speedTexture.loadFromFile("Images/speed.png"))
		throw std::runtime_error("Could not load speed.png");
	speedImage.setTexture(speedTexture);

	if (!no_speedTexture.loadFromFile("Images/no_speed.png"))
		throw std::runtime_error("Could not load no_speed.png");
	no_speedImage.setTexture(no_speedTexture);

	if (!birdTexture.loadFromFile("Images/bird.png"))
		throw std::runtime_error("Could not load bird.png");

	if (!overTexture.loadFromFile("Images/gameover.png"))
		throw std::runtime_error("Could not load gameover.png");

	if (!get_pointMusic.openFromFile("sounds/get_point.ogg"))
		std::cout << "Can't find" << std::endl;

	if (!go_upMusic.openFromFile("sounds/go_up.ogg"))
		std::cout << "Can't find" << std::endl;

	if (!dieMusic.openFromFile("sounds/die.ogg"))
		std::cout << "Can't find" << std::endl;
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
		//sf::Time elapsed = cronometru.restart();
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
				//updateGame(elapsed);
				//std::cout << elapsed.asSeconds() << std::endl;
				//clock.restart();
			}
			else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
				(event.type == sf::Event::MouseButtonReleased) &&
				(event.key.code == sf::Mouse::Left))
			{
				state = 3;
			}
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
void Leaderboard()
{
	bkImage.setTexture(bkTexture);
	bkImage.setPosition(0, 0);
	overImage.setTexture(overTexture);
	overImage.setPosition(100, 180);
	floorImage.setPosition(0, 550);

	//retrun to menu
	sf::Text back("Back To MENU", font, 30);
	back.setStyle(sf::Text::Bold);
	back.setFillColor(sf::Color(255, 0, 0));
	back.setPosition(310, 430);

	//Leaderboard
	sf::Text leaderboard("Leaderboard", font, 100);
	leaderboard.setStyle(sf::Text::Bold);
	leaderboard.setFillColor(sf::Color(255, 0, 0));
	leaderboard.setPosition(135, 40);

	sf::Text Score;
	Score.setFont(font);
	Score.setCharacterSize(36);
	Score.setStyle(sf::Text::Bold);
	Score.setFillColor(sf::Color(255, 255, 255));
	Score.setPosition(300, 200);

	sf::Text Index;
	Index.setFont(font);
	Index.setCharacterSize(36);
	Index.setStyle(sf::Text::Bold);
	Index.setFillColor(sf::Color(255, 255, 255));
	Index.setPosition(300, 200);

	while (state == 3)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
				event.key.code == sf::Keyboard::Escape)
				state = 0;
			else if (back.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				state = 1;
		}
		window.clear();
		window.draw(bkImage);
		window.draw(leaderboard);
		window.draw(overImage);
		window.draw(floorImage);
		window.draw(back);

		int yPos = 220;
		for (int i = 0; i < 5; i++)
		{
			char index[3] = "";
			sprintf_s(index, "%d", i + 1);
			sprintf_s(leaderScores, "%d", highScore[i]);

			switch (i)
			{
			case 0:
				Index.setFillColor(sf::Color(255, 0, 0));
				Score.setFillColor(sf::Color(255, 0, 0));
				break;
			default:
				Index.setFillColor(sf::Color(255, 255, 255));
				Score.setFillColor(sf::Color(255, 255, 255));
				break;
			}
			Index.setPosition(300, yPos);
			Index.setString(index);

			Score.setPosition(450, yPos);
			Score.setString(leaderScores);
			window.draw(Score);
			window.draw(Index);
			if (i == 4)
			{
				yPos = 220;
			}
			else
			{
				yPos += 40;
			}

		}
		window.display();
	}
}

void resetBird()
{
	timeScurs = 0;
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
		if (yBird <= y + pipe_len)
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
		get_pointMusic.play();
	}
	//std::cout << points;
}

void Play()
{
	int sprintInt;
	points = 0;
	resetPipes();
	resetBird();
	bkImage.setPosition(0, 0);
	overImage.setTexture(overTexture);
	floorImage.setPosition(0, 550);
	speedImage.setPosition(170, 565);
	upImage.setPosition(745, 565);
	no_speedImage.setPosition(470, 565);
	birdImage.setTexture(birdTexture);
	birdImage.setPosition(xBird, yBird);
	overImage.setPosition(100, 200); 

	sf::Text normal("Normal speed", font, 20);
	normal.setStyle(sf::Text::Bold);
	normal.setFillColor(sf::Color(0, 0, 0));
	normal.setPosition(620, 565);

	sf::Text speed("Increase the speed", font, 20);
	speed.setStyle(sf::Text::Bold);
	speed.setFillColor(sf::Color(0, 0, 0));
	speed.setPosition(1, 565);

	sf::Text no_speed("Decrease the speed", font, 20);
	no_speed.setStyle(sf::Text::Bold);
	no_speed.setFillColor(sf::Color(0, 0, 0));
	no_speed.setPosition(300, 565);

	sf::Text gameTime("Time", font, 60);
	gameTime.setStyle(sf::Text::Bold);
	gameTime.setFillColor(sf::Color(255, 255, 255));
	gameTime.setPosition(150, 340);

	sf::Text Scores("Score", font, 60);
	Scores.setStyle(sf::Text::Bold);
	Scores.setFillColor(sf::Color(255, 255, 255));
	Scores.setPosition(150, 230);

	sf::Text over("Game Over", font, 100);
	over.setStyle(sf::Text::Bold);
	over.setFillColor(sf::Color(255, 0, 0));
	over.setPosition(180, 50);

	sf::Text back("Back To MENU", font, 30);
	back.setStyle(sf::Text::Bold);
	back.setFillColor(sf::Color(255, 0, 0));
	back.setPosition(150, 430);

	sf::Text button("Replay", font, 30);
	button.setStyle(sf::Text::Bold);
	button.setFillColor(sf::Color(255, 0, 0));
	button.setPosition(560, 430);

	sf::Text timeM(timeText, font, 60);
	timeM.setStyle(sf::Text::Bold);
	timeM.setFillColor(sf::Color(255, 255, 255));
	timeM.setPosition(400, 340);
	
	sf::Text scor(scorText, font, 60);
	scor.setStyle(sf::Text::Bold);
	scor.setFillColor(sf::Color(255, 255, 255));
	scor.setPosition(400, 230);

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
		sprintInt = sprintf_s(scorText, "%d", points);

		scor.setString(scorText);
		sf::Event event;
		sf::Vector2f mouse(sf::Mouse::getPosition(window));


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				state = 0;
			}

			else if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Space)
			{
				if (speed_bird != 0)
				{
					yBird= yBird - 60;
					go_upMusic.play();
				}
			}
			else if (button.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))//Jocul o ia de la capat
			{
				replay();
			}
		}
		if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Right)
			speed_pipe = 5.5;
		else
		if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Left)
			speed_pipe = 2.5;
		else
		if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up)
			speed_pipe = 4, 5;

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
		window.draw(speed);
		window.draw(no_speed);
		window.draw(normal);
		window.draw(speedImage);
		window.draw(no_speedImage);
		window.draw(upImage);
		window.draw(birdImage);
		if (checkCollision(xPipe1, yPipe1) || checkCollision(xPipe2, yPipe2) || checkCollision(xPipe3, yPipe3))
		{
			dieMusic.play();
			state = 4;
			updateScore();
			updateFile();
			timeM.setString(timeText);
			speed_bird = 0;
			speed_pipe = 0;
			window.draw(overImage);
			window.draw(over);
			window.draw(back);
			window.draw(button);
			window.draw(scor);
			window.draw(Scores);
			window.draw(gameTime);
			window.draw(timeM);
			window.display();
			while (state == 4)
			{
				sf::Vector2f mouse(sf::Mouse::getPosition(window));
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						state = 0;
					else if (back.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						timeScurs = 0;
						state = 1;
					}
					else if (button.getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))//Jocul o ia de la capat
					{
						state = 2;
						replay();
					}
				}	
			}
		}

		window.display();
	}
	updateScore();
	updateFile();
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
		case 3:
			Leaderboard();
			break;
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