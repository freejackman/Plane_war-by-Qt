#ifndef MAP_H
#define MAP_H
#include<QPixmap>

class map
{
    public:
        map();
    public:
        QPixmap map1;   //地图图片1
        QPixmap map2;   //地图图片2

        int map1_y;     //地图图片1的y坐标
        int map2_y;     //地图图片2的y坐标

        int map_speed;  //地图滚动速度
};

#endif // MAP_H
