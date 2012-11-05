#ifndef IQGRAPHICSSCENE_H
#define IQGRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include "wqgraphicsscene.h"
#include <vector>

class IQGraphicsScene : public WQGraphicsScene
{
        Q_OBJECT
protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );

public slots:
    void mouseReleaseEvent(double, double);
    void save();

private:
    std::vector<int> v_pixels;
};

#endif // IQGRAPHICSSCENE_H
