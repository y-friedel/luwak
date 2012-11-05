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

WQGraphicsScene::WQGraphicsScene(QObject *parent, QImage* _img) :
    QGraphicsScene(parent)
{
    img = _img;
}

void WQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){

    if(mouseEvent->button()==Qt::RightButton)
    {
        emit rightMouseReleaseEvent(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
    }
}


void WQGraphicsScene::rightMouseReleaseEvent(double x, double y)
{
    std::cout << "right click" << std::endl;
    QMenu * menu = new QMenu("m_right_click");

    QAction *a_save = new QAction("&Save image...", this);
    connect(a_save, SIGNAL(triggered()), this, SLOT(save()));
    menu->addAction(a_save);

    QAction *a_full_view = new QAction("&Full Image...", this);
    connect(a_full_view, SIGNAL(triggered()), this, SLOT(full_view()));
    menu->addAction(a_full_view);

    // add menu in the WQGraphicsScene
    menu->move(x, y);
    menu->show();
}

void WQGraphicsScene::save()
{
    std::cout <<"Save..." << std::endl;
    QString filename;
    filename = QFileDialog::getSaveFileName(0, tr("Save Image"), "./data/output.png", tr("Images (*.png *.xpm *.jpg)"));

    img->save(filename);

}

void WQGraphicsScene::full_view()
{
    std::cout << "Full View" << std::endl;
    FullImg* fi = new FullImg(img);
    fi->show();
}
