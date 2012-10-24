#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>


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
    
private:
    Ui::MainWindow *ui;
    std::vector<QImage> v_imgs;
};

#endif // MAINWINDOW_H
