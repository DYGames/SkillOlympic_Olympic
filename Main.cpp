#include "DXUT.h"
#include "Main.h"

void Main::init()
{
	mciSendString(L"open video.wmv type MPEGvideo alias aslias", NULL, NULL, NULL);
	mciSendString(L"play aslias", NULL, NULL, NULL);
}

void Main::update()
{
	Node::update();

}

void Main::exit()
{

	mciSendString(L"close aslias", NULL, NULL, NULL); 
	for (auto it : _children)
		removeChild(it);
}