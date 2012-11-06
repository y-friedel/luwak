#include "wqgraphicsscene.h"
#include <iostream>
#include <QMenu>
#include <QPainter>
#include <QFileDialog>
#include <QtGui/QApplication>
#include "fullimg.h"

WQGraphicsScene::WQGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{

}

void WQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){

    if(mouseEvent->button()==Qt::RightButton)
    {
        std::cout << "right click" << std::endl;
        QMenu * menu = new QMenu("m_right_click");

        QAction *a_save = new QAction("&Save image...", this);
        connect(a_save, SIGNAL(triggered()), this, SIGNAL(s_save()));
        menu->addAction(a_save);

        QAction *a_full_img = new QAction("&Full Image...", this);
        connect(a_full_img, SIGNAL(triggered()), this, SIGNAL(s_full_img()));
        menu->addAction(a_full_img);

        menu->move(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
        menu->show();
    }
}
