#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>


enum W_pic
{
    NO,
    NE,
    SO,
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
    void load_img(QPixmap pixmap, W_pic pos);
    void save_img(W_pic pos);
    
private:
    Ui::MainWindow *ui;
    std::vector<QPixmap> v_pixmaps;
};

#endif // MAINWINDOW_H
