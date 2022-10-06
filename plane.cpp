#include "plane.h"
#include"config.h"
#include"bullet.h"

plane::plane()   //玩家飞机初始化
{
    planepix.load(PLANE_PATH);
    plane_y=MAP_HIGHT-PLANE_RECT_Y-10;
    plane_x=(MAP_WIDE-PLANE_RECT_X)/2;
    rect.setWidth(PLANE_RECT_X);
    rect.setHeight(PLANE_RECT_Y);
    rect.moveTo(plane_x,plane_y);
    plane_speed=PLANE_SPEED;
    sign=0;               //爆炸标志位初始化

    invert=0;               //每个子弹发射时间间隔初始化

    for(int i=0;i<BULLET_AMOUNT;i++)   //子弹库里每个子弹的初始化
    {
        bull[i]=bullet();
    }
}

void plane::shoot()
{
    invert++;       //控制发射子弹的时间间隔
    if(invert<BULLET_INVERT)
    {
        return;
    }
    invert=0;
    for(int i=0;i<BULLET_AMOUNT;i++)    //遍历玩家子弹库中的所有子弹
    {
        if(bull[i].isfree)         //将要发射空闲的子弹位置改在玩家飞机前方，并发射
        {
            if(invert==0)             //判断子弹从玩家飞机哪一边发射
            {
                bull[i].bullet_x=plane_x+(PLANE_RECT_X-BULLET_RECT_X)/2-36;
                bull[i].bullet_y=plane_y+BULLET_RECT_Y;
                bull[i].rect.moveTo(bull[i].bullet_x,bull[i].bullet_y);

                bull[i].isfree=false;         //非空闲代表已经发射
                invert++;
            }
            else if(invert==1)
            {
                bull[i].bullet_x=plane_x+(PLANE_RECT_X-BULLET_RECT_X)/2+34;
                bull[i].bullet_y=plane_y+BULLET_RECT_Y;
                bull[i].rect.moveTo(bull[i].bullet_x,bull[i].bullet_y);
                bull[i].isfree=false;         //非空闲代表已经发射
                invert++;
            }
            else
            {
                invert=0;
                break;               //每次飞机两边各自发射一颗子弹
            }
        }
    }
}

plane::~plane()
{

}
