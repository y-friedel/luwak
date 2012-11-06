#include "iqgraphicsscene.h"
#include "contour.h" 
#include <iostream>
#include <QMenu>
#include <QFileDialog>

void IQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){
    if(mouseEvent->button()==Qt::LeftButton)
    {
        double x = mouseEvent->scenePos().x();
        double y = mouseEvent->scenePos().y();
        emit leftMouseReleaseEvent(x,y);
    }
    else if(mouseEvent->button()==Qt::RightButton)
    {
        emit rightMouseReleaseEvent(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
    }

        /*if(mouseEvent->button()==Qt::RightButton)
    {
        std::cout << "right click" << std::endl;
        QMenu * menu = new QMenu("Im_menu");

        QAction *a_open = new QAction("&Save image...", this);
        connect(a_open, SIGNAL(triggered()), this, SLOT(save()));

        menu->addAction(a_open);

        // ajout des actions
        menu->move(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
        menu->show();
    }*/
}


void IQGraphicsScene::leftMouseReleaseEvent(double x, double y)
{
    //If the vector is empty, we only add the vertice
    if(v_pixels.size()==0)
    {
        v_pixels.push_back((double)x);
        v_pixels.push_back((double)y);

        for(int i=0; i < items().size(); i++)
        {
            removeItem(items()[i]);
        }

        this->addLine(x-.1, y-.1, x, y);
    }else{
        for(int i=0; i < items().size(); i++)
    	{
    		removeItem(items()[i]);
    	}

    	for(unsigned int i=0; i<v_pixels.size()/2 - 1; i++)
    	{
    		addLine(v_pixels[2*i], v_pixels[2*i+1], v_pixels[2*i+2], v_pixels[2*i+3]);
    	}
    	addLine(x, y, v_pixels[v_pixels.size()-2], v_pixels[v_pixels.size()-1]);
        addLine(x, y, v_pixels[0], v_pixels[1]);
    	
    	v_pixels.push_back((double)x);
        v_pixels.push_back((double)y);
    }
    update(0,0,1000,1000);
}

void IQGraphicsScene::rightMouseReleaseEvent(double x, double y)
{
    std::cout << "right click" << std::endl;
    QMenu * menu = new QMenu("Im_menu");

    QAction *a_save = new QAction("Save outline...", this);
    connect(a_save, SIGNAL(triggered()), this, SLOT(save()));

    QAction *a_load = new QAction("Open outline...", this);
    connect(a_load, SIGNAL(triggered()), this, SLOT(load()));

    menu->addAction(a_save);
    menu->addAction(a_load);

    // ajout des actions
    menu->move(x, y);
    menu->show();
}

void IQGraphicsScene::save()
{
    std::cout <<"Save..." << std::endl;
    QString filename;
    filename = QFileDialog::getSaveFileName(0, tr("Save Image"), "./data/output.txt", tr("Images (*.txt)"));

    Contour::save(v_pixels, filename.toStdString());

}

void IQGraphicsScene::load()
{
    std::cout <<"Browse..." << std::endl;
    QString filename;
    filename = QFileDialog::getOpenFileName(0,
    tr("Open outline"), "../data", tr("Image Files (*.txt)"));
    Contour::load(filename.toStdString(), v_pixels);

    for(int i=0; i < items().size(); i++)
    {
        removeItem(items()[i]);
    }

    for(unsigned int i=0; i<v_pixels.size()/2 - 1; i++)
    {
        addLine(v_pixels[2*i], v_pixels[2*i+1], v_pixels[2*i+2], v_pixels[2*i+3]);
    }

    addLine(v_pixels[v_pixels.size()-2], v_pixels[v_pixels.size()-1], v_pixels[0], v_pixels[1]);

}
