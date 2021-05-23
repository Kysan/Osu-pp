#ifndef mapparser_h
#define mapparser_h
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Note.hpp"


#include "Skin.hpp"

class MapParser
{
private:
    std::vector<Note> notes;
public:
    MapParser(std::string mapPath);
    std::vector<Note> generateNotes();
    
};

MapParser::MapParser(std::string mapPath)
{
    // rien pour le moment
    
    
}

std::vector<Note> MapParser::generateNotes() {
    
    for(float n = 0; n <= 20; ++n) {
        int x = std::rand() % 1024;
        int y = std::rand() % 768;
        Note note(x, y, 1, n * 0.5, 0.800, &Skin::hitcircle);
        this->notes.push_back(note);
    }

    
    return this->notes;
}

#endif
