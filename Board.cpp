#include "DXUT.h"
#include "Board.h"

void Board::init(Sprite* parent)
{
	Sprite::initWithFile(L"bdboard/popup.png");
	_position = Vec2(640, 360);
	_color.a = 0;
	parent->addChild(this);

	for (int i = 0; i < 8; i++)
	{
		_sfinal[i] = new Sprite();
		_sfinal[i]->initWithFile(L"bdboard/korea.png");
		_sfinal[i]->_position = Vec2(200 + (i * 125), 640);
		if (i > 3)
			_sfinal[i]->_position = Vec2(720 + ((i - 4) * 125), 640);
		_sfinal[i]->_zorder = 234;
		parent->addChild(_sfinal[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		_finals[i] = L"korea";
		_final[i] = new Sprite();
		_final[i]->initWithFile(L"bdboard/korea.png");
		_final[i]->_position = Vec2(460 + (i * 125), 440);
		_final[i]->_visible = false;
		parent->addChild(_final[i]);
	}

	_wins = L"korea";
	_win = new Sprite();
	_win->initWithFile(L"bdboard/korea.png");
	_win->_position = Vec2(640, 220);
	_win->_visible = false;
	parent->addChild(_win);
}

void Board::update()
{
	Sprite::update();

	for (int i = 0; i < 8; i++)
	{
		if (_sfinals[i] != L"korea" && _sfinal[i]->_name != _sfinals[i])
		{
			_sfinal[i]->_texture = TextureMng::getInstance()->getTexture(L"bdboard/" + _sfinals[i] + L".png");
			_sfinal[i]->_name = _sfinals[i];
			_sfinal[i]->_visible = true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (_finals[i] != L"korea" && _final[i]->_name != _sfinals[i])
		{
			_final[i]->_texture = TextureMng::getInstance()->getTexture(L"bdboard/" + _finals[i] + L".png");
			_final[i]->_name = _finals[i];
			_final[i]->_visible = true;
		}
	}
	if (_wins != L"korea" && _win->_name != _wins)
	{
		_win->_texture = TextureMng::getInstance()->getTexture(L"bdboard/" + _wins + L".png");
		_win->_name = _wins;
		_win->_visible = true;
	}

}

void Board::FadeOn()
{
	AlphaTo(1, 1.f / 60.f, nullptr);
	for (int i = 0; i < 8; i++)
		_sfinal[i]->AlphaTo(1, 1.f / 60.f, nullptr);
	for (int i = 0; i < 4; i++)
		_final[i]->AlphaTo(1, 1.f / 60.f, nullptr);
	_win->AlphaTo(1, 1.f / 60.f, nullptr);
}

void Board::FadeOff()
{
	AlphaTo(0, 1.f / 60.f, nullptr);
	for (int i = 0; i < 8; i++)
		_sfinal[i]->AlphaTo(0, 1.f / 60.f, nullptr);
	for (int i = 0; i < 4; i++)
		_final[i]->AlphaTo(0, 1.f / 60.f, nullptr);
	_win->AlphaTo(0, 1.f / 60.f, nullptr);
}