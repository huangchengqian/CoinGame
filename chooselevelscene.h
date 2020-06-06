#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QWidget>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    // 重写绘图事件
    void paintEvent(QPaintEvent *);

    // 游戏场景对象指针
    PlayScene * playScene = NULL;

    // 关卡数
    int gates = 0;

signals:
    // 自定义信号
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
