#ifndef skin_h
#define skin_h
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Skin
{
private:
    
public:
    static void loadSkin(std::string skinFolderPath);

    static std::string folderPath;


    static sf::Texture cursor;
    static sf::Texture hitcircle;
    static sf::Texture approachcircle;
    static sf::Texture hit0;
    


    // static sf::SoundBuffer hitSoundBuffer;
    static sf::SoundBuffer& getHitsoundBuffer();

};

void Skin::loadSkin(std::string skinFolderPath)
{   
    // !!! gérer les erreurs de chargement !!!
    folderPath = skinFolderPath;
    cursor.loadFromFile(skinFolderPath + "/cursor.png");

    hitcircle.loadFromFile(skinFolderPath + "/hitcircleoverlay-0.png");
    approachcircle.loadFromFile(skinFolderPath + "/approachcircle.png");

    hit0.loadFromFile(skinFolderPath + "/hit0.png");
    
    
    // visiblement il serait local à cette fonction 
    // peut être faire un malloc et le gérer avec un pointeur?
    
    // hitSoundBuffer.loadFromFile(folderPath+"/normal-hitnormal.ogg");

}

sf::SoundBuffer& Skin::getHitsoundBuffer() {
    static sf::SoundBuffer buffer;
    buffer.loadFromFile(folderPath+"/normal-hitnormal.ogg");
    
    return buffer;
}


// * très important pour les rendre global
sf::Texture Skin::cursor;
sf::Texture Skin::hitcircle;
sf::Texture Skin::approachcircle;
sf::Texture Skin::hit0;


// sf::SoundBuffer Skin::hitSoundBuffer;

std::string Skin::folderPath;


#endif