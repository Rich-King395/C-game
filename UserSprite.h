#pragma once
#include "SpriteBase.h"
class UserSprite :public SpriteBase
{
    int score;//��¼�÷�
    int life;//��¼�ۻ�������
public:
    UserSprite(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r1);//���캯��
    UserSprite(UserSprite& sprite);
    ~UserSprite();//��������

    void move(int x, int y);//�ƶ�
    void move(int key);//�����ƶ�
    void move(rect r);
    int collision(rect r1);//�ж��û����������������ײ
    int getScore();//���ص÷�
    int getLife();//��������
    void setScore(int s);//���õ÷�
    void setLife(int s);//��������
    void addScore(int m);//�ӷ�
    void addLife(int m);//������
};

