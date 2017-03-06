#pragma once

#include "DXUT.h"
#include "Node.h"
#include "Director.h"
#include "Animation.h"
#include <functional>

class Texture
{
public:
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _info;
	std::wstring _name;
};

class TextureMng
{
public:
	std::vector<Texture*> _textures;

	static TextureMng* _tinstance;
	static TextureMng* getInstance()
	{
		if (!_tinstance)
			_tinstance = new TextureMng();
		return _tinstance;
	}

	Texture* getTexture(std::wstring path)
	{
		std::wstring realpath;
		realpath = L"Resource/" + path;

		for (auto it : _textures)
		{
			if (it->_name == realpath)
				return it;
		}

		Texture* t = new Texture();
		t->_name = realpath;
		
		if (FAILED(D3DXCreateTextureFromFileEx(
			DXUTGetD3D9Device(),
			realpath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			0,
			D3DFORMAT::D3DFMT_A8B8G8R8,
			D3DPOOL::D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			NULL,
			&t->_info,
			NULL,
			&t->_texture)))
			return NULL;

		D3DXGetImageInfoFromFile(realpath.c_str(), &t->_info);

		_textures.push_back(t);

		return t;
	}

	void Release()
	{
		for (auto it : _textures)
		{
			SAFE_RELEASE(it->_texture);
			SAFE_DELETE(it);
		}
		_textures.clear();
	}

};

class Sprite : public Node
{
public:
	Texture* _texture;
	Animation ani;


	Vec2 _movetotarget = Vec2();
	Vec2 _normalized = Vec2();
	float _movetospeed = 0;
	bool _islerp = true;
	std::function<void()> _movetocallback = nullptr;

	Vec2 _scaletotarget = Vec2();
	float _scaletospeed = 0;
	std::function<void()> _scaletocallback = nullptr;

	float _alphatotarget = 0;
	float _alphatospeed = 0;
	std::function<void()> _alphatocallback = nullptr;

	float _delay = 0;
	std::function<void()> _delaycallback = nullptr;


	void MoveTo(Vec2 target, float speed, bool lerp = true)
	{
		_movetotarget = target;
		_movetospeed = speed;
		D3DXVec2Normalize(&_normalized, &(target - _position));
		_islerp = lerp;
	}

	void ScaleTo(Vec2 target, float speed, std::function<void()> callback)
	{
		_scaletotarget = target;
		_scaletospeed = speed;
		_scaletocallback = callback;
	}

	void AlphaTo(float target, float speed, std::function<void()> callback)
	{
		_alphatotarget = target;
		_alphatospeed = speed;
		_alphatocallback = callback;
	}

	void Delay(float delay, std::function<void()> callback)
	{
		_delay = delay;
		_delaycallback = callback;
	}

	Sprite()
	{
		_texture = nullptr;
	}

	virtual ~Sprite()
	{
		//SAFE_DELETE(_texture);
	}

	void initWithFile(std::wstring str)
	{
		_active = true;
		_texture = TextureMng::getInstance()->getTexture(str);
	}

	void update() override
	{
		Node::update();

		if (_movetospeed)
		{
			if (_islerp)
			{
				D3DXVec2Lerp(&_position, &_position, &_movetotarget, 0.1f * (_movetospeed / 2));
			}
			else
			{
				_position += _normalized * _movetospeed;
			}
			if (_position.distance(_movetotarget) <= _movetospeed)
			{
				_position = _movetotarget;
				_movetospeed = 0;
				if (_movetocallback)
					_movetocallback();
			}
		}
		if (_scaletospeed)
		{
			D3DXVec2Lerp(&_scale, &_scale, &_scaletotarget, 0.1f * (_scaletospeed / 2));
			if (_scale.distance(_scaletotarget) <= 0.025f)
			{
				_scale = _scaletotarget;
				_scaletospeed = 0;
				if (_scaletocallback)
					_scaletocallback();
			}
		}
		if (_alphatospeed)
		{
			if (_color.a > _alphatotarget)
				_color.a -= _alphatospeed;
			else
				_color.a += _alphatospeed;
			if (fabs(_color.a - _alphatotarget) <= 0.05f)
			{
				_color.a = _alphatotarget;
				_alphatospeed = 0;
				if (_alphatocallback)
					_alphatocallback();
			}

		}
		if (_delay)
		{
			_delay -= Time::dt;
			if (_delay <= 0)
			{
				_delay = 0;
				_delaycallback();
			}
		}



		if (_texture)
		{
			_rect.left = _position.x - (_texture->_info.Width / 2.f);
			_rect.right = _position.x + (_texture->_info.Width / 2.f);
			_rect.top = _position.y - (_texture->_info.Height / 2.f);
			_rect.bottom = _position.y + (_texture->_info.Height / 2.f);
		}
	}

	void draw() override
	{
		Node::draw();

		if (!_texture)
			return;

		if (ani._run)
			ani.update();

	//	if (_parent->_color.a < 1.f)
	//		_color.a = _parent->_color.a;

		Director::_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		Director::_sprite->SetTransform(&getMatrix());
		D3DXVECTOR3 center = { _texture->_info.Width * _anchor.x,_texture->_info.Height * _anchor.y, 0 };
		Director::_sprite->Draw(_texture->_texture, nullptr, &center, nullptr, _color);
		Director::_sprite->End();
	}

};