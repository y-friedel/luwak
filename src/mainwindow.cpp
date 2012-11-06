#include "mainwindow.h"
#include "iqgraphicsscene.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include "wqgraphicsscene.h"
#include "fullimg.h"

#include "contour.h"
#include "fourier.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //My Pixmap vector
    v_imgs.resize(4);
    v_outline = std::vector<double>();


    is_m_outline = false;

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

    //--white board menu
    QAction *a_mode_outline = new QAction("Outline mode", this);
    connect(a_mode_outline, SIGNAL(triggered()), this, SLOT(mode_outline()));

    //Quit menu
    QAction *a_quit = new QAction("&Quit", this);
    connect(a_quit , SIGNAL(triggered()), qApp, SLOT(quit()));

    m_file->addAction(a_open);
    m_file->addMenu(m_save);
    m_file->addSeparator();
    m_file->addAction(a_mode_outline);
    m_file->addSeparator();
    m_file->addAction(a_quit);

    m_save->addAction(a_save_NW);
    m_save->addAction(a_save_NE);
    m_save->addAction(a_save_SW);
    m_save->addAction(a_save_SE);

    //Tools menu
    m_file = menuBar()->addMenu(tr("&Tools"));

    //To Grey Menu
    QAction *a_toGray = new QAction("Convert to &Gray", this);
    connect(a_toGray, SIGNAL(triggered()), this, SLOT(toGray()));
    m_file->addAction(a_toGray);

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
    tr("Open Image"), "../data", tr("Image Files (*.png *.jpg *.bmp *.pgm)"));
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
    QImage* q_img = new QImage();
    q_img->load(filename);
    switch(pos)
    {
    case(NW):
        v_imgs[0] = q_img;
        break;

    case(NE):
        v_imgs[1] = q_img;
        break;

    case(SW):
        v_imgs[2] = q_img;
        break;

    case(SE):
        v_imgs[3] = q_img;
        break;
    }
    refresh();
}

void MainWindow::save_img_NW()
{
        std::cout <<"Save NW..." << std::endl;
        QString filename;
        filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"), "./data/NW.png", tr("Images (*.png *.xpm *.jpg)"));
        v_imgs[NW]->save(filename);
}

void MainWindow::save_img_NE()
{
    std::cout <<"Save NE..." << std::endl;
    QString filename;
    filename = QFileDialog::getSaveFileName(this,
    tr("Save Image"), "./data/NE.png", tr("Images (*.png *.xpm *.jpg)"));
    v_imgs[NE]->save(filename);

}

void MainWindow::save_img_SW()
{
    std::cout <<"Save SW..." << std::endl;
    QString filename;
    filename = QFileDialog::getSaveFileName(this,
    tr("Save Image"), "./data/SW.png", tr("Images (*.png *.xpm *.jpg)"));
    v_imgs[SW]->save(filename);

}

void MainWindow::save_img_SE()
{
    std::cout <<"Save SE..." << std::endl;
    QString filename;
    filename = QFileDialog::getSaveFileName(this,
    tr("Save Image"), "./data/SE.png", tr("Images (*.png *.xpm *.jpg)"));
    v_imgs[SE]->save(filename);

}

void MainWindow::toNW()
{
    std::cout <<"To NW..." << std::endl;
    int i = ui->cb_toNW->currentIndex()+1;
    v_imgs[0] = v_imgs[i];

    refresh();
}

void MainWindow::refresh()
{

    if(is_m_outline)
    {
        IQGraphicsScene* sceneNW ;
        sceneNW = new IQGraphicsScene();
        //Connect with scene menu
        connect(sceneNW, SIGNAL(s_update_pixels(const std::vector<double>&)), this, SLOT(update_pixels(const std::vector<double>&)));
    }
    else if(v_imgs[0] != NULL)
    {
        WQGraphicsScene* sceneNW ;
        sceneNW = new WQGraphicsScene();
        sceneNW->addPixmap(QPixmap::fromImage(*v_imgs[0]).scaled(
                     QSize(ui->graphicsViewNW->width(),
                           ui->graphicsViewNW->height()),
                     Qt::KeepAspectRatio));
        ui->graphicsViewNW->setScene(sceneNW);

        //Connect with scene menu
        connect(sceneNW, SIGNAL(s_save()), this, SLOT(save_img_NW()));
        connect(sceneNW, SIGNAL(s_full_img()), this, SLOT(full_img_NW()));
    }

    if(v_imgs[1] != NULL)
    {
        QGraphicsScene* sceneNE = new WQGraphicsScene();
        sceneNE->addPixmap(QPixmap::fromImage(*v_imgs[1]).scaled(
                             QSize(ui->graphicsViewNE->width(),
                                   ui->graphicsViewNE->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewNE->setScene(sceneNE);

        //Connect with scene menu
        connect(sceneNE, SIGNAL(s_save()), this, SLOT(save_img_NE()));
        connect(sceneNE, SIGNAL(s_full_img()), this, SLOT(full_img_NE()));
    }

    if(v_imgs[2] != NULL)
    {
        QGraphicsScene* sceneSW = new WQGraphicsScene();
        sceneSW->addPixmap(QPixmap::fromImage(*v_imgs[2]).scaled(
                             QSize(ui->graphicsViewSW->width(),
                                   ui->graphicsViewSW->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewSW->setScene(sceneSW);

        //Connect with scene menu
        connect(sceneSW, SIGNAL(s_save()), this, SLOT(save_img_SW()));
        connect(sceneSW, SIGNAL(s_full_img()), this, SLOT(full_img_SW()));
    }

    if(v_imgs[3] != NULL)
    {
        QGraphicsScene* sceneSE = new WQGraphicsScene();
        sceneSE->addPixmap(QPixmap::fromImage(*v_imgs[3]).scaled(
                             QSize(ui->graphicsViewSE->width(),
                                   ui->graphicsViewSE->height()),
                             Qt::KeepAspectRatio));
        ui->graphicsViewSE->setScene(sceneSE);

        //Connect with scene menu
        connect(sceneSE, SIGNAL(s_save()), this, SLOT(save_img_SE()));
        connect(sceneSE, SIGNAL(s_full_img()), this, SLOT(full_img_SE()));
    }
}

void MainWindow::toGray()
{
    IplImage *input = ImgConvert::toIplImage(*v_imgs[0]);
    IplImage *output = cvCreateImage( cvSize( input->width, input->height ), IPL_DEPTH_8U, 1);
    cvCvtColor( input, output, CV_RGB2GRAY );
    v_imgs[NE] = ImgConvert::toQImage(output);
    ui->l_NE->setText("To Grey");
    refresh();

    //free(input);
    //free(output);
}

void MainWindow::fourier()
{
    std::cout << "Fourier" << std::endl;

    Contour c = Contour(v_outline);
    Fourier fourier = Fourier(c);
    std::vector<double> f_pts = std::vector<double>();
    fourier.to_double(f_pts);

    //Affichage Fourier
    QImage* im_freq = new QImage(ui->graphicsViewNE->width(), ui->graphicsViewNE->height(), QImage::Format_Mono);
    im_freq->fill(Qt::darkBlue);
    for(unsigned int i=0; i<f_pts.size()/2; i++)
    {
        im_freq->setPixel(
                    QPoint(
                        (int)f_pts[2*i] /*+ ui->graphicsViewNW->width()/2*/,
                        (int)f_pts[2*i+1] /*+ ui->graphicsViewNW->height()/2*/),
                    1);
    }

    v_imgs[NE] = im_freq;

    Contour c_rep;
    fourier.invertFourier(c_rep);

    //Affichage inverse fourier

    QImage* im_ret = new QImage(ui->graphicsViewSW->width(), ui->graphicsViewSW->height(), QImage::Format_Mono);
    im_ret->fill(Qt::darkBlue);
    for(unsigned int i=0; i<c_rep.getTaille(); i++)
    {
        im_ret->setPixel(
                    QPoint(
                        (int)real(c_rep.getValeur(i)) /*+ ui->graphicsViewNW->width()/2*/,
                        (int)imag(c_rep.getValeur(i)) /*+ ui->graphicsViewNW->height()/2*/),
                    1);
    }
    v_imgs[SW] = im_ret;

        refresh();

}

void MainWindow::mode_outline()
{
    IQGraphicsScene* sceneNW;
    sceneNW = new IQGraphicsScene();
    QPixmap white = QPixmap(ui->graphicsViewNW->width(), ui->graphicsViewNW->height());
    QPainter painter(&white);
    painter.setPen(QColor(240,255,240));
    for(int i = 0; i<white.width(); i++)
    {
        for(int j=0; j<white.height(); j++)
        {
            painter.drawPoint(i,j);
        }
    }
    sceneNW->addPixmap(white);
    v_imgs[0] = new QImage(white.toImage());
    ui->graphicsViewNW->setScene(sceneNW);
    is_m_outline = true;
    ui->l_NW->setText("White Board");
    connect(sceneNW, SIGNAL(s_update_pixels(const std::vector<double>&)), this, SLOT(update_pixels(const std::vector<double>&)));
    connect(sceneNW, SIGNAL(s_fourier()), this, SLOT(fourier()));
}

void MainWindow::update_pixels(const std::vector<double>& v_pix)
{
    v_outline.resize(v_pix.size());
    copy(v_pix.begin(), v_pix.end(), v_outline.begin());
}



void MainWindow::full_img(int pos)
{
    std::cout << "Full View" << std::endl;
    FullImg* fi = new FullImg(v_imgs[pos]);
    fi->show();
}

void MainWindow::full_img_NW()
{
    full_img(NW);
}

void MainWindow::full_img_NE()
{
    full_img(NE);
}

void MainWindow::full_img_SW()
{
    full_img(SW);
}

void MainWindow::full_img_SE()
{
    full_img(SE);
}
