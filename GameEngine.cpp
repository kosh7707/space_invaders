#include "GameEngine.h"
#include <memory>

GameEngine::GameEngine()
{
    m_Resolution.x = 1024; m_Resolution.y = 768;
    m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y), "Space Invaders", Style::None);

	m_ScreenManager = std::make_unique<ScreenManager>(Vector2i(m_Resolution.x, m_Resolution.y));
}

void GameEngine::run()
{
	while (m_Window.isOpen()) {
		m_DT = m_Clock.restart();
		m_FPS = m_DT.asSeconds();
		handleInput();
		update();
		draw();
	}
}

void GameEngine::handleInput()
{
	m_ScreenManager->handleInput(m_Window);
}

void GameEngine::update()
{
	m_ScreenManager->update(m_FPS);
}

void GameEngine::draw()
{
	m_Window.clear(Color::Black);
	m_ScreenManager->draw(m_Window);
	m_Window.display();
}