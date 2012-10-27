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
    void set_white_board();
    
private:
    Ui::MainWindow *ui;
    std::vector<QImage> v_imgs;
    bool is_white_board;
};

#endif // MAINWINDOW_H
