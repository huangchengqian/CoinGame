#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>
#include "chooselevelscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 配置主场景

    // 设置固定大小
    setFixedSize(320, 588);
    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    // 设置标题
    setWindowTitle("翻金币");
    // 退出按钮
    connect(ui->actionQuit, &QAction::triggered, [=]() {
        this->close();
    });

    // 开始音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav", this);

    // 开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    // 实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    // 监听选择关卡返回按钮信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this,[=]() {
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=]() {
        // 播放音效
        startSound->play();
        qDebug() << "开始";
        startBtn->zoom1();
        startBtn->zoom2();
        // 延时进入选择关卡场景
        QTimer::singleShot(500,this,[=]{
            // 设置下一个场景位置
            chooseScene->setGeometry(this->geometry());
            // 自身隐藏
            this->hide();
            // 进入选择关卡场景
            chooseScene->show();
        });

    });

}

void MainScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // icon
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);

}


MainScene::~MainScene()
{
    delete ui;
}

