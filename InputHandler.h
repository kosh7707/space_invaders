#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Screen.h"
#include <memory>

using namespace sf;
using namespace std;

class Screen;
class InputHandler {
private:
	Screen* m_ParentScreen;
	vector<shared_ptr<Button>> m_Buttons;
	View* m_PointerToUIPanelView;

public:
	void initialiseInputHandler(vector<shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen);

	void handleInput(RenderWindow& window, Event& event);

	virtual void handleGamepad();
	virtual void handleKeyPressed(Event& event, RenderWindow& window);
	virtual void handleKeyReleased(Event& event, RenderWindow& window);
	virtual void handleLeftClick(string& buttonInteractedWith, RenderWindow& window);

	View* getPointerToUIView();
	Screen* getmParentScreen();
};