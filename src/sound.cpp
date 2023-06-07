#include "sound.h"

#include <SFML/Audio.hpp>

#include <filesystem>

sf::SoundBuffer Sound::bufferCapture;
sf::SoundBuffer Sound::bufferMove;
sf::SoundBuffer Sound::bufferCheck;
sf::SoundBuffer Sound::bufferCastle;
sf::SoundBuffer Sound::bufferPromote;

sf::Sound Sound::soundCapture;
sf::Sound Sound::soundMove;
sf::Sound Sound::soundCheck;
sf::Sound Sound::soundCastle;
sf::Sound Sound::soundPromote;

void Sound::initialization(void)
{
    Sound::bufferCapture.loadFromFile
    (
        std::filesystem::current_path().string() + "/assets/sounds/capture.wav"
    );
    Sound::bufferMove.loadFromFile
    (
        std::filesystem::current_path().string() + "/assets/sounds/move.wav"
    );
    Sound::bufferCheck.loadFromFile
    (
        std::filesystem::current_path().string() + "/assets/sounds/check.wav"
    );
    Sound::bufferCastle.loadFromFile
    (
        std::filesystem::current_path().string() + "/assets/sounds/capture.wav"
    );
    Sound::bufferPromote.loadFromFile
    (
        std::filesystem::current_path().string() + "/assets/sounds/promote.wav"
    );

    Sound::soundCapture.setBuffer(Sound::bufferCapture);
    Sound::soundMove.setBuffer(Sound::bufferMove);
    Sound::soundCheck.setBuffer(Sound::bufferCheck);
    Sound::soundCastle.setBuffer(Sound::bufferCastle);
    Sound::soundPromote.setBuffer(Sound::bufferPromote);
}

void Sound::capture(void)
{
    Sound::soundCapture.play();
}

void Sound::move(void)
{
    Sound::soundMove.play();
}

void Sound::check(void)
{
    Sound::soundCheck.play();
}

void Sound::castle(void)
{
    Sound::soundCastle.play();
}

void Sound::promote(void)
{
    Sound::soundPromote.play();
}