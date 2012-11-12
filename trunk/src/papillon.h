#ifndef FPAPILLON_H
#define FPAPILLON_H

#include <vector>
#include <string>
#include <iostream>
#include <complex>
#include "contour.h"

class FPapillon
{

public:

    FPapillon();
    FPapillon(const std::vector< std::complex<double> >& image, 
    						unsigned int _width, 
    						unsigned int _height);

    void setFPapillon(const std::vector< std::complex<double> >& image, 
    						unsigned int width, 
    						unsigned int height);
    //void invertFourier(Contour& c);

    void setFPapillon1D(unsigned int num, bool colonne = false);
    const std::complex<double>& getPixel(int x, int y);
    int getTaille() const;

    void to_double_amplitude (std::vector<double>& v_pixels) const;
    void to_double_phase (std::vector<double>& v_pixels) const;

    unsigned int height() const;
	unsigned int width() const;
	unsigned int getNormalizedSize() const;

	void setPixel(const std::complex<double>& value, int x, int y);

public:
	std::vector< std::complex<double> > v_fpapillon;
	unsigned int _height;
	unsigned int _width;
	unsigned int _n_size;
};

#endif // FPAPILLON_H
