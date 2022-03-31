#include "SpriteBase.h"
SpriteBase::SpriteBase(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dx = dx;
	this->dy = dy;
	this->img = img;
	r = r1;
}
SpriteBase::SpriteBase(SpriteBase& spirit)
{
	x = spirit.x;
	y = spirit.y;
	width = spirit.width;
	height = spirit.height;
	dx = spirit.dx;
	dy = spirit.dy;
	img = spirit.img;
}
SpriteBase::~SpriteBase() 
{
}

void SpriteBase::drawSpirit(int width, int height)
{
	putImageScale(img, x, y, width, height);
}
void SpriteBase::drawSpirit()
{
	putImageScale(img, x, y, width, height);
}
rect SpriteBase::getRect() 
{
	rect r = { x, y, width, height };
	return r;
}
