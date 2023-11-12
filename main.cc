#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main(){
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
	sf::RectangleShape paddle(sf::Vector2f(300.f, 50.f));
	sf::CircleShape ball(20.f);
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
		window.display();
	}
	return 0;
}
