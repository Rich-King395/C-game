#include "AvoidSprite.h"
#include<math.h>
#include"acllib.h"
AvoidSprite::AvoidSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign):AutoSprite(x,y,width,height,dx,dy,img,r1,score,sign)
{
	oldx = dx;
	oldy = dy;
	first = true;
}
AvoidSprite::AvoidSprite(AvoidSprite& sprite):AutoSprite(sprite)
{
	oldx = dx;
	oldy = dy;
	first = true;
}
void AvoidSprite::move(rect ur)
{
	if (mynear(ur))
	{
		if (x < ur.x) dx = -abs(dx);
		else dx = abs(dx);

		if (y < ur.y) dy = -abs(dy);
		else dy = abs(dy);

		x += 1.5 * dx;
		y += 1.5 * dy;
	}
	else
	{
		x += dx;
		y += dy;
	}

	if ((dx < 0) && (x < -width / 2)) x = r.width - width / 2;
	if ((dx > 0) && (x > (r.width - width / 2))) x = -width / 2;
	if ((dy < 0) && (y < -height / 2)) y = r.height - height / 2;
	if ((dy > 0) && (y > (r.height - height / 2))) y = -height / 2;

}
bool AvoidSprite::mynear(rect ur)
{
	int cx = (x + width) / 2;
	int cy = (y + height) / 2;
	int ux = (ur.x + ur.width) / 2;
	int uy = (ur.y + ur.height) / 2;
	float dist = sqrt((cx - ux) * (cx - ux) + (cy - uy) * (cy - uy));
	if (dist < 125)
		return true;
	else return false;
}
