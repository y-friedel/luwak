#include "iqgraphicsscene.h"
#include <iostream>

void IQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){
    double x = mouseEvent->scenePos().x();
    double y = mouseEvent->scenePos().y();
    emit mouseReleaseEvent(x,y);
}


void IQGraphicsScene::mouseReleaseEvent(double x, double y)
{
    //If the vector is empty, we only add the vertice
    if(v_pixels.size()==0)
    {
        v_pixels.push_back((int)x);
        v_pixels.push_back((int)y);

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
    	
    	v_pixels.push_back((int)x);
        v_pixels.push_back((int)y);
    }
    update(0,0,1000,1000);
}
