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
    v_pixmaps.resize(4, NULL);

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
    QAction *a_save_NO = new QAction("NO...", this);
    //connect(a_open, SIGNAL(triggered()), this, SLOT(save_img(NO)));

    QAction *a_save_NE = new QAction("NE...", this);
    //connect(a_open, SIGNAL(triggered()), this, SLOT(save_img(NE)));

    QAction *a_save_SO = new QAction("SO...", this);
    //connect(a_open, SIGNAL(triggered()), this, SLOT(save_img(SO)));

    QAction *a_save_SE = new QAction("NO...", this);
    //connect(a_open, SIGNAL(triggered()), this, SLOT(save_img(SE)));

    //Quit Button
    QAction *a_quit = new QAction("&Quit", this);
    connect(a_quit , SIGNAL(triggered()), qApp, SLOT(quit()));

    m_file->addAction(a_open);
    m_file->addMenu(m_save);
    m_file->addSeparator();
    m_file->addAction(a_quit);

    m_save->addAction(a_save_NO);
    m_save->addAction(a_save_NE);
    m_save->addAction(a_save_SO);
    m_save->addAction(a_save_SE);

    //Title name
    this->setWindowTitle(QString("Luwak"));

    //Browse button
    connect(ui->b_browse_img, SIGNAL(clicked()), this, SLOT(browse_img()));
//    //Resize Event
//    this->connect(ui->centralWidget, ui->centralWidget->resizeEvent(), SLOT(Resize()));
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

    load_img(filename, NO);
}



void MainWindow::load_img(QString filename, W_pic pos)
{
    QImage q_img;
    q_img.load(filename);
    QGraphicsScene* scene = new QGraphicsScene();
    switch(pos)
    {
    case(NO):
        v_pixmaps[0] = QPixmap::fromImage(q_img);

        scene->addPixmap(v_pixmaps[0].scaled(QSize(ui->graphicsViewNO->width(),ui->graphicsViewNO->height()), Qt::KeepAspectRatio));
        ui->graphicsViewNO->setScene(scene);
        break;

    case(NE):
        v_pixmaps[1] = QPixmap::fromImage(q_img);

        scene->addPixmap(v_pixmaps[1].scaled(QSize(ui->graphicsViewNE->width(),ui->graphicsViewNE->height()), Qt::KeepAspectRatio));
        ui->graphicsViewNE->setScene(scene);
        break;

    case(SO):
        v_pixmaps[2] = QPixmap::fromImage(q_img);

        scene->addPixmap(v_pixmaps[2].scaled(QSize(ui->graphicsViewSO->width(),ui->graphicsViewSO->height()), Qt::KeepAspectRatio));
        ui->graphicsViewSO->setScene(scene);
        break;

    case(SE):
        v_pixmaps[3] = QPixmap::fromImage(q_img);

        scene->addPixmap(v_pixmaps[3].scaled(QSize(ui->graphicsViewSE->width(),ui->graphicsViewSE->height()), Qt::KeepAspectRatio));
        ui->graphicsViewSE->setScene(scene);
        break;

        default:
            std::cout << "nothing to do here" << std::endl;
            break;
    }

}

void MainWindow::load_img(QPixmap pixmap, W_pic pos)
{
    QGraphicsScene* scene = new QGraphicsScene();
    switch(pos)
    {
    case(NO):
        v_pixmaps[0] = pixmap;

        scene->addPixmap(v_pixmaps[0].scaled(QSize(ui->graphicsViewNO->width(),ui->graphicsViewNO->height()), Qt::KeepAspectRatio));
        ui->graphicsViewNO->setScene(scene);
        break;

    case(NE):
        v_pixmaps[1] = pixmap;

        scene->addPixmap(v_pixmaps[1].scaled(QSize(ui->graphicsViewNE->width(),ui->graphicsViewNE->height()), Qt::KeepAspectRatio));
        ui->graphicsViewNE->setScene(scene);
        break;

    case(SO):
        v_pixmaps[2] = pixmap;

        scene->addPixmap(v_pixmaps[2].scaled(QSize(ui->graphicsViewSO->width(),ui->graphicsViewSO->height()), Qt::KeepAspectRatio));
        ui->graphicsViewSO->setScene(scene);
        break;

    case(SE):
        v_pixmaps[3] = pixmap;

        scene->addPixmap(v_pixmaps[3].scaled(QSize(ui->graphicsViewSE->width(),ui->graphicsViewSE->height()), Qt::KeepAspectRatio));
        ui->graphicsViewSE->setScene(scene);
        break;

        default:
            std::cout << "nothing to do here" << std::endl;
            break;
    }

}

void MainWindow::save_img(W_pic pos)
{


}
