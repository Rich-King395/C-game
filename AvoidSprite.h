#pragma once
#include "AutoSprite.h"
#include"acllib.h"
class AvoidSprite :
    public AutoSprite
{
    int oldx, oldy;
    bool mynear(rect ur);
    bool first;
public:
    AvoidSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign);
    AvoidSprite(AvoidSprite& sprite);
    virtual ~AvoidSprite() {};
    void move(rect ur);
};

