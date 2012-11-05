#ifndef FULLIMG_H
#define FULLIMG_H

#include <QDialog>

namespace Ui {
class FullImg;
}

class FullImg : public QDialog
{
    Q_OBJECT
    
public:
    explicit FullImg(QImage* img, QWidget *parent = 0);
    ~FullImg();
    
private:
    Ui::FullImg *ui;
};

#endif // FULLIMG_H
