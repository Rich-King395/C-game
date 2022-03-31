#include "chaserSprite.h"
#include "AvoidSprite.h"
#include<math.h>
#include"acllib.h"
chaserSprite::chaserSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1, int score,int sign) :AutoSprite(x, y, width, height, dx, dy, img, r1, score,sign)
{
	oldx = dx;
	oldy = dy;
	first = true;
}//追逐精灵的构造函数
chaserSprite::chaserSprite(chaserSprite& sprite) :AutoSprite(sprite)
{
	oldx = dx;
	oldy = dy;
	first = true;
}//追逐精灵的复制函数
void chaserSprite::move(rect ur)
{
	if (mynear(ur))
	{
		
		if (x < ur.x) dx = abs(dx);
		else if (x == ur.x)
			dx = 0;
		else dx = -abs(dx);

		if (y < ur.y) dy = abs(dy);
		else if (y == ur.y)
			dy = 0;
		else dy = -abs(dy);

		x += 2 * dx;
		y += 2 * dy;
	}
	else
	{
		x += dx;
		y += dy;
	}

	if ((dx < 0) && (x < -width / 2)) x = r.width - width / 2;
	if ((dx > 0) && (x > (r.width - width / 2))) x = -width / 2;
	if ((dy < 0) && (y < -height / 2)) y = r.height - height / 2;
	if ((dy > 0) && (y > (r.height - height / 2))) y = -height / 2;//让追逐精灵与墙碰撞后从另一面墙出现


}
bool chaserSprite::mynear(rect ur)
{
	int cx = (x + width) / 2;
	int cy = (y + height) / 2;//追逐精灵的中心点位置
	int ux = (ur.x + ur.width) / 2;
	int uy = (ur.y + ur.height) / 2;//用户精灵的中心点位置
	float dist = sqrt((cx - ux) * (cx - ux) + (cy - uy) * (cy - uy));
	if (dist < 250)
		return true;
	else return false;
}//判断追逐精灵与用户精灵的距离