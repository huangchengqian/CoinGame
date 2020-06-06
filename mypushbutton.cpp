#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalIMG, QString pressIMG) {
    this->normalIMGPath = normalIMG;
    this->pressIMGPath = pressIMG;

    QPixmap pix;
    bool ret = pix.load(normalIMG);
    if (!ret) {
        qDebug() << "图片加载失败";
        return;
    }
    // 设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    this->setIcon(pix);
    // 设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));


}
void MyPushButton::zoom1() {

    // 创建动画特效
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    // 设置动画时间间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 结束位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 执行动画
    animation->start();
}
void MyPushButton::zoom2() {
    // 创建动画特效
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    // 设置动画时间间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 结束位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 执行动画
}
void MyPushButton::mousePressEvent(QMouseEvent * e) {
    if (this->pressIMGPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->pressIMGPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        // 设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        // 设置图标
        this->setIcon(pix);
        // 设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    // 让父类执行其他操作
    return QPushButton::mousePressEvent(e);

}
void MyPushButton::mouseReleaseEvent(QMouseEvent * e) {

    if (this->pressIMGPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->normalIMGPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        // 设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        // 设置图标
        this->setIcon(pix);
        // 设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    // 让父类执行其他操作
    return QPushButton::mouseReleaseEvent(e);

}
