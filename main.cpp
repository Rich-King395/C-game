#include"acllib.h"
#include"AutoSprite.h"
#include"AvoidSprite.h"
#include"UserSprite.h"
#include"ChaserSprite.h"
#include<time.h>
#include<stdio.h>
const int maxNum = 200;//精灵的最大数目
const int divider = 100;//改变用户精灵大小的分子
const int winWidth = 1500, winHeight = 1000;//游戏窗口的大小
AutoSprite* spirit[maxNum] = {0};//创建自由精灵的数组
UserSprite* seal =NULL;//用户精灵
int autoWidth = 100, autoHeight = 100;//自由精灵的大小
int usrWidth = 100, usrHeight = 100;//用户精灵的大小
ACL_Image img,imgtom,imgAvoid,imgChaser,imgBackground;
ACL_Sound sound;
rect winRect;
void timerEvent(int id);
void createData(AutoSprite** autosprite);
void createData(UserSprite** seal);
void keyEvent(int key, int event);
void BackgroundMusic(ACL_Sound* sound);
int nowNum = 0;//当前精灵的数目，全局变量
void paint();
char endScore[10];
int m=0;
int Setup()
{
	winRect.x = DEFAULT;
	winRect.y = DEFAULT;
	winRect.width = winWidth;
	winRect.height = winHeight;
	initWindow("spirit game", DEFAULT, DEFAULT, winWidth, winHeight);//创建游戏窗口
	srand((unsigned)time(NULL));//随机函数
	loadImage("sea.gif", &imgBackground);
	loadImage("fish.gif",&img);
	loadImage("seal.gif", &imgtom);
	loadImage("penguin.gif", &imgAvoid);
	loadImage("shark.gif", &imgChaser);//放入图片文件
	loadSound("bgm.mp3", &sound);//放入音乐文件

	
	BackgroundMusic(&sound);//开始循环播放背景音乐
	createData(spirit);//创建自由精灵（包括躲避精灵和追逐精灵）
	createData(&seal);//创建用户精灵
	registerTimerEvent(timerEvent);//自由精灵定时器
	registerKeyboardEvent(keyEvent);//用户精灵定时器
	startTimer(0, 40);//40毫秒触发一次，id=0
	startTimer(1, 1000);//1000毫秒触发一次,id=1
	return 0;//无限循环
}
void timerEvent(int id)
{
	int i = 0;
	switch(id)
	{
	case 0://每促发一次，移动一次用户精灵
		for(i=0;i<nowNum;i++)
		if (spirit[i]) 
		{
			int s = spirit[i]->getScore();
			int L = spirit[i]->getLife();
			rect ur = seal->getRect();//得到用户精灵的位置
			spirit[i]->move(ur);//自由精灵移动
			if (seal->collision(spirit[i]->getRect()))
			{
				delete(spirit[i]);
				spirit[i] = NULL;
				if (seal)seal->addLife(L);//获取每种自由精灵可以加的分数
				if (seal)seal->addScore(s);
			}//如果因为自由精灵的移动发生撞击，自由精灵会消失

		}
		break;
	case 1://每促发一次，创建一个自由精灵
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
	if (y < 0)y = 0;//随机生成自由精灵的位置
	int dx = rand() % 3 + 2;
	int dy = rand() % 3 + 2;//随机生成速度区间
	int t = rand() % 100;
    if (t < 80)
		autosprite[nowNum++] = new AutoSprite(x, y, autoWidth, autoHeight, dx, dy, &img, winRect,1,0);
	else if(t<95&&t>=80)
		autosprite[nowNum++] = new AvoidSprite(x, y, autoWidth, autoHeight, dx, dy, &imgAvoid, winRect,5,1);
	else
		autosprite[nowNum++] = new chaserSprite(x, y, 2*autoWidth, 1.5 * autoHeight, dx, dy, &imgChaser, winRect,-10,-5);//随机生成三种不同类型的自由精灵
}
void createData(UserSprite** seal)
{
	int x = rand() % winWidth - autoWidth;
	if (x < 0)x = 0;
	int y = rand() % winHeight - autoHeight;
	if (y < 0)y = 0;//随机生成用户精灵的位置
	int dx = rand() % 3+5;
	int dy = rand() % 3+5;//随机生成用户精灵的速度区间
	*seal = new UserSprite(x, y,usrWidth, usrHeight, dx, dy, &imgtom, winRect);//创建新的用户精灵实现用户精灵的移动

}
void paint()
{
	beginPaint();
	clearDevice();//绘图函数
	putImageScale(&imgBackground, 0, 0, winWidth, winHeight);//绘制背景图片
	int i;
	float large;
	for (int i = 0; i < nowNum; i++)
	{
		if (spirit[i])
		{
			spirit[i]->drawSpirit();//绘制自由精灵
		}

	}
	if(seal)
	{
	float Score = seal->getScore();
	large = 1 + Score / double(divider);
	if(large<2)
		seal->drawSpirit(large * double(usrWidth), large * double(usrHeight));
	else
		seal->drawSpirit(2 * double(usrWidth), 2 * double(usrHeight));//随着分数的增大，用户精灵会逐渐变大但不会超过两倍
	char txt1[10];
	char word1[20] = "Score:";
	sprintf_s(txt1, "%d", seal->getScore());
	setTextSize(20);
	paintText(10, 10, word1);
	paintText(100, 10, txt1);//绘制分数
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
			putImageScale(&imgBackground, 0, 0, winWidth, winHeight);//绘制背景图片
			setTextSize(50);
			char word3[100] = "Your final score:";
			paintText(500, 500, word3);
			paintText(1000, 500, endScore);//绘制分数
			nowNum = maxNum;
			endPaint();
			
	}
	else
	{
		paintText(10, 40, word2);
		paintText(100, 40, txt2);//绘制生命数
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
				if (seal)seal->addScore(s);//获取每种自由精灵可以加的分数
				int L = spirit[i]->getLife();
				if (seal)seal->addLife(L);//获取每种自由精灵可以加的生命
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