#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "GameScreen.h"
#include "SelectScreen.h"
#include "LevelManager.h"
#include "BitmapStore.h"
#include <iostream>

using namespace sf;
using namespace std;

class ScreenManager {
private:
	map <string, unique_ptr<Screen>> m_Screens;
	LevelManager m_LevelManager;

protected:
	string m_CurrentScreen = "Select";

public:
    static ScreenManager* m_s_Instance;

	BitmapStore m_BS;

	ScreenManager(Vector2i res);
	static void update(float fps);
	static void draw(RenderWindow& window);
	static void handleInput(RenderWindow& window);
	static void SwitchScreens(const string& screenToSwitchTo);
	static void loadLevelInPlayMode(const string& screenToLoad);
	static vector<GameObject>& getGameObjects();
	static GameObjectSharer& shareGameObjectSharer();
};