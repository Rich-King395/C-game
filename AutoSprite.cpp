#include "AutoSprite.h"
AutoSprite::AutoSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign) :SpriteBase(x, y, width, height, dx, dy, img, r1)
{
	this->score = score;
	this->sign = sign;
}
AutoSprite::AutoSprite(AutoSprite& sprite) : SpriteBase(sprite)
{
	score = sprite.score;
}
AutoSprite::~AutoSprite()
{
}
void AutoSprite::move(rect r1)
{
	if (x<0 || x>(r.width - width))dx *= -1;//当x轴方向图片超过界面边界时，速度方向
	if (y<0 || y>(r.height - height))dy *= -1;//当y轴方向图片超过界面边界时，速度方向
	x += dx;//x方向位置变化
	y += dy;//y方向位置变化
}
int AutoSprite::getScore()
{
	return score;
}
int AutoSprite::getLife()
{
	return sign;
}
