#ifndef WQGRAPHICSSCENE_H
#define WQGRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
//#include <QImage>

class WQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit WQGraphicsScene(QObject *parent = 0);
    WQGraphicsScene(QObject *parent, QImage* img);

protected:
void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );
QImage * img;

public slots:
void rightMouseReleaseEvent(double, double);
void save();
void full_view();
    
};

#endif // WQGRAPHICSSCENE_H
