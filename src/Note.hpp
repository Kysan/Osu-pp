

#ifndef note_h
#define note_h

#include <SFML/Graphics.hpp>


class Note 
{
private:
    sf::Time emergenceTiming; // lulz
    sf::Time visibilityDuration;
    sf::Sprite hitcircle;
    int circleSize;
public:
    Note(int x, int y, int circleSize, float emergenceTiming, float visibilityDuration, sf::Texture *hitcircleTexutre);
    void draw(sf::RenderTarget *target, sf::Clock timer);
};

// * timing en seconde
// * emergenceTiming -> temps auquel le cercle doit apparaître
// * exemple: à 3.2 secondes
// * visibilityDuration -> temps que le cercle mets à se fermer
// * ex: 800ms 
Note::Note(int x, int y, int circleSize, float emergenceTiming, float visibilityDuration, sf::Texture *hitcircleTexutre){
        this->emergenceTiming = sf::Time(sf::seconds(emergenceTiming));
        this->visibilityDuration = sf::Time(sf::seconds(visibilityDuration));
        this->circleSize = circleSize;

        this->hitcircle = sf::Sprite(*hitcircleTexutre);
        this->hitcircle.setPosition(x, y);
        this->hitcircle.setScale(circleSize, circleSize);
}




void Note::draw(sf::RenderTarget *target, sf::Clock timer) {
    sf::Time elapsedTime = timer.getElapsedTime();
    sf::Time disapearanceTiming(this->emergenceTiming + this->visibilityDuration);
    if(this->emergenceTiming <= elapsedTime && elapsedTime < disapearanceTiming) {
        target->draw(this->hitcircle);
    }
}


#endif