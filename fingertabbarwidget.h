#ifndef FINGERTABBARWIDGET_H
#define FINGERTABBARWIDGET_H

#include <QTabBar>
#include <QtGui>
#include <QtCore>
#include <QStylePainter>
#include <QStyleOptionTab>

class FingerTabBarWidget : public QTabBar
{
    Q_OBJECT
public:
    explicit FingerTabBarWidget(QWidget *parent = 0, int width = 120, int height = 25);
    void paintEvent(QPaintEvent *);
    QSize tabSizeHint(int index);

private:
    QSize tabSize;

signals:

public slots:

};

#endif // FINGERTABBARWIDGET_H
