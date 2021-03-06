#pragma once
#include "Component.h"
#include <iostream>

class ColliderComponent : public Component
{
private:
	string m_Type = "collider";
	bool m_Enabled = false;

public:

	/****************************************************
	*****************************************************
	From Component interface
	*****************************************************
	*****************************************************/

	string getType() override {
		return m_Type;
	}

	void disableComponent() override {
		m_Enabled = false;
	}

	void enableComponent() override {
		m_Enabled = true;
	}

	bool enabled() override {
		return m_Enabled;
	}

	void start(GameObjectSharer* gos, GameObject* self) override {

	}
};

