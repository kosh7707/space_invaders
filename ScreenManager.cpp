#include "ScreenManager.h"
#include <cassert>
#include <memory>

ScreenManager* ScreenManager::m_s_Instance = nullptr;

ScreenManager::ScreenManager(Vector2i res)
{
    assert(m_s_Instance == nullptr);
	m_Screens["Game"] = std::make_unique<GameScreen>(res);
	m_Screens["Select"] = std::make_unique<SelectScreen>(res);
    m_s_Instance = this;
}

void ScreenManager::handleInput(RenderWindow& window)
{
    m_s_Instance->m_Screens[m_s_Instance->m_CurrentScreen]->handleInput(window);
}

void ScreenManager::update(float fps)
{
    m_s_Instance->m_Screens[m_s_Instance->m_CurrentScreen]->update(fps);
}

void ScreenManager::draw(RenderWindow& window)
{
    m_s_Instance->m_Screens[m_s_Instance->m_CurrentScreen]->draw(window);
}

void ScreenManager::SwitchScreens(const string& screenToSwitchTo) {
    m_s_Instance->m_CurrentScreen = "" + screenToSwitchTo;
    m_s_Instance->m_Screens[m_s_Instance->m_CurrentScreen]->initialise();
}

void ScreenManager::loadLevelInPlayMode(const string& screenToLoad) {
    m_s_Instance->m_LevelManager.getGameObjects().clear();
    m_s_Instance->m_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
    SwitchScreens("Game");
}

vector<GameObject>& ScreenManager::getGameObjects() {
    return m_s_Instance->m_LevelManager.getGameObjects();
}

GameObjectSharer& ScreenManager::shareGameObjectSharer() {
    return m_s_Instance->m_LevelManager;
}