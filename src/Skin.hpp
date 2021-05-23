#ifndef skin_h
#define skin_h
#include <string>
#include <SFML/Graphics.hpp>


class Skin
{
private:
    
public:
    Skin();
    static void loadSkin(std::string skinFolderPath);

    static sf::Texture cursor;
    static sf::Texture hitcircle;

};

Skin::Skin() {

}

void Skin::loadSkin(std::string skinFolderPath)
{ 
    // this->cursor = sf::Texture();
    cursor.loadFromFile(skinFolderPath + "/cursor.png");

    
    hitcircle.loadFromFile(skinFolderPath + "/hitcircleoverlay-0.png");
    

}


// * très important pour les rendre global
sf::Texture Skin::cursor;
sf::Texture Skin::hitcircle;


#endif