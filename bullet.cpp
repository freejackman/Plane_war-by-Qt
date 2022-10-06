#include "bullet.h"
#include "config.h"

bullet::bullet()     //子弹初始化
{
    bulletpix.load(BULLET1_PATH);

    bullet_x=0;
    bullet_y=0;

    rect.setWidth(BULLET_RECT_X);
    rect.setHeight(BULLET_RECT_Y);
    rect.moveTo(0,0);

    bullet_speed=BULLET_SPEESD;

    isfree=true;
}
