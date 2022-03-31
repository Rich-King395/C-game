#pragma once
#include"acllib.h"
class SpriteBase
{
protected:
	int x, y;//图片中心在游戏界面的位置
	int width, height;//图片的高度和宽度
	int dx, dy;//横纵坐标位置的变化
	ACL_Image* img;//图片参数
	rect r;//结构体r包含游戏界面的大小，位置参数
public:
	SpriteBase(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r);//构造函数
	SpriteBase(SpriteBase& spirit);//复制构造函数
	virtual ~SpriteBase();//析构函数

	virtual void move(rect r) = 0;
	void drawSpirit(int width, int height);//
	void drawSpirit();
	rect getRect();

};

