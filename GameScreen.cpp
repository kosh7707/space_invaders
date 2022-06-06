#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "WorldState.h"
#include "GameObject.h"
#include "BulletUpdateComponent.h"
#include "InvaderUpdateComponent.h"
#include "RandomObstacleUpdateComponent.h"
#include <random>

class BulletSpawner;

int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;

GameScreen::GameScreen(Vector2i res)
{
	m_GIH = make_shared<GameInputHandler>();
	auto guip = make_unique<GameUIPanel>(res);
	addPanel(move(guip), m_GIH);

	auto m_GOIH = make_shared<GameOverInputHandler>();
	auto gouip = make_unique<GameOverUIPanel>(res);
	addPanel(move(gouip), m_GOIH);

	float screenRatio = VideoMode::getDesktopMode().width /
		VideoMode::getDesktopMode().height;

	WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH /
		screenRatio;

	m_View.setSize(
		WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);

	m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH /
		2, WorldState::WORLD_HEIGHT / 2));

	m_BackgroundTexture.loadFromFile("graphics/background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	auto textureSize = m_BackgroundSprite.getTexture()->getSize();
	m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x,
		float(m_View.getSize().y) / textureSize.y);
}

void GameScreen::initialise() {
	m_GIH->initialize();
	m_PhysicsEnginePlayMode.initilize(ScreenManager::shareGameObjectSharer());
	WorldState::NUM_INVADERS = 0;
	int i = 0;
    for (auto& it : ScreenManager::getGameObjects()) {
		if (it.getTag() == "bullet")
			m_BulletObjectLocations.push_back(i);
        if (it.getTag() == "randomobstacle")
            m_ObstacleObjectLocations.push_back(i);
		if (it.getTag() == "invader") {
			static_pointer_cast<InvaderUpdateComponent>(
				it.getFirstUpdateComponent())->
				initializeBulletSpawner(
					getBulletSpawner(), i);
			WorldState::NUM_INVADERS++;
		}
		++i;
	}

	m_GameOver = false;

	if (WorldState::WAVE_NUMBER == 0) {
		WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;
		WorldState::WAVE_NUMBER = 1;
		WorldState::LIVES = 3;
		WorldState::SCORE = 0;
	}
}

void GameScreen::update(float fps) {
	Screen::update(fps);

	if (!m_GameOver) {
        Time RandomObstacleClockCounter = m_RandomObstacleClock.getElapsedTime();
        if (RandomObstacleClockCounter.asMilliseconds() > 5000) {
            m_WaitingToSpawnRandomObstacle = true;
            m_RandomObstacleClock.restart();
        }

        if (m_WaitingToSpawnRandomObstacle) {
            std::cout << "m_WaitingToSpawnRandomObstacle is true!\n";
            for (auto& it : ScreenManager::getGameObjects()) {
                if (it.getTag() == "randomobstacle") {
                    std::cout << "Obstacle Spawned!!\n";
                    static_pointer_cast<RandomObstacleUpdateComponent>(it.getFirstUpdateComponent())->spawnForRandom();
                    m_WaitingToSpawnRandomObstacle = false;
                }
            }
        }

		if (m_WaitingToSpawnBulletForPlayer) {
			static_pointer_cast<BulletUpdateComponent>(ScreenManager::getGameObjects()[m_BulletObjectLocations[m_NextBullet]].getFirstUpdateComponent())
			        ->spawnForPlayer(m_PlayerBulletSpawnLocation);
			m_WaitingToSpawnBulletForPlayer = false;
			m_NextBullet++;
			if (m_NextBullet == m_BulletObjectLocations.size())
				m_NextBullet = 0;
		}
		if (m_WaitingToSpawnBulletForInvader) {
			static_pointer_cast<BulletUpdateComponent>(ScreenManager::getGameObjects()
				    [m_BulletObjectLocations[m_NextBullet]].
				    getFirstUpdateComponent())->
				    spawnForInvader(m_InvaderBulletSpawnLocation);

			m_WaitingToSpawnBulletForInvader = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size())
				m_NextBullet = 0;
		}

		for (auto& it : ScreenManager::getGameObjects())
			it.update(fps);

        // 충돌 처리 부분
		m_PhysicsEnginePlayMode.detectCollisions(ScreenManager::getGameObjects(), m_BulletObjectLocations);

		if (WorldState::NUM_INVADERS <= 0) {
			WorldState::WAVE_NUMBER++;
            ScreenManager::loadLevelInPlayMode("level1");
		}

		if (WorldState::LIVES <= 0)
			m_GameOver = true;
	}
}

void GameScreen::draw(RenderWindow& window)
{
	window.setView(m_View);
	window.draw(m_BackgroundSprite);


    for (auto& it : ScreenManager::getGameObjects())
		it.draw(window);

	Screen::draw(window);
}


BulletSpawner* GameScreen::getBulletSpawner() {
	return this;
}
