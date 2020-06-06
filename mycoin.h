#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);

    /**
     * @brief MyCoin   构造函数
     * @param btnIMG   初始金币还是银币
     */
    MyCoin(QString btnIMG);

    // 金币属性
    int posx;
    int posy;
    bool flag = false;

    // 金币变化
    void changeFlag();
    QTimer * timer1;
    QTimer * timer2;

    int min = 1;
    int max = 8;

    bool isAnimation = false;

    // 重写按下
    void mousePressEvent(QMouseEvent * e);

    // 胜利标志
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
