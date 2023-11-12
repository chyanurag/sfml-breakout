#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen, settings);
	sf::RectangleShape paddle(sf::Vector2f(300.f, 50.f));
	sf::CircleShape ball(20.f);
	sf::Vector2f ballVelocity(2.f,3.f);
	enum GameState gameState = Home;
	bool ended = false;
	paddle.setPosition(sf::Vector2f(810.f, 1030.f));
	while(window.isOpen()){
		sf::Event ev;
		while(window.pollEvent(ev)){
			switch(ev.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
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
			}
		}
		window.clear();
		window.draw(paddle);
		window.draw(ball);
		if(checkCollision(ball.getPosition(), paddle.getPosition())){
			ballVelocity.y > 0 ? ballVelocity.y = -ballVelocity.y : NULL;
		}
		if(ball.getPosition().x < 0 || ball.getPosition().x > 1900){
			ballVelocity.x = -ballVelocity.x;
		}
		if(ball.getPosition().y < 0){
			ballVelocity.y = -ballVelocity.y;
		}
		ball.setPosition(ball.getPosition() + ballVelocity);
		window.display();
	}
	return 0;
}
