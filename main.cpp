#include"acllib.h"
#include"AutoSprite.h"
#include"AvoidSprite.h"
#include"UserSprite.h"
#include"ChaserSprite.h"
#include<time.h>
#include<stdio.h>
const int maxNum = 200;//����������Ŀ
const int divider = 100;//�ı��û������С�ķ���
const int winWidth = 1500, winHeight = 1000;//��Ϸ���ڵĴ�С
AutoSprite* spirit[maxNum] = {0};//�������ɾ��������
UserSprite* seal =NULL;//�û�����
int autoWidth = 100, autoHeight = 100;//���ɾ���Ĵ�С
int usrWidth = 100, usrHeight = 100;//�û�����Ĵ�С
ACL_Image img,imgtom,imgAvoid,imgChaser,imgBackground;
ACL_Sound sound;
rect winRect;
void timerEvent(int id);
void createData(AutoSprite** autosprite);
void createData(UserSprite** seal);
void keyEvent(int key, int event);
void BackgroundMusic(ACL_Sound* sound);
int nowNum = 0;//��ǰ�������Ŀ��ȫ�ֱ���
void paint();
char endScore[10];
int m=0;
int Setup()
{
	winRect.x = DEFAULT;
	winRect.y = DEFAULT;
	winRect.width = winWidth;
	winRect.height = winHeight;
	initWindow("spirit game", DEFAULT, DEFAULT, winWidth, winHeight);//������Ϸ����
	srand((unsigned)time(NULL));//�������
	loadImage("sea.gif", &imgBackground);
	loadImage("fish.gif",&img);
	loadImage("seal.gif", &imgtom);
	loadImage("penguin.gif", &imgAvoid);
	loadImage("shark.gif", &imgChaser);//����ͼƬ�ļ�
	loadSound("bgm.mp3", &sound);//���������ļ�

	
	BackgroundMusic(&sound);//��ʼѭ�����ű�������
	createData(spirit);//�������ɾ��飨������ܾ����׷���飩
	createData(&seal);//�����û�����
	registerTimerEvent(timerEvent);//���ɾ��鶨ʱ��
	registerKeyboardEvent(keyEvent);//�û����鶨ʱ��
	startTimer(0, 40);//40���봥��һ�Σ�id=0
	startTimer(1, 1000);//1000���봥��һ��,id=1
	return 0;//����ѭ��
}
void timerEvent(int id)
{
	int i = 0;
	switch(id)
	{
	case 0://ÿ�ٷ�һ�Σ��ƶ�һ���û�����
		for(i=0;i<nowNum;i++)
		if (spirit[i]) 
		{
			int s = spirit[i]->getScore();
			int L = spirit[i]->getLife();
			rect ur = seal->getRect();//�õ��û������λ��
			spirit[i]->move(ur);//���ɾ����ƶ�
			if (seal->collision(spirit[i]->getRect()))
			{
				delete(spirit[i]);
				spirit[i] = NULL;
				if (seal)seal->addLife(L);//��ȡÿ�����ɾ�����Լӵķ���
				if (seal)seal->addScore(s);
			}//�����Ϊ���ɾ�����ƶ�����ײ�������ɾ������ʧ

		}
		break;
	case 1://ÿ�ٷ�һ�Σ�����һ�����ɾ���
		if (nowNum < maxNum)
		{
			createData(spirit);
		}

		break;
	}
	paint();
}
void createData(AutoSprite** autosprite)
{
	int x = rand() % winWidth - autoWidth;
	if (x < 0)x = 0;
	int y = rand() % winHeight - autoHeight;
	if (y < 0)y = 0;//����������ɾ����λ��
	int dx = rand() % 3 + 2;
	int dy = rand() % 3 + 2;//��������ٶ�����
	int t = rand() % 100;
    if (t < 80)
		autosprite[nowNum++] = new AutoSprite(x, y, autoWidth, autoHeight, dx, dy, &img, winRect,1,0);
	else if(t<95&&t>=80)
		autosprite[nowNum++] = new AvoidSprite(x, y, autoWidth, autoHeight, dx, dy, &imgAvoid, winRect,5,1);
	else
		autosprite[nowNum++] = new chaserSprite(x, y, 2*autoWidth, 1.5 * autoHeight, dx, dy, &imgChaser, winRect,-10,-5);//����������ֲ�ͬ���͵����ɾ���
}
void createData(UserSprite** seal)
{
	int x = rand() % winWidth - autoWidth;
	if (x < 0)x = 0;
	int y = rand() % winHeight - autoHeight;
	if (y < 0)y = 0;//��������û������λ��
	int dx = rand() % 3+5;
	int dy = rand() % 3+5;//��������û�������ٶ�����
	*seal = new UserSprite(x, y,usrWidth, usrHeight, dx, dy, &imgtom, winRect);//�����µ��û�����ʵ���û�������ƶ�

}
void paint()
{
	beginPaint();
	clearDevice();//��ͼ����
	putImageScale(&imgBackground, 0, 0, winWidth, winHeight);//���Ʊ���ͼƬ
	int i;
	float large;
	for (int i = 0; i < nowNum; i++)
	{
		if (spirit[i])
		{
			spirit[i]->drawSpirit();//�������ɾ���
		}

	}
	if(seal)
	{
	float Score = seal->getScore();
	large = 1 + Score / double(divider);
	if(large<2)
		seal->drawSpirit(large * double(usrWidth), large * double(usrHeight));
	else
		seal->drawSpirit(2 * double(usrWidth), 2 * double(usrHeight));//���ŷ����������û�������𽥱�󵫲��ᳬ������
	char txt1[10];
	char word1[20] = "Score:";
	sprintf_s(txt1, "%d", seal->getScore());
	setTextSize(20);
	paintText(10, 10, word1);
	paintText(100, 10, txt1);//���Ʒ���
	char txt2[10];
	char word2[20] = "life:";
	sprintf_s(txt2, "%d", seal->getLife());
	setTextSize(20);
	if (seal->getLife() < 0)
	{
			endPaint();
			beginPaint();
			clearDevice();
			sprintf_s(endScore, "%d", seal->getScore());
			clearDevice();
			putImageScale(&imgBackground, 0, 0, winWidth, winHeight);//���Ʊ���ͼƬ
			setTextSize(50);
			char word3[100] = "Your final score:";
			paintText(500, 500, word3);
			paintText(1000, 500, endScore);//���Ʒ���
			nowNum = maxNum;
			endPaint();
			
	}
	else
	{
		paintText(10, 40, word2);
		paintText(100, 40, txt2);//����������
	}
	}
	endPaint();
}
void keyEvent(int key, int event)
{
	if (event != KEY_DOWN)return;
	if (seal)seal->move(key);
	for (int i = 0; i < nowNum; i++)
	{
		if (spirit[i])
		{
			if (seal->collision(spirit[i]->getRect()))
			{

				int s = spirit[i]->getScore();
				if (seal)seal->addScore(s);//��ȡÿ�����ɾ�����Լӵķ���
				int L = spirit[i]->getLife();
				if (seal)seal->addLife(L);//��ȡÿ�����ɾ�����Լӵ�����
				delete(spirit[i]);
				spirit[i] = NULL;
			}
		}
	}
	paint();

}
void BackgroundMusic(ACL_Sound* sound)
{
	playSound(*sound, 1);
}