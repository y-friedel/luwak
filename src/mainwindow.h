#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "imgconvert.h"


enum W_pic
{
    NW,
    NE,
    SW,
    SE,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void browse_img();
    void load_img(QString filename, W_pic pos);

    //Save
    void save_img_NW();
    void save_img_NE();
    void save_img_SW();
    void save_img_SE();

    //To main
    void toNW();
    void refresh();

    //Resize
    void resizeEvent(QResizeEvent *);

    void toGray();
    void fourier();

    void mode_outline();
    void update_pixels(const std::vector<double>&);

    void full_img(int pos);
    void full_img_NW();
    void full_img_NE();
    void full_img_SW();
    void full_img_SE();
    
private:
    Ui::MainWindow *ui;
    std::vector<QImage*> v_imgs;
    std::vector<double> v_outline;
    bool is_m_outline;
};

#endif // MAINWINDOW_H
