#pragma once

#include "DXUT.h"
#include "Node.h"

class Scene : public Node
{
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;

};

class Director
{
public:
	static LPD3DXSPRITE _sprite;

	Scene* _cur;
	Scene* _next;

	static Director* _dinstance;
	static Director* getInstance()
	{
		if (!_dinstance)
			_dinstance = new Director();
		return _dinstance;
	}

	void replaceScene(Scene* scene)
	{
		if (!_cur)
		{
			_cur = scene;
			_cur->init();
		}
		else
			_next = scene;
	}

	void update()
	{
		if (!_cur)
			return;
		if (_next)
		{
			_cur->exit();
			_cur->removeChildAll();
			_cur->deleteChildAll();
			_cur = _next;
			_cur->init();
			_next = NULL;
		}

		_cur->update();
		_cur->draw();
		_cur->addChildAll();
		_cur->removeChildAll();
		_cur->deleteChildAll();
	}

	void Release()
	{
		_cur->exit();
		_cur->removeChildAll();
		_cur->deleteChildAll();
		SAFE_DELETE(_cur);
		SAFE_DELETE(_next);
	}

};