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
    void leftMouseReleaseEvent(double, double);
    void rightMouseReleaseEvent(double, double);
    void save();
    void load();

signals:
    void s_fourier();
    void s_update_pixels(const std::vector<double>&);

private:
    std::vector<double> v_pixels;
};

#endif // IQGRAPHICSSCENE_H
