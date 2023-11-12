#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include <iostream>

bool checkCollision(sf::Vector2f ballPos, sf::Vector2f padPos){
	float ballX = ballPos.x;
	float bally = ballPos.y;
	float padX = padPos.x;
	float pady = padPos.y;
	sf::Vector2f ballContact = sf::Vector2f(ballPos.x + 10.f, ballPos.y + 10.f);
	if(ballContact.x >= padX && ballContact.x <= (padX + 300.f) && ballContact.y < 1080.f && ballContact.y >= 1030.f){
		return true;
	}
	return false;
}

enum GameState{
	Home,
	Play,
	Ended
};

int main(){
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	short int score = 0;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen, settings);
	sf::RectangleShape paddle(sf::Vector2f(300.f, 50.f));
	sf::CircleShape ball(20.f);
	sf::Vector2f ballVelocity(2.f,3.f);
	enum GameState gameState = Home;
	bool ended = false;
	paddle.setPosition(sf::Vector2f(810.f, 1030.f));
	sf::Font font;
	if(!font.loadFromFile("GTAV.ttf")){
		std::cerr << "font not loaded! exiting.." << std::endl;
		std::exit(1);
	}
	sf::Text playText, scoreText;
	playText.setFont(font);
	playText.setCharacterSize(50);
	playText.setString("Press SPACE to play");
	playText.setFillColor(sf::Color::White);
	playText.setPosition(800.f, 500.f);
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::Black + sf::Color::White);
	scoreText.setPosition(1700.f, 50.f);
	std::string scoreFont;
	sf::Text totalScore;
	totalScore.setFont(font);
	totalScore.setCharacterSize(50.f);
	totalScore.setFillColor(sf::Color::White);
	totalScore.setPosition(700.f, 400.f);
	sf::Text restartText;
	restartText.setFont(font);
	restartText.setString("Press SPACE to restart");
	restartText.setCharacterSize(50.f);
	restartText.setFillColor(sf::Color::White);
	restartText.setPosition(700.f, 500.f);
	while(window.isOpen()){
		sf::Event ev;
		while(window.pollEvent(ev)){
			switch(ev.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch(gameState){
						case Home:
							switch(ev.key.scancode){
								case sf::Keyboard::Scan::Space:
									gameState = Play;
									break;
							}
							break;
						case Play:
							switch(ev.key.scancode){
								case sf::Keyboard::Scan::Left:
									// left key pressed
									if(paddle.getPosition().x >= 20){
										float paddlex = paddle.getPosition().x;
										float paddley = paddle.getPosition().y;
										paddle.setPosition(paddlex-20, paddley);
									}
									break;
								case sf::Keyboard::Scan::Right:
									// right key pressed
									if(paddle.getPosition().x <= 1900){
										float paddlex = paddle.getPosition().x;
										float paddley = paddle.getPosition().y;
										paddle.setPosition(paddlex+20, paddley);
									}
									break;
							}
							break;
						case Ended:
							switch(ev.key.scancode){
								case sf::Keyboard::Scan::Space:
									gameState = Home;
									score = 0;
									window.clear();
									continue;
							}
							break;
					}
					break;
			}
		}
		window.clear();
		switch(gameState){
			case Home:
				window.draw(playText);
				break;
			case Play:
				window.clear();
				window.draw(paddle);
				window.draw(ball);
				scoreFont = "Score : ";
				scoreFont.append(std::to_string(score));
				scoreText.setString(scoreFont);
				window.draw(scoreText);
				if(checkCollision(ball.getPosition(), paddle.getPosition())){
					ballVelocity.y > 0 ? ballVelocity.y = -ballVelocity.y : NULL;
					score++;
					ballVelocity.x += .5f;
					ballVelocity.y += .5f;
				}
				if(ball.getPosition().x < 0 || ball.getPosition().x > 1900){
					ballVelocity.x = -ballVelocity.x;
				}
				if(ball.getPosition().y < 0){
					ballVelocity.y = -ballVelocity.y;
				}
				if(ball.getPosition().y > 1080){
					gameState = Ended;
					std::string total = "Your total score was : ";
					total.append(std::to_string(score));
					totalScore.setString(total);
				}
				ball.setPosition(ball.getPosition() + ballVelocity);
				break;
			case Ended:
				window.draw(restartText);
				window.draw(totalScore);
				break;
		}
		window.display();
	}
	return 0;
}
