#pragma once
#include "SpriteBase.h"
class AutoSprite :
    public SpriteBase
{
    int sign;//������������
    int score;//�ӵķ���
public:
    AutoSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1,int score,int sign);
    AutoSprite(AutoSprite& sprite);
    ~AutoSprite() ;

    void move(rect r);//ͼƬ�ƶ�
    int getScore();//���ص÷�
    int getLife();//����������
};

