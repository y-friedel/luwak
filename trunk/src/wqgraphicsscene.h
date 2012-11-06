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

protected:
void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );

signals:
void s_save();
void s_full_img();
    
};

#endif // WQGRAPHICSSCENE_H
