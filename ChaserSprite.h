#pragma once
#include "AutoSprite.h"
class chaserSprite :
    public AutoSprite
{
    int oldx, oldy;//
    bool mynear(rect ur);//�ж����û������Ƿ���׷�����
    bool first;
public:
   chaserSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign);
   chaserSprite(chaserSprite& sprite);
    virtual ~chaserSprite() {};
    void move(rect ur);

};

