#pragma once
#include "SpriteBase.h"
class UserSprite :public SpriteBase
{
    int score;//记录得分
    int life;//记录累积生命数
public:
    UserSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1);//构造函数
    UserSprite(UserSprite& sprite);
    ~UserSprite();//析构函数

    void move(int x, int y);//移动
    void move(int key);//键盘移动
    void move(rect r);
    int collision(rect r1);//判断用户精灵和其他精灵碰撞
    int getScore();//返回得分
    int getLife();//返回生命
    void setScore(int s);//设置得分
    void setLife(int s);//设置生命
    void addScore(int m);//加分
    void addLife(int m);//加生命
};

