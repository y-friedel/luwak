#include "imgconvert.h"

ImgConvert::ImgConvert()
{

}

QImage* ImgConvert::toQImage(const IplImage *_i)
{
    QImage *outputImg = new QImage(_i->width, _i->height, QImage::Format_RGB32);

    CvScalar v_rgb;
    v_rgb.val[0] = 0;
    v_rgb.val[1] = 0;
    v_rgb.val[2] = 0;

    for(int j = 0; j < _i->width; j++)
    {
        for(int i = 0; i < _i->height; i++)
        {
            v_rgb = cvGet2D(_i,i,j);
            if(_i->nChannels == 1)
                outputImg->setPixel(j,i, qRgb(v_rgb.val[0],v_rgb.val[0],v_rgb.val[0]));
            else
                outputImg->setPixel(j,i, qRgb(v_rgb.val[0],v_rgb.val[1],v_rgb.val[2]));
        }
    }

    return outputImg;
}

IplImage* ImgConvert::toIplImage(const QImage& _q)
{
    IplImage* output = cvCreateImage(cvSize(_q.width(),_q.height()),IPL_DEPTH_8U,3);

    CvScalar v_rgb;
    v_rgb.val[0] = 0;

    for(int i = 0; i < _q.width(); i++)
    {
        for(int j = 0; j < _q.height(); j++)
        {
            QRgb p(_q.pixel(i,j));
            v_rgb.val[0] = qRed(p)-1;
            v_rgb.val[1] = qGreen(p)-1;
            v_rgb.val[2] = qBlue(p)-1;
            cvSet2D(output,j,i,v_rgb);
        }
    }

    return output;
}
