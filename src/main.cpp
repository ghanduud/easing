#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

float easeInOutQuart(float timeElapsed, float duration) {
    float t = timeElapsed / duration; 

    if (t < 0.5) {
        t *= t;
        return 8 * t * t;
    }
    else {
        t = (--t) * t;
        return 1 - 8 * t * t;
    }
}

//another implementation
//float easeIn(float t, float b, float c, float d) {
//    return c * (t /= d) * t * t * t + b;
//}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Snake", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 80.f);

    sf::CircleShape circle(25.0f);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOrigin(25.0f, 25.0f);
    circle.setPosition(100, 100);
    sf::Vector2f startPos = circle.getPosition();
    sf::Vector2f targetPos = startPos;



    sf::Clock gameClock;

    bool isMoving = false;
    float moveDuration = 3.0f;




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                isMoving = true;

                startPos = circle.getPosition();
                targetPos = sf::Vector2f(mouseX,mouseY);
                gameClock.restart();
                std::cout << "Left mouse button released at position: " << mouseX << ", " << mouseY << std::endl;
            }
        }

        sf::Time elapsedTime = clock.restart();

        while (elapsedTime > timePerFrame) {

            if (isMoving) {
                float time = gameClock.getElapsedTime().asSeconds();
                float  movingKoffeitiont = easeInOutQuart(time,moveDuration);


                sf::Vector2f newPosition = startPos + movingKoffeitiont * (targetPos - startPos);
                circle.setPosition(newPosition);

                //another implementation
                /*float  movingKoffeitiontX = easeIn(time, startPos.x, targetPos.x - startPos.x, moveDuration);
                float  movingKoffeitiontY = easeIn(time, startPos.y, targetPos.y - startPos.y, moveDuration);

                circle.setPosition(movingKoffeitiontX, movingKoffeitiontY);*/

            }

            if (gameClock.getElapsedTime().asSeconds() >= moveDuration) {
                isMoving = false;
            }

            elapsedTime -= timePerFrame;
        }

        window.clear();

        window.draw(circle);

        window.display();
    }

    return 0;
}
