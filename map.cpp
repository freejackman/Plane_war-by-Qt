#include "map.h"
#include"config.h"

map::map()     //地图初始化
{
    map1.load(MAP_PATH);
    map2.load(MAP_PATH);
    map_speed=MAP_SPEED;
    map1_y=0;
    map2_y=-MAP_HIGHT;
}


