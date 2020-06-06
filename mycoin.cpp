#include "mycoin.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnIMG) {
    QPixmap pix;
    bool l = pix.load(btnIMG);
    if(!l) {
        qDebug() << "金币图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    // 监听翻面信号
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        // 翻完了
        if (this->min > this->max) {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        // 翻完了
        if (this->min > this->max) {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });

}

void MyCoin::mousePressEvent(QMouseEvent * e) {
    if (this->isAnimation || this->isWin) {
        return;
    }
    else {
        QPushButton::mousePressEvent(e);
    }
}

void MyCoin::changeFlag() {
    if (this->flag) {
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
