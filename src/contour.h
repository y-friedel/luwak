#ifndef CONTOUR_H
#define CONTOUR_H

#include <vector>
#include <string>
#include <iostream>
#include <complex>

class Contour
{

public:
    Contour();
    Contour(const std::vector<double> & v_pts);
    Contour(const std::vector<std::complex<double> >& _v_complex);
    Contour(const std::string filename);
    
    void ajout_point(const std::complex<double>& c);
    void ajout_point(double reel, double imag);

    
    const std::complex<double>& getValeur(int i);
    int getTaille() const;

    void load(const std::string filename);
    void save(const std::string filename);
    static void save(const std::vector<double>& vec_pts, const std::string filename);
    static void load(const std::string filename, std::vector<double>& vec);
    
protected:
	std::vector<std::complex<double> > v_complex;
};

#endif // CONTOUR_H
