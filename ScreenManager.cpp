#include "ScreenManager.h"

#include <memory>

ScreenManager::ScreenManager(Vector2i res)
{
	m_Screens["Game"] = std::make_unique<GameScreen>(this, res);
	m_Screens["Select"] = std::make_unique<SelectScreen>(this, res);
}

void ScreenManager::handleInput(RenderWindow& window)
{
	m_Screens[m_CurrentScreen]->handleInput(window);
}

void ScreenManager::update(float fps)
{
	m_Screens[m_CurrentScreen]->update(fps);
}

void ScreenManager::draw(RenderWindow& window)
{
	m_Screens[m_CurrentScreen]->draw(window);
}