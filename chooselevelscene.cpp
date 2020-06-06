#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include "mypushbutton.h"
#include "mainscene.h"
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    // 配置基础信息
    this->setFixedSize(320, 588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡");

    // 创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    // 创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    // 创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    // 点击退出
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    QSound * chooseLevelSound = new QSound(":/res/TapButtonSound.wav", this);
    QSound * backSound = new QSound(":/res/BackButtonSound.wav", this);

    // 返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        qDebug() << "返回";
        this->hide();
        // 告诉主场景 返回 主场景监听
        // 延时进入选择关卡场景
        QTimer::singleShot(200,this,[=]{
            backSound->play();
            emit this->chooseSceneBack();
        });

    });

    // 创建选择关卡按钮
    gates = 20;
    for (int i = 0; i < gates; i++) {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i % 4 * 70 + 25, i / 4 * 70 + 130);

        // 监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=]() {
            chooseLevelSound->play();
            QString str = QString("已选择第 %1 关").arg(i + 1);
            qDebug() << str;

            // 进入游戏场景
            this->hide();
            playScene = new PlayScene(i + 1);
            // 设置位置一致
            playScene->setGeometry(this->geometry());
            playScene->show();

            // 监听游戏场景返回按钮
            connect(playScene, &PlayScene::chooseSceneBack, [=]() {
                this->setGeometry(playScene->geometry());
                this->show();
                delete playScene;
                playScene = NULL;
            });

        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(i % 4 * 70 + 25, i / 4 * 70 + 130);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // 设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    // background
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // icon
    pix.load(":/res/Title.png");
    //pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}
