#ifndef BULLET_H
#define BULLET_H

#include<QPixmap>

class bullet
{
    public:
        bullet();
    public:

        QPixmap bulletpix;   //子弹的图像

        int bullet_x;       //子弹坐标
        int bullet_y;

        QRect rect;        //子弹碰撞矩阵

        int bullet_speed;    //子弹速度

        bool isfree;         //子弹是否空闲
};

#endif // BULLET_H
