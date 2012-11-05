#include "fullimg.h"
#include "ui_fullimg.h"
#include <QGraphicsScene>

FullImg::FullImg(QImage* img, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullImg)
{
    ui->setupUi(this);


    //OK Button
    connect(ui->b_ok, SIGNAL(clicked()), this, SLOT(close()));

    //Load Image
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->resize(img->width(), img->height());
    //ui->graphicsView->setMaximumSize(img->width(), img->height());

    scene->addPixmap(QPixmap::fromImage(*img).scaled(
                         QSize(ui->graphicsView->width(),
                               ui->graphicsView->height()),
                         Qt::KeepAspectRatio));
    ui->graphicsView->setScene(scene);
}

FullImg::~FullImg()
{
    delete ui;
}
