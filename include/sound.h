#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class Sound
{
    public:
        static void initialization(void);
        static void capture(void);
        static void move(void);
        static void check(void);
        static void castle(void);
        static void promote(void);
        
    private:
        static sf::SoundBuffer bufferCapture;
        static sf::SoundBuffer bufferMove;
        static sf::SoundBuffer bufferCheck;
        static sf::SoundBuffer bufferCastle;
        static sf::SoundBuffer bufferPromote;
        static sf::Sound soundCapture;
        static sf::Sound soundMove;
        static sf::Sound soundCheck;
        static sf::Sound soundCastle;
        static sf::Sound soundPromote;
};

#endif