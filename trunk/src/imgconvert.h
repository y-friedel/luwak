#ifndef IMGCONVERT_H
#define IMGCONVERT_H

#include <QImage>
#include <cv.h>
#include <highgui.h>


class ImgConvert
{
public:
    ImgConvert();
    static QImage* toQImage(const IplImage *_i);
    static IplImage* toIplImage(const QImage& _q);
};

#endif // IMGCONVERT_H
