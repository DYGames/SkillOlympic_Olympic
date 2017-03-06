#pragma once

#include "DXUT.h"
#include "Sprite.h"
#include "Swim.h"

class SwimPlayer : public Sprite
{
public:
	Swim::SWIMPLAYERSTATE _state;

	Swim* _scene;

	float _speed;

	float _dir;
	int _tcount;

	bool _isPlayer;

	SwimPlayer()
	{
		_speed = 0;
		_tcount = 0;
		_dir = 1;
	}

	void DiveAI()
	{
		MoveTo(_position + Vec2(250, 0), 3);
		_state = Swim::SWIMPLAYERSTATE::ONDIVE;
		_movetocallback = [=]()
		{
			_state = Swim::SWIMPLAYERSTATE::DHPNKICK; _texture = TextureMng::getInstance()->getTexture(L"swimplayer.png");
			Delay(1.5f, [=]()
			{
				_state = Swim::SWIMPLAYERSTATE::SWIM;
			});
		};
	}

	void TurnAI()
	{
		MoveTo(_position + Vec2(200 * _dir, 0), 2);
		_state = Swim::SWIMPLAYERSTATE::ONDIVE;
		_movetocallback = [=]()
		{
			_state = Swim::SWIMPLAYERSTATE::DHPNKICK; _texture = TextureMng::getInstance()->getTexture(L"swimplayer.png");
			Delay(1.5f, [=]()
			{
				_state = Swim::SWIMPLAYERSTATE::SWIM;
			});
		};
	}

	void update() override
	{
		Sprite::update();

		if (_speed > 0)
			_speed -= Time::dt * 4;

		_scale.x = _dir;

		if (!_isPlayer && _state == Swim::SWIMPLAYERSTATE::WAITFORDIVE)
			DiveAI();
		if (!_isPlayer && _state == Swim::SWIMPLAYERSTATE::WAITFORTURN)
			TurnAI(), _tcount++;
		if (!_isPlayer && _state == Swim::SWIMPLAYERSTATE::DHPNKICK)
			_speed = 2.1f;


		if (_state == Swim::SWIMPLAYERSTATE::SWIM)
		{
			if (!_isPlayer)
				_speed += Time::dt * (rand() % 12);

			if (_dir == 1)
			{
				if (_position.x > 2740)
				{
					_state = Swim::SWIMPLAYERSTATE::WAITFORTURN;
					_dir = -1;
					_speed = 0;
					if (_isPlayer)
					{
						_scene->_zb->_visible = false;
						_scene->_xb->_visible = false;
						_scene->_spaceb->_visible = true;
					}
				}
			}
			else
			{
				if (_position.x < 410)
				{
					if (_tcount >= 3)
					{
						_state = Swim::SWIMPLAYERSTATE::GOALIN;
						return;
					}
					_state = Swim::SWIMPLAYERSTATE::WAITFORTURN;
					_dir = 1;
					_speed = 0;
					if (_isPlayer)
					{
						_scene->_zb->_visible = false;
						_scene->_xb->_visible = false;
						_scene->_spaceb->_visible = true;
					}
				}
			}
		}


		if (_speed < 0)
			_speed = 0;
		if (_speed > 10)
			_speed = 10;

		_position.x += _speed * _dir;
	}


};