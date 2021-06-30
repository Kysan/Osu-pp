#ifndef mapparser_h
#define mapparser_h



#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Note.hpp"
#include "Skin.hpp"




class Map
{
private:
    
public:
    static std::vector<Note> Notes;
    static bool Load(std::string mapPath); // * pour pouvoir lire la map sans la jouer
    static std::vector<Note> generateRandomMap(sf::Time duration, float BPM, float CS, float AR, float OD);
};

bool Map::Load(std::string mapPath)
{
    // rien pour le moment
    
    
}

std::vector<Note> Map::generateRandomMap(sf::Time duration, float BPM, float CS, float AR, float OD) {
    float notePerSecond = BPM/60;
    std::cout << "note par seconde : " << notePerSecond << std::endl;
    int nbNote = duration.asSeconds()*notePerSecond;
    std::cout << "duree: " << duration.asSeconds() << "s" <<  std::endl;
    std::cout << "nbNote: " << nbNote << std::endl;
    Notes.clear();
    for(int n = 0; n < nbNote; ++n) {

       int x = 400 + std::rand() % 1024 - 400;
       int y = 400 + std::rand() % 768 - 400;
        float timing = 1.5 +((float) n) / notePerSecond;
        std::cout << "timing: " << timing << "\tx: " << x << "\ty: " << y << std::endl;
        Note note(timing, x, y, 3, 8, 7);
        Notes.push_back(note);
    }

    // * on est pas obligé de return mais on s'en bat les couilles parce que c'est un pointeur
    return Notes;
}


std::vector<Note> Map::Notes;

#endif
