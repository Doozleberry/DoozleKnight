// Build Process
//g++ main.cpp -o main -lsfml-system -lsfml-window
#include <SFML/Graphics.hpp>
//#include "AssetManager.h"


int main()
{
    /* Create the Window */
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "DoozleBerryzz");
    //AssetManager manager;

    /* Set Framerate and Clock*/
    sf::Time deltaTime;
    sf::Clock clock;

    window.setFramerateLimit(60);
    /* Basic Player Rectangle Setup */
    //sf::Sprite playerSprite = sf::Sprite(AssetManager::GetTexture("platformerSprites/knightPlayer/knightIdleRight/knightIdleRight1.png"));
    sf::Texture texture;
    texture.loadFromFile("platformerSprites/knightPlayer/knightIdleRight/knightIdleRight1.png");

    sf::Sprite playerSprite = sf::Sprite(texture);


    /* Rectangular Ground Setup */
    sf::RectangleShape groundShape(sf::Vector2f(800, 60));
    groundShape.setFillColor(sf::Color::Black);
    groundShape.setPosition(sf::Vector2f(0, 500));

    //sf::Sprite playerSprite("platformerSprites/knightPlayer/knightIdleRight/knightIdleRight1.png");
    /* Moving Variable */
    float dy;
    //bool jumpPermission = false;
    bool onGround = false;
    bool jumpMax = false;
    bool movingRight = false;
    bool movingLeft = false;
    bool movingUp = false;
    /* Main Loop */
    while (window.isOpen())
    {
      /* Stages of main loop

        1. Handle Inputs - handle events from input devices and the window
        2. Update Frame - update objects in the frame
        3. Render Frame - render objects from the scene to the window
        */

        sf::Time deltaTime = clock.restart();
        /* Input Handling */

        sf::Event event;
        while (window.pollEvent(event))
        {
          switch (event.type)
          {
            case sf::Event::Closed:
              window.close();
              break;
            case sf::Event::KeyPressed:
              if (event.key.code == sf::Keyboard::Space)
                window.setTitle("Space Pressed");
              if (event.key.code == sf::Keyboard::Right)
                movingRight = true;
              if (event.key.code == sf::Keyboard::Left)
                movingLeft = true;
              if (event.key.code == sf::Keyboard::Up) {
                if(onGround) {
                  movingUp = true;
                }
              }

              break;
            case sf::Event::KeyReleased:
              if (event.key.code == sf::Keyboard::Space)
                window.setTitle("Space Released");
              if (event.key.code == sf::Keyboard::Right)
                movingRight = false;
              if (event.key.code == sf::Keyboard::Left)
                movingLeft = false;
              if (event.key.code == sf::Keyboard::Up)
                  movingUp = false;
              if (event.key.code == sf::Keyboard::Escape)
                window.close();
              break;
            default:
              break;
            }
          }
          /* Updating Frame */

          if (movingRight) {
            playerSprite.move(sf::Vector2f(3, 0));
          }

          if (movingLeft) {
            playerSprite.move(sf::Vector2f(-3, 0));
          }

          if (playerSprite.getGlobalBounds().intersects(groundShape.getGlobalBounds())) {
            playerSprite.move(sf::Vector2f(0, 0));
            onGround = true;
          }

          if (movingUp) {
            dy -= -0.2;
            onGround = false;
            playerSprite.move(0, dy);
            if (dy = -14) {
              dy = -14;
              jumpMax = false;
              movingUp = false;
            }
          }
          if (!onGround && !jumpMax) {
            dy += 0.7;
            if (dy > 7)
              dy = 7;
            playerSprite.move(sf::Vector2f(0, dy));
          }

          /* Rendering Frame */
          window.clear(sf::Color::White);
          // window.draw(circleShape);
          // window.draw(rect);
          window.draw(groundShape);
          window.draw(playerSprite);



          window.display();
    }

    return 0;
}
