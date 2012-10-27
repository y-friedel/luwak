#ifndef IQGRAPHICSSCENE_H
#define IQGRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsScene>
#include <vector>

class IQGraphicsScene : public QGraphicsScene
{
        Q_OBJECT
protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );

public slots:
    void mouseReleaseEvent(double, double);

private:
    std::vector<int> v_pixels;
};

#endif // IQGRAPHICSSCENE_H
