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
	if (x<0 || x>(r.width - width))dx *= -1;//��x�᷽��ͼƬ��������߽�ʱ���ٶȷ���
	if (y<0 || y>(r.height - height))dy *= -1;//��y�᷽��ͼƬ��������߽�ʱ���ٶȷ���
	x += dx;//x����λ�ñ仯
	y += dy;//y����λ�ñ仯
}
int AutoSprite::getScore()
{
	return score;
}
int AutoSprite::getLife()
{
	return sign;
}
