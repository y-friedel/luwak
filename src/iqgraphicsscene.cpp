#include "iqgraphicsscene.h"
#include <iostream>

void IQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){
    double x = mouseEvent->scenePos().x();
    double y = mouseEvent->scenePos().y();
    emit mouseReleaseEvent(x,y);
}


void IQGraphicsScene::mouseReleaseEvent(double x, double y)
{
    if(v_pixels.size()==0)
    {
        v_pixels.push_back((int)x);
        v_pixels.push_back((int)y);
    }else{
        this->addLine(x, y, v_pixels[v_pixels.size()-2], v_pixels[v_pixels.size()-1]);
        v_pixels.push_back((int)x);
        v_pixels.push_back((int)y);
    }
}
