#pragma once
#include"acllib.h"
class SpriteBase
{
protected:
	int x, y;//ͼƬ��������Ϸ�����λ��
	int width, height;//ͼƬ�ĸ߶ȺͿ��
	int dx, dy;//��������λ�õı仯
	ACL_Image* img;//ͼƬ����
	rect r;//�ṹ��r������Ϸ����Ĵ�С��λ�ò���
public:
	SpriteBase(int x, int y, int width, int height, int dx, int dy, ACL_Image* img, rect r);//���캯��
	SpriteBase(SpriteBase& spirit);//���ƹ��캯��
	virtual ~SpriteBase();//��������

	virtual void move(rect r) = 0;
	void drawSpirit(int width, int height);//
	void drawSpirit();
	rect getRect();

};

