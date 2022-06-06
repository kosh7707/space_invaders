#ifndef SPACE_INVADERS_RANDOMOBSTACLEUPDATECOMPONENT_H
#define SPACE_INVADERS_RANDOMOBSTACLEUPDbATECOMPONENT_H

#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "RectColliderComponent.h"
#include "GameObject.h"
#include "GameObjectSharer.h"

class RandomObstacleUpdateComponent : public UpdateComponent {
private:
    string m_SpecificType = "randomobstacle";

    shared_ptr<TransformComponent> m_TC;
    shared_ptr<RectColliderComponent> m_RCC;

    float m_Speed = 65.0f;
    bool m_MovingUp = false;

public:
    bool m_IsSpawned = false;

    void spawnForRandom();
    void deSpawn();

    // From Component interface base class
    string getSpecificType() override {
        return m_SpecificType;
    }

    void start(GameObjectSharer* gos, GameObject* self) override {
        // Where is this specific invader
        m_TC = static_pointer_cast<TransformComponent>(self->getComponentByTypeAndSpecificType("transform", "transform"));
        m_RCC = static_pointer_cast<RectColliderComponent>(self->getComponentByTypeAndSpecificType("collider", "rect"));
    }

    // From UpdateComponent
    void update(float fps) override;
};

#endif //SPACE_INVADERS_RANDOMOBSTACLEUPDATECOMPONENT_H
