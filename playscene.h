#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int levelNum);

    int levelIndex;

    // 重写paintEvent事件
    void paintEvent(QPaintEvent *);

    // 维护关卡信息
    int gameArray[4][4];
    MyCoin *coinBtn[4][4];

    // 胜利标志
    bool isWin = false;

signals:
    // 自定义信号
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
