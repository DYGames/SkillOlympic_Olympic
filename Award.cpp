#include "DXUT.h"
#include "Award.h"

void Award::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	Sprite* aw = new Sprite();
	aw->initWithFile(L"awardback.png");
	aw->_position = Vec2(640, 360);
	_game->addChild(aw);

}

void Award::update()
{
	Node::update();

}

void Award::exit()
{
	for (auto it : _children)
		removeChild(it);
}
