#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Skin.hpp"
#include "Utils.hpp"
#include "Note.hpp"
#include "Map.hpp"
#include "Keyboard.hpp"



int main(int argc, char const *argv[])
{   
    // * pour tout ce qui est généré aléatoirement
    std::srand(std::time(nullptr));

    std::string cwd = currentWorkingDirectory(argv[0]);
    printf("Game running in %s\n", argv[0]);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Osu!++", sf::Style::Titlebar);
    window.setMouseCursorVisible(false);
    // * chargement du skin
    Skin::loadSkin(cwd + "/skins/Cinia Cursor Green");
    
    // sf::SoundBuffer sb;
    // sb.loadFromFile(std::string("bin/skins/Cinia Cursor Green")+"/normal-hitnormal.ogg");
    sf::Sound s(Skin::getHitsoundBuffer());
    s.play();
    // * création du curseur
    sf::Sprite cursor(Skin::cursor);
    sf::Vector2i mousePos(0, 0);
    cursor.setOrigin(cursor.getTextureRect().width/2, cursor.getTextureRect().height/2);
    

    // * pour afficher le framerate en bas à droite
    sf::Font font;
    font.loadFromFile(cwd + "/consolas.ttf");
    sf::Clock delta;
    sf::Text framerate("0", font);
    framerate.setCharacterSize(24);
    framerate.setFillColor(sf::Color(255, 0, 0));
    framerate.setPosition(window.getSize().x-60, window.getSize().y-30);

    sf::Text timerText("0", font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color(255, 0, 0));
    timerText.setPosition(0, window.getSize().y-30);
    
    
    // * barre de progression de la map
    sf::RectangleShape progressBar(sf::Vector2f(10, 40));
    progressBar.setFillColor(sf::Color(255, 0, 0));
    sf::Clock timer;
    sf::Time mapLength(sf::seconds(3));
    

    
    
    // * pour charger uen map
    Map::Load(cwd+"/map/1337");
    
    
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                // printf("x: %d\ny: %d", event.mouseMove.x, event.mouseMove.y);
                mousePos.x = event.mouseMove.x;
                mousePos.y = event.mouseMove.y;
                cursor.setPosition((sf::Vector2f) mousePos);
            }

            if(event.type == sf::Event::KeyPressed) {
                // * pour éviter que la même touche soit trigger plusieurs fois
                if(Keyboard::isKeyAlreadyPressed(event.key.code)) {
                    continue;
                }
                Keyboard::pressKey(event.key.code);
            
                // std::cout << "<"<<event.key.code << ">" << std::endl;
                if(event.key.code == sf::Keyboard::Key::E || event.key.code == sf::Keyboard::Key::R) {
                    sf::Vector2f cursorPos = cursor.getPosition();
                    bool circleTouched;
                    for(int i = 0; i < Map::Notes.size(); ++i) {
                        circleTouched = Map::Notes[i].tryHit(timer.getElapsedTime(), cursorPos.x, cursorPos.y);
                        if(circleTouched) {
                            break;
                        }
                    }
                    std::string message = circleTouched ? "hit!" : "miss!" ;
                }

            } else if(event.type == sf::Event::KeyReleased) {
                Keyboard::releaseKey(event.key.code);
            }
        }
        // #######################################################################
        // * update
        // #######################################################################

        
        // * pour reset la barre de progression toutes les 5 secondes
        if(timer.getElapsedTime() >= mapLength) {
            timer.restart();
            Map::generateRandomMap(sf::seconds(300), 200, 3, 8, 8);
            mapLength = sf::seconds(300);
        }
        float x = (timer.getElapsedTime() / mapLength) * window.getSize().x;
        progressBar.setPosition(x, 0);

        // * pour avoir l'input lag en bas
        std::string info = std::to_string(delta.getElapsedTime().asMicroseconds()/1000.0);
        info = info.substr(0, 4);
        
        framerate.setString(info + " ms");

        delta.restart();

        timerText.setString(std::to_string(timer.getElapsedTime().asSeconds()));
        
        


        // #######################################################################
        // * draw
        // #######################################################################
        window.clear(sf::Color(40, 40, 40));
        
        

        for(int i = 0; i < Map::Notes.size(); ++ i) {
            Map::Notes[i].draw(&window, timer.getElapsedTime());
        }

        window.draw(timerText);
        window.draw(framerate);
        window.draw(progressBar);    
        window.draw(cursor);

        window.display();
    }

    return 0;
}