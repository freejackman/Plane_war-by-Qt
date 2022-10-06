#include "widget.h"
#include"QIcon"
#include"config.h"
#include"plane.h"
#include"em_plane.h"
#include"bullet.h"
#include"mainwidget.h"
#include<QMouseEvent>
#include<Qlabel>
#include<QTimer>
#include<QPainter>
#include<QKeyEvent>
#include"QPushButton"
#include<QMediaPlayer>     //音乐播放器
#include<QMediaPlaylist>    //音乐列表


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(MAP_WIDE,MAP_HIGHT);   //固定窗口大小
    setWindowTitle("飞机大战(自制版)");   //设置窗口标题
    setWindowIcon(QIcon(SORTWARE_ICON));     //设置图标
    timer.setInterval(MAP_INTER);    //设置定时器
    maper=map();         //设置地图
    planer=plane();      //设置玩家飞机

    endbutton = new QPushButton;    //设置结束按钮
    endbutton->setParent(this);
    endbutton->setText("结束游戏");
    endbutton->move(BUTTON_X,BUTTON_Y);           //设置按钮位置
    endbutton->resize(BUTTON_WIDTH,BUTTON_HIGHT);  //设置按钮的宽高

    restartbutton = new QPushButton;    //设置重新开始按钮
    restartbutton->setParent(this);
    restartbutton->setText("重新开始");
    restartbutton->move(RESTARTBUTTON_X,RESTARTBUTTON_Y);           //设置按钮位置
    restartbutton->resize(RESTARTBUTTON_WIDTH,RESTARTBUTTON_HIGHT);  //设置按钮的宽高

    boom_music= new QMediaPlayer(this);         //爆炸音效初始化
    background= new QMediaPlayer(this);          //背景音乐初始化
    background_list= new QMediaPlaylist(this);      //音乐列表初始化
    background_list->addMedia(QUrl(BACKGROUND_MUSIC));  //为音乐列表添加音乐
    background_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);   //设置音乐列表中音乐循环播放
    background->setPlaylist(background_list);    //为背景音乐绑定音乐列表
    background->setVolume(BACKGROUND_MUSIC_VOLUME);                    //设置背景音乐音量
    boom_music->setMedia(QUrl(BOOM_MUSIC));      //设置爆炸音效
    boom_music->setVolume(BOOM_MUSIC_VOLUME);     //设置爆炸音效音量


    for(int i=0;i<PLANE2_AMOUNT;i++)        //设置敌机库
    {
        em_planer[i]=em_plane();
    }
    for(int i=0;i<BULLET_AMOUNT;i++)        //设置敌机子弹库
    {
       em_bull[i]=bullet();
       em_bull[i].bulletpix.load(BULLET2_PATH);
    }
    this->grabKeyboard();      //保证键盘事件监听正常
}

void Widget::update_map_y()
{
    maper.map1_y+=MAP_SPEED;      //地图图片1的位置向下移动2
    planer.shoot();

    if(maper.map1_y>MAP_HIGHT)     //位置重置条件
    {
        maper.map1_y=0;
    }
    maper.map2_y+=MAP_SPEED;     //地图图片2的位置向下移动2
    if(maper.map2_y>0)              //位置重置条件
    {
        maper.map2_y=-MAP_HIGHT;
    }
}

void Widget::playgame()
{
    background->play();    //背景音乐开始播放
    timer.start();  //开始计时
    //监听计时器
    //匿名函数
    connect(&timer,&QTimer::timeout,[=]{
        update_map_y();
        em_appear();
        update_em_plane();
        em_shoot();
        update_em_bullet();
        planer.shoot();
        update_bullet();
        collision_detection();
        this->update();         //手动触发绘图事件
    });
    //绑定按钮与槽
    connect(endbutton,&QPushButton::clicked,this,&Widget::close);
    connect(restartbutton,&QPushButton::clicked,this,&Widget::close);
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(0,maper.map1_y,maper.map1);
    painter.drawPixmap(0,maper.map2_y,maper.map2);

    //判断玩家飞机是否已经被击毁
    if(planer.sign>0&& planer.sign<BOOL_INVERT)
    {
        planer.sign++;
    }
    else if(planer.sign>BOOL_INVERT)      //通过爆炸间隔来确定击毁图像持续时间
    {
        planer.sign=0;
        timer.stop();      //停止计时
    }
    //显示当前玩家飞机的位置
    painter.drawPixmap(planer.plane_x,planer.plane_y,planer.planepix);


    for(int i=0;i<PLANE2_AMOUNT;i++)      //遍历所有敌机
    {
        if(em_planer[i].isfree)     //排除空闲敌机
        {
            continue;
        }

        //判断敌机是否已经被击毁
        if(em_planer[i].sign>0&& em_planer[i].sign<BOOL_INVERT)
        {
            em_planer[i].sign++;
        }
        else if(em_planer[i].sign>BOOL_INVERT)      //通过爆炸间隔来确定击毁图像持续时间
        {
            em_planer[i].sign=0;
            em_planer[i].em_planepix.load(PLANE2_PATH);
            em_planer[i].isfree=true;
        }

        painter.drawPixmap(em_planer[i].em_plane_x,em_planer[i].em_plane_y,em_planer[i].em_planepix);
    }
    for(int i=0;i<BULLET_AMOUNT;i++)        //遍历并显示玩家飞机所有非空闲的子弹
    {
        if(planer.bull[i].isfree)
        {
            continue;
        }
        painter.drawPixmap(planer.bull[i].bullet_x,planer.bull[i].bullet_y,planer.bull[i].bulletpix);
    }
    for(int i=0;i<PLANE2_BULLET;i++)       //遍历并显示敌机所有非空闲的子弹
    {
        if(em_bull[i].isfree)
        {
            continue;
        }
        painter.drawPixmap(em_bull[i].bullet_x,em_bull[i].bullet_y,em_bull[i].bulletpix);
    }
}

void Widget::keyPressEvent(QKeyEvent * ev)
{
    if(ev->key()==Qt::Key_Up)
    {
        planer.plane_y-=planer.plane_speed;    //将玩家飞机向上移动
        if(planer.plane_y<0)                    //边界检测
        {
            planer.plane_y=0;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_Down)
    {
        planer.plane_y+=planer.plane_speed;       //将玩家飞机向下移动
        if(planer.plane_y>MAP_HIGHT-PLANE_RECT_Y)      //边界检测
        {
            planer.plane_y=MAP_HIGHT-PLANE_RECT_Y;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_Left)
    {
        planer.plane_x-=planer.plane_speed;        //将玩家飞机向左移动
        if(planer.plane_x<0)            //边界检测
        {
            planer.plane_x=0;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_Right)
    {
        planer.plane_x+=planer.plane_speed;        //将玩家飞机向右移动
        if(planer.plane_x>MAP_WIDE-PLANE_RECT_X)    //边界检测
        {
            planer.plane_x=MAP_HIGHT-PLANE_RECT_X;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_W)
    {
        planer.plane_y-=planer.plane_speed;       //将玩家飞机向上移动
        if(planer.plane_y<0)                    //边界检测
        {
            planer.plane_y=0;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_S)
    {
        planer.plane_y+=planer.plane_speed;       //将玩家飞机向下移动
        if(planer.plane_y>MAP_HIGHT-PLANE_RECT_Y)      //边界检测
        {
            planer.plane_y=MAP_HIGHT-PLANE_RECT_Y;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_A)
    {
        planer.plane_x-=planer.plane_speed;       //将玩家飞机向左移动
        if(planer.plane_x<0)            //边界检测
        {
            planer.plane_x=0;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
    else if(ev->key()==Qt::Key_D)
    {
        planer.plane_x+=planer.plane_speed;       //将玩家飞机向右移动
        if(planer.plane_x>MAP_WIDE-PLANE_RECT_X)    //边界检测
        {
            planer.plane_x=MAP_HIGHT-PLANE_RECT_X;
        }
        planer.rect.moveTo(planer.plane_x,planer.plane_y);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *ev)
{

    int x=ev->x()-planer.rect.width()*0.5;          //获得当前鼠标点位并做好鼠标偏移
    int y=ev->y()-planer.rect.height()*0.5;

    //边界检测
    if(x<0)
    {
        x=0;
    }
    else if(x>MAP_WIDE-PLANE_RECT_X)
    {
        x=MAP_WIDE-PLANE_RECT_X;
    }
    if(y<0)
    {
        y=0;
    }
    else if(y>MAP_HIGHT-PLANE_RECT_Y)
    {
        y=MAP_HIGHT-PLANE_RECT_Y;
    }

    planer.plane_x=x;               //移动图像位置
    planer.plane_y=y;
    planer.rect.moveTo(x,y);
}

void Widget::update_bullet()
{
    for(int i=0;i<BULLET_AMOUNT;i++)
    {
        if(planer.bull[i].isfree)
        {
            continue;
        }
        planer.bull[i].bullet_y-=planer.bull[i].bullet_speed;    //子弹向上移动
        planer.bull[i].rect.moveTo(planer.bull[i].bullet_x,planer.bull[i].bullet_y);
        if(planer.bull[i].bullet_y<-BULLET_RECT_Y)              //边界检测
        {
            planer.bull[i].isfree=true;
        }
    }
}

void Widget::em_shoot()
{
    for(int i=0;i<PLANE2_AMOUNT;i++)
    {
        if(em_planer[i].isfree)
        {
            continue;
        }
        else
        {
            //找到空闲的飞机,并按照子弹发射的时间间隔发射子弹
            em_planer[i].inverts++;
            if(em_planer[i].inverts<PLANE2_BULLET_INVERT)
            {
                continue;
            }
            em_planer[i].inverts=0;
            for(int j=0;j<PLANE2_BULLET;j++)
            {
                if(em_bull[j].isfree)           //每次只发射一颗非空闲的子弹
                {
                    em_bull[j].bullet_x=em_planer[i].em_plane_x+PLANE2_RECT_X/2;
                    em_bull[j].bullet_y=em_planer[i].em_plane_y+PLANE2_RECT_Y;
                    em_bull[j].rect.moveTo(em_bull[j].bullet_x,em_bull[j].bullet_y);
                    em_bull[j].isfree=false;         //非空闲代表已经发射
                    break;
                }
            }

        }
    }
}

void Widget::em_appear()
{
    em_invert++;
    if(em_invert<PLANE2_INVERT)
    {
        return;
    }
    em_invert=0;     //控制敌机出现的时间

    for(int i=0;i<PLANE2_AMOUNT;i++)
    {
        if(em_planer[i].isfree)
        {
            em_planer[i].em_plane_x=rand()%(MAP_WIDE-PLANE2_RECT_X);       //敌机出现位置是随机的
            em_planer[i].em_plane_y=-PLANE2_RECT_Y;
            em_planer[i].rect.moveTo(em_planer[i].em_plane_x,em_planer[i].em_plane_y);
            em_planer[i].isfree=false;
            break;
        }
    }
}

void Widget::update_em_bullet()
{
    for(int i=0;i<PLANE2_BULLET;i++)
    {
        if(em_bull[i].isfree)
        {
            continue;
        }
        em_bull[i].bullet_y+=em_bull[i].bullet_speed;    //子弹向下移动
        em_bull[i].rect.moveTo(em_bull[i].bullet_x,em_bull[i].bullet_y);
        if(em_bull[i].bullet_y>MAP_HIGHT)     //边界检测
        {
            em_bull[i].isfree=true;
        }
    }
}

void Widget::update_em_plane()
{
    for(int i=0;i<PLANE2_AMOUNT;i++)
    {
        if(em_planer[i].isfree)
        {
            continue;
        }
        em_planer[i].em_plane_y+=em_planer[i].em_plane_speed;    //敌机向下移动
        em_planer[i].rect.moveTo(em_planer[i].em_plane_x,em_planer[i].em_plane_y);
        if(em_planer[i].em_plane_y>MAP_HIGHT)    //边界检测
        {
            em_planer[i].isfree=true;
        }
    }
}

void Widget::collision_detection()
{
    for(int i=0;i<PLANE2_AMOUNT;i++)     //遍历所有敌机
    {
        if(em_planer[i].isfree)    //判断敌机是否空闲
        {
            continue;
        }

        //判断是否有未被击毁的敌机与玩家飞机相撞
        if(em_planer[i].sign==0&&em_planer[i].rect.intersects(planer.rect))
        {
            boom_music->play();        //爆炸音效开始播放
            em_planer[i].sign++;
            planer.sign++;
            return;
        }


        for(int j=0;j<BULLET_AMOUNT;j++)    //遍历玩家飞机的所有子弹
        {
            if(planer.bull[j].isfree)   //判断玩家飞机的子弹是否空闲
            {
                continue;
            }

            //判断每个非空闲的敌机的碰撞矩阵是否与玩家飞机的每颗非空闲子弹的碰撞矩阵相交
            if(em_planer[i].rect.intersects(planer.bull[j].rect))
            {
                boom_music->play();        //爆炸音效开始播放
                planer.bull[j].isfree=true;
                em_planer[i].sign++;
                em_planer[i].em_planepix.load(PLANE2_PATH2);
                return;
            }
        }
    }


    for(int i=0;i<PLANE2_BULLET;i++)                          //遍历敌机的所有子弹
    {
        if(em_bull[i].isfree)       //排除空闲的敌机子弹
        {
            continue;
        }

        //判断每个非空闲的敌机的子弹的碰撞矩阵是否与玩家飞机的碰撞矩阵相交
        if(planer.rect.intersects(em_bull[i].rect))
        {
            boom_music->play();        //爆炸音效开始播放
            em_bull[i].isfree=true;
            planer.sign++;
            planer.planepix.load(PLANE_PATH2);
        }
    }
}

Widget::~Widget()
{
    delete background_list;
    delete background;
    delete endbutton;
    delete boom_music;
    delete restartbutton;
}
