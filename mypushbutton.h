#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyPushButton(QWidget *parent = nullptr);
    /**
     * @brief MyPushButton
     * @param normalIMG 正常显示图片路径
     * @param pressIMG  按下后显示图片路径
     */
    MyPushButton(QString normalIMG, QString pressIMG = "");

    QString normalIMGPath;
    QString pressIMGPath;

    // 弹跳特效
    void zoom1();
    void zoom2();

    // 重写按钮按下施放事件
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

signals:

};

#endif // MYPUSHBUTTON_H
