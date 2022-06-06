#include "RandomObstacleUpdateComponent.h"
#include "WorldState.h"
#include <random>

void RandomObstacleUpdateComponent::spawnForRandom() {
    m_IsSpawned = true;
    srand(time(nullptr));
    m_MovingUp = static_cast<bool>(rand()%2);
    Vector2i rand_position;
    if (m_MovingUp) {
        rand_position.x = rand()%WorldState::WORLD_WIDTH;
        rand_position.y = WorldState::WORLD_HEIGHT;
    }
    else {
        rand_position.x = rand()%WorldState::WORLD_WIDTH;
        rand_position.y = -10;
    }
    std::cout << "Spawnpoint: (" << rand_position.x << ", " << rand_position.y << ")\n";

    m_TC->getLocation().x = rand_position.x;
    m_TC->getLocation().y = rand_position.y;
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y, m_TC->getSize().x, m_TC->getSize().y);
}

void RandomObstacleUpdateComponent::deSpawn() {
    m_IsSpawned = false;
}

void RandomObstacleUpdateComponent::update(float fps) {
    if (m_IsSpawned) {
        if (m_MovingUp)
            m_TC->getLocation().y -= m_Speed * fps;
        else
            m_TC->getLocation().y += m_Speed * fps;

        if (m_TC->getLocation().y > static_cast<float>(WorldState::WORLD_HEIGHT + 10) || m_TC->getLocation().y < -10.0)
            deSpawn();

        m_RCC->setOrMoveCollider(m_TC->getLocation().x,m_TC->getLocation().y,m_TC->getSize().x, m_TC->getSize().y);
    }
}