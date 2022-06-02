#include "Screen.h"

void Screen::initialise() {}

void Screen::addPanel(unique_ptr<UIPanel> uip, const shared_ptr<InputHandler>& ih) {
	ih->initialiseInputHandler(uip->getButtons(), &uip->m_View, this);
	m_Panels.push_back(move(uip));
	m_InputHandlers.push_back(ih);
}

void Screen::handleInput(RenderWindow& window) {
	Event event;
	while (window.pollEvent(event)) {
        for (const auto& it : m_InputHandlers)
			it->handleInput(window, event);
	}
}

void Screen::update(float fps) {}

void Screen::draw(RenderWindow& window) {
    for (const auto& it : m_Panels)
		it->draw(window);

}
