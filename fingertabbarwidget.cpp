#include "fingertabbarwidget.h"

FingerTabBarWidget::FingerTabBarWidget(QWidget *parent, int width, int height) :
    QTabBar(parent)
{
    this->tabSize = QSize(width, height);
    this->setStyleSheet("QTabBar::tab{height:"+QString::number(height)+"px; width:"+QString::number(width)+"px;}");
}

void FingerTabBarWidget::paintEvent(QPaintEvent *){
    QStylePainter *painter = new QStylePainter(this);
    QStyleOptionTab *option = new QStyleOptionTab();

    int c = count();
    for(int index = 0; index < c; index++){
        this->initStyleOption(option, index);
        QRect tabRect = this->tabRect(index);
        tabRect.moveLeft(10);
        painter->drawControl(QStyle::CE_TabBarTabShape, *option);
        painter->drawText(tabRect, Qt::AlignVCenter | Qt::TextDontClip, this->tabText(index));
        //TODO Pass multiple flags
        //painter->drawText(tabRect, Qt::AlignVCenter,  Qt::TextDontClip, this->tabText(index));
    }
    painter->end();
    /*
    foreach(int index, count()) {
        this->initStyleOption(option, index);
        QRect tabRect = this->tabRect(index);
        tabRect.moveLeft(10);
        //painter.drawControl(QStyle::CE_TabBarTabShape, option);
        //painter.drawText(tabRect, Qt::AlignVCenter, Qt::TextDontClip, this->tabText(index));
    }
    */
}

QSize FingerTabBarWidget::tabSizeHint(int index){
    return this->tabSize;
}
