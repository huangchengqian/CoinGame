#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "mypushbutton.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    // 初始化
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle(QString("第 %1 关").arg(levelIndex));

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

    QSound * backSound = new QSound(":/res/BackButtonSound.wav", this);
    QSound * coinSound = new QSound(":/res/ConFlipSound.wav", this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav", this);

    // 返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        backSound->play();
        qDebug() << "返回";
        this->hide();
        // 告诉选择等级场景 返回 选择等级场景监听
        // 延时进入选择关卡场景
        QTimer::singleShot(200,this,[=]{
            emit this->chooseSceneBack();
        });

    });

    // 显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华光行楷_CNKI");
    font.setPointSize(18);
    QString levelSign = QString("Level: %1 ").arg(this->levelIndex);
    label->setFont(font);
    label->setText(levelSign);
    label->setGeometry(30, this->height() - 50, 120, 50);

    //关卡信息初始化
    dataConfig config;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    // 胜利图片
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move(this->width() - tmpPix.width() * 0.5 - 158, -tmpPix.height());

    // 显示金币背景图案
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            QLabel * label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            // 创建金币
            QString co;
            if (gameArray[i][j] == 1){
                co = ":/res/Coin0001.png";
            }
            else {
                co = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(co);
            coin->setParent(this);
            coin->move(59 + i * 50, 204 + j * 50);

            // 给金币属性赋值
            coin->posx = i;
            coin->posy = j;
            coin->flag = gameArray[i][j];

            // 将金币放入 金币二维数组，便于后期维护
            coinBtn[i][j] = coin;

            // 点击金币
            connect(coin, &MyCoin::clicked, [=]() {
                coinSound->play();
                // 禁用其他金币按钮
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                // 反转周围
                QTimer::singleShot(300, this, [=]() {
                    if (coin->posx + 1 <= 3) {
                        coinBtn[coin->posx + 1][coin->posy]->changeFlag();
                        this->gameArray[coin->posx + 1][coin->posy] = this->gameArray[coin->posx + 1][coin->posy] == 0 ? 1 : 0;
                    }
                    if (coin->posx - 1 >= 0) {
                        coinBtn[coin->posx - 1][coin->posy]->changeFlag();
                        this->gameArray[coin->posx - 1][coin->posy] = this->gameArray[coin->posx - 1][coin->posy] == 0 ? 1 : 0;
                    }
                    if (coin->posy + 1 <= 3) {
                        coinBtn[coin->posx][coin->posy + 1]->changeFlag();
                        this->gameArray[coin->posx][coin->posy + 1] = this->gameArray[coin->posx][coin->posy + 1] == 0 ? 1 : 0;
                    }
                    if (coin->posy - 1 >= 0) {
                        coinBtn[coin->posx][coin->posy - 1]->changeFlag();
                        this->gameArray[coin->posx][coin->posy - 1] = this->gameArray[coin->posx][coin->posy - 1] == 0 ? 1 : 0;
                    }

                    // 解禁其他金币按钮
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    // 判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if (!coinBtn[i][j]->flag) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if (this->isWin) {
                        qDebug() << "Win!";
                        // 屏蔽所有按钮
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        winSound->play();
                        // 胜利图片显示
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel, "geometry");
                        // 时间间隔
                        animation->setDuration(1000);
                        // 设置起始位置
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 150, winLabel->width(), winLabel->height()));
                        // 缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();

                    }

                });

            });

        }
    }

}

void PlayScene::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QPixmap pix;
    // background
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // icon
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}
