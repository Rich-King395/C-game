#include "UserSprite.h"
UserSprite::UserSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1):SpriteBase(x, y, width, height, dx, dy, img, r1){}
UserSprite::UserSprite(UserSprite& sprite): SpriteBase(sprite){}
UserSprite::~UserSprite(){}

void UserSprite::move(int xx, int yy)
{
	this->x = xx;
	this->y = yy;
	if (x < r.x)x = r.x;
	if (x > (r.x + r.width - width))x = r.x + r.width - width;
	if (y < r.y)y = r.y;
	if (y > (r.y + r.height - height))y = r.y + r.height - height;
}
void UserSprite::move(int key)
{
	switch (key)
	{
	case VK_UP:
		y -= 3 * dy;//�����ƶ�
		if (y < r.y)y = r.y;//���������߽�ʱ�����ƶ�
		break;
	case VK_DOWN:
		y += 3 * dy;//�����ƶ�
		if (y > (r.y + r.height - height))y = r.y + r.height - height;//���������߽�ʱ�����ƶ�
		break;
	case VK_LEFT:
		x -= 3 * dx;//�����ƶ�
		if (x < r.x)x = r.x;//���������߽�ʱ�����ƶ�
		break;
	case VK_RIGHT:
		x += 3 * dx;//�����ƶ�
		if (x > (r.x + r.width - width))x = r.x + r.width - width;//���������߽�ʱ�����ƶ�
		break;

	}
}
int UserSprite::collision(rect r2)
{
	rect r1 = { x,y, width, height };//�û������x���꣬y���꣬�߶ȣ����
	int a = 1;//��־λ��ʼ��Ϊ1
	if (r1.x < r2.x && r1.x + r1.width >r2.x) {
		if (r1.y > r2.y && r1.y < r2.y + r2.height)return a;
		if (r1.y <r2.y && r1.y + r1.height >r2.y)return a;
	}
	else {
		if (r1.x > r2.x && r2.x + r2.width > r1.x)
		{
			if (r1.y > r2.y && r1.y < r2.y + r2.height)return a;
			if (r1.y <r2.y && r1.y + r1.height >r2.y)return a;
		}
	}
	a = 0;//��־λΪ0��û����ײ
	return a;
}
int UserSprite::getScore()
{
	return score;
}
void UserSprite::setScore(int s)
{
	score = s;
}
void UserSprite::addScore(int m)
{
	score += m;
}
int UserSprite::getLife()
{
	return life;
}
void UserSprite::setLife(int s)
{
	life = s;
}
void UserSprite::addLife(int m)
{
	life += m;
}
void UserSprite::move(rect r1)
{
	x = r1.x;
	y = r1.y;
	if (x < r.x)x = r.x;
	if (x > (r.x + r.width - width))x = r.x + r.width - width;
	if (y < r.y)y = r.y;
	if (y > (r.y + r.height - height))y = r.y + r.height - height;

}