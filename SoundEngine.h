#pragma once
#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <SFML/Audio.hpp>
#include "VolumeControl.h"

using namespace sf;

class SoundEngine
{
private:
	SoundBuffer m_ShootBuffer;
	SoundBuffer m_PlayerExplodeBuffer;
	SoundBuffer m_InvaderExplodeBuffer;
	SoundBuffer m_ClickBuffer;

	CustomSound m_ShootSound;
    CustomSound m_PlayerExplodeSound;
    CustomSound m_InvaderExplodeSound;
    CustomSound m_UhSound;
    CustomSound m_OhSound;
    CustomSound m_ClickSound;

public:
	SoundEngine();

	static void playShoot();
	static void playPlayerExplode();
	static void playInvaderExplode();
	static void playClick();

	static SoundEngine* m_s_Instance;
};

#endif