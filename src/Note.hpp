

#ifndef note_h
#define note_h

#include <SFML/Graphics.hpp>
#include <cmath>


class Note 
{
private:
    // * pour les timings d'affichage
    sf::Time timing;
    sf::Time appearanceTiming;
    sf::Time maxedOpacityTiming;
    sf::Time remainingTime;
    sf::Time remainingTimeAfterOpacityMaxed;
    sf::Sprite hitcircle;
    sf::Sprite approachCircle;
    
    float acFactor; // scale l'approchCircle

    // pour la gestion des inputs
    int ray;
    sf::Time hitWindow50;
    sf::Time hitWindow100;
    sf::Time hitWindow300;
    bool alreadyHit = false;
public:
    Note(float timing, int x, int y, float CS, float AR, float OD);
    void draw(sf::RenderTarget *target, sf::Time elapsedTime);
    bool tryHit(sf::Time elapsedTime, int x, int y);
};

Note::Note(float timing, int x, int y, float CS, float AR, float OD) {
        // timing d'apparition
        this->timing = sf::seconds(timing);

        // https://osu.ppy.sh/wiki/fr/Beatmapping/Approach_rate
        //
        int fadingInAdv;
        if(AR < 5) {
            fadingInAdv = 1200 + 600 * ((5 - AR) / 5);
        } else if (AR == 5) {
            fadingInAdv = 1200;
        } else {
            fadingInAdv = 1200 - 750 * ((AR - 5) / 5);
        }

        this->remainingTime = sf::milliseconds(fadingInAdv);
        this->appearanceTiming = this->timing - remainingTime;

        int fullOpacityAdv;
        if(AR < 5) {
            fullOpacityAdv = 800 + 400 * ((5 - AR) / 5);
        } else if (AR == 5) {
            fullOpacityAdv = 800;
        } else {
            fullOpacityAdv = 800 - 500 * ((AR - 5) / 5);
        }
        this->remainingTimeAfterOpacityMaxed = sf::milliseconds(fullOpacityAdv);
        this->maxedOpacityTiming = this->timing - remainingTimeAfterOpacityMaxed;


        
        // à revoir
        // https://osu.ppy.sh/wiki/cs/Beatmapping/Circle_size
        // 54 pixels pour de l'ar 0 au max
        
        this->ray = 54.4 - 4.48 * CS;
        float pixelSize = this->ray * 2.0; // parce qu'on passe du rayon à la largeur (donc x2)
        pixelSize *= 1.6; // par ce que je ne sais pas à quel résolution c'est sensé correspondre
        // on doit resize le sprite pour qu'il fasse pixelSize 


        this->hitcircle = sf::Sprite(Skin::hitcircle);
        this->hitcircle.setPosition(x, y);

        float hcFactor =  pixelSize / this->hitcircle.getLocalBounds().width ;
        this->hitcircle.setScale(hcFactor, hcFactor); // CS calculé au dessus


        this->hitcircle.setOrigin(this->hitcircle.getLocalBounds().width/2, this->hitcircle.getLocalBounds().height/2);

        this->approachCircle = sf::Sprite(Skin::approachcircle);
        acFactor =  pixelSize / this->approachCircle.getLocalBounds().width;
        this->approachCircle.setScale(acFactor*3, acFactor*3);
        this->approachCircle.setOrigin(this->approachCircle.getLocalBounds().width/2, this->approachCircle.getLocalBounds().height/2);
        this->approachCircle.setPosition(x, y);
        
        // pour l'effet de fade in
        this->hitcircle.setColor(sf::Color(255, 255, 255, 0));
        this->approachCircle.setColor(sf::Color(255, 255, 255, 0));

        // sf::Time t = sf::seconds(3) / sf::seconds(1);
        // * https://osu.ppy.sh/wiki/fr/Beatmapping/Overall_difficulty
        this->hitWindow50 = sf::milliseconds((400 - 20 * OD)/2);
        this->hitWindow100 = sf::seconds((280 - 20 * OD)/2);
        this->hitWindow300 = sf::seconds((160 - 12 * OD)/2);
}




void Note::draw(sf::RenderTarget *target, sf::Time elapsedTime) {
    

    
    if( this->appearanceTiming <= elapsedTime && elapsedTime <= this->timing) {
        
        // *** calcul de l'opacité jusqu'a moment ou l'opacité doit être maxé
        if(elapsedTime <= this->maxedOpacityTiming) {
            sf::Time timeBeforeMax = this->maxedOpacityTiming - elapsedTime;
            
            float progress = 1.0 - (timeBeforeMax.asSeconds()/this->remainingTimeAfterOpacityMaxed.asSeconds());
            // printf("%f\n", progress);
            float opacity = progress * 255;
            this->hitcircle.setColor(sf::Color(255, 255, 255,(int) opacity));
            this->approachCircle.setColor(sf::Color(255, 255, 255, (int) opacity));
        }




        // *** calcul de la fermeture du cercle
        // temps restant ex: 200ms
        sf::Time lastingTime = this->timing - elapsedTime;
        
        // progression dans la fermeture
        // 200 / 800 -> 1/4 = 25%
        float progressPercent =  1.0 - (lastingTime.asSeconds()/(this->remainingTime.asSeconds()));
        float scale = acFactor*(3-(2*progressPercent));
        
        // - test
        // this->hitcircle.setColor(sf::Color(255, 255, 255, progressPercent*255));
        // - fin test

        this->approachCircle.setScale(scale, scale);

        target->draw(this->hitcircle);
        target->draw(this->approachCircle);
    }

    // * continuer à afficher le cercle après jusqu'a timing + hitWindow50  
    // * après ça afficher le miss
}


// retourne true si le cercle à bien été touché
bool Note::tryHit(sf::Time elapsedTime, int x, int y) {
    if(this->alreadyHit) {
        return false;
    }

    sf::Vector2f vect = this->hitcircle.getPosition() - sf::Vector2f(x, y);
    float dist = std::hypotf(vect.x, vect.y);   
    if(dist <= this->ray) { // * peut être mettre ray+10 pour augmenter la taille du curseur ?
        // sf::SoundBuffer hitsoundbuffer = sf::SoundBuffer();
        // hitsoundbuffer.loadFromFile(
        sf::Sound s(Skin::getHitsoundBuffer());
        s.play();
        if( timing - hitWindow300 <= elapsedTime && elapsedTime <= timing + hitWindow300) {
            std::cout << "300 hit !" << std::endl;
            

            
            this->alreadyHit = true;
            

            return true;
        } else if (timing - hitWindow100 <= elapsedTime && elapsedTime <= timing + hitWindow100) {
            std::cout << "100 hit!" << std::endl;
            
            this->alreadyHit = true;


            return true;
        } else if (timing - hitWindow50 <= elapsedTime && elapsedTime <= timing + hitWindow50) {

            
            std::cout << "50 hit!" << std::endl;
            
            
            this->alreadyHit = true;
            return true;
        } else  {
            std::cout << "miss" << std::endl;
            this->alreadyHit = true;
            return false;
        }
        
    }

    return false;
}


#endif