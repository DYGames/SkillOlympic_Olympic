#pragma once

#include "DXUT.h"
#include "Sprite.h"

class RunPlayer : public Sprite
{
public:
	float _speed;
	bool _isPlayer;
	bool _isGoal;

	RunPlayer()
	{
		_speed = 0;
		_isGoal = false;
	}

	void update() override
	{
		Sprite::update();

		if (!_isGoal)
			_speed -= Time::dt * 3;
		else
			_speed -= Time::dt * 20;

		if (!_isGoal)
		{
			if (!_isPlayer)
			{
				_speed += Time::dt * (rand() % 2 + 5);
			}
		}

		if (_position.x > 3000)
		{
			_isGoal = true;
		}

		if (_speed < 0)
			_speed = 0;
		if (_speed > 15)
			_speed = 15;

		_position.x += _speed;



	}


};