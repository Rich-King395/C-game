#pragma once
#include "SpriteBase.h"
class AutoSprite :
    public SpriteBase
{
    int sign;//加生命的条数
    int score;//加的分数
public:
    AutoSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign);
    AutoSprite(AutoSprite& sprite);
    ~AutoSprite() ;

    void move(rect r);//图片移动
    int getScore();//返回得分
    int getLife();//返回生命数
};

