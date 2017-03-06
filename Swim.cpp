#include "DXUT.h"
#include "Swim.h"
#include "SwimPlayer.h"

void Swim::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	Sprite* back = new Sprite();
	back->initWithFile(L"swimback.png");
	back->_position = Vec2(back->_texture->_info.Width / 2.f, 360);
	_game->addChild(back);

	_player = new SwimPlayer();
	_player->initWithFile(L"swimstand.png");
	_player->_position = Vec2(100, 120);
	_player->_scene = this;
	_player->_isPlayer = true;
	_player->_state = SWIMPLAYERSTATE::WAITFORDIVE;
	_game->addChild(_player);

	for (int i = 0; i < 3; i++)
	{
		_enemy[i] = new SwimPlayer();
		_enemy[i]->initWithFile(L"swimstand.png");
		_enemy[i]->_position = Vec2(100, 120 + ((i + 1) * 160));
		_enemy[i]->_scene = this;
		_enemy[i]->_isPlayer = false;
		_enemy[i]->_state = SWIMPLAYERSTATE::WAITFORDIVE;
		_game->addChild(_enemy[i]);
	}


	_zb = new Sprite();
	_zb->initWithFile(L"zb.png");
	_zb->_position = Vec2(500, 580);
	_zb->_color.a = 0;
	_ui->addChild(_zb);

	_xb = new Sprite();
	_xb->initWithFile(L"xb.png");
	_xb->_position = Vec2(780, 580);
	_xb->_color.a = 0;
	_ui->addChild(_xb);

	_spaceb = new Sprite();
	_spaceb->initWithFile(L"space.png");
	_spaceb->_position = Vec2(640, 620);
	_spaceb->_visible = false;
	_ui->addChild(_spaceb);

}

void Swim::update()
{
	Node::update();

	_game->MoveTo(Vec2(640 - _player->_position.x, 360 - _player->_position.y), 2);

	if (_game->_position.y > 0)
		_game->_position.y = 0;
	if (_game->_position.x > 0)
		_game->_position.x = 0;

	if (DXUTWasKeyPressed(VK_SPACE))
	{
		if (_player->_state == SWIMPLAYERSTATE::WAITFORDIVE)
		{
			_player->MoveTo(_player->_position + Vec2(250, 0), 3);
			_player->_state = SWIMPLAYERSTATE::ONDIVE;
			_player->_movetocallback = [=](){_player->_state = SWIMPLAYERSTATE::DHPNKICK; _player->_texture = TextureMng::getInstance()->getTexture(L"swimplayer.png"); _spaceb->_visible = true, _player->Delay(1.5f, [=](){_spaceb->_visible = false, _player->_state = SWIMPLAYERSTATE::SWIM; _zb->_color.a = 0, _xb->_color.a = 0; _zb->AlphaTo(1, Time::dt * 3, nullptr); }); };
		}
		if (_player->_state == SWIMPLAYERSTATE::WAITFORTURN)
		{
			if (_player->_tcount < 3)
			{
				_player->_tcount++;
				_player->MoveTo(_player->_position + Vec2(200 * _player->_dir, 0), 2);
				_player->_state = SWIMPLAYERSTATE::ONDIVE;
				_player->_movetocallback = [=]()
				{
					_player->_state = SWIMPLAYERSTATE::DHPNKICK;
					_player->_texture = TextureMng::getInstance()->getTexture(L"swimplayer.png");
					_player->Delay(1.5f, [=]()
					{
						_spaceb->_visible = false;
						_player->_state = SWIMPLAYERSTATE::SWIM;
						_zb->_color.a = 0, _xb->_color.a = 0;
						_zb->_visible = true, _xb->_visible = true;
						_zb->AlphaTo(1, Time::dt * 3, nullptr);
					}); 
				};
			}
		}
		if (_player->_state == SWIMPLAYERSTATE::DHPNKICK)
			_player->_speed = 2.5f;
	}
	if (DXUTWasKeyPressed('Z'))
	{
		if (_zb->_alphatotarget == 1.f && _player->_state == SWIMPLAYERSTATE::SWIM)
		{
			_zb->AlphaTo(0, Time::dt * 3, nullptr);
			_xb->AlphaTo(1, Time::dt * 3, nullptr);
			_player->_speed += 3;
		}
	}
	if (DXUTWasKeyPressed('X'))
	{
		if (_xb->_alphatotarget == 1.f && _player->_state == SWIMPLAYERSTATE::SWIM)
		{
			_xb->AlphaTo(0, Time::dt * 3, nullptr);
			_zb->AlphaTo(1, Time::dt * 3, nullptr);
			_player->_speed += 3;
		}
	}

	if (_player->_state == SWIMPLAYERSTATE::GOALIN && _enemy[0]->_state == SWIMPLAYERSTATE::GOALIN && _enemy[1]->_state == SWIMPLAYERSTATE::GOALIN && _enemy[2]->_state == SWIMPLAYERSTATE::GOALIN && !_end)
	{
		_end = true;
	}

}

void Swim::exit()
{
	for (auto it : _children)
		removeChild(it);
}