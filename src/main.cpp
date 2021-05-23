#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <string>
#include <vector>
#include "Skin.hpp"
#include "Utils.hpp"
#include "Note.hpp"
#include "MapParser.hpp"



int main(int argc, char const *argv[])
{   
    // * pour tout ce qui est généré aléatoirement
    std::srand(std::time(nullptr));

    std::string cwd = currentWorkingDirectory(argv[0]);
    printf("%s", argv[0]);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Osu!++");
    window.setMouseCursorVisible(false);
    // * chargement du skin
    Skin::loadSkin(cwd + "/skins/Cinia Cursor Green");
    


    // * création du curseur
    sf::Sprite cursor(Skin::cursor);
    sf::Vector2i mousePos(0, 0);
    cursor.setOrigin(cursor.getTextureRect().width/2, cursor.getTextureRect().height/2);
    

    // * pour afficher le framerate en bas à droite
    sf::Font font;
    font.loadFromFile(cwd + "/consolas.ttf");
    sf::Text framerate("0", font);
    sf::Clock delta;
    framerate.setCharacterSize(24);
    framerate.setFillColor(sf::Color(255, 0, 0));
    framerate.setPosition(window.getSize().x, window.getSize().y);
    
    
    // * barre de progression de la map
    sf::RectangleShape progressBar(sf::Vector2f(10, 40));
    progressBar.setFillColor(sf::Color(255, 0, 0));
    sf::Clock timer;
    sf::Time mapLength(sf::seconds(3));
    

    MapParser parser(cwd+"/maps/1337");
    
    std::vector<Note> notes = parser.generateNotes();
    
    
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
        }
        // #######################################################################
        // * update
        // #######################################################################

        
        // * pour reset la barre de progression toutes les 5 secondes
        if(timer.getElapsedTime() >= mapLength) {
            timer.restart();
        }
        float x = (timer.getElapsedTime() / mapLength) * window.getSize().x;
        progressBar.setPosition(x, 0);

        // * pour avoir l'input lag en bas
        std::string info = std::to_string(delta.getElapsedTime().asSeconds()*1000.0);
        info.substr(0, 3);
        
        framerate.setString(info + " ms");
        framerate
            .setOrigin(
                    framerate.getLocalBounds().width+10,
                    framerate.getLocalBounds().height+20
            );
        delta.restart();

        
        


        // #######################################################################
        // * draw
        // #######################################################################
        window.clear(sf::Color(40, 40, 40));
        
        

        for(int i = 0; i < notes.size(); ++ i) {
            notes[i].draw(&window, timer);
        }

        window.draw(framerate);
        window.draw(progressBar);    
        window.draw(cursor);

        window.display();
    }

    return 0;
}