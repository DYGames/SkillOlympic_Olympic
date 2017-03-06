#pragma once

#include "DXUT.h"
#include "Type.h"
#include <algorithm>
#include <vector>

class Node 
{
public:
	bool _active;
	bool _visible;

	Vec2 _position;
	Vec2 _scale;
	Vec2 _anchor;
	float _rotation;

	Rect _rect;

	D3DXCOLOR _color;

	int _zorder;
	int _tag;
	std::wstring _name;

	Node* _parent;

	std::vector<Node*> _children;
	std::vector<Node*> _willaddChild;
	std::vector<Node*> _willdeleteChild;

	Node()
	{
		_parent = nullptr;
		_active = false;
		_visible = true;
		_position = Vec2();
		_scale = Vec2(1, 1);
		_anchor = Vec2(0.5f, 0.5f);
		_rotation = 0;
		_color = D3DXCOLOR(1, 1, 1, 1);
		_zorder = 0;
		_tag = 0;
		_name = L"";
		_children.clear();
		_willaddChild.clear();
		_willdeleteChild.clear();
	}

	virtual ~Node(){}

	virtual void update()
	{
		for (auto it : _children)
		{
			if (it->_active)
				it->update();
		}
	}

	virtual void draw()
	{
		std::sort(_children.begin(), _children.end(), [=](Node* a, Node* b){return a->_zorder < b->_zorder; });

		for (auto it : _children)
		{
			if (it->_active && it->_visible)
				it->draw();
		}
	}

	void addChild(Node* c)
	{
		c->_parent = this;
		c->_active = true;
		_willaddChild.push_back(c);
	}

	void removeChild(Node* c)
	{
		for (auto it : c->_children)
			removeChild(it);
		c->_active = false;
	}

	void addChildAll()
	{
		for (auto it : _willaddChild)
		{
			_children.push_back(it);
		}
		_willaddChild.clear();

		for (auto it : _children)
		{
			it->addChildAll();
		}
	}

	void removeChildAll()
	{
		for (auto it = _children.begin(); it != _children.end();)
		{
			(*it)->removeChildAll();
			if (!(*it)->_active)
			{
				_willdeleteChild.push_back(*it);
				it = _children.erase(it);
			}
			else
				it++;
		}
	}
	
	void deleteChildAll()
	{
		for (auto it : _willdeleteChild)
		{
			it->deleteChildAll();
			SAFE_DELETE(it);
		}
		_willdeleteChild.clear();
	}

	D3DXMATRIX getMatrix()
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTransformation2D(&mat, nullptr, NULL, &_scale, nullptr, _rotation, &_position);
		if (_parent)
			mat *= _parent->getMatrix();
		return mat;
	}


};

class Label : public Node
{
public:
	LPD3DXFONT _font;
	std::wstring _str;

	virtual ~Label()
	{
		SAFE_RELEASE(_font);
	}

	void initFont(std::wstring str, int pt)
	{
		_active = true;
		_str = str;

		D3DXCreateFont(DXUTGetD3D9Device(), pt, 0, 0, 1, FW_BOLD, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"Consolas", &_font);
	}

	void draw() override
	{
		Node::draw();

		Rect rc = { _position.x, 0, _position.y, 0 };
		_font->DrawText(nullptr, _str.c_str(), _str.size(), &rc, 0 | FF_DONTCARE, _color);
	}

};