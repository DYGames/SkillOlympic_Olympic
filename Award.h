#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Sprite.h"

class Award : public Scene
{
public:
	void init() override;
	void update() override;
	void exit() override;

	Sprite* _game;
	Sprite* _ui;


}; 