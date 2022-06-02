#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include "ScreenManager.h"
#include <iostream>

void GameOverInputHandler::handleKeyPressed(Event& event,
	RenderWindow& window)
{
	if (event.key.code == Keyboard::Escape)
	{
		SoundEngine::playClick();
		ScreenManager::SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleLeftClick(
	std::string& buttonInteractedWith, RenderWindow& window)
{
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
        ScreenManager::loadLevelInPlayMode("level1");
	}

	else if (buttonInteractedWith == "Home") {
		SoundEngine::playClick();
        ScreenManager::SwitchScreens("Select");
	}
}