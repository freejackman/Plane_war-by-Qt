#include "em_plane.h"

em_plane::em_plane()   //每个敌机初始化
{
    em_planepix.load(PLANE2_PATH);
    em_plane_y=0;
    em_plane_x=0;
    rect.setWidth(PLANE2_RECT_X);
    rect.setHeight(PLANE2_RECT_Y);
    rect.moveTo(0,0);
    em_plane_speed=PLANE2_SPEED;
    inverts=0;
    sign=0;
    isfree=true;
}

