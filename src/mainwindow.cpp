#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //My Pixmap vector
    v_imgs.resize(4);

    /* ==MENU== */
    //FileMenu
    QMenu* m_file;
    m_file = menuBar()->addMenu(tr("&File"));

    //--Open menu
    QAction *a_open = new QAction("&Open...", this);
    connect(a_open, SIGNAL(triggered()), this, SLOT(browse_img()));
    //--Save menu
    QMenu *m_save;
    m_save = m_file->addMenu(tr("&Save"));
    //----4 images
    QAction *a_save_NW = new QAction("NW...", this);
    connect(a_save_NW, SIGNAL(triggered()), this, SLOT(save_img_NW()));

    QAction *a_save_NE = new QAction("NE...", this);
    connect(a_save_NE, SIGNAL(triggered()), this, SLOT(save_img_NE()));

    QAction *a_save_SW = new QAction("SW...", this);
    connect(a_save_SW, SIGNAL(triggered()), this, SLOT(save_img_SW()));

    QAction *a_save_SE = new QAction("SE...", this);
    connect(a_save_SE, SIGNAL(triggered()), this, SLOT(save_img_SE()));

    //Quit menu
    QAction *a_quit = new QAction("&Quit", this);
    connect(a_quit , SIGNAL(triggered()), qApp, SLOT(quit()));

    m_file->addAction(a_open);
    m_file->addMenu(m_save);
    m_file->addSeparator();
    m_file->addAction(a_quit);

    m_save->addAction(a_save_NW);
    m_save->addAction(a_save_NE);
    m_save->addAction(a_save_SW);
    m_save->addAction(a_save_SE);

    //Title name
    this->setWindowTitle(QString("Luwak"));


    //To NW Button
    connect(ui->b_toNW , SIGNAL(clicked()), this, SLOT(toNW()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browse_img()
{
    std::cout <<"Browse..." << std::endl;
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "./data", tr("Image Files (*.png *.jpg *.bmp *.pgm)"));
    std::cout << filename.toStdString() << std::endl;

    load_img(filename, NW);
}

//Resize IN PROGRESSW
void MainWindow::resizeEvent(QResizeEvent *)
{
    refresh();
}


void MainWindow::load_img(QString filename, W_pic pos)
{
    QImage q_img;
    q_img.load(filename);
    QGraphicsScene* scene = new QGraphicsScene();
    switch(pos)
    {
    case(NW):
        v_imgs[0] = q_img;

        scene->addPixmap(QPixmap::fromImage(q_img).scaled(
                             QSize(ui->graphicsViewNW->width(),
                                   ui->graphicsViewNW->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewNW->setScene(scene);
        break;

    case(NE):
        v_imgs[1] = q_img;

        scene->addPixmap(QPixmap::fromImage(q_img).scaled(
                             QSize(ui->graphicsViewNE->width(),
                                   ui->graphicsViewNE->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewNE->setScene(scene);
        break;

    case(SW):
        v_imgs[2] = q_img;

        scene->addPixmap(QPixmap::fromImage(q_img).scaled(
                             QSize(ui->graphicsViewSW->width(),
                                   ui->graphicsViewSW->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewSW->setScene(scene);
        break;

    case(SE):
        v_imgs[3] = q_img;

        scene->addPixmap(QPixmap::fromImage(q_img).scaled(
                             QSize(ui->graphicsViewSE->width(),
                                   ui->graphicsViewSE->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewSE->setScene(scene);
        break;
    }
}

void MainWindow::save_img_NW()
{
        std::cout <<"Save NW..." << std::endl;
        QString filename;
        filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"), "./data/NW.png", tr("Images (*.png *.xpm *.jpg)"));
        v_imgs[NW].save(filename);
}

void MainWindow::save_img_NE()
{


}

void MainWindow::save_img_SW()
{


}

void MainWindow::save_img_SE()
{


}

void MainWindow::toNW()
{
    std::cout <<"To NW..." << std::endl;
    int i = ui->cb_toNW->currentIndex()+1;
    v_imgs[0] = v_imgs[i];

    refresh();
}

//TODO cas particulier pour les Images vides
void MainWindow::refresh()
{
    QGraphicsScene* sceneNW = new QGraphicsScene();
    sceneNW->addPixmap(QPixmap::fromImage(v_imgs[0]).scaled(
                         QSize(ui->graphicsViewNW->width(),
                               ui->graphicsViewNW->height()),
                         Qt::KeepAspectRatio));
    ui->graphicsViewNW->setScene(sceneNW);

    QGraphicsScene* sceneNE = new QGraphicsScene();
    sceneNE->addPixmap(QPixmap::fromImage(v_imgs[1]).scaled(
                         QSize(ui->graphicsViewNE->width(),
                               ui->graphicsViewNE->height()),
                         Qt::KeepAspectRatio));
    ui->graphicsViewNE->setScene(sceneNE);

    QGraphicsScene* sceneSW = new QGraphicsScene();
    sceneSW->addPixmap(QPixmap::fromImage(v_imgs[2]).scaled(
                         QSize(ui->graphicsViewSW->width(),
                               ui->graphicsViewSW->height()),
                         Qt::KeepAspectRatio));
    ui->graphicsViewSW->setScene(sceneSW);

    QGraphicsScene* sceneSE = new QGraphicsScene();
    sceneSE->addPixmap(QPixmap::fromImage(v_imgs[3]).scaled(
                         QSize(ui->graphicsViewSE->width(),
                               ui->graphicsViewSE->height()),
                         Qt::KeepAspectRatio));
    ui->graphicsViewSE->setScene(sceneSE);
}
