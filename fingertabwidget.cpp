#include "fingertabwidget.h"

FingerTabWidget::FingerTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabBar(new FingerTabBarWidget(this));
    this->setTabPosition(QTabWidget::West);
}
