#ifndef CONFIG_H
#define CONFIG_H

//========窗口配置=====
#define MAP_HIGHT  700     //窗口高
#define MAP_WIDE   480     //窗口宽
#define MAP_PATH   ":/image/background.png"   //游戏地图
#define MAP_SPEED  2       //地图滚动速度
#define MAP_INTER  10      //地图帧率

//=====玩家飞机配置======
#define PLANE_PATH ":/image/me1.png"   //玩家飞机正常图像
#define PLANE_PATH2 ":/image/me_destroy_1.png"  //玩家飞机毁坏图像
#define PLANE_SPEED 3      //玩家飞机移动速度
#define PLANE_RECT_X 102    //玩家飞机图像宽
#define PLANE_RECT_Y 126    //玩家飞机图像高

//=====敌机配置=======
#define PLANE2_PATH    ":/image/enemy1.png"   //敌机正常图像
#define PLANE2_PATH2    ":/image/enemy1_down1.png"   //敌机毁坏图像
#define PLANE2_SPEED 2      //敌机移动速度
#define PLANE2_RECT_X 57    //敌机图像宽
#define PLANE2_RECT_Y 43    //敌机图像高
#define PLANE2_INVERT  100  //敌机出场的时间间隔
#define PLANE2_AMOUNT  20   //敌机的数量

//=======子弹及爆炸配置===
#define BULLET1_PATH  ":/image/bullet1.png"     //玩家飞机子弹图像
#define BULLET2_PATH  ":/image/bullet2.png"     //敌机子弹图像
#define BULLET_RECT_X 5     //子弹图像宽
#define BULLET_RECT_Y 11    //子弹图像高
#define BULLET_SPEESD  5    //子弹速度
#define BULLET_AMOUNT  30   //玩家飞机子弹数量
#define BULLET_INVERT  40   //玩家子弹发射时间间隔
#define PLANE2_BULLET  100    //敌机子弹数量
#define PLANE2_BULLET_INVERT 80  //敌机子弹发射时间间隔
#define BOOL_INVERT    15   //爆炸图像的持续时间

//======音效配置=======
#define BACKGROUND_MUSIC "qrc:/image/background.wav"   //背景音乐
#define BOOM_MUSIC     "qrc:/image/boom.wav"          //爆炸音效
#define BACKGROUND_MUSIC_VOLUME  50          //背景音乐音量
#define BOOM_MUSIC_VOLUME   30            //爆炸音效音量

//======图标配置=======
#define SORTWARE_ICON ":/image/pl.ico"      //软件图标
#define TITLE   ":/image/title.png"      //软件封面

//=====按钮配置========
#define BUTTON_X  370        //结束按钮位置的x坐标
#define BUTTON_Y  10        //结束按钮位置的y坐标
#define BUTTON_HIGHT 50    //结束按钮的高度
#define BUTTON_WIDTH 100    //结束按钮的宽度
#define STARTBUTTON_X  90        //开始游戏按钮位置的x坐标
#define STARTBUTTON_Y  500        //开始游戏按钮位置的y坐标
#define STARTBUTTON_HIGHT 50    //开始游戏按钮的高度
#define STARTBUTTON_WIDTH 300    //开始游戏按钮的宽度
#define RESTARTBUTTON_X  10        //重新开始按钮位置的x坐标
#define RESTARTBUTTON_Y  10        //重新开始按钮位置的y坐标
#define RESTARTBUTTON_HIGHT 50    //重新开始按钮的高度
#define RESTARTBUTTON_WIDTH 100    //重新开始按钮的宽度

#endif // CONFIG_H
