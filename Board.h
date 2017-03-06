#pragma once

#include "Sprite.h"

class Board : public Sprite
{
public:

	Sprite* _sfinal[8];
	std::wstring _sfinals[8];

	Sprite* _final[4];
	std::wstring _finals[4];

	Sprite* _win;
	std::wstring _wins;

	void init(Sprite* parent);

	void update() override;

	void FadeOn();
	void FadeOff();

};