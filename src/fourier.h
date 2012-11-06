#ifndef FOURIER_H
#define FOURIER_H

#include <vector>
#include <string>
#include <iostream>
#include <complex>
#include "contour.h"

class Fourier
{

public:
    Fourier();
    Fourier(const Contour& c);

    void setFourier(const Contour& c);
    void invertFourier(Contour& c);

    const std::complex<double>& getValeur(int i);
    int getTaille() const;

    void to_double (std::vector<double>& v_pixels) const;
    
public:
	std::vector<std::complex<double> > v_complex_fourier;
};

#endif // FOURIER_H
