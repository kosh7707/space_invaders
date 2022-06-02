#pragma once
#include "Screen.h"

class SelectScreen : public Screen
{
private:
	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;

public:
	SelectScreen(Vector2i res);
	void draw(RenderWindow& window) override;
};