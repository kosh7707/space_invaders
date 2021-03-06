#include <iostream>
#include <utility>
#include "InputHandler.h"

using namespace sf;
using namespace std;

void InputHandler::initialiseInputHandler(vector<shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen) {
	m_Buttons = std::move(buttons);
	m_PointerToUIPanelView = pointerToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(RenderWindow& window, Event& event)
{
	// Handle any key presses
	if (event.type == Event::KeyPressed)
	{
		handleKeyPressed(event, window);
	}

	if (event.type == Event::KeyReleased)
	{
		handleKeyReleased(event, window);
	}

	// Handle any left mouse click released
	if (event.type == Event::MouseButtonReleased) {
        Vector2i mouse_pos {Mouse::getPosition().x - window.getPosition().x, Mouse::getPosition().y - window.getPosition().y};
        for (const auto& it : m_Buttons) {
			if (it->m_Collider.contains(window.mapPixelToCoords(mouse_pos,(*getPointerToUIView())))) {
				handleLeftClick(it->m_Text, window);
				break;
			}
		}
	}

	handleGamepad();
}

void InputHandler::handleGamepad()
{}// Do nothing unless handled by a derived class

void InputHandler::handleKeyPressed(Event& event,
	RenderWindow& window)
{}// Do nothing unless handled by a derived class

void InputHandler::handleKeyReleased(Event& event,
	RenderWindow& window)
{}// Do nothing unless handled by a derived class

void InputHandler::handleLeftClick(std::
	string& buttonInteractedWith,
	RenderWindow& window)
{}// Do nothing unless handled by a derived class

View* InputHandler::getPointerToUIView()
{
	return m_PointerToUIPanelView;
}

Screen* InputHandler::getmParentScreen() {
	return m_ParentScreen;
}