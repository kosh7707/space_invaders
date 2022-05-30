#ifndef SPACE_INVADERS_VOLUMECONTROL_H
#define SPACE_INVADERS_VOLUMECONTROL_H

#include <SFML/Audio.hpp>
#include "WorldState.h"

using namespace sf;

class CustomSound : public Sound{
public:
    CustomSound() {
        this->setVolume(WorldState::SOUND);
    }
};

#endif //SPACE_INVADERS_VOLUMECONTROL_H
